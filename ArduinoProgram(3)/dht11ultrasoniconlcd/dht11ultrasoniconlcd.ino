/*This is the DHT11 and Ultrasonic on LCD Program.
In this program, the LCD will display the measurement of the temperature,
humidity and distance.*/

#include "DHT.h";
#include "NewPing.h"; 
#include <LiquidCrystal.h> 

#define DHTPIN 6 
#define DHTTYPE DHT11 
#define TRIGGER_PIN 9 
#define ECHO_PIN 10 
#define MAX_DISTANCE 400 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 

DHT dht(DHTPIN, DHTTYPE);  // Initializing the DHT sensor object with the DHT pin and type
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Initializing the NewPing object with trigger, echo pins, and max distance
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initializing the LCD object with the corresponding pin


float hum; // variable to store humidity
float temp; // variable to store temperature
float duration; // variable to store the duration of the sound wave
float distance; // variable to store the distance measured by the sonar sensor
float soundsp; // variable to store the speed of sound in m/s
float soundcm; // variable to store the speed of sound in cm/s
int iterations = 5;  // number of iterations for the median filter used in the sonar sensor

void setup() {
// initializing the serial communication
Serial.begin (9600);
lcd.begin(16, 2);

// initializing the DHT sensor
dht.begin();
}

void loop() {
delay(2000);


hum = dht.readHumidity();  // read the humidity value from the DHT sensor
temp = dht.readTemperature(); // read the temperature value from the DHT sensor


soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);// calculate the speed of sound based on the temperature and humidity values

soundcm = soundsp / 10000;  // convert the speed of sound to cm/s

duration = sonar.ping_median(iterations); 
distance = (duration / 2) * soundcm; // calculate the distance based on the duration and the speed of sound


Serial.print("Sound: ");
Serial.print(soundsp);
Serial.print(" m/s, ");
Serial.print("Humid: ");
Serial.print(hum);
Serial.print(" %, Temp: ");
Serial.print(temp);
Serial.print(" C, ");
Serial.print("Distance: ");


if (distance >= 400 || distance <= 2) {
Serial.print("Out of range"); // if it's out of range, print "Out of range" on the serial monitor
}
else { 
Serial.print(distance);   // if it's within range, print the distance value on the serial monitor
Serial.println("cm");
delay(200);
}


lcd.clear();
lcd.setCursor(0,0);
lcd.print("Sound:");
lcd.print(soundsp);
lcd.print("m/s");


lcd.setCursor(0,1);
lcd.print("Distance:");
lcd.print(distance);
lcd.print("cm");
}
