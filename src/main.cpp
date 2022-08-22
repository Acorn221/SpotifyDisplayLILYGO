/*******************************************************************
This code is partically based off of the ArduinoSpotify example
 *******************************************************************/

// ----------------------------
// Libraries
// ----------------------------
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <SpotifyArduino.h>
#include <GxEPD.h>
#include <GxGDE0213B72B/GxGDE0213B72B.h>      // 2.13" b/w
#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <SpotifyArduino.h>
#include <ArduinoJson.h>


void printCurrentlyPlayingToDisplay(CurrentlyPlaying currentlyPlaying);
void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying);


#define DEBUG true
#define MAX_LENGTH_PER_LINE 22
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 300
#define PRE_RESTART_TIME 15

//------- Replace the following! ------
const char* ssid = "";
const char* password =  "";

// Follow the instructions on the ArduinoSpotify "getRefreshToken" example to get all of this
char clientId[] =     "";     // Your client ID of your spotify APP
char clientSecret[] = ""; // Your client Secret of your spotify APP (Do Not share this!)

// Country code, including this is advisable
#define SPOTIFY_MARKET "GB"

#define SPOTIFY_REFRESH_TOKEN ""

const unsigned char spotifyLogo [] PROGMEM = {
  0xff, 0xff, 0xe0, 0x1f, 0xff, 0xfc, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xfc, 0xff, 0xf8, 0x00, 0x00, 
  0x7f, 0xfc, 0xff, 0xe0, 0x00, 0x00, 0x1f, 0xfc, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xfc, 0xff, 0x00, 
  0x00, 0x00, 0x03, 0xfc, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x0f, 0xff, 0xc0, 0x00, 0x1c, 0xc0, 0xff, 
  0xff, 0xfe, 0x00, 0x0c, 0xc1, 0xff, 0xff, 0xff, 0xc0, 0x0c, 0x81, 0xff, 0xff, 0xff, 0xf8, 0x04, 
  0x81, 0xff, 0xff, 0xff, 0xfc, 0x04, 0x81, 0xe0, 0x00, 0x0f, 0xfe, 0x04, 0x80, 0x00, 0x00, 0x01, 
  0xfe, 0x04, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x0c, 0x00, 0x00, 0x7f, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x70, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xf0, 0x00, 0x80, 0x00, 0xf8, 0x00, 0x70, 0x04, 0x80, 0x3f, 0xff, 0xe0, 0x00, 0x04, 0x80, 0x7f, 
  0xff, 0xfc, 0x00, 0x04, 0x80, 0x7f, 0xff, 0xff, 0x00, 0x04, 0xc0, 0x20, 0x00, 0x3f, 0x80, 0x0c, 
  0xc0, 0x00, 0x00, 0x07, 0x80, 0x0c, 0xe0, 0x00, 0x00, 0x01, 0x80, 0x1c, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xf8, 0x00, 
  0x00, 0x00, 0x00, 0x7c, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xfc, 
  0xff, 0x00, 0x00, 0x00, 0x03, 0xfc, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xfc, 0xff, 0xe0, 0x00, 0x00, 
  0x1f, 0xfc, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xfc, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xfc, 0xff, 0xff, 
  0xe0, 0x1f, 0xff, 0xfc
};

const char* root_ca = // this certificate is for scannables.scdn.co to get the scan link
"-----BEGIN CERTIFICATE-----\n"ß
"MIIGAzCCBOugAwIBAgIQD20nTNczzv6uOjzyUv6AqjANBgkqhkiG9w0BAQsFADBN\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMScwJQYDVQQDEx5E\n"
"aWdpQ2VydCBTSEEyIFNlY3VyZSBTZXJ2ZXIgQ0EwHhcNMjAwODA1MDAwMDAwWhcN\n"
"MjEwOTAxMTIwMDAwWjBKMQswCQYDVQQGEwJTRTESMBAGA1UEBxMJU3RvY2tob2xt\n"
"MRMwEQYDVQQKEwpTcG90aWZ5IEFCMRIwEAYDVQQDDAkqLnNjZG4uY28wggEiMA0G\n"
"CSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDID9qN0a5/WfTmGmSoRgGUUas49dfa\n"
"wxBqGSTV97Rjtv03iBF6yNQ37O600TQe8U4xXhrO5iaB0j6aDW1bW6bQCjK8MMGJ\n"
"UhCLMYjan7mCQ5Db4rd9/PJk+pOlYJHqXfSWB5zrcSgxGQ42sGUIBwy61FKyC65H\n"
"dVkMr3xFoKi5WYSgMoVNrW6pIXle+xoI1sHnxtKD7bPSOE+T/7ciaALVgXlVlIN6\n"
"tSRwO33HkLOsjwGicM4VboAKtPIaBsj5J6R0LfB1QZiUsewUPmeB/OfTmY/B3PTC\n"
"7R9FwDtETw/lpomWQZsfzszFyOLHGOMd07Rv6/FQBNjUa3hzazClKWkTAgMBAAGj\n"
"ggLgMIIC3DAfBgNVHSMEGDAWgBQPgGEcgjFh1S8o541GOLQs4cbZ4jAdBgNVHQ4E\n"
"FgQUJr5o9Oob7MeWbi/T+RiiiNQd61YwHQYDVR0RBBYwFIIJKi5zY2RuLmNvggdz\n"
"Y2RuLmNvMA4GA1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYB\n"
"BQUHAwIwawYDVR0fBGQwYjAvoC2gK4YpaHR0cDovL2NybDMuZGlnaWNlcnQuY29t\n"
"L3NzY2Etc2hhMi1nNi5jcmwwL6AtoCuGKWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNv\n"
"bS9zc2NhLXNoYTItZzYuY3JsMEwGA1UdIARFMEMwNwYJYIZIAYb9bAEBMCowKAYI\n"
"KwYBBQUHAgEWHGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwCAYGZ4EMAQIC\n"
"MHwGCCsGAQUFBwEBBHAwbjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNl\n"
"cnQuY29tMEYGCCsGAQUFBzAChjpodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20v\n"
"RGlnaUNlcnRTSEEyU2VjdXJlU2VydmVyQ0EuY3J0MAwGA1UdEwEB/wQCMAAwggED\n"
"BgorBgEEAdZ5AgQCBIH0BIHxAO8AdgD2XJQv0XcwIhRUGAgwlFaO400TGTO/3wwv\n"
"IAvMTvFk4wAAAXO/YUA3AAAEAwBHMEUCIQCKZTwhR3LM+PszAAWNdh3m4nOpF0t1\n"
"5+9scMcCQhH9IAIgVMJa3FDGw5q2ieWB0GL7h4FF1TETlq9+VxrdxFYWktcAdQBc\n"
"3EOS/uarRUSxXprUVuYQN/vV+kfcoXOUsl7m9scOygAAAXO/YUBrAAAEAwBGMEQC\n"
"IB4P+FuP4f1K5e+rJ0lp799B+Nrq24ZUl6zwg4I1TXsjAiBk63IqoNMlsXm81ab3\n"
"xQ77mYBd6WF9Hzmrz8uoe7BWGDANBgkqhkiG9w0BAQsFAAOCAQEAn9uHdEVD5W2f\n"
"I/Ql+h8ljZZC5wmjGjS/GgohYQ5Zw4m11gL/PewxjlQwr8EhanP1LO7DhvO/8Ofw\n"
"QyXse9uCSIwS/gzd1U1CxmhuH8uF2AY2aKib8bvVXwGWwmxpd6prHDks7+iF9Jif\n"
"pih2wJOQcHXJmnQ72a/DoPMhS9ODdvxLYOiDbKymB59Zvhrh37hQlbHVi69y6xFw\n"
"Az5Y89K70+JoXBW0zExSQl2bynID9HvXLR/d1z/VsKhMUDsUblwsXVdU7QqvPNWK\n"
"5/BAMjjx4IeknKOCxxii4dUUzYmI0nrUBrBymHUPqbBqX+utWG+5bKcAAlTzofAl\n"
"7d0oisi77g==\n"
"-----END CERTIFICATE-----\n";


WiFiClientSecure client;
SpotifyArduino spotify(client, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 10000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4); // arbitrary selection of (16), 4

RTC_DATA_ATTR String oldSongURI = "";
RTC_DATA_ATTR bool wasPlaying = false;

void setup()
{
  long setupTime = millis();
  display.init(115200);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextSize(1);
  display.setTextWrap(true);

  Serial.begin(112500);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //Serial.println("");

  // Wait for connection
  if (WiFi.waitForConnectResult() != WL_CONNECTED){
    ESP.restart();
  }
    
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    client.setCACert(root_ca);

    // If you want to enable some extra debugging
    // uncomment the "#define SPOTIFY_DEBUG" in ArduinoSpotify.h

    Serial.println("Refreshing Access Tokens");
    if (!spotify.refreshAccessToken())
    {
        if(DEBUG) Serial.println("Failed to get access tokens");
        ESP.restart();
    }
    while(millis()-setupTime < PRE_RESTART_TIME * 1000) delay(10);

    if(DEBUG) Serial.println("getting currently playing song:");

    // Market can be excluded if you want e.g. spotify.getCurrentlyPlaying()
    int status = spotify.getCurrentlyPlaying(printCurrentlyPlayingToSerial, SPOTIFY_MARKET);
    
    if (status == 200) {
        Serial.println("Successfully got currently playing");
    } else if (status == 204) {
        Serial.println("Doesn't seem to be anything playing");
    } else {
        if(DEBUG){
          Serial.print("Error: ");
          Serial.println(status);
        } 
        ESP.restart();
    }

    if(currentlyPlaying.isPlaying != wasPlaying || strcmp(currentlyPlaying.trackUri, oldSongURI.c_str()) != 0){
      oldSongURI = String(currentlyPlaying.trackUri);
      printCurrentlyPlayingToDisplay(currentlyPlaying);
      printCurrentlyPlayingToSerial(currentlyPlaying);
      wasPlaying = currentlyPlaying.isPlaying;
    }
    if(currentlyPlaying.isPlaying){
      long deepSleepDelay = ((currentlyPlaying.duraitonMs-currentlyPlaying.progressMs)/1000)-PRE_RESTART_TIME;
      if(deepSleepDelay < 1){
        ESP.restart();
      } else {
        esp_sleep_enable_timer_wakeup(deepSleepDelay * uS_TO_S_FACTOR);
      }
    } else {
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    }
    esp_deep_sleep_start();
}

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying)
{
    if (!currentlyPlaying.error)
    {
        Serial.println("--------- Currently Playing ---------");

        Serial.print("Is Playing: ");
        if (currentlyPlaying.isPlaying)
        {
            Serial.println("Yes");
        }
        else
        {
            Serial.println("No");
        }

        Serial.print("Track: ");
        Serial.println(currentlyPlaying.trackName);
        Serial.print("Track URI: ");
        Serial.println(currentlyPlaying.trackUri);
        Serial.println();

        Serial.print("Artist: ");
        Serial.println(currentlyPlaying.firstArtistName);
        Serial.print("Artist URI: ");
        Serial.println(currentlyPlaying.firstArtistUri);
        Serial.println();

        Serial.print("Album: ");
        Serial.println(currentlyPlaying.albumName);
        Serial.print("Album URI: ");
        Serial.println(currentlyPlaying.albumUri);
        Serial.println();

        long progress = currentlyPlaying.progressMs; // duration passed in the song
        long duration = currentlyPlaying.duraitonMs; // Length of Song
        Serial.print("Elapsed time of song (ms): ");
        Serial.print(progress);
        Serial.print(" of ");
        Serial.println(duration);
        Serial.println();

        float precentage = ((float)progress / (float)duration) * 100;
        int clampedPrecentage = (int)precentage;
        Serial.print("<");
        for (int j = 0; j < 50; j++)
        {
            if (clampedPrecentage >= (j * 2))
            {
                Serial.print("=");
            }
            else
            {
                Serial.print("-");
            }
        }
        Serial.println(">");
        Serial.println();

        // will be in order of widest to narrowest
        // currentlyPlaying.numImages is the number of images that
        // are stored
        for (int i = 0; i < currentlyPlaying.numImages; i++)
        {
            Serial.println("------------------------");
            Serial.print("Album Image: ");
            Serial.println(currentlyPlaying.albumImages[i].url);
            Serial.print("Dimensions: ");
            Serial.print(currentlyPlaying.albumImages[i].width);
            Serial.print(" x ");
            Serial.print(currentlyPlaying.albumImages[i].height);
            Serial.println();
        }
        Serial.println("------------------------");
    } else {
      Serial.println("Error");
    }
}

void handleCurrentlyPlayingCallback(CurrentlyPlaying currentlyPlaying){
  if(DEBUG) printCurrentlyPlayingToSerial(currentlyPlaying);
  printCurrentlyPlayingToDisplay(currentlyPlaying);
  
}

void printCurrentlyPlayingToDisplay(CurrentlyPlaying currentlyPlaying){
  display.fillScreen(GxEPD_WHITE);
  if(currentlyPlaying.isPlaying && !currentlyPlaying.error){
    char buff[150];
    sprintf(buff, "%s by %s", currentlyPlaying.trackName, currentlyPlaying.firstArtistName);
    showLines("I'm listening to: ", 1, 10);
    showLines(String(buff), 3, 0); // Display the name of the song and the artist name
    HTTPClient http;
    String url = "https://scannables.scdn.co/uri/plain/svg/ffffff/black/256/";
    url.concat(currentlyPlaying.trackUri); // add the URI
    http.begin(url.c_str(), root_ca); //Specify the URL and certificate
    int httpCode = http.GET();//Make the request
    if (httpCode > 0) { //Check for the returning code
          String payload = http.getString();
          int lengths[25];
          int location = 0;
          for(int i = 0; i < 3; i++){
            location = payload.indexOf("height=\"", location+8);
          }
          for(int i = 0; i < 23; i++){
            int length = payload.substring(location+8, payload.indexOf(".", location)).toInt();
            lengths[i] = map(length, 0, 60, 0, 46);
            location = payload.indexOf("height=\"", location+8);
          }
          drawSpotifyScan(0, 76, lengths);
        }
   
      else {
        Serial.println("Error on HTTP request");
      }
   
      http.end(); //Free the resources
  } else {
    showLines("I'm not listening to anything right now :(", 2, 50);
  }
  
  display.update();
}
void showLines(String text, int maxLines, int y) { // this function displays words whole on the display and limits the lines they use
  if(y > 0) { // if a Y is given, set the cursor to it
    display.setCursor(0, y);
  }
  if(text.length() > MAX_LENGTH_PER_LINE){
    for(int i = 0; i < maxLines; i++){
      if(text.length() > 0) {
        if(text.length() > 21){
          if(i == maxLines-1){
            text = text.substring(0, 18);
            text.concat("...");
            //display.setCursor(0, y);
            display.println(text.c_str());
          } else {
            int endOfLastWord = text.lastIndexOf(" ", 21);
            String temp = text.substring(0, endOfLastWord);
            text = text.substring(endOfLastWord+1);
            //display.setCursor(0, y);
            display.println(temp.c_str());
            y += 15;
          }
        } else {
          display.println(text.c_str());
          text = "";
        }
      }
    }
  } else {
    display.println(text.c_str());
  }
}
void drawSpotifyScan(int x, int y, int lengths[24]){ // the function to show the spotify scan code
  display.drawExampleBitmap(spotifyLogo, x, y, 46, 46, GxEPD_BLACK);
  drawRoundedLines(3, 5, lengths, 23, x+58, y+23);
}

void drawRoundedLines(int distanceBetween, int width, int lengths[], int count, int x, int y){ // for drawing rounded lines next to eachother
  for(int i = 0; i < count; i++){
    drawRoundedLine(lengths[i], width, x+((distanceBetween+width)*i), y);
  }
}
void drawRoundedLine(int height, int width, int x, int y){ // for drawing a singular rounded line, y is parsed in the middle of the line
  y = y -(height/2);
  display.fillRoundRect(x, y, width, height, width, GxEPD_BLACK);
}

void loop()
{
  
}
