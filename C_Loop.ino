



// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {
  static bool ok2Charge = true;

  currentMillis = millis();     // Update current time for this loop

  checkRunProgSw();

  if (SettingsMode_FLAG == true) {
    runStdby = true;                              // Set to standby
    chargerOff();                                 // Turn off charger when changing settings
    noInterrupts();
    virtualPositionSave = virtualPosition;        // Save the current virtual position from RUN mode
    ProgramSettings();                            // Enter the program settings menus
    virtualPosition = virtualPositionSave;        // Restore the virtual position for RUN mode
    interrupts();
  }
  else {        // NOT in settings mode
    checkEncoderButton();       // Poll Encoder Pushbutton   - Flag as needed

    checkModeButton();          // Check if run / Standby state change requested

    if (ChangeMode_FLAG == true) {  // If Mode change requested ...
      debugPrint("Run / Standby Toggle", 1);
      runStdby = !runStdby;         // change mode
      ok2Charge = true;             // if button pressed to change mode, it can't be due to maint mode on/standby, Therefore reset.
//      debugPrint("ok2Charge: True", 1);
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
    /*        debugPrint("VCharge RAW: ");
            debugPrint(VChargeRAW, 1);
            debugPrint("VCharge mV : ");
            debugPrint(VChargeInmV, 1);
    */
    /*
        if (VChargeRAW != 0) {
          debugPrint("VCharge RAW: ");
          debugPrint(VChargeRAW);
          debugPrint("  VCharge mV : ");
          debugPrint(VChargeInmV, 1);
        }
    */

    ChargePercent = calcBatteryPercent(VChargeInmV);          // Converts Voltage to integer (byte) showing Battery %
    //    debugPrint("Charge %: ");
    //    debugPrint(ChargePercent,1);


    if (isDischarge) {
      int VDischargeRAW = analogRead(VDischarge_PIN);
      //      VDischargeRAW = analogRead(VDischarge_PIN);         // Double read to try to improve stability
      VDischargeInmV = VRawTOmV(VDischargeRAW);
      /*
            debugPrint("                 VBatt RAW: ");
            debugPrint(VDischargeRAW, 1);
            debugPrint("                 VBatt mV:  ");
            debugPrint(VDischargeInmV, 1);
      */

      /*
            if (VDischargeRAW != 0) {
              debugPrint("                 VBatt RAW: ");
              debugPrint(VDischargeRAW, 1);
              debugPrint("                 VBatt mV:  ");
              debugPrint(VDischargeInmV, 1);
            }
      */
      DischargePercent = calcBatteryPercent(VDischargeInmV);    // Converts Voltage to integer showing Battery %
    }

    if (runStdby == false) {                  // If in Run Mode:
      if (isCurrent) {                          // & current measurement module installed
        unsigned int IchargeRaw = analogRead(Icharge_PIN);                    // Read ADC value for charging current

        //        debugPrint("                                  Icharge Raw: ");
        //        debugPrint(IchargeRaw,1);

        if (IchargeRaw < 512)
          IchargeRaw = 512;                          // If sensor reading negative current, set to 0A.

        IchargeRaw += iFudge;           // Add a fudge factor on raw value

        if (maxAmps == 5)
          IchargemA = (((map(IchargeRaw, 0, 1023, 0, 5000) - 2500) * mAper10mV5) / 10);

        else if (maxAmps == 20) {
          //          debugPrint((map(IchargeRaw, 512, 1023, 2500, 5000)-2500), 1);
          IchargemA = (((map(IchargeRaw, 512, 1023, 2500, 5000) - 2500) * mAper10mV20) / 10); // Convert Raw to mV, then subtract 2.5V module offset - Then, multiply by mA/mV constant
        }                                                             // mV * (mA/mV) = total mAs


        else if (maxAmps == 30)
          IchargemA = (((map(IchargeRaw, 0, 1023, 0, 5000) - 2500) * mAper10mV30) / 10);

        if (IchargeRaw == (512 + iFudge))    // IF 0 current, make sure set to zero
          IchargemA = 0;

        /*
                if (IchargemA != 0) {
                  debugPrint("                                  Icharge Raw: ");
                  debugPrint(IchargeRaw, 1);
                  debugPrint("                                  Icharge mA:  ");
                  debugPrint(IchargemA, 1);
                }
        */
      }
    }


    ///  Define controlling voltage based on settings

    if ((controlVoltage == 1) && (isDischarge == true)) {     // If controlling voltage is from the Battery & battery voltage turned on
      if (DischargePercent >= 1)                              // Ensure Batt Batt % is atleast 1 %  (in case battery not connected)
        controlPercent = DischargePercent;
      else {
        controlPercent = ChargePercent;                       // if not, default back to charger voltage
        DischargePercent = 222;                                 // & set Batt % to 222 as flag for battery voltage error
      }
    }
    else                                                      // If controlling voltage is from the charger, OR battery voltage not turned on
      controlPercent = ChargePercent;

    ////////////////////////////////////////////////////////////
    //       For testing only - Delete after testing          //
 //   controlPercent = 77;                                      //
    ////////////////////////////////////////////////////////////

    //  if(updateDisplay_FLAG == true){
    updateDisplay();
    //  }




    // Control charger On/Off

    if (runStdby == true) {                  // If in Standby Mode:
      chargerOff();                         // Turn off Charger - we're in Standby, duh
    }
    else {                                  // If in Run mode
      if (monitorMode == true) {           // And monitor mode
        chargerOn();     // Turn on the charger - Let it control itself
      }
      else {                       // If in Run Mode & active control
        if (runOnce == true) {
          if (controlPercent <= virtualPosition) {   // If charge is less than target
            chargerOn();     // Turn on the charger
          }
          else {            // Charge above target - ie. done one charge
            runStdby = true;                      // Return back to standby mode
            chargerOff();                         // Turn off Charger
          }
        }         // End if:  (RunOnce == true)


        else {                      // runOnce != true, ie Maint. Mode

          if (controlPercent < (virtualPosition - Hysteresis)) {   // if outside Hyst. area
            //                                                          NOTE: if using static Charge% for testing, operation revered to actual

            if(ok2Charge == false){
              debugPrint("ok2Charge: 1",1);
            }
            
            ok2Charge = true;                                       // reset pause flag

 //           debugPrint("Only Display if hyst. amount lower than current % ", 1);
            //            debugPrint(" hyst ok2Charge: ");
            //            debugPrint(ok2Charge, 1);
          }


          // Control output area

//          debugPrint("  1  ok2Charge: ");
//          debugPrint(ok2Charge, 1);

          if ((controlPercent < virtualPosition) && (ok2Charge == true)) {   // If charge is less than target & its ok 2 charge

            chargerOn();                          // Turn on the charger
//            debugPrint("  2  ok2Charge: ");
//            debugPrint(ok2Charge, 1);
          }
          else if (controlPercent >= virtualPosition) {                        // else - If already charged enough
            chargerOff();                         // Turn off Charger
            
            if(ok2Charge == true){
              debugPrint("ok2Charge: 0",1);
            }
               
            ok2Charge = false;                   // Set flag for hyst. loop, if not already set

//            debugPrint("  3   ok2Charge: ");
//            debugPrint(ok2Charge, 1);
          }
          else {                                          // During hysteresis period
            chargerOff();                         // Turn off Charger
            /*
                        if (ok2Charge != false) {
                          debugPrint("     ok2Charge: ");
                          debugPrint(!ok2Charge, 1);
                        }
            */
            //            ok2Charge = false;                   // Set flag for next loop, if not already set
            //            debugPrint("  3   ok2Charge: ");
            //            debugPrint(ok2Charge, 1);

          }

        }           // end else for:   if (runOnce == true). ie, in Maint mode


      }           // end else, equal to:  // If in Run Mode & active control


    }
  }

}   // End Main Loop

void chargerOn(void) {
  if (digitalRead(ChargeOn_PIN) == false)     // If pin was off before this:
    debugPrint("Charger: ON", 1);                 // debug  notice of pin change
  digitalWrite(ChargeOn_PIN, HIGH);     // Turn on the charger
}

void chargerOff(void) {
  if (digitalRead(ChargeOn_PIN) == true)         // If pin was ON before this:
    debugPrint("Charger: OFF", 1);              // debug  notice of pin change
  digitalWrite(ChargeOn_PIN, LOW);        // Turn off Charger

}
