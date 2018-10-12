



// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {
  static bool runStdby = true;    // Run Mode = 0, Standby mode = 1

  currentMillis = millis();     // Update current time for this loop

  checkRunProgSw();

  /*              // Change to make MODE output ON/Off override??
                  // Original Function now part of settings
  */


  if (SettingsMode_FLAG == true) {
    noInterrupts();
    virtualPositionSave = virtualPosition;        // Save the current virtual position from RUN mode
    ProgramSettings();                            // Enter the program settings menus
    virtualPosition = virtualPositionSave;        // Restore the virtual position for RUN mode
    interrupts();
  }
  else {
    checkEncoderButton();       // Poll Encoder Pushbutton   - Flag as needed

    checkModeButton();          // Check if run / Standby state change requested

    if (ChangeMode_FLAG == true) {  // If Mode change requested ...
      debugPrint("Run / Standby Toggle",1);
      runStdby = !runStdby;         // change mode
      ChangeMode_FLAG = false;     // Reset Flag
    }
//    debugPrint("Mode: (0 = RUN) ");
//    debugPrint(runStdby,1);

    if (encoderButton_FLAG == true) { // If encoder Button pushed while in Run mode
      monitorMode = !monitorMode;     // Toggle Monitor Vs Control Mode
      encoderButton_FLAG = false;     // Reset Flag
    }

    int VChargeRAW = analogRead(VCharge_PIN);
    VChargeInmV = VRawTOmV(VChargeRAW);
    debugPrint("VChargeRAW: ");
    debugPrint(VChargeRAW, 1);
    debugPrint("VChargeInmV: ");
    debugPrint(VChargeInmV, 1);
//    VCharge = mVToVolts(VChargeInmV);         // Convert mV readings to float V   -- Try to remove later - Processor heavy
    ChargePercent = calcBatteryPercent(VChargeInmV);          // Converts Voltage to integer (byte) showing Battery %
    debugPrint("Charge %: ");
    debugPrint(ChargePercent,1);
    

    if (isDischarge) {
      int VDischargeRAW = analogRead(VDischarge_PIN);
      VDischargeInmV = VRawTOmV(VDischargeRAW);
      debugPrint("VDischargeRAW: ");
      debugPrint(VDischargeRAW, 1);
      debugPrint("VDischargeInmV: ");
      debugPrint(VDischargeInmV, 1);
//      VDischarge = mVToVolts(VDischargeInmV);   // Convert mV readings to float V   -- Try to remove later - Processor heavy
      DischargePercent = calcBatteryPercent(VDischargeInmV);    // Converts Voltage to integer showing Battery %
    }

    if (isCurrent) {
      int IchargeRaw = analogRead(Icharge_PIN);                    // Read ADC value for charging current
      if (IchargeRaw < 512)
        IchargeRaw = 512;           // If sensor reading negative current, set to 0.
      //      debugPrint("IchargeRaw: ");
      //      debugPrint(IchargeRaw,1);
      IchargemA = map(IchargeRaw, 512, 1023, 0, (maxAmps * 1000));   // Convert to mA value - Module 0mA at mid range, 512.
      //      debugPrint("IchargemA: ");
      //      debugPrint(IchargemA,1);
    }

    if (isTempSensor) {          // If the temp sensor present
      //    checkTemp();                  // get current temp
    }


    //  if(updateDisplay_FLAG == true){
    updateDisplay();
    //  }


    if (runStdby == true) {                  // If in Standby Mode:
      digitalWrite(ChargeOn_PIN, LOW);        // output off
    }
    else {                                  // If in Run mode
      if (monitorMode == false) {                 // *****************************************  Add some sort of hysterysis to prevent cycling after initial charge attempt
        if (ChargePercent < virtualPosition) {
          digitalWrite(ChargeOn_PIN, HIGH);
        }
        else {
          digitalWrite(ChargeOn_PIN, LOW);
        }
      }
      else {                                    // If in Monitor Only mode
        digitalWrite(ChargeOn_PIN, HIGH);       // set output on - Let charger do it's thing
      }

    }

  }

}   // End Main Loop
