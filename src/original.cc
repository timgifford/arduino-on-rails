// #include <LocoNet.h>
#include <SerialLCD.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

SerialLCD slcd(11,12);//this is a must, assign soft serial pins

//Loconet Shield uses digital pins 7 & 8, GND above digital pin 13, 5Vo and GND pins

//Variables
//this initiates the 7 pin-3x4 button numeric pad
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 2, 3, 4, 5 };

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 8, 7, 6 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Route numbers are adjustable to allow infinite number of routes
// Routes "1" through "50" are left-bound routes  // lists all left-bound routes
// Routes "51" through "99" are right-bound routes  // lists all right-bound routes

int LLBR //Last Left-Bound Routes
int LRBR //Last Right-Bound Routes

//Would it be possible to have a default LLBR & LRBR ID and sent out at start up?
int LCDCState  = LOW;    //sets current state of LCD Backlight to Off
long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup(){
  slcd.begin();   //initials LCD screen
  slcd.noBacklight();   //Starts LCD backlight as off
  slcd.print("Welcome");
  delay(5000);
  // LocoNet.init()
}

void loop(){
  if (LCDLState == LOW)
  {
    LCDLState = HIGH;
  }
  else if (LCDLState = HIGH)
  {
    LCDLState = LOW;
  };
  slcd.print("Yard Name"); //LCD screen "Yard Name" display 10 seconds
  delay (10000);
}
// recall the last left-bound and right-bound routes selected
//start by setting the default LLBR & LRBR?
//LCD screen recall and display last routes (top line left-bound, bottom line right-bound)
//"<-Route 00 Route 99->"
// the new route's line on LCD blinks text for 5 seconds before displaying as steady.

/*
{
 slcd.noDisplay();  // Turn off the display:
  delay(500);
  slcd.display();   // Turn on the display:
  delay(500);
 slcd.noDisplay();  // Turn off the display:
  delay(500);
  slcd.display();   // Turn on the display:
  delay(500);
 slcd.noDisplay();  // Turn off the display:
  delay(500);
  slcd.display();   // Turn on the display:
  delay(500);
 slcd.noDisplay();  // Turn off the display:
  delay(500);
  slcd.display();   // Turn on the display:
  delay(500);
 slcd.noDisplay();  // Turn off the display:
  delay(500);
  slcd.display();   // Turn on the display:
}

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
