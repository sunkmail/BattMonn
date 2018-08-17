



void ProgramSettings(void){
  noInterrupts();                 // Ensure Disable Interrupts

  settings1isDischarge();           // Is the Discharge Port connected for monitoring?
  
  checkRunProgSw();
  if(SettingsMode_FLAG == false)    // If setting mode switch has NOT been moved to run
    settings2PackVoltage();           // Set Pack Voltage
    
  checkRunProgSw();
  if(SettingsMode_FLAG == false)    // If setting mode switch has NOT been moved to run
    settings3();
    
  checkRunProgSw();
  if(SettingsMode_FLAG == false)    // If setting mode switch has NOT been moved to run
      settings4();
      
  noInterrupts();
}



void settings1isDischarge(){
  
  virtualPosition = isDischarge;  // Set Virtual position to current Discharge connect Setting
  
  interrupts();                 // Re-enable Interrupts
  while(encoderButton_FLAG == false){
    checkEncoderButton();
    
    if(virtualPosition > true){
      virtualPosition = true;
    }
    settingsDisplay(1);       // update display with appropriate settings screen
    
  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  isDischarge = virtualPosition;        // Set the new value of voltageMode
  encoderButton_FLAG = false;           // Reset Encoder Flag
}


void settings2PackVoltage(){
  
  virtualPosition = voltageMode;  // Set Virtual position to current Pack Voltage Setting
  
  interrupts();                 // Re-enable Interrupts
  while(encoderButton_FLAG == false){
    checkEncoderButton();
    
    if(virtualPosition > sizeof(packVoltage)){
      virtualPosition = sizeof(packVoltage);
    }
    settingsDisplay(2);       // update display with appropriate settings screen
    
  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  voltageMode = virtualPosition;        // Set the new value of voltageMode
  encoderButton_FLAG = false;           // Reset Encoder Flag
}








void settings3(){
  
}


void settings4(){
  
}
