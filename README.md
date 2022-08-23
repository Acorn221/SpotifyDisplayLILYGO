# SpotifyDisplayLILYGO

For the LILYGO E-Paper display, T5 v2.3

This shows the song that is currently playing and the spotify scan code, it's for the the ESP32 LILYGO E-Paper board and uses deep sleep when it doesn't need to be awake

![Image](https://github.com/Acorn221/SpotifyDisplayLILYGO/blob/main/IMG_0240.jpg?raw=true)


## Installation

This repo is has been created with PlatformIO and uses the ESP32 LILYGO E-Paper board.

Change the definitions in /src/Config.h to your WifFi and Spotify details!

Install the PlatformIO Extension in VSCode and click 'Upload and Monitor' under esp32dev.

Hopefully this should all work without any errors.

For optimal efficiency, comment the 'SPOTIFY_DEBUG 1' and 'SPOTIFY_SERIAL_OUTPUT 1' lines in SpotifyArduino.h