
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h> 
#include "config.h"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

int ServoPin = D4;
int ANGLE_OFF = 20;
int ANGLE_ON = 90;

Servo servo;

void setup()
{

  Serial.begin(115200);
  // We need to attach the servo to the used pin number 
  servo.attach(ServoPin); 
  servo.write(ANGLE_OFF);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

bool feed = false;
int feedAmount = 3000;
String basePath = "/Dispenser/";
String feedPath = basePath + "feed";
String amountPath = basePath + "feedAmount";



void doFeed(int feedTime) {
  servo.write(ANGLE_ON);
  Serial.println("Feeding...");
  delay(feedTime);
  servo.write(ANGLE_OFF);
}

void loop()
{
  // Check if feed option is available  
  if (Firebase.getBool(firebaseData, feedPath)) {
    if (firebaseData.dataType() == "boolean") {
      feed = firebaseData.boolData();
      Serial.println(firebaseData.boolData());
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }

  // Get the feeding amount of time from firebase
  if (Firebase.getInt(firebaseData, amountPath)) {
    Serial.println(firebaseData.dataType());
    if (firebaseData.dataType() == "int") {
      feedAmount = firebaseData.intData();
      Serial.println(firebaseData.intData());
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }

  // Check if feed chosen
  if (feed) {
      doFeed(feedAmount);
      Firebase.setBool(firebaseData, feedPath, false);
      delay(100);
    }
}
