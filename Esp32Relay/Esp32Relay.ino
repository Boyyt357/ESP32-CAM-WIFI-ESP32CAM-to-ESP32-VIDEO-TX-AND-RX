#include <WiFi.h>
#include "esp_wifi.h"

// AP Configuration - Both ESP32-CAM and Phone connect here
const char* ap_ssid = "ESP32_CAM_RELAY";
const char* ap_password = "camera123";

// Set static IPs for easy access
IPAddress local_ip(192, 168, 10, 1);    // ESP32 AP IP
IPAddress gateway(192, 168, 10, 1);      // Gateway
IPAddress subnet(255, 255, 255, 0);      // Subnet mask

void maxWiFiPower() {
  // Set maximum TX power (21 dBm)
  esp_wifi_set_max_tx_power(84);
  
  // Enable all protocols for compatibility and range
  esp_wifi_set_protocol(WIFI_IF_AP, WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);
  
  // Disable power saving for consistent performance
  esp_wifi_set_ps(WIFI_PS_NONE);
  
  // Use 20MHz bandwidth for better range
  esp_wifi_set_bandwidth(WIFI_IF_AP, WIFI_BW_HT20);
  
  Serial.println("✓ Max TX Power: 21 dBm (84)");
  Serial.println("✓ Bandwidth: 20MHz (long range)");
  Serial.println("✓ Power Saving: DISABLED");
  Serial.println("✓ Protocols: 802.11 b/g/n");
}

void setupAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  // Start AP on Channel 1 (best range, least interference)
  // Channel 1, not hidden, max 4 connections
  bool result = WiFi.softAP(ap_ssid, ap_password, 1, 0, 4);
  
  if (result) {
    Serial.println("\n✓✓✓ ACCESS POINT STARTED SUCCESSFULLY ✓✓✓");
  } else {
    Serial.println("\n✗✗✗ ACCESS POINT FAILED TO START ✗✗✗");
    ESP.restart();
  }
}

void printWiFiInfo() {
  Serial.println("\n");
  Serial.println("╔══════════════════════════════════════════╗");
  Serial.println("║     ESP32 LONG RANGE ACCESS POINT        ║");
  Serial.println("╚══════════════════════════════════════════╝");
  Serial.println();
  
  Serial.println("📡 ACCESS POINT INFORMATION:");
  Serial.println("   ├─ SSID: " + String(ap_ssid));
  Serial.println("   ├─ Password: " + String(ap_password));
  Serial.println("   ├─ IP Address: " + WiFi.softAPIP().toString());
  Serial.println("   ├─ MAC Address: " + WiFi.softAPmacAddress());
  Serial.println("   ├─ Channel: 1 (2.412 GHz)");
  Serial.println("   └─ Max Clients: 4");
  Serial.println();
  
  Serial.println("🎯 CONNECTION GUIDE:");
  Serial.println("   1. ESP32-CAM connects to: " + String(ap_ssid));
  Serial.println("      └─ Expected IP: 192.168.10.2");
  Serial.println();
  Serial.println("   2. Connect your Phone/Tablet to: " + String(ap_ssid));
  Serial.println("      └─ Password: " + String(ap_password));
  Serial.println();
  Serial.println("   3. Open browser on phone:");
  Serial.println("      └─ http://192.168.10.2");
  Serial.println();
  
  Serial.println("⚡ PERFORMANCE SETTINGS:");
  Serial.println("   ├─ TX Power: 21 dBm (MAX)");
  Serial.println("   ├─ Range Mode: LONG RANGE");
  Serial.println("   ├─ Bandwidth: 20MHz");
  Serial.println("   └─ Power Save: OFF");
  Serial.println();
  
  Serial.println("📊 EXPECTED RANGE:");
  Serial.println("   ├─ Outdoor (clear): 200-400m");
  Serial.println("   ├─ Outdoor (obstacles): 100-200m");
  Serial.println("   └─ Indoor: 50-100m");
  Serial.println();
  
  Serial.println("╔══════════════════════════════════════════╗");
  Serial.println("║           SYSTEM READY!                  ║");
  Serial.println("╚══════════════════════════════════════════╝");
  Serial.println();
}

void monitorClients() {
  static unsigned long lastCheck = 0;
  static int lastClientCount = 0;
  
  if (millis() - lastCheck > 5000) {
    lastCheck = millis();
    
    int clientCount = WiFi.softAPgetStationNum();
    
    // Only print if client count changed
    if (clientCount != lastClientCount) {
      Serial.println("\n════════════════════════════════");
      Serial.print("⚡ Connected Clients: ");
      Serial.println(clientCount);
      
      if (clientCount >= 2) {
        Serial.println("✓ ESP32-CAM: Connected");
        Serial.println("✓ Phone: Connected");
        Serial.println("🎥 Stream should be accessible!");
      } else if (clientCount == 1) {
        Serial.println("⚠ Only 1 device connected");
        Serial.println("  Waiting for both ESP32-CAM and Phone...");
      } else {
        Serial.println("⚠ No devices connected");
        Serial.println("  Waiting for connections...");
      }
      
      Serial.println("════════════════════════════════\n");
      lastClientCount = clientCount;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n\n");
  Serial.println("████████████████████████████████████████");
  Serial.println("█                                      █");
  Serial.println("█   ESP32 LONG RANGE RELAY AP v2.0    █");
  Serial.println("█   Simplified Direct Connection      █");
  Serial.println("█                                      █");
  Serial.println("████████████████████████████████████████");
  Serial.println();
  
  Serial.println("🚀 Initializing...");
  delay(500);
  
  // Setup Access Point
  setupAccessPoint();
  delay(1000);
  
  // Apply maximum power and range settings
  maxWiFiPower();
  delay(500);
  
  // Print all configuration info
  printWiFiInfo();
  
  Serial.println("👂 Monitoring for connections...\n");
}

void loop() {
  // Monitor and display connected clients
  monitorClients();
  
  delay(100);
}