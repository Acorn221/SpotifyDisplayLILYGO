#include <Arduino.h>
#include <SpotifyArduino.h>
#include <GxGDE0213B72B/GxGDE0213B72B.h> // 2.13" b/w

#include "HelperFunctions.h"

void showLines(String text, int maxLines, int y, GxEPD_Class display)
{ // this function displays words whole on the display and limits the lines they use
  if (y > 0)
  { // if a Y is given, set the cursor to it
    display.setCursor(0, y);
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
            // display.setCursor(0, y);
            display.println(text.c_str());
          }
          else
          {
            int endOfLastWord = text.lastIndexOf(" ", 21);
            String temp = text.substring(0, endOfLastWord);
            text = text.substring(endOfLastWord + 1);
            // display.setCursor(0, y);
            display.println(temp.c_str());
            y += 15;
          }
        }
        else
        {
          display.println(text.c_str());
          text = "";
        }
      }
    }
  }
  else
  {
    display.println(text.c_str());
  }
}

void setDisplayNotListening(GxEPD_Class display){
  display.fillScreen(GxEPD_WHITE);
  showLines("I'm not listening to anything right now :(", 2, 50, display);
  display.update();
}

void drawSpotifyScan(int x, int y, int lengths[24], GxEPD_Class display)
{ // the function to show the spotify scan code
  display.drawExampleBitmap(spotifyLogo, x, y, 46, 46, GxEPD_BLACK);
  drawRoundedLines(3, 5, lengths, 23, x + 58, y + 23, display);
}

void drawRoundedLines(int distanceBetween, int width, int lengths[], int count, int x, int y, GxEPD_Class display)
{ // for drawing rounded lines next to eachother
  for (int i = 0; i < count; i++)
  {
    drawRoundedLine(lengths[i], width, x + ((distanceBetween + width) * i), y, display);
  }
}

void drawRoundedLine(int height, int width, int x, int y, GxEPD_Class display)
{ // for drawing a singular rounded line, y is parsed in the middle of the line
  y = y - (height / 2);
  display.fillRoundRect(x, y, width, height, width, GxEPD_BLACK);
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