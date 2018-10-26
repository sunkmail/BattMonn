



void ProgramSettings(void) {
  noInterrupts();                 // Ensure Disable Interrupts

  settings0();              // Setting Menu 0 - Run Mode - Run Once Vs Maintenance Mode

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    settings1();           // Setting Menu 1 - Is the Discharge Port connected for monitoring?

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    settings2();           // Setting Menu 2 - Set Pack Voltage

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    if (isDischarge == true)      //  AND is the battery ourput monitoring active?
      settings3();                    // Setting Menu 3 - What is the controlling voltage?

  checkRunProgSw();
  if (SettingsMode_FLAG == true)   // If setting mode switch has NOT been moved to run
    settings4();                      // Setting Menu 4 - Hysteresis for Maintanence mode

  noInterrupts();
}


void settings0(void) {           // Settings:  Run Mode - Once or Maintenancevv

  virtualPosition = runOnce;  // Set Virtual position to current Run Mode Setting

  interrupts();                 // Re-enable Interrupts
  while (encoderButton_FLAG == false) {
    checkEncoderButton();

    if (virtualPosition > true) {
      virtualPosition = true;
    }
    runOnce = virtualPosition;        // Set the new value of runOnce
    settingsDisplay(0);               // update display with appropriate settings screen

    currentMillis = millis();     // Update current time for this loop

  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  runOnce = virtualPosition;        // Ensure the new (final) value of voltageMode is set
  encoderButton_FLAG = false;           // Reset Encoder Flag
}


void settings1(void) {           // Settings:  Is the Battery output being monitored

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


void settings2(void) {         // Settings:  What is the Pack voltage

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





void settings3(void) {            // What is the controlling voltage
  // Only Available if Battery Output being monitored

  virtualPosition = controlVoltage;  // Set Virtual position to current Controlling Voltage source

  interrupts();                 // Re-enable Interrupts
  while (encoderButton_FLAG == false) {
    checkEncoderButton();

    if (virtualPosition > true) {
      virtualPosition = true;
    }
    controlVoltage = virtualPosition;        // Set the new value of voltageMode (Is reading the battery output (discharge) port available)
    settingsDisplay(3);       // update display with appropriate settings screen

    currentMillis = millis();     // Update current time for this loop

  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  controlVoltage = virtualPosition;        // Ensure the new (final) value of voltageMode is set
  encoderButton_FLAG = false;           // Reset Encoder Flag
}


void settings4(void) {            // Hysteresis for Maintanence mode - if used

  virtualPosition = Hysteresis;  // Set Virtual position to current vHysteresis Setting

  interrupts();                 // Re-enable Interrupts
  while (encoderButton_FLAG == false) {
    checkEncoderButton();

    if (virtualPosition <= minHysteresis) {       // If the current setting is lower than min value ...
      virtualPosition = minHysteresis;      // Set to min value
    }
    if (virtualPosition >= maxHysteresis) {       // If the current setting is higher than max value ...
      virtualPosition = maxHysteresis;      // Set to max value
    }

    Hysteresis = virtualPosition;        // Update value of Hysteresis

    settingsDisplay(4);       // update display with appropriate settings screen

    currentMillis = millis();     // Update current time for this loop

  }   // Once Encoder Button pushed to confirm setting, move on.
  noInterrupts();                       // Disable interrupts to not corrupt data while moving info
  debugPrint("Exit Settings 2, step 1", 1);
  Hysteresis = virtualPosition;        // ensure newest value of vHysteresis
  encoderButton_FLAG = false;           // Reset Encoder Flag
}
