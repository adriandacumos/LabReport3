/*This is the Ultrasonic on LCD Program.
In this program, the LCD will display a value of the distance that is being measured
by the sensor.*/

#define trigPin 9  
#define echoPin 10 

// Include the LiquidCrystal library for displaying results on an LCD
#include <LiquidCrystal.h> 

// Define the pin connections for the LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float duration, distance;

void setup() {
// Initialize the serial communication
Serial.begin(9600);
// Set the trigger pin as an output and the echo pin as an input
pinMode(trigPin, OUTPUT);    
pinMode(echoPin, INPUT);     
  lcd.begin(16, 2);


}

void loop() {
// Send a short LOW pulse to the trigger pin to start a measurement
digitalWrite(trigPin, LOW); 
delayMicroseconds(2);      
digitalWrite(trigPin, HIGH); 
delayMicroseconds(20);    
digitalWrite(trigPin, LOW); 

// Measure the duration of the pulse on the echo pin
duration = pulseIn(echoPin, HIGH);
// Calculate the distance based on the duration and the speed of sound
distance = (duration /2 ) * 0.0343;

// Print the distance to the serial monitor
Serial.print("Distance: ");

// If the distance is out of range, print an error message
if (distance >= 400 || distance <= 2) {
  Serial.println("Out od Range");
} else {
  // Otherwise, print the distance in centimeters
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
// Clear the LCD display and set the cursor to the top left corner
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance: ");
// If the distance is out of range, print an error message
if (distance >= 400 || distance <= 2) {
  lcd.setCursor(0,1);
  lcd.print("Out of Range");
} else {
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print(" cm");
}
}
