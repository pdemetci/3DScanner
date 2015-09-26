#include <Firmata.h>
#include <Boards.h>

/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h>
//import processing.serial.*;
Servo verticalServo;
Servo horizontalServo;// create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
long pos_horizontal = 0;    // variable to store the servo position 
long pos_vertical = 0;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

#include <Arduino.h>
#include <stdint.h>

// Output pins
const unsigned char LED = LED_BUILTIN; // signed char has a range of -128 to 127; unsigned char is same as byte

// Other Constants (in C++, static const is redundant, ie same as const; extern const is opposite):
#define PC_BAUD 250000 // baud rate used for serial communication [hz]

// Counters
signed long int timeSinceLast = 0; // 32-bit (4-byte)
unsigned long long int prevTime = 0; // 64-bit (8-byte)
uint64_t currTime = 0; // uint64_t is the same as "unsigned long long int"
float timeInSeconds = 0.0; 

// State variables
boolean isRunning = true;

// Serial port
HardwareSerial & pcSer = Serial;


void setup() 
{ 

  pinMode(9, OUTPUT); 
  pinMode(A0, INPUT);
  verticalServo.attach(4);  // attaches the servo on pin 9 to the servo object 
  horizontalServo.attach(5);
  Serial.begin(9600); 
   pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pcSer.begin(PC_BAUD);
 } 
 
void loop() 
{ 
  for(pos_horizontal = 0; pos_horizontal <= 175; pos_horizontal += 7) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    horizontalServo.write(pos_horizontal);
    for (pos_vertical = 70; pos_vertical <= 170; pos_vertical += 1){
      sensorValue = analogRead(analogInPin);
      outputValue = map(sensorValue, 0, 1023, 0, 255);
      analogWrite(analogOutPin, outputValue);
      Serial.println(outputValue);
     currTime = micros();
    timeSinceLast = currTime - prevTime;
    timeInSeconds = currTime/1000000.0;
    Serial.println()
    sendValues(outputValue, currTime, timeInSeconds);
    delayMicroseconds(random(1000));
    
    if (timeInSeconds > 1) {
      isRunning = false;
      pcSer.println("This means we're going to stop sending data now.");
    }
    
    prevTime = currTime;
  } 
      verticalServo.write(pos_vertical);
      delay(15);
    }
    for (pos_vertical = 170; pos_vertical >= 70; pos_vertical -= 1){
      sensorValue = analogRead(analogInPin);
      outputValue = map(sensorValue, 0, 1023, 0, 255);
      analogWrite(analogOutPin, outputValue);
      Serial.println(outputValue);
      Serial.print(",");
      Serial.print(pos_vertical);
      Serial.print(pos_horizontal);
           currTime = micros();
    timeSinceLast = currTime - prevTime;
    timeInSeconds = currTime/1000000.0;
    Serial.println()
    sendValues(outputValue, currTime, timeInSeconds);
    delayMicroseconds(random(1000));
    
    if (timeInSeconds > 1) {
      isRunning = false;
      pcSer.println("This means we're going to stop sending data now.");
    }
    
    prevTime = currTime;
  } 
      verticalServo.write(pos_vertical);
        delay(15); 
    }
  }

  for(pos_horizontal = 175; pos_horizontal >=0; pos_horizontal -= 7) {                                  // in steps of 1 degree 
    horizontalServo.write(pos_horizontal);
    for (pos_vertical = 70; pos_vertical <= 170; pos_vertical += 1){
        sensorValue = analogRead(analogInPin);
        outputValue = map(sensorValue, 0, 1023, 0, 255);
        analogWrite(analogOutPin, outputValue);
        Serial.println(outputValue);
       Serial.print(",");
      Serial.print(pos_vertical);
      Serial.print(pos_horizontal);
           currTime = micros();
    timeSinceLast = currTime - prevTime;
    timeInSeconds = currTime/1000000.0;
    Serial.println()
    sendValues(outputValue, currTime, timeInSeconds);
    delayMicroseconds(random(1000));
    
    if (timeInSeconds > 1) {
      isRunning = false;
      pcSer.println("This means we're going to stop sending data now.");
    }
    
    prevTime = currTime;
  } 
      verticalServo.write(pos_vertical);
      delay(15);
    }
    for (pos_vertical = 170; pos_vertical >= 70; pos_vertical -= 1){
   sensorValue = analogRead(analogInPin);
      outputValue = map(sensorValue, 0, 1023, 0, 255);
      analogWrite(analogOutPin, outputValue);
      Serial.println(outputValue);
      Serial.print(",");
      Serial.print(pos_vertical);
      Serial.print(pos_horizontal);
           currTime = micros();
    timeSinceLast = currTime - prevTime;
    timeInSeconds = currTime/1000000.0;
    Serial.println()
    sendValues(outputValue, currTime, timeInSeconds);
    delayMicroseconds(random(1000));
    
    if (timeInSeconds > 1) {
      isRunning = false;
      pcSer.println("This means we're going to stop sending data now.");
    }
    
    prevTime = currTime;
  } 
      verticalServo.write(pos_vertical);
      delay(15);
    }
  }
    exit();  // Stops the program
  } 

void sendValues(signed long int signedInt, unsigned long long int Int, float Float) {
  pcSer.print(signedInt);
  pcSer.print(", ");
  pcSer.print((uint32_t) (Int >> 32), HEX); // send bigger 4 bytes
  pcSer.print((uint32_t) Int, HEX); // send littler 4 bytes
  pcSer.print(", ");
  pcSer.println(Float, 6); // make sure to print lots of digits for your floats to get max precision!
}
