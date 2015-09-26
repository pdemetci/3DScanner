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
Servo horizontalServo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
long pos_horizontal = 0;    // variable to store the servo position 
long pos_vertical = 0;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int array[]= {0};
PrintWriter output;
void setup() 
{ 

  pinMode(9, OUTPUT); 
  pinMode(A0, INPUT);
  verticalServo.attach(4);  // attaches the servo on pin 9 to the servo object 
  horizontalServo.attach(5);
  output = createWriter( "data.txt" );
  Serial.begin(9600); 
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
   if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         if ( value != null ) {
              output.println( value );
         }
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
       if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         if ( value != null ) {
              output.println( value );
         }
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
      if ( value != null ) {
         output.println( value );
         }
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
       if ( value != null ) {
         output.println( value );
         }
    }
      verticalServo.write(pos_vertical);
      delay(15);
    }
  }
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
  } 
