/* SevSeg Counter Example
 
 Copyright 2017 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object
SevSeg sevseg1; 
SevSeg sevseg2; 

int advancePin = 2; // pin to advance counter (advances on open circuit)
int clearPin = 3; // pin to clear counter (resets on closed circuit)

int advanceState;
int lastAdvanceState = LOW;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int dig0 = 0;
int dig1 = 0;
int dig2 = 0;

void setup() {

  pinMode(advancePin, INPUT_PULLUP); // internal pullup - when circuit to ground is closed pin reads low
  pinMode(clearPin, INPUT_PULLUP);   //                   on open circuit pin reads high
  
  byte numDigits = 1;
  byte digitPins[] = {10};
  byte segmentPins[] = {30, 28, 26, 24, 22, 32, 34};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(90);

  byte numDigits1 = 1;
  byte digitPins1[] = {11};
  byte segmentPins1[] = {48, 46, 44, 42, 40, 50, 52};
  bool resistorsOnSegments1 = true; // 'false' means resistors are on digit pins
  byte hardwareConfig1 = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays1 = false; // Default. Recommended
  bool leadingZeros1 = false; // Use 'true' if you'd like to keep the leading zeros
  
  sevseg1.begin(hardwareConfig1, numDigits1, digitPins1, segmentPins1, resistorsOnSegments1, updateWithDelays1, leadingZeros1);
  sevseg1.setBrightness(90);

  byte numDigits2 = 1;
  byte digitPins2[] = {12};
  byte segmentPins2[] = {49, 47, 45, 43, 41, 51, 53};
  bool resistorsOnSegments2 = true; // 'false' means resistors are on digit pins
  byte hardwareConfig2 = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays2 = false; // Default. Recommended
  bool leadingZeros2 = false; // Use 'true' if you'd like to keep the leading zeros
  
  sevseg2.begin(hardwareConfig2, numDigits2, digitPins2, segmentPins2, resistorsOnSegments2, updateWithDelays2, leadingZeros2);
  sevseg2.setBrightness(90);
}

void loop() {

  // read the state of the clear pin & reset if circuit is closed (low)
  int clear = digitalRead(clearPin);
  if (clear == LOW) {
    dig0 = 0;
    dig1 = 0;
    dig2 = 0;
  }

  // read the state of the switch into a local variable:
  int reading = digitalRead(advancePin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastAdvanceState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != advanceState) {
      advanceState = reading;

      // only advance counter if new state is high
      if (advanceState == HIGH) {
        dig0++;
        if (dig0 > 9) {
          dig0 = 0;
          dig1++;
          if (dig1 > 9) {
            dig1 = 0;
            dig2++;
            if (dig2 > 9) dig2 = 0;
          }
        }
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastAdvanceState:
  lastAdvanceState = reading;

  sevseg.setNumber(dig0, 0);
  //sevseg.blank();
  //sevseg.setChars("-");
  sevseg.refreshDisplay(); // Must run repeatedly

  sevseg1.setNumber(dig1, 0);
  //sevseg1.blank();
  //sevseg1.setChars("-");
  sevseg1.refreshDisplay(); // Must run repeatedly

  sevseg2.setNumber(dig2, 0);
  //sevseg2.blank();
  //sevseg2.setChars("-");
  sevseg2.refreshDisplay(); // Must run repeatedly
}

/// END ///
