#line 1 "original.ino"
// #include <LocoNet.h>
#include <SerialLCD.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

#include "Arduino.h"
void setup();
void loop();
boolean isNumber(char key);
boolean isClear(char key);
#line 6
SerialLCD slcd(11,12);//this is a must, assign soft serial pins

//Loconet Shield uses digital pins 7 & 8, GND above digital pin 13, 5Vo and GND pins

//this initiates the 7 pin-3x4 button numeric pad
const byte ROWS = 4;
const byte COLS = 3;

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

/*
  Wiring for Numberpad
  /--------1--2--3
  | /------4--5--6
  | | /----7--8--9
  | | | /--*--0--#
  | | | |  |  |  |
  | | | |  |  |  |
  | | | |  |  |  |
  | | | |  |  |  |
  8 7 6 5  4  3  2 (pins)
*/

// Connect keypad Arduino pins.
byte rowPins[ROWS] = { 8, 7, 6, 5 };
byte colPins[COLS] = { 4, 3, 2 };
Keypad keyPad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
  slcd.begin();
  slcd.backlight();
  // LocoNet.init()
}

void loop(){
  
  char customKey = keyPad.getKey();
  
  if (customKey){
    if(isNumber(customKey)){
      slcd.backlight();
      slcd.print(customKey);
    }
    else if(isClear(customKey)){
      slcd.clear();
    }
    else{
      slcd.noBacklight();
      slcd.clear();
    }  
  }
}

boolean isNumber(char key){
  return (key != '#' && key != '*');
}

boolean isClear(char key){
  return (key == '*');
}



//Route numbers are adjustable to allow infinite number of routes
// Routes "1" through "50" are left-bound routes  // lists all left-bound routes
// Routes "51" through "99" are right-bound routes  // lists all right-bound routes

//int LLBR //Last Left-Bound Routes
//int LRBR //Last Right-Bound Routes

//Would it be possible to have a default LLBR & LRBR ID and sent out at start up?
// recall the last left-bound and right-bound routes selected
//start by setting the default LLBR & LRBR?
//LCD screen recall and display last routes (top line left-bound, bottom line right-bound)
//"<-Route 00 Route 99->"
// the new route's line on LCD blinks text for 5 seconds before displaying as steady.
/*

//debounce button inputs
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;

setLoconetTurnout(turnout 1, Normal)

delay 0500 //this is to keep the power draw of the turnouts staggered

setLoconetTurnout(turnout 2, Normal)
delay 0500

setLoconetTurnout(turnout 3, Reverse)
delay 0500

setLoconetTurnout(turnout 4, Normal)
*/


