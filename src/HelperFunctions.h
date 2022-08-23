// ----------------------------
// External Libraries
// ----------------------------

#include <Arduino.h>
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <GxEPD.h>
#include <GxGDE0213B72B/GxGDE0213B72B.h> // 2.13" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <SpotifyArduino.h>
#include <ArduinoJson.h>
#include "Config.h"

#ifndef CONST_H
    #define CONST_H

    #define MAX_LENGTH_PER_LINE 22 // this is the maximum amount of text characters per line of the screen

    #define uS_TO_S_FACTOR 1000000ULL // Conversion factor for micro seconds to seconds

    extern const char *scannables_root_ca;
    extern const char *scannablesURL;
    extern const unsigned char spotifyLogo[];

    void getSpotifyScanCode(String URI, int lengths[25]);
    void showLines(String text, int maxLines, int y, GxEPD_Class* display);
    void setDisplayNotListening(GxEPD_Class * display);
    void drawSpotifyScan(int x, int y, int lengths[24], GxEPD_Class* display);
    void drawRoundedLines(int distanceBetween, int width, int lengths[], int count, int x, int y, GxEPD_Class* display);
    void drawRoundedLine(int height, int width, int x, int y, GxEPD_Class* display);
    void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying);


#endif
