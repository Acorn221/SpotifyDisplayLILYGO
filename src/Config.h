//------- Replace the following! ------
#define SSID ""
#define PASSWORD ""

#define CLIENT_ID  ""    // Your client ID of your spotify APP
#define CLIENT_SECRET "" // Your client Secret of your spotify APP (Do Not share this!)


// Country code, including this is advisable
#define SPOTIFY_MARKET "GB"


// Go here to get your refresh token, this is not very secure but it's the most convenient way to get it
// Tick the boxes "user-read-playback-state", "user-read-playback-position" and "user-modify-playback-state"
// https://acorn221.github.io/spotify-token-getter/
#define SPOTIFY_REFRESH_TOKEN ""

#ifndef DEBUG
	#define DEBUG true // Debug flag enables/disables serial output
#endif
