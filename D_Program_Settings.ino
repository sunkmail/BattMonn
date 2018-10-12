



void ProgramSettings(void) {
  noInterrupts();                 // Ensure Disable Interrupts

  settings1isDischarge();           // Is the Discharge Port connected for monitoring?

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    settings2PackVoltage();           // Set Pack Voltage

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    settings3();

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    settings4();

  noInterrupts();
}



void settings1isDischarge() {

  virtualPosition = isDischarge;  // Set Virtual position to current Discharge connect Setting

  interrupts();                 // Re-enable Interrupts
  while (encoderButton_FLAG == false) {
    checkEncoderButton();

    if (virtualPosition > true) {
      virtualPosition = true;
    }
    isDischarge = virtualPosition;        // Set the new value of voltageMode (Is reading the battery output (discharge) port available)
    settingsDisplay(1);       // update display with appropriate settings screen

    currentMillis = millis();     // Update current time for this loop

  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  isDischarge = virtualPosition;        // Ensure the new (final) value of voltageMode is set
  encoderButton_FLAG = false;           // Reset Encoder Flag
}


void settings2PackVoltage() {

  virtualPosition = voltageMode;  // Set Virtual position to current Pack Voltage Setting
  //  debugPrint(sizeof(packVoltage), 1);

  interrupts();                 // Re-enable Interrupts
  while (encoderButton_FLAG == false) {
    checkEncoderButton();

    if (virtualPosition >= sizeof(packVoltage)) {       // If the current setting is higher than # of elements ...
      virtualPosition = (sizeof(packVoltage) - 1);      // Set to highest element
    }

    voltageMode = virtualPosition;        // Update value of voltageMode

    /*    debugPrint("virtualPosition: ");
        debugPrint(virtualPosition, 1);
        debugPrint("voltageMode: ");
        debugPrint(voltageMode, 1);
        debugPrint("packVoltage: ");
        debugPrint(packVoltage[voltageMode], 1);
    */
    settingsDisplay(2);       // update display with appropriate settings screen

    currentMillis = millis();     // Update current time for this loop

  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  debugPrint("Exit Settings 2, step 1", 1);
  voltageMode = virtualPosition;        // ensure newest value of voltageMode
  encoderButton_FLAG = false;           // Reset Encoder Flag
}








void settings3() {

}


void settings4() {

}
