


const bool isDebug = true;              // Debug messages?
//const bool isDebug = false;

/*   Intro
  Battery_Monitor.ino

  Controls
    Rotary Encoder with PB Switch - Most controls
    Momentary Switch - run / Standby switch
    Toggle Switch - Program Settings Vs Run
    OLED display for showing current mode/status & setting change info.


To DO:

    Settings menu:
      - Battery Vs Charger Voltage to control Mosfet
          - made smart ... if battery voltage below charger, use charger, or give error and stop
          - in place
          - NOT tested yet
          
      - Hysterysis for charge
            - in place
            - NOT tested yet
    
    - Add check for overvoltage 
          - if vRaw is 1023, the pack voltage setting is too low
          - IIf that is the case - do not allow charge
          - provide error message  (Check Pack Voltage)??

    - If in monitor mode - don't change OR display target

    - Store settings into EEMPROM for next cycle

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


// Wire - Version: Latest   // I2C Library
#include <Wire.h>           

// U8g2 - Version: Latest   // I2C Displays
#include <U8g2lib.h>
#include <U8x8lib.h>


/*
// EEPROMEx - Version: Latest 
#include <EEPROMVar.h>
#include <EEPROMex.h>
*/


const bool isDisplay128x32 = true;

bool isDischarge = true;                 // Is the discharge port Voltage monitoring present - User changable

const bool isCurrent = true;             // Is a current sensor present?

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const byte maxAmps = 20;                   // Max Amps module can mesure  (5, 20, 30)



const bool ButtonActive = LOW;    // Pushbuttons are using pull-ups.  Signal is Low when active

// **************************************************************
// ************** Rotary Encoder Assignments ********************


const byte EncodeA_PIN = 3;      // HW Int1 - CLK signal from Rotary Encoder (Pin A) - Used for generating interrupts      
const byte EncodeB_PIN = 4;      // DT (data) signal from Rotary Encoder (Pin B) - Used for reading direction
const byte EncodeSW_PIN = 5;     // Push button switch on Rotary Encoder

const byte EncoderBounce = 5;       // Encoder Debounce time (max) in milliseconds
const byte SwBounce = 50;           // Encoder Debounce time (max) in milliseconds

volatile byte virtualPosition = 80;   // Updated by the ISR (Interrupt Service Routine)
byte virtualPositionSave = 80;        // Place to save position for moving through various settings





// **************************************************************
// ****************** Module Set-ups ****************************

// 0.91" OLED display module  128x32
/* Constructor */    // U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C(rotation, [reset [, clock, data]])
U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C OLED(U8G2_R0);  // roation only setting due to HW I2C and not reset pin


// **************************************************************
// ****************** General Assignments ***********************

const byte ModeSwitch_PIN = 12;          // Pin Assignment for Mode Switch

const unsigned int MaxModeChangFreq = (200);    // Min time between switching modes in ms

const byte ChargeOn_PIN = 13;

unsigned long currentMillis;      // Working/scratchpad variable for checking times

const byte VDischarge_PIN = A0;   // To Read voltage from Discharge Port of Battery Pack
const byte VCharge_PIN = A1;      // To Read voltage from Charger to Battery Pack
const byte Icharge_PIN = A2;      // To read current from module


bool ChangeMode_FLAG = false;
byte packVoltage[] = {36,48,52,60,72};  // Pack Voltage Size options
byte voltageMode = 1;                   // Set default pack voltage to 48V

//const unsigned long MaxVRange = 85;              // max Voltage device designed for / expecting
const unsigned long MaxmVRange = 85000;         // max Voltage device designed for / expecting in mV

const byte RunProgSw_PIN = 8;       // Run Vs Program mode Switch  (Settings lock)
                                  // Cannot change mode/Pack Voltage when On


bool controlVoltage = 1;          // determines controlling voltage -> 0 = Charger, 1 = Battery Output

byte controlPercent = 0;          // Contolling percentage for controlling on/off of charger

byte Hysteresis = 5;             // Percent of charge between going to standby and starting up charging again in Maintenance mode
const byte minHysteresis = 3;    // Set a min Hysteresis value - Percent of Charge
const byte maxHysteresis = 15;    // Set a max Hysteresis value - Percent of Charge

// **************************************************************
// ****************** Global Variables **************************

bool SettingsMode_FLAG = false;
bool encoderButton_FLAG = false;
bool monitorMode = false;            // Default to monitoring mode (Not actively charging at power-up)

unsigned long VChargeInmV = 0;
byte ChargePercent = 0;

unsigned long VDischargeInmV = 0;
byte DischargePercent = 0;

unsigned long IchargemA = 0;                  // Charging Current in mA
                                     // From Datasheet:
const byte mAper10mV30 = 151;            // 66 mV/A -> 1000mA/66mV = 15.15 mA/mV = 151 mA/10mV
const byte mAper10mV20 = 100;          // 100mV/A = 100mV/1000mA -> inverted = 1000mA/100mV = 10 mA/mV = 100mA/10mV
const byte mAper10mV5 = 54;            // 185mV/A -> 1000mA/185mV = 5.4 mA/mV = 54 mA/10mV

const int iFudge = 1;                 // Fudge Factor for current measurement


bool runStdby = true;    // Run Mode = 0, Standby mode = 1

bool runOnce = false;    // Run once Vs Maintenance Modes



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

