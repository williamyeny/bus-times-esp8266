#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "keys.h"

void setup()
{
  Serial.begin(921600);
  Serial.println();

  WiFi.begin("DukeOpen");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");


//  Serial.println("Connected, IP address: " + WiFi.localIP());
  Serial.println("Mac address: " + WiFi.macAddress());

  HTTPClient http;
  
  String fingerprint = "21:1E:D8:65:8C:D0:76:58:45:DB:70:A3:01:F4:E1:1C:13:BE:9E:A3"; // fingerprint of website
  String url = "https://transloc-api-1-2.p.mashape.com/arrival-estimates.json?agencies=176&routes=4008330%2C+4007592%2C+4005486%2C+4008336&stops=4146366";
  
  http.begin(url, fingerprint);
  http.addHeader("Accept", "application/json");
  http.addHeader("X-Mashape-Key", MASHAPE_KEY);
  
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET CODE: %d\n", httpCode);

    // file found at server
    if(httpCode == HTTP_CODE_OK) {
       String payload = http.getString();
       Serial.println(payload);
    }
  } else {
    Serial.println("[HTTP] GET... failed, error: " + http.errorToString(httpCode));
  }

  http.end();
}

void loop() {
  
}
