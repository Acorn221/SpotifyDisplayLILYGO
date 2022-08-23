/*******************************************************************
This code is partically based off of the ArduinoSpotify example
 *******************************************************************/

// ----------------------------
// Internal Helper Functions
// ----------------------------
#include "HelperFunctions.h"
#include "Config.h"

#include <Fonts/FreeMonoBold9pt7b.h>
#include <SpotifyArduinoCert.h>

void printCurrentlyPlayingToDisplay(CurrentlyPlaying currentlyPlaying);
void handleDeepSleep(CurrentlyPlaying currentlyPlaying);
void handleCurrentlyPlayingCallback(CurrentlyPlaying currentlyPlaying);

#define TIME_TO_SLEEP 300 // Time between checking if songs are playing (in deepsleep)

WiFiClientSecure client;

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/17, /*RST=*/16); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/16, /*BUSY=*/4);        // arbitrary selection of (16), 4

// used to decide whether or not to update the display
RTC_DATA_ATTR String oldSongURI = "";
RTC_DATA_ATTR bool wasPlaying = false;
RTC_DATA_ATTR bool hasResetDisplay = false;
RTC_DATA_ATTR BearerToken bearerToken = {"", 0, 0};
RTC_DATA_ATTR unsigned long int lastSleepDuration = 0;

SpotifyArduino spotify(client, CLIENT_ID, CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN, false);

void setup()
{

  // Initialising the display
  display.init(115200);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextSize(1);
  display.setTextWrap(true);

  if (DEBUG)
    Serial.begin(115200);

  // Connecting to the wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  // Wait for connection
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    lastSleepDuration = millis();
    ESP.restart();
  }

  if (DEBUG)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // Setting the Spotify SSL key
  client.setCACert(spotify_server_cert);

  // If you want to enable some extra debugging
  // uncomment the "#define SPOTIFY_DEBUG" in ArduinoSpotify.h

  if (DEBUG)
    Serial.println("Checking Access Tokens");

  if (bearerToken.timeTokenRefreshed - lastSleepDuration < 1)
  {
    if (!spotify.checkAndRefreshAccessToken())
    {
      if (DEBUG)
        Serial.println("Failed to get access tokens");
      ESP.restart();
    }
    else
    {
      bearerToken = spotify.getAccessToken();

      if (DEBUG)
        Serial.println("Got access tokens");
    }
  }
  else
  {
    bearerToken.timeTokenRefreshed -= lastSleepDuration;
    if (DEBUG)
      Serial.printf("Access tokens are still valid, they have %dm left, last sleep duration was %dm\n", (int)(bearerToken.timeTokenRefreshed / 1000 / 60), (int)(lastSleepDuration / 1000 / 60));
  }

  if (DEBUG)
    Serial.println("getting currently playing song:");

  // Market can be excluded if you want e.g. spotify.getCurrentlyPlaying()
  int status = spotify.getCurrentlyPlaying(handleCurrentlyPlayingCallback, SPOTIFY_MARKET);
  if (status == 200)
  {
    if (DEBUG)
      Serial.println("Successfully got currently playing");
  }
  else if (status == 204)
  {
    // sometimes spotify returns 204 when there is no song playing, sometimes it returns 200
    if (DEBUG)
      Serial.println("Doesn't seem to be anything playing");
    if (wasPlaying || !hasResetDisplay)
    {
      setDisplayNotListening(&display);
      wasPlaying = false;
      if (!hasResetDisplay)
        hasResetDisplay = true;
    }
  }
  else
  {
    if (DEBUG)
    {
      Serial.print("Error: ");
      Serial.println(status);
    }
    lastSleepDuration = millis();
    ESP.restart();
  }
}

/**
 * @brief This function is called when the Spotify API returns a currently playing song
 *
 * @param currentlyPlaying This is passed through the callback and is an instance of the CurrentlyPlaying Class
 */
void handleCurrentlyPlayingCallback(CurrentlyPlaying currentlyPlaying)
{
  Serial.println("Callback Called");
  // if the playing status has changed or the song has changed
  if (currentlyPlaying.isPlaying != wasPlaying || strcmp(currentlyPlaying.trackUri, oldSongURI.c_str()) != 0)
  {
    oldSongURI = String(currentlyPlaying.trackUri);
    if (DEBUG)
      printCurrentlyPlayingToSerial(currentlyPlaying);
    printCurrentlyPlayingToDisplay(currentlyPlaying);
    wasPlaying = currentlyPlaying.isPlaying;
  }
  handleDeepSleep(currentlyPlaying);
}

/**
 * @brief This prints the currently playing song to the display
 *
 * @param currentlyPlaying
 */
void printCurrentlyPlayingToDisplay(CurrentlyPlaying currentlyPlaying)
{
  if (currentlyPlaying.isPlaying)
  {
    display.fillScreen(GxEPD_WHITE);
    String Artists = String(currentlyPlaying.trackName);
    Artists.concat(" By ");
    for (int i = 0; i < currentlyPlaying.numArtists; i++)
    {
      // add the artist name to the string
      Artists.concat(currentlyPlaying.artists[i].artistName);
      // if it's the last artist, don't add a comma, otherwise do
      if (i < currentlyPlaying.numArtists - 1)
        Artists.concat(", ");
    }
    showLines("I'm listening to: ", 1, 10, &display);
    showLines(Artists, 3, 0, &display); // Display the name of the song and the artist name

    // Setting the lengths to 2 incase the HTTP request fails so it doesn't break the whole display
    int lengths[25] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    getSpotifyScanCode(currentlyPlaying.trackUri, lengths);

    drawSpotifyScan(0, 76, lengths, &display);

    display.update();
    hasResetDisplay = true;
  }
  else if (wasPlaying || !hasResetDisplay)
  {
    setDisplayNotListening(&display);
    wasPlaying = false;
    hasResetDisplay = true;
  }
}

/**
 * @brief This puts the ESP32 into deep sleep for the song duration (if one is playing), or the 'deepSleepDelay' variable
 *
 * @param currentlyPlaying
 */
void handleDeepSleep(CurrentlyPlaying currentlyPlaying)
{
  if (currentlyPlaying.isPlaying)
  {
    long deepSleepDelay = (currentlyPlaying.durationMs - currentlyPlaying.progressMs) / 1000;
    if (deepSleepDelay < 1)
    {
      lastSleepDuration = millis();
      ESP.restart();
    }
    else
    {
      esp_sleep_enable_timer_wakeup(deepSleepDelay * uS_TO_S_FACTOR);
      lastSleepDuration = deepSleepDelay * uS_TO_S_FACTOR + millis();
    }
  }
  else
  {
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    lastSleepDuration = TIME_TO_SLEEP * uS_TO_S_FACTOR + millis();
  }
  esp_deep_sleep_start();
}

void loop()
{
  // We have nothing in the loop because the ESP32 is supposed to go into deep sleep after displaying the song
  // However we need the loop due to the Arduino framework
}
