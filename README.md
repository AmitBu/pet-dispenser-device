# Pet dispenser device
Pet dispenser ESP8266 device code.

The device is a pet food container with a servo controlling the feeding mechanism.
It subscribes to firebase variable changes to trigger the feeding + the feeding time amount.

To run this code you should create `config.h` file containing several variable definitions (not included - sensitive data):
```
#define FIREBASE_HOST "[PROJECT_ID].firebaseio.com"
#define FIREBASE_AUTH "[YOUR_SECRET]"
#define WIFI_SSID "[WIFI_SSID]"
#define WIFI_PASSWORD "[WIFI_PASSWORD]"
```
Or, just copy the the lines to the .ino file.
