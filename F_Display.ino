/*
  Display(s) being used:
        0.91" OLED display module  128x32

  Possible alternative for future expansion
        0.96" OLED display module  128x64


  http://4umi.com/web/javascript/xbm.php   - For making custom characters
*/

// Custom Character - Left Arrow//

const byte custH = 5;
const byte custW = 8;
static const unsigned char lArrowBits[] = {
  B00001000,
  B00001110,
  B11111111,
  B00001110,
  B00001000,
};

// Custom Character - Right Arrow//
static const unsigned char rArrowBits[] = {
  B00010000,
  B01110000,
  B11111111,
  B01110000,
  B00010000,
};

// Custom Character - Maint. Mode Logo//
const byte custMaintH = 10;
const byte custMaintW = 9;
static const unsigned char custMaintBits[] = {
  0x0e, 0x00,
  0x0c, 0x00,
  0x4a, 0x00,
  0x81, 0x00,
  0x01, 0x01,
  0x01, 0x01,
  0x02, 0x01,
  0xa4, 0x00,
  0x60, 0x00,
  0xe0, 0x00
};

const byte custHystH = 11;
static const unsigned char custHystBits[] = {
  0x18, 0x00,
  0x3c, 0x00,
  0x7e, 0x00,
  0x18, 0x00,
  0x18, 0x00,
  0x18, 0x00,
  0x18, 0x00,
  0x00, 0x00,
  0x66, 0x00,
  0x99, 0x00,
  0x66, 0x00
};

// Custom Character - Run Once Mode Logo//
static const unsigned char custRunOnceBits[] = {
  0x04, 0x00,
  0x0e, 0x00,
  0x1f, 0x00,
  0x84, 0x00,
  0xc4, 0x00,
  0xa4, 0x00,
  0x84, 0x00,
  0x84, 0x00,
  0x84, 0x00,
  0xe4, 0x01
};



// Custom Character - Run/charge active Logo//

const byte custRunH = 11;
const byte custRunW = 10;
static const unsigned char custRunBits[] = {
  0xc0, 0x00,
  0xaf, 0x00,
  0xe0, 0x00,
  0x47, 0x00,
  0x40, 0x02,
  0xe0, 0x01,
  0x58, 0x00,
  0xc0, 0x00,
  0xa7, 0x00,
  0x20, 0x01,
  0x10, 0x01
};

// ------------------------------------------------------------------
// settingsDisplay     settingsDisplay     settingsDisplay     settingsDisplay
// ------------------------------------------------------------------

void settingsDisplay(byte Page) {

  const byte _arrowX = 7;
  const byte _arrowY = 16;
  const byte _settingX = 17;
  const byte _settingY = 22;

  OLED.firstPage();
  do {
    /* all graphics commands have to appear within the loop body. */
    OLED.setFont(u8g2_font_5x7_mr);         // Set a font for 6 Pixel high
    OLED.setCursor(0, 31);                    // Set cursor to prepare for write
    OLED.print("Adjust or Press to accept");

    OLED.setCursor(40, 06);                    // Set cursor to prepare for write
    OLED.print("SETTING: ");
    OLED.setCursor(0, 13);                    // Set cursor to prepare for write

    switch (Page) {

      case 0:     // runOnce    - Run Mode Select
        OLED.print("Run Mode:");

        OLED.drawXBM(_arrowX, _arrowY, custW, custH, rArrowBits);  //Print custom custom Right arrow Glyph
        OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
        OLED.setCursor(_settingX, _settingY);                    // Set cursor to prepare for write
        if (runOnce == true)
          OLED.print("Charge Once Only");
        else
          OLED.print("Maintenance Charge");
        break;


      case 1:     // isDischarge    - Monitoring the Battery Output voltage
        //OLED.print("Monitor Discharge Port:");
        OLED.print("Monitor Battery Output:");

        OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
        OLED.setCursor(10, 21);                    // Set cursor to prepare for write
        if (isDischarge == true)
          OLED.print("Yes");
        else
          OLED.print("No");
        break;

      case 2:      // PackVoltage
        OLED.print("Pack Voltage");

        OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
        OLED.setCursor(10, 21);                    // Set cursor to prepare for write
        OLED.print(packVoltage[voltageMode]);
        OLED.print("V");
        break;


      case 3:     // Controlling Voltage
        OLED.print("Controlling Voltage");

        OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
        OLED.setCursor(10, 21);                    // Set cursor to prepare for write
        if (controlVoltage == 0)
          OLED.print("Charger");
        else
          OLED.print("Battery Output");
        break;

      case 4:     // Hysteresis
        OLED.print("Maint. Hysteresis");

        OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
        OLED.setCursor(10, 21);            // Set cursor to prepare for write
        OLED.print(Hysteresis);
        OLED.print("%");
        break;
    }

  } while ( OLED.nextPage() );

}




// ------------------------------------------------------------------
// updateDisplay     updateDisplay     updateDisplay     updateDisplay
// ------------------------------------------------------------------

// Displayed info for when active (NOT in Settings mode)
void updateDisplay() {

  if (isDisplay128x32 == true) {  // Use this function if the 128x32 module attached
    OLED.firstPage();
    do {
      /* all graphics commands have to appear within the loop body. */
      OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
      OLED.setCursor(0, 6);                    // Set cursor to prepare for write
      OLED.print("Chrg:");              // Display Charging port Voltage and % of Max.
      OLED.setCursor(36, 6);                    // Set cursor to prepare for write

      mUnitToUnitPrint(VChargeInmV, 1);         //  Voltage with 1 decimal places
      //    mUnitToUnitPrint(VChargeInmV, 2);         //  Voltage with 2 decimal places
      OLED.setCursor(59, 6);                    // Set cursor to prepare for write
      OLED.print("V");


      if (isDischarge) {
        OLED.setCursor(0, 13);
        OLED.print("Batt:");                        // Display Battery (Discharging) port Voltage and % of Max.
        OLED.setCursor(36, 13);                    // Set cursor to prepare for write

        mUnitToUnitPrint(VDischargeInmV, 1);         //  Voltage with 1 decimal places
        //        mUnitToUnitPrint(VDischargeInmV, 2);         //  Voltage with 2 decimal places
        OLED.setCursor(59, 13);                    // Set cursor to prepare for write
        OLED.print("V");

      }

      if (runOnce == false)                                                             // If in Maintanence mode
        //        OLED.drawXBM((128 - custMaintW), 0, custMaintW, custMaintH, custMaintBits);   //Print custom 'Maintanence Mode' Glyph in Upper Right Corner
        OLED.drawXBM((128 - custMaintW), 0, custMaintW, custHystH, custHystBits);       //Print Alternate custom 'Maintanence Mode' Glyph in Upper Right Corner

      else                                                                                  // Or, if in 'Run Once' Mode
        OLED.drawXBM((128 - custMaintW), 0, custMaintW, custMaintH, custRunOnceBits);      //Print custom 'Run Once Mode' Glyph in Upper Right Corner


      /*
         Comment out below part when done !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      */

      ////// For display testing only:
      //      ChargePercent = virtualPosition;
//      ChargePercent = 75;
      //      DischargePercent = ChargePercent;

      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



      const int _percentX = 70;
      const int _percentY = 11;
      const int _targetPercentX = 102;
      const int _arrowX = 66;
      const int _topArrowY = 0;
      const int _botArrowY = 8;

      //      OLED.setCursor(79, 12);           // Set cursor to prepare for write of Charger Voltage percentage
      OLED.setFont(u8g2_font_9x15_mn);    // Set a Larger Number font



      if ((controlVoltage == 0) || (isDischarge == false)) {    // If controlling voltage is from the charger, OR battery voltage not turned on
        // Put indicator in front of appropriate Voltage
        // & Display the appropriate percentage
        if (ChargePercent >= 100)
          OLED.setCursor(_percentX, _percentY);           // Set cursor to prepare for write of Charger Voltage percentage
        else if (ChargePercent >= 10)
          OLED.setCursor((_percentX + 9), _percentY);         // Set cursor to prepare for write of Charger Voltage percentage
        else
          OLED.setCursor((_percentX + 18), _percentY);         // Set cursor to prepare for write of Charger Voltage percentage
        OLED.print(ChargePercent);

        OLED.drawXBM(_arrowX, _topArrowY, custW, custH, lArrowBits);        //Print custom custom arrow Glyph
      }
      else {                        // If controlling voltage is from Battery Output
        if (DischargePercent >= 100)
          OLED.setCursor(_percentX, _percentY);           // Set cursor to prepare for write of Batt Voltage percentage
        else if (DischargePercent >= 10)
          OLED.setCursor((_percentX + 9), _percentY);         // Set cursor to prepare for write of Batt Voltage percentage
        else
          OLED.setCursor((_percentX + 18), _percentY);         // Set cursor to prepare for write of Batt Voltage percentage

        if (DischargePercent == 222) {        // If % == 222, Batt voltage is too Low - ie, not connected
          OLED.print("ERR");                      // Display 'ERR'
        }
        else
          OLED.print(DischargePercent);       // Otherwise display the Batt %

        OLED.drawXBM(_arrowX, _botArrowY, custW, custH, lArrowBits);        //Print custom custom arrow Glyph
      }
      OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
      OLED.setCursor((_percentX + 28), _percentY);           // Set cursor to prepare for write
      OLED.print("%");

      OLED.setCursor(0, 22);
      if (runStdby == false) {                  // If in Run Mode:
        OLED.drawXBM((128 - custRunW - custMaintW - 2), 0, custRunW, custRunH, custRunBits); //Print custom 'Running/charging' Glyph next to Mode Glyph
        if (isCurrent) {                        // AND current sensor installed
          OLED.setCursor(0, 21);
          OLED.print("Ichrg:");
          OLED.setCursor(36, 21);
          mUnitToUnitPrint(IchargemA, 2);
          //       debugPrint(IchargemA, 1);
          OLED.setCursor(59, 21);                    // Set cursor to prepare for write
          OLED.print("A");
        }

      }
      else {                                  // If in Standby Mode
        OLED.print("  -- Standby Mode --");     // State it!
      }


      if (monitorMode == true) {
        OLED.setCursor(0, 32);
        OLED.print("MONITOR ONLY");
      }
      

      OLED.setCursor(67, 31);
      OLED.print("Target: ");
      OLED.setFont(u8g2_font_9x15_mn);    // Set a Larger Number font
      if (virtualPosition < 10)   // if the target value a single digit
        OLED.setCursor((_targetPercentX + 9), 32);
      else
        OLED.setCursor(_targetPercentX, 32);
      OLED.print(virtualPosition);
      OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
      OLED.setCursor(123, 32);
      if (virtualPosition != 100)         // Show % only if less than 100
        OLED.print("%");


    } while ( OLED.nextPage() );
  }

}

void mUnitToUnitPrint(unsigned long _mUnit, int _dPArray) {
  int _dPlaces[] = {1000, 100, 10, 1};                      // Dirt simple decimal places - doesn;t display leading zeros after decimals -  not needed for this program

  OLED.print(_mUnit / 1000);
  OLED.print(".");
  OLED.print((_mUnit % 1000) / _dPlaces[_dPArray]);
}
