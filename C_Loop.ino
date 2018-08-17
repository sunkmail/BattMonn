



// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {
  
  currentMillis = millis();     // Update current time for this loop
  
  checkRunProgSw();
  
  /*              // Change to make output ON/Off override??
                  // Original Function now part of settings
                  
  checkModeButton();            // Poll the Mode Switch once per loop  - Flag as needed
  
    if (ChangeMode_FLAG == true){
      voltageMode = voltageMode + 1;                  // Move to next voltage range
      if(voltageMode > 4){                            // Return to first value if out of range
        voltageMode = 0;
      }
      ChangeMode_FLAG = false;        // Reset mode button flag
    }
*/
  
  if (digitalRead(RunProgSw_PIN) == ButtonActive)  // If the Run/Progam Switch is in Program ... 
    SettingsMode_FLAG = true;
  else SettingsMode_FLAG = false;
  
  
  if(SettingsMode_FLAG == true){
    noInterrupts();
    virtualPositionSave = virtualPosition;        // Save the current virtual position from RUN mode
    ProgramSettings();                            // Enter the program settings menus
    virtualPosition = virtualPositionSave;        // Restore the virtual position for RUN mode
    interrupts();
  }
  else{  
    checkEncoderButton();       // Poll Encoder Pushbutton   - Flag as needed 
    
    if(encoderButton_FLAG == true){   // If encoder Button pushed while in Run mode
      monitorMode = !monitorMode;     // Toggle Monitor Vs Control Mode
      encoderButton_FLAG = false;     // Reset Flag
    }
    
    int VChargeRAW = digitalRead(VCharge_PIN);
    VChargeInmV = VRawTOmV(VChargeRAW);  
    VCharge = mVToVolts(VChargeInmV);         // Convert mV readings to float V   -- Try to remove later - Processor heavy  
    ChargePercent = calcBatteryPercent(VChargeInmV);          // Converts Voltage to integer showing Battery % 
    
    if(isDischarge){
      int VDischargeRAW = digitalRead(VDischarge_PIN);
      VDischargeInmV = VRawTOmV(VDischargeRAW);
      VDischarge = mVToVolts(VDischargeInmV);   // Convert mV readings to float V   -- Try to remove later - Processor heavy
      DischargePercent = calcBatteryPercent(VDischargeInmV);    // Converts Voltage to integer showing Battery % 
    } 
  
    if(isCurrent){
      int IchargeRaw = digitalRead(Icharge_PIN);                    // Read ADC value for charging current
     // int IchargemA = IchargeRaw* SOMETHING TBD                   // Convert to mA value
    }
  
    if(isTempSensor){            // If the temp sensor present
  //    checkTemp();                  // get current temp
    }

  
  //  if(updateDisplay_FLAG == true){ 
      updateDisplay();
  //  }
  
    if(monitorMode == false){                   // *****************************************  Add some sort of hysterysis to prevent cycling after initial charge attempt
      if(ChargePercent < virtualPosition)
        digitalWrite(chargeOn_PIN, HIGH);
      else
        digitalWrite(chargeOn_PIN, LOW);
  }
  
  }
  
}   // End Main Loop
