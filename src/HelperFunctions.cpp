#include "HelperFunctions.h"

const char *scannables_root_ca = // this certificate is for scannables.scdn.co to get the scan link
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
    "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
    "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
    "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
    "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
    "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
    "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
    "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
    "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
    "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
    "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
    "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
    "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
    "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
    "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
    "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
    "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
    "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
    "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
    "-----END CERTIFICATE-----";

const char *scannablesURL = "https://scannables.scdn.co/uri/plain/svg/ffffff/black/256/";

const unsigned char spotifyLogo[] PROGMEM = {
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
    0xe0, 0x1f, 0xff, 0xfc};

void getSpotifyScanCode(String URI, int lengths[25]){
    
    HTTPClient http;
    String url = String(scannablesURL);
    url.concat(URI);
    http.begin(url.c_str(), scannables_root_ca); // Specify the URL and certificate
    int httpCode = http.GET();                   // Make the request
    if (httpCode > 0)
    { // Check for the returning code
      String payload = http.getString();
      
      int location = 0;
      for (int i = 0; i < 3; i++)
      {
        location = payload.indexOf("height=\"", location + 8);
      }
      for (int i = 0; i < 23; i++)
      {
        int length = payload.substring(location + 8, payload.indexOf(".", location)).toInt();
        lengths[i] = map(length, 0, 60, 0, 46);
        location = payload.indexOf("height=\"", location + 8);
      }
    }
    else
    {
      if (DEBUG)
        Serial.println("Error on HTTP request");
    }
    http.end(); // Free the resources
}

void showLines(String text, int maxLines, int y, GxEPD_Class* display)
{ // this function displays words whole on the display and limits the lines they use
  if (y > 0)
  { // if a Y is given, set the cursor to it
    display->setCursor(0, y);
  }
  if (text.length() > MAX_LENGTH_PER_LINE)
  {
    for (int i = 0; i < maxLines; i++)
    {
      if (text.length() > 0)
      {
        if (text.length() > 21)
        {
          if (i == maxLines - 1)
          {
            text = text.substring(0, 18);
            text.concat("...");
            // display->setCursor(0, y);
            display->println(text.c_str());
          }
          else
          {
            int endOfLastWord = text.lastIndexOf(" ", 21);
            String temp = text.substring(0, endOfLastWord);
            text = text.substring(endOfLastWord + 1);
            // display->setCursor(0, y);
            display->println(temp.c_str());
            y += 15;
          }
        }
        else
        {
          display->println(text.c_str());
          text = "";
        }
      }
    }
  }
  else
  {
    display->println(text.c_str());
  }
}

void setDisplayNotListening(GxEPD_Class * disp){
  disp->fillScreen(GxEPD_WHITE);
  showLines("I'm not listening to anything right now :(", 2, 50, disp);
  disp->update();
}

void drawSpotifyScan(int x, int y, int lengths[24], GxEPD_Class* display)
{ // the function to show the spotify scan code
  display->drawExampleBitmap(spotifyLogo, x, y, 46, 46, GxEPD_BLACK);
  drawRoundedLines(3, 5, lengths, 23, x + 58, y + 23, display);
}

void drawRoundedLines(int distanceBetween, int width, int lengths[25], int count, int x, int y, GxEPD_Class* display)
{ // for drawing rounded lines next to eachother
  for (int i = 0; i < count; i++)
  {
    drawRoundedLine(lengths[i], width, x + ((distanceBetween + width) * i), y, display);
  }
}

void drawRoundedLine(int height, int width, int x, int y, GxEPD_Class* display)
{ // for drawing a singular rounded line, y is parsed in the middle of the line
  y = y - (height / 2);
  display->fillRoundRect(x, y, width, height, width, GxEPD_BLACK);
}

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying)
{
  // Use the details in this method or if you want to store them
  // make sure you copy them (using something like strncpy)
  // const char* artist =

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

  Serial.println("Artists: ");
  for (int i = 0; i < currentlyPlaying.numArtists; i++)
  {
    Serial.print("Name: ");
    Serial.println(currentlyPlaying.artists[i].artistName);
    Serial.print("Artist URI: ");
    Serial.println(currentlyPlaying.artists[i].artistUri);
    Serial.println();
  }

  Serial.print("Album: ");
  Serial.println(currentlyPlaying.albumName);
  Serial.print("Album URI: ");
  Serial.println(currentlyPlaying.albumUri);
  Serial.println();

  long progress = currentlyPlaying.progressMs; // duration passed in the song
  long duration = currentlyPlaying.durationMs; // Length of Song
  Serial.print("Elapsed time of song (ms): ");
  Serial.print(progress);
  Serial.print(" of ");
  Serial.println(duration);
  Serial.println();

  float percentage = ((float)progress / (float)duration) * 100;
  int clampedPercentage = (int)percentage;
  Serial.print("<");
  for (int j = 0; j < 50; j++)
  {
    if (clampedPercentage >= (j * 2))
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
}