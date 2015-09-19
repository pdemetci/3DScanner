/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 

Servo verticalServo;
Servo horizontalServo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
long pos_horizontal = 0;    // variable to store the servo position 
long pos_vertical = 0;
 
void setup() 
{ 
  verticalServo.attach(4);  // attaches the servo on pin 9 to the servo object 
  horizontalServo.attach(5);
} 
 
void loop() 
{ 
  for(pos_horizontal = 0; pos_horizontal <= 175; pos_horizontal += 7) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 

    horizontalServo.write(pos_horizontal);
    for (pos_vertical = 0; pos_vertical <= 180; pos_vertical += 1){
      verticalServo.write(pos_vertical);
       /// Collect data
      delay(15);
    }
    for (pos_vertical = 180; pos_vertical >= 0; pos_vertical -= 1){
      verticalServo.write(pos_vertical);
      ////Collect data
      delay(15);
    }
  }

  for(pos_horizontal = 175; pos_horizontal >=0; pos_horizontal -= 7) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 

    horizontalServo.write(pos_horizontal);
    for (pos_vertical = 0; pos_vertical <= 180; pos_vertical += 1){
      verticalServo.write(pos_vertical);
      /// Collect data
      delay(15);
    }
    for (pos_vertical = 180; pos_vertical >= 0; pos_vertical -= 1){
      verticalServo.write(pos_vertical);
      /// Collect data
      delay(15);
    }
  }
  } 
