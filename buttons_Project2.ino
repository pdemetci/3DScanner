//Button Press Detection - debounce with millis()

#include <Servo.h>  
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position 

int var = 0;

int leftButtonPin = 7;
int rightButtonPin = 6;
String systemState;
boolean currentStateLeft = LOW;//stroage for current measured button state
boolean currentStateRight = LOW;
boolean lastStateLeft = LOW;//storage for last measured button state
boolean lastStateRight = LOW;//storage for last measured button state
boolean debouncedStateLeft = LOW;//debounced button state
boolean debouncedStateRight = LOW;//debounced button state

int debounceInterval = 20;//wait 20 ms for button pin to settle
unsigned long timeOfLastButtonEvent = 0;//store the last time the button state changed

void setup(){
  pinMode(leftButtonPin, INPUT);//this time we will set the pin as INPUT
  pinMode(rightButtonPin, INPUT);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);//initialize Serial connection
}

void loop(){
  
  currentStateLeft = digitalRead(leftButtonPin);
  currentStateRight = digitalRead(rightButtonPin);
  unsigned long currentTime = millis();
  
  if (currentStateLeft != lastStateLeft){
    timeOfLastButtonEvent = currentTime;
  }
  if (currentStateRight != lastStateRight){
    timeOfLastButtonEvent = currentTime;
  }
  
  if (currentTime - timeOfLastButtonEvent > debounceInterval){//if enough time has passed
    if (currentStateLeft != debouncedStateLeft){//if the current state is still different than our last stored debounced state
      debouncedStateLeft = currentStateLeft;//update the debounced state
      
      //trigger an event
      if (debouncedStateLeft == HIGH){
        systemState = "Left";
        pos = pos+30;
        myservo.write(pos);
      }
    }
       if (currentStateRight != debouncedStateRight){//if the current state is still different than our last stored debounced state
      debouncedStateRight = currentStateRight;//update the debounced state
      
      //trigger an event
      if (debouncedStateRight == HIGH){
        systemState = "Right";
        pos = pos-30;
        myservo.write(pos);
      } 
    }
    }
  
  lastStateLeft = currentStateLeft;
  lastStateRight = currentStateRight;
}

