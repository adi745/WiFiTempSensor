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

// Define a struct to hold temperature and humidity values
struct dhtVals
{
  float temperature;
  float humidity;
};

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
    Serial.println("New client connected"); //Print message when a new client connects

    String request = ""; // Variable to store the HTTP request from the client
}

// put function definitions here:
dhtVals readTempHumidity() {
  dhtVals values; // Create a new dhtVals struct to hold the temperature and humidity values
  delay(100);
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  display.clearDisplay();             //Clear the display
  display.setTextColor(WHITE);        //Set the color
  display.setTextSize(1);             //Set the text size
  display.setCursor(8, 20);          //Set the cursor position
  display.print("Humidity:");      //Send text to the cursor position
  display.setTextSize(2);             //Set the text size
  display.setCursor(16, 35);          //Set the cursor position
  display.print(h);                   //Print the temperature
  display.setTextSize(1);             //Set the text size
  display.print(h);      //Send text to the cursor position
  display.setTextSize(1);             //Set the text size
  display.setCursor(26, 20);          //Set the cursor position
  display.print("Temperature:");      //Send text to the cursor position
  display.setTextSize(2);             //Change text size
  display.setCursor(34, 35);          //Set the cursor position
  display.print(t);                   //Print the temperature
  display.display();                  //Send all the commands to the dislplay
  Serial.print("Humidity = ");
  Serial.println(h);
  Serial.print("Temperature = ");
  Serial.println(t);
  delay(100);
  values.humidity = h; // Create a new dhtVals struct to hold the temperature and humidity values
  values.temperature = t; // Assign the temperature value to the struct
  return values; // Return the struct containing the temperature and humidity values
}