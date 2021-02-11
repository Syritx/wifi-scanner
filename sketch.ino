#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// SCL and SDA pins should be: D1 and D2 (NodeMCU)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
}

void loop() {
  
    int n = WiFi.scanNetworks();
    Serial.println(String(n)+" networks found");
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(5, 5);
            if (i+1 < 10 && n >= 10) { 
                display.println("NETWORKS: 0"+String(i+1) + " OF " + String(n));
            }
            else if (i+1 >= 10 && n >= 10) {
                display.println("NETWORKS: "+String(i+1) + " OF " + String(n));
            }
            else if (n < 10) {
              display.println("NETWORKS: "+String(i+1) + " OF " + String(n));
            }
            display.setCursor(5, 20);
            display.println(String(WiFi.SSID(i)));
            display.setCursor(5, 40);
            display.setTextSize(2);
            display.println(String(WiFi.RSSI(i)));
            display.display();
            delay(2000);
        }
    }
}
