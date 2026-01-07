#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "wifi/name";
const char* password = "wifi/password";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");

    if (!display.begin(SSD1306_PAGEADDR, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1.5);
    display.setCursor(0, 0);
    display.println("Connecting to WiFi...");
    display.display();

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("\nConnected to WiFi");

    timeClient.begin();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Connected");
    display.println(WiFi.localIP());
    display.display();
    delay(2000);

    display.clearDisplay();
}

void loop() {
    timeClient.update();

    String currentTime = timeClient.getFormattedTime();

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(20, 32);
    display.println(currentTime);
    display.display();

    Serial.println("Current Time: " + currentTime);

    delay(1000);
}


