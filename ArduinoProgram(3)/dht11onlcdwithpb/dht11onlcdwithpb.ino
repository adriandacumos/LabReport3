/*This is Dht11 on LCD with PB Program.
In this program, it has the same concept as the DHT11 on LCD as it will display 3 variables
which are the temperature and the humidity, but with the push button, the LCD will display
those 3 variables one by one.*/

#include <LiquidCrystal.h> 
#include <Adafruit_Sensor.h> 
#include <DHT.h> 
#include <DHT_U.h>

#define DHTPIN   6 
#define DHTTYPE  DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE); // create a DHT object with DHTPIN and DHTTYPE
uint32_t delayMS;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // create a LiquidCrystal object with the given pins

const int buttonPin = 7;  // set the button pin

int buttonState = LOW;    // initialize the button state to LOW
int lastButtonState = LOW;  // initialize the last button state to LOW


unsigned long lastDebounceTime = 0;  // initialize the last debounce time to 0
unsigned long debounceDelay = 50;  // set the debounce delay to 50ms

int count= 0; // initialize the count to 0

void setup() {
  
  pinMode(buttonPin, INPUT_PULLUP);  // set the button pin to input with pull-up resistor
  lcd.begin(16, 2);  // set the number of columns and rows of the LCD display
  Serial.begin(9600);   // initialize the serial communication     

  dht.begin();  // initialize the DHT object
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  
  delayMS = sensor.min_delay / 1000;
}

void loop() {

int reading = digitalRead(buttonPin); 

if (reading != lastButtonState) {
  lastDebounceTime = millis();
}
if ((millis() - lastDebounceTime) > debounceDelay) {
  
  if (reading != buttonState) {
    buttonState = reading;
    
    if (buttonState == HIGH) {
      count++;
      
      if(count == 4){
        count = 1;
      }
      
      switch(count){
        case 1:
          
          sensors_event_t event;
          dht.temperature().getEvent(&event);
          if (isnan(event.temperature)) { 
            Serial.println(F("Error reading temperature!")); 
          }
          else { 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Temp: ");
            lcd.print(event.temperature);
            lcd.print(char(223));
            lcd.print("C");
          }
          break;
        case 2:
          //Display humidity
          dht.humidity().getEvent(&event); 
          if (isnan(event.relative_humidity)) { 
            Serial.println(F("Error reading humidity!")); 
          }
          else {
            lcd.clear(); 
            lcd.setCursor(0,0);
            lcd.print("Humidity: ");
            lcd.print(event.relative_humidity);
            lcd.print("%");
          }
          break;
        case 3:
          
          dht.temperature().getEvent(&event);
          if (isnan(event.temperature)) {
            Serial.println(F("Error reading temperature!"));
          }
          else {  
            float f = (event.temperature * 1.8) + 32;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Temp: ");
            lcd.print(f);
            lcd.print(char(223));
            lcd.print("F");
          }
          break;
      }
    }
  }
}
lastButtonState = reading;
}
