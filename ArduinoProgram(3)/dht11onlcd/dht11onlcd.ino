/*This is Dht11 on LCD Program.
In this program, the LCD will display 3 different values which are
the temperature in fahrenheit and celsius and the humidity(%).*/

#include <LiquidCrystal.h>      // Import the LiquidCrystal library
#include <Adafruit_Sensor.h>    // Import the Adafruit_Sensor library
#include <DHT.h>                // Import the DHT library
#include <DHT_U.h>              // Import the DHT Unified Sensor library

#define DHTPIN   6            // Define the pin to which the DHT sensor is connected
#define DHTTYPE  DHT11     // Define the type of DHT sensor used
DHT_Unified dht(DHTPIN, DHTTYPE);  // Create a DHT sensor object
uint32_t delayMS;            // Define the delay between sensor readings

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;    // Define the pins for the LCD display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);    // Create an LCD object with the defined pins


void setup() {

  lcd.begin(16, 2);   // Initialize the LCD display with 16 columns and 2 rows
  Serial.begin(9600); // Initialize the serial communication 

    dht.begin();      // Initialize the DHT sensor
    Serial.println(F("DHTxx Unified Sensor Example"));  // Print a message to the serial monitor
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);   // Get the temperature sensor details
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
    // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);        // Get the humidity sensor details
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  
  delayMS = sensor.min_delay / 1000;  // Calculate the delay between sensor readings
}

void loop() {
 
  delay(delayMS);   // Wait for the specified delay before taking readings
  sensors_event_t event;
  dht.temperature().getEvent(&event);  // Get the temperature reading
  if (isnan(event.temperature)) {      // Check for errors in the temperature reading               
    Serial.println(F("Error reading temperature!")); 
  }
  else {  // Print the temperature reading to the serial monitor

    Serial.print(F("Temperature: ")); 
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {           
    Serial.println(F("Error reading humidity!"));   
  }
  else {                                    
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }


  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.setCursor(0, 0); 
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.setCursor(0, 0); 
    lcd.print(F("Temp: "));
    lcd.print(event.temperature);
    lcd.print(char(223));
    lcd.print(F("C"));
  }
  
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.setCursor(0, 1); 
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.setCursor(0, 1); 
    lcd.print(F("Humidity: "));
    lcd.print(event.relative_humidity);
    lcd.print(F("%"));
  }

}
