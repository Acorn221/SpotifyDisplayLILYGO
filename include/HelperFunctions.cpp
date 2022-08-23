#include <Arduino.h>
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