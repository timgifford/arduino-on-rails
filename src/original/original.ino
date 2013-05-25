#include <LocoNet.h>
#include <SerialLCD.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

lnMsg        *LnPacket;

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
 10 9 6 5  4  3  2 (pins)
*/

/*
LED Pin 11
*/

/* LocoNet board Wiring (http://www.scuba.net/wiki/index.php/LocoShield)
Ground goes to Ground, Vcc goes to a source of 5v power
TX goes to D7 on your Arduino, and
RX goes to pin D8
*/

// Connect keypad Arduino pins.
byte rowPins[ROWS] = { 10, 9, 6, 5 };
byte colPins[COLS] = { 4, 3, 2 };
Keypad keyPad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
  slcd.begin();
  slcd.backlight();
  
    // First initialize the LocoNet interface
  LocoNet.init();

  // Configure the serial port for 57600 baud
  Serial.begin(57600);
  Serial.println("LocoNet Monitor");
}

void loop(){
  
  
  receiveLocoNetMessage();
  
  char customKey = keyPad.getKey();
  
  if (customKey){
    if(isNumber(customKey)){
      slcd.backlight();
      slcd.print(customKey);
      
//      ( uint16_t Address, uint8_t Output, uint8_t Direction ) ;
      uint16_t Address = 1;
      uint8_t Output = 0;
      uint8_t Direction = 0;
      uint8_t output = 0;

      
      Serial.print("requestSwitch: ");
      Serial.print(Address);
      Serial.print(":");
      Serial.print(Direction);
      Serial.print(" - ");
      Serial.println(Output);
      LocoNet.requestSwitch(1,0,0);
      
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

void receiveLocoNetMessage(){
// Check for any received LocoNet packets
  LnPacket = LocoNet.receive() ;
  if( LnPacket )
  {
      // First print out the packet in HEX
    Serial.print("RX: ");
    uint8_t msgLen = getLnMsgSize(LnPacket); 
    for (uint8_t x = 0; x < msgLen; x++)
    {
      uint8_t val = LnPacket->data[x];
        // Print a leading 0 if less than 16 to make 2 HEX digits
      if(val < 16)
        Serial.print('0');
        
      Serial.print(val, HEX);
      Serial.print(' ');
    }
    
      // If this packet was not a Switch or Sensor Message then print a new line 
    if(!LocoNet.processSwitchSensorMessage(LnPacket))
      Serial.println();
  }
}

  // This call-back function is called from LocoNet.processSwitchSensorMessage
  // for all Switch Request messages
void notifySwitchRequest( uint16_t Address, uint8_t Output, uint8_t Direction )
{
  Serial.print("Switch Request: ");
  Serial.print(Address, DEC);
  Serial.print(':');
  Serial.print(Direction ? "Closed" : "Thrown");
  Serial.print(" - ");
  Serial.println(Output ? "On" : "Off");
}

  // This call-back function is called from LocoNet.processSwitchSensorMessage
  // for all Switch Report messages
void notifySwitchReport( uint16_t Address, uint8_t Output, uint8_t Direction )
{
  Serial.print("Switch Report: ");
  Serial.print(Address, DEC);
  Serial.print(':');
  Serial.print(Direction ? "Closed" : "Thrown");
  Serial.print(" - ");
  Serial.println(Output ? "On" : "Off");
}

  // This call-back function is called from LocoNet.processSwitchSensorMessage
  // for all Switch State messages
void notifySwitchState( uint16_t Address, uint8_t Output, uint8_t Direction )
{
  Serial.print("Switch State: ");
  Serial.print(Address, DEC);
  Serial.print(':');
  Serial.print(Direction ? "Closed" : "Thrown");
  Serial.print(" - ");
  Serial.println(Output ? "On" : "Off");
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

