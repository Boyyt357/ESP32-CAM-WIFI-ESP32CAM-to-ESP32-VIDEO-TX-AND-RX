#include <WiFi.h>

// ======== Access Point credentials ========
const char* ssid = "Esp 32 Cam";
const char* password = "12345678";  // at least 8 characters

void setup() {
  Serial.begin(115200);
  Serial.println();

  // ======== Configure Access Point ========
  WiFi.mode(WIFI_AP);  // Set device as Access Point
  WiFi.softAP(ssid, password);

  // Optional: set static IP (for easier debugging / known address)
  IPAddress local_ip(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  Serial.println("======================================");
  Serial.println("ESP32 Wi-Fi Access Point Started!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("======================================");
}

void loop() {
  // Display number of connected devices every few seconds
  Serial.print("Connected devices: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(5000);
}
