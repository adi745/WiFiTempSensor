#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <WiFi.h>

// Define the DHT sensor type and pin
#define DHTPIN 4              // DHT GPIO
#define DHTTYPE    DHT11      // Define DHT type as DHT11

DHT dht(DHTPIN, DHTTYPE);    // Create DHT object

//Define the display size
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// define wifi credentials
const char* ssid = "ADI_DECO";
const char* password = "0506248863";

// create a wifi server object on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  //Start the temperature sensor
  dht.begin();
  //Start the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println(F("Display failed"));
  }
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Trying to connect to WiFi network: ");
    Serial.println(ssid); // Print the SSID that we are trying to connect to
  }
  // Print connection details when connected
  Serial.println();
  Serial.print("Successfully connected to WiFi network: ");
  Serial.println(ssid);
  Serial.print("with IP Address: ");
  Serial.println(WiFi.localIP()); // Print the local IP address assigned to the ESP32

  server.begin(); // Start the server
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}