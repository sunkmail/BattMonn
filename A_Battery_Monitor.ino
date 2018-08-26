/*   Intro
  Battery_Monitor.ino

  Controls
    Rotary Encoder with PB Switch - Most controls
    Momentary Switch - TBD - Change mode?
    Toggle Switch - Charge On/Off - Locks Voltage Setting
    LCD or OLED display for showing current mode/status & setting change info.







  The circuit:

  https://easyeda.com/editor#id=cd391fdaa1844334b64dbed0d9089972|cf2aac25675649f187dca4c7ea3dd5f3

    list the components attached to each input
    list the components attached to each output






  Created: 4 August 2018
  By Scott Mitten (Sunkmail)

  Modified: day month year
  By author's name
       create.arduino.cc/editor/Sunkmail/c23df1d6-b125-42d2-90a3-8b5a11351a9c
*/



/*
// HardWire - Version: Latest 
#include <HardWire.h>

// EnableInterrupt - Version: Latest 
#include <EnableInterrupt.h>

*/



// Wire - Version: Latest   // I2C Library
#include <Wire.h>           

// U8g2 - Version: Latest   // I2C Displays
#include <U8g2lib.h>
#include <U8x8lib.h>

/*
// DallasTemperature - Version: Latest 
#include <DallasTemperature.h>
#include <OneWire.h>
*/



/*
// EEPROMEx - Version: Latest 
#include <EEPROMVar.h>
#include <EEPROMex.h>
*/



const bool isDebug = true;              // Debug messages?
//bool isDebug = false;



const bool isTempSensorPresent = false;    // Is the Temp sensor installed

const bool isOLED = false;                // Is the OLED display attached



const bool ButtonActive = LOW;    // Pushbuttons are using pull-ups.  Signal is Low when active

// **************************************************************
// ************** Rotary Encoder Assignments ********************

const byte EncodeSW_PIN = 5;     // Push button switch on Rotary Encoder
const byte EncodeA_PIN = 3;      // HW Int1 - CLK signal from Rotary Encoder (Pin A) - Used for generating interrupts      
const byte EncodeB_PIN = 4;      // DT (data) signal from Rotary Encoder (Pin B) - Used for reading direction

const byte EncoderBounce = 5;       // Encoder Debounce time (max) in milliseconds
const byte SwBounce = 50;           // Encoder Debounce time (max) in milliseconds

volatile int virtualPosition = 80;   // Updated by the ISR (Interrupt Service Routine)






// **************************************************************
// ****************** Module Set-ups ****************************

// 0.91" OLED display module  128x32-------------------------------------------WORING IN THIS AREA -----------------------------------------------------------------
/* Constructor */    // U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C(rotation, [reset [, clock, data]])
U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C OLED(U8G2_R0);  // roation only setting due to HW I2C and not reset pin
bool updateDisplay_FLAG = true;              // Set initially true to do first display






// Temperature Sensor (DS18B20)   
const byte TempSense_PIN = A2;
/* Constructor */
  // OneWire oneWire(TempSense_PIN);           // Setup a oneWire instance to communicate with any OneWire devices  
                                          // (not just Maxim/Dallas temperature ICs)
  // DallasTemperature tempSensor(&oneWire);   // Pass our oneWire reference to Dallas Temperature Library. 



//const byte TempSensorCount = 1;           // How many sensors are we expecting      // not needed if only using 1
  // byte tempSensorAddr[8];                   // Variable to store device's uniquie ID
  // const byte TempSensorResolution = 9;      // Integer value for sensor precision.  Can be 9, 10, 11 or 12 bits
/*
          Mode	    Resol	  Conversion time
          9 bits	  0.5°C	    93.75 ms
          10 bits	  0.25°C  	187.5 ms
          11 bits	  0.125°C	  375 ms
          12 bits	  0.0625°C	750 ms
*/
const unsigned int TempSensorConvTime = 100;  // Time in ms to wait between request for temp conv. and read of temperature - Based on info above.
float currentTempC = 0.0;                 // Current Temperature in C




// **************************************************************
// ****************** General Assignments ***********************

const byte ModeSwitch_PIN = 12;          // Pin Assignment for Mode Switch

const unsigned int MaxModeChangFreq = (200);    // Min time between switching modes in ms

const byte ChargeOn_PIN = 13;

unsigned long currentMillis;      // Working/scratchpad variable for checking times

const byte VDischarge_PIN = A0;   // To Read voltage from Discharge Port of Battery Pack
const byte VCharge_PIN = A1;      // To Read voltage from Charger to Battery Pack



bool ChangeMode_FLAG = false;
byte packVoltage[] = {36,48,52,60,72};  // Pack Voltage Size options
byte voltageMode = 1;                   // Set default pack voltage to 48V

const byte OnOffSw_PIN = 8;       // Charge to Battery ON/OFF Switch  (Settings lock)
                                  // Cannot change mode/Pack Voltage when On



// ----------------------------------------------------------------------------
// DEBUG      DEBUG      DEBUG      DEBUG      DEBUG      DEBUG      DEBUG
// One size fits all Serial Monitor debugging messages
// ----------------------------------------------------------------------------
//bool isDebug = true;              // Debug messages?          Moved to top of code - easier to find
//bool isDebug = false;

template<typename T> void debugPrint(T printMe, bool newLine = false) {
	if (isDebug) {
		if (newLine) {
			Serial.println(printMe);
		}
		else {
			Serial.print(printMe);
		}
		Serial.flush();
	}
}






  
//   Below here is Sample loop Code - for Example only!!
/*
  // If the current rotary switch position has changed then update everything
  if (virtualPosition != lastCount) {

    // Write out to serial monitor the value and direction
    debugPrint(virtualPosition > lastCount ? "Up  :" : "Down:");
    debugPrint(virtualPosition,1);

    // Keep track of this new value
    lastCount = virtualPosition ;
  }
*/
void doNothing();       //spacer for code readability - compiler should ignore






// ------------------------------------------------------------------
// checkTemp     checkTemp     checkTemp     checkTemp
// ------------------------------------------------------------------
void checkTemp(){
  /*
  static unsigned long lastTempCheck = 0;                       // keep track of when last converstion started
  
  if(currentMillis - lastTempCheck > TempSensorConvTime){         // if the last read was more than conversion time: 
    currentTempC = tempSensor.getTempC(tempSensorAddr);           // Read Current Temperature in Degrees C 
    tempSensor.requestTemperaturesByAddress(tempSensorAddr);    // Send request for new temp conversion
    lastTempCheck = currentMillis;                                // reset timer reference for conversion
    updateDisplay_FLAG = true;                                       // Set flag to trigger display update
  }
  */
}


