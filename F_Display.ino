/*
  Displays Possibly being used:   
        0.91" OLED display module  128x32
        16x2 Character Module with I2C connection
  
*/


// ------------------------------------------------------------------
// settingsDisplay     settingsDisplay     settingsDisplay     settingsDisplay
// ------------------------------------------------------------------

void settingsDisplay(byte Page){
  
  OLED.firstPage();
    do {
      /* all graphics commands have to appear within the loop body. */   
      OLED.setFont(u8g2_font_5x7_mr);         // Set a font for 6 Pixel high
      OLED.setCursor(0,31);                     // Set cursor to prepare for write
      OLED.print("Adjust or Press to accept");
      
      OLED.setCursor(40,06);                     // Set cursor to prepare for write
      OLED.print("SETTING: ");
      OLED.setCursor(0,13);                     // Set cursor to prepare for write
      
      switch(Page){                
        
        case 1:     // isDischarge
          //OLED.print("Monitor Discharge Port:");
          OLED.print("Monitor Battery Output:");
          
          OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
          OLED.setCursor(10,21);                     // Set cursor to prepare for write
          if(isDischarge == true)
            OLED.print("Yes"); 
          else
            OLED.print("No");
        break;
        
        case 2:      // PackVoltage
          OLED.print("Pack Voltage");
          
          OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
          OLED.setCursor(0,21);                     // Set cursor to prepare for write
          OLED.print(packVoltage[voltageMode]); 
          OLED.print("V");
        break;
      }
      
    } while ( OLED.nextPage() );
  
}




// ------------------------------------------------------------------
// updateDisplay     updateDisplay     updateDisplay     updateDisplay
// ------------------------------------------------------------------

// Displayed info for when active (NOT in Settings mode)
void updateDisplay(){
  
  if(isDisplay128x32==true){      // Use this function if the 128x32 module attached
    OLED.firstPage();
    do {
      /* all graphics commands have to appear within the loop body. */    
      OLED.setFont(u8g2_font_5x7_mr);    // Set a font for 6 Pixel high
      OLED.setCursor(0,6);                     // Set cursor to prepare for write
      OLED.print("Charger:");              // Display Charging port Voltage and % of Max.
      OLED.setCursor(50,6);                     // Set cursor to prepare for write
 //     OLED.print(VCharge,2);                      //  Voltage with 2 decimal places
      mUnitToUnitPrint(VChargeInmV);
      
      OLED.setCursor(78,6);                     // Set cursor to prepare for write
      OLED.print("V");
      OLED.setCursor(108,6);                     // Set cursor to prepare for write
      OLED.print(ChargePercent);
      OLED.setCursor(123,6);                     // Set cursor to prepare for write
      OLED.print("%");
      
      if(isDischarge){
        OLED.setCursor(0,13);
        OLED.print("Batt:");                        // Display Battery (Discharging) port Voltage and % of Max.
        OLED.setCursor(50,13);                     // Set cursor to prepare for write
//        OLED.print(VDischarge,2);
        mUnitToUnitPrint(VDischargeInmV);
        OLED.setCursor(78,13);                     // Set cursor to prepare for write
        OLED.print("V");
        OLED.setCursor(108,13);                     // Set cursor to prepare for write
        OLED.print(DischargePercent);
        OLED.setCursor(123,13);                     // Set cursor to prepare for write
        OLED.print("%");
      }

      if(isCurrent){
        OLED.setCursor(0,21);
        OLED.print("Current:");
        OLED.setCursor(50,21);
//        OLED.print(IchargemA);
        mUnitToUnitPrint(IchargemA);
        OLED.setCursor(73,21);                     // Set cursor to prepare for write
        OLED.print("A");
      }
      
      if(monitorMode == true){
        OLED.setCursor(0,32);
        OLED.print("MONITOR ONLY");
        }
        
      OLED.setCursor(68,31);
      OLED.print("Target: ");
      OLED.print(virtualPosition);
      OLED.print("%");
      
 
    } while ( OLED.nextPage() );
  }
  
  
  else if(isDisplay16x2==true){
    // Not yet programmed / set up
  }
  
  updateDisplay_FLAG = false;            // Reset Flag
}

void mUnitToUnitPrint(unsigned long _mUnit){
  OLED.print(_mUnit/1000);
  OLED.print(".");
  OLED.print((_mUnit%1000)/10);
}
