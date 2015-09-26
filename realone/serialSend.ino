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


// ---------------------Main Methods--------------------- //
// Note that Arduino both defines main() and makes function prototypes for us

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pcSer.begin(PC_BAUD);
}

void loop() {
  if (isRunning) {
    currTime = micros();
    
    timeSinceLast = currTime - prevTime;
    timeInSeconds = currTime/1000000.0;
    Serial.println()
    sendValues(timeSinceLast, currTime, timeInSeconds);
    delayMicroseconds(random(1000));
    
    if (timeInSeconds > 1) {
      isRunning = false;
      pcSer.println("This means we're going to stop sending data now.");
    }
    
    prevTime = currTime;
  } else {
    digitalWrite(LED, HIGH); // turn on LED when we stop running
  }
  
}

// ---------------------Sub Methods---------------------- //

void sendValues(signed long int signedInt, unsigned long long int Int, float Float) {
  pcSer.print(signedInt);
  pcSer.print(", ");
  pcSer.print((uint32_t) (Int >> 32), HEX); // send bigger 4 bytes
  pcSer.print((uint32_t) Int, HEX); // send littler 4 bytes
  pcSer.print(", ");
  pcSer.println(Float, 6); // make sure to print lots of digits for your floats to get max precision!
}
