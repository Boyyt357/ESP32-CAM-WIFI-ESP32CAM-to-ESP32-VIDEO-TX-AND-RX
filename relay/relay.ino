#include <WiFi.h>

const char* ssid = "Esp32Cam";       // ESP32-CAM AP
const char* password = "12345678";

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);                // Set device as Wi-Fi client
  WiFi.setSleep(false);               // Disable sleep for max performance
  WiFi.setTxPower(WIFI_POWER_19_5dBm); // Max transmit power (also helps reception in some cases)
  WiFi.begin(ssid, password);

  Serial.print("Connecting to AP ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("RSSI: ");             // Show signal strength
  Serial.println(WiFi.RSSI());
  delay(5000);
}
