#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// ========== RESOLUTION & QUALITY SETTINGS ==========
// Change the value below to choose resolution:
//FRAMESIZE_QVGA for 320x240 (Faster, lower bandwidth)
//FRAMESIZE_VGA for 640x480 (Slower, higher quality)
#define DEFAULT_FRAME_SIZE FRAMESIZE_VGA

// JPEG Quality (0-63). Lower number = better quality, larger file size.
#define DEFAULT_JPEG_QUALITY 20
// =================================================

// ESP32 AP (Ground) Credentials - MUST MATCH ESP32 AP!
const char* ssid = "ESP32_CAM_RELAY";
const char* password = "camera123";

// Camera pins for AI-THINKER model
#define PWDN_GPIO_NUM 	 32
#define RESET_GPIO_NUM 	 -1
#define XCLK_GPIO_NUM 	 0
#define SIOD_GPIO_NUM 	 26
#define SIOC_GPIO_NUM 	 27
#define Y9_GPIO_NUM 	 35
#define Y8_GPIO_NUM 	 34
#define Y7_GPIO_NUM 	 39
#define Y6_GPIO_NUM 	 36
#define Y5_GPIO_NUM 	 21
#define Y4_GPIO_NUM 	 19
#define Y3_GPIO_NUM 	 18
#define Y2_GPIO_NUM 	 5
#define VSYNC_GPIO_NUM 	 25
#define HREF_GPIO_NUM 	 23
#define PCLK_GPIO_NUM 	 22

WebServer server(80);

void configureCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 30000000; // 30Hz clock
  config.pixel_format = PIXFORMAT_JPEG;
  
  // *** SET RESOLUTION HERE ***
  config.frame_size = DEFAULT_FRAME_SIZE; 
  // *** SET QUALITY HERE ***
  config.jpeg_quality = DEFAULT_JPEG_QUALITY; 
  
  config.fb_count = 2;
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x\n", err);
    ESP.restart();
  }
  
  sensor_t * s = esp_camera_sensor_get();
  if (s) {
    // Set resolution again to ensure it takes effect and apply other sensor settings
    s->set_framesize(s, DEFAULT_FRAME_SIZE);
    s->set_quality(s, DEFAULT_JPEG_QUALITY);
    s->set_brightness(s, 0);
    s->set_contrast(s, 0);
    s->set_saturation(s, 0);
  }
}

// Function to convert the FRAMESIZE enum to a readable string for the web UI
String getResolutionString() {
  switch (DEFAULT_FRAME_SIZE) {
    case FRAMESIZE_QVGA: return "QVGA (320x240)";
    case FRAMESIZE_VGA:  return "VGA (640x480)";
    case FRAMESIZE_SVGA: return "SVGA (800x600)";
    case FRAMESIZE_XGA:  return "XGA (1024x768)";
    default: return "Custom/Unknown";
  }
}

void handleRoot() {
  // Minimalist, dark-themed HTML with centered stream
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'><title>ESP32-CAM Stream</title><style>";
  html += "body{margin:0;font-family:Arial,sans-serif;background:#111;color:#fff;display:flex;flex-direction:column;align-items:center;padding:20px;}";
  html += "h1{color:#00ff88;text-shadow:0 0 5px #00ff88;margin:0 0 10px 0;font-size:1.5em;}";
  html += ".container{max-width:800px;width:100%;background:#222;border-radius:15px;padding:10px;box-shadow:0 0 20px rgba(0,255,136,0.1);text-align:center;}";
  html += "#stream{width:100%;border-radius:10px;box-shadow:0 2px 10px rgba(0,0,0,0.5);background:#000;display:block;}";
  html += ".info{margin-top:10px;color:#999;font-size:0.9em;}";
  html += "</style></head><body>";
  html += "<h1>Live Stream</h1>";
  html += "<div class='container'>";
  html += "<img id='stream' src='/stream' alt='Loading stream...'>";
  html += "<div class='info'>Resolution: " + getResolutionString() + " | Quality: " + String(DEFAULT_JPEG_QUALITY) + "</div>";
  html += "</div></body></html>";
  
  server.send(200, "text/html", html);
}

void handleStream() {
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: multipart/x-mixed-replace; boundary=frame");
  client.println();
  
  unsigned long lastFrame = 0;
  // A lower frameInterval might be needed for VGA, so keep it somewhat higher
  const unsigned long frameInterval = 66; // Limit to ~15 FPS (1000/15) for better stability on VGA
  
  while (client.connected()) {
    unsigned long now = millis();
    if (now - lastFrame >= frameInterval) {
      camera_fb_t * fb = esp_camera_fb_get();
      if (!fb) {
        Serial.println("Frame capture failed");
        continue;
      }
      
      client.println("--frame");
      client.println("Content-Type: image/jpeg");
      client.printf("Content-Length: %d\r\n\r\n", fb->len);
      client.write(fb->buf, fb->len);
      client.println();
      
      esp_camera_fb_return(fb);
      lastFrame = now;
    }
    delay(1);
  }
}

void handleCapture() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    server.send(500, "text/plain", "Capture failed");
    return;
  }
  
  WiFiClient client = server.client();
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: image/jpeg\r\n";
  response += "Content-Length: " + String(fb->len) + "\r\n";
  response += "Connection: close\r\n\r\n";
  server.sendContent(response);
  
  client.write(fb->buf, fb->len);
  esp_camera_fb_return(fb);
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nESP32-CAM Starting...");
  
  // Configure camera
  configureCamera();
  
  // Connect to ESP32 AP
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to ESP32 AP");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    
    // Setup web server
    server.on("/", handleRoot);
    server.on("/stream", handleStream);
    server.on("/capture", handleCapture); 
    server.begin();
    
    Serial.println("Web server started");
    Serial.println("Access at: http://" + WiFi.localIP().toString());
    Serial.printf("Current Resolution: %s, Quality: %d\n", getResolutionString().c_str(), DEFAULT_JPEG_QUALITY);
  } else {
    Serial.println("\nFailed to connect! Restarting...");
    ESP.restart();
  }
}

void loop() {
  server.handleClient();
}