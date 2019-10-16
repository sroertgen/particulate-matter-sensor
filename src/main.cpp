#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"
#include <SDS011.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <InfluxDb.h>

static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// Setup DHT22
#define DHTPIN D7
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

//Setup SDS011
#define RXPIN D1
#define TXPIN D2
SDS011 my_sds;

// Setup InfluxDB
#define INFLUXDB_HOST "141.5.108.58"
#define INFLUXDB_PORT "8086"
#define INFLUXDB_DATABASE "espdb"

Influxdb influx(INFLUXDB_HOST);

// Define vars
float p10, p25;
float temp, humid;

int error;
uint32_t delayMS;


void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while (!Serial){ }

  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(sensor.name);

  dht.humidity().getSensor(&sensor);
  Serial.println(sensor.name);

  // delayMS = sensor.min_delay / 1000;
  delayMS = 1000;

  // Setup WiFI
  WiFiManager wifiManager;
  wifiManager.autoConnect("NodeMCU-Arduino-PlatformIO");
  Serial.println("Connected!");
  
  // Setup SDS011
  my_sds.begin(RXPIN, TXPIN);

  // Set Influx Database
  influx.setDb(INFLUXDB_DATABASE);

}

void loop() 
{
  // Get temperature event and print value
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temp = event.temperature;
  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
  }

  // Get humidity
  dht.humidity().getEvent(&event);
  humid = event.relative_humidity;
  if (isnan(event.relative_humidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    Serial.print(F("Humidity: "));
    Serial.print(humid);
    Serial.println(F("%"));
  }

  // Read SDS011
  error = my_sds.read(&p25, &p10);
  if (!error)
  {
    Serial.println("P2.5: " + String(p25));
    Serial.println("P10:  " + String(p10));
  }

  // Send to InfluxDB
  Serial.println("Collecting measurements...");

  InfluxData measurement_temp("temperature");
  measurement_temp.addValue("value", temp);
  influx.prepare(measurement_temp);

  InfluxData measurement_humid("humidity");
  measurement_humid.addValue("value", humid);
  influx.prepare(measurement_humid);

  InfluxData measurement_p25("p25");
  measurement_p25.addValue("value", p25);
  influx.prepare(measurement_p25);

  InfluxData measurement_p10("p10");
  measurement_p10.addValue("value", p10);
  influx.prepare(measurement_p10);

  boolean success = influx.write();

  delay(delayMS);
}
