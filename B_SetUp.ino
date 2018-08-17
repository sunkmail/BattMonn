

// ------------------------------------------------------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------------------------------------------------------
void setup() {
  // Just for debug, view output on serial monitor -
  if(isDebug)
    Serial.begin(9600);       // Only open Serial comms if in Debug mode


  // **************************************************************
  // **************** Rotary Encoder Setup ************************  
  
  pinMode(EncodeSW_PIN, INPUT_PULLUP);      // Switch is floating - use the in-built PULLUP so we don't need a resistor
  
  pinMode(EncodeA_PIN, INPUT_PULLUP);       // Rotary pulses are INPUTs - Possibly floating if not using module board.  (Extra Pull up shouldn't hurt, even if using module board.)
  pinMode(EncodeB_PIN, INPUT_PULLUP);


  // **************************************************************
  // ****************** Other Pin Setups **************************  

  pinMode(ModeSwitch_PIN, INPUT_PULLUP);   // Mode Switch - Internal Pull-up for push button
  pinMode(RunProgSw_PIN, INPUT_PULLUP);     // Charge ON/Off - Locks Pack voltage setting
  
  pinMode(TempSense_PIN, INPUT);  
  
  digitalWrite(chargeOn_PIN, false);      // Default Charger state to off.
  pinMode(chargeOn_PIN, OUTPUT);          // charger on = Mosfet activation
  
  
  pinMode(VCharge_PIN, INPUT);            // Analog input for Charge voltage
  pinMode(VDischarge_PIN, INPUT);         // Analog input from discharge port
  pinMode(Icharge_PIN, INPUT);            // Analog input for current measurement
  

  
  
  // **************************************************************
  // ********************** Misc Setup ****************************
  
  // 0.91" OLED display module  128x32
  OLED.begin();                             // Start the OLED display Object/Library
//  OLED.setFont(u8g2_font_logisoso32_tr);    // Set the (initial?) font for 32 Pixel high
//  OLED.setCursor(0,32);                     // Set cursor to prepare for first write

  // Temperature Sensor (DS18B20)
/*  
  if(isTempSensorPresent){                              // If Temp sensor present:
    tempSensor.begin();                                 // Start the Library
    tempSensor.getAddress(tempSensorAddr, 0);           // Get addrress for device at index 0  (only sensor, no loop needed)
                                                        // Addresses used as faster than doing by index.

    tempSensor.setResolution(tempSensorAddr, TempSensorResolution);     // Set resolution of temp sensor
    tempSensor.setWaitForConversion(false);             // Put into Async. Mode
    // tempSensor.setCheckForConversion(true);             // Program will look for flag that conversion complete    //NOT ACTUALLY SURE what this setting does.  Will just track millis
    tempSensor.requestTemperaturesByAddress(tempSensorAddr);    // Send request for current temp - To get initial value going
  }
  
    // Attach the routines to service the interrupts
  attachInterrupt(digitalPinToInterrupt(EncodeA_PIN), isr_EncoderKnob, LOW);            //Move to sub-routine that changes LED values, updates settings,wakes up backlight, etc)
                                                                        // Here just for initial testing of encoder - Or adjust to turn on Backlight of display ??

*/  
  delay(100);         // Let everything settle for 100 ms on boot-up
  
  // Ready to go!
  debugPrint("Setup finished successfully.",1);

}
