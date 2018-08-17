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
      OLED.setFont(u8g2_font_t0_15_mr);         // Set a font for 10 Pixel high
      OLED.setCursor(0,32);                     // Set cursor to prepare for write
      OLED.print("Turn to Adjust - Press to accept");
      
      OLED.setCursor(0,10);                     // Set cursor to prepare for write
      OLED.print("SETTING: ");
      
      switch(Page){                
        
        case 1:     // isDischarge
          OLED.print("Monitor Discharge Port");
          
          OLED.setFont(u8g2_font_t0_15_mr);    // Set a font for 10 Pixel high
          OLED.setCursor(0,21);                     // Set cursor to prepare for write
          if(isDischarge == true)
            OLED.print("Yes"); 
          else
            OLED.print("No");
        break;
        
        case 2:      // PackVoltage
          OLED.print("Pack Voltage");
          
          OLED.setFont(u8g2_font_t0_15_mr);    // Set a font for 10 Pixel high
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
      OLED.setFont(u8g2_font_t0_15_mr);    // Set a font for 10 Pixel high
      OLED.setCursor(0,10);                     // Set cursor to prepare for write
      OLED.print("Charge Port: ");              // Display Charging port Voltage and % of Max.
      OLED.print(VCharge,2);                      //  Voltage with 2 decimal places
      OLED.print("V     ");
      OLED.print(ChargePercent);
      OLED.print("%");
      
      if(isDischarge){
        OLED.setCursor(0,21);
        OLED.print("Discharge Port: ");           // Display Discharging port Voltage and % of Max.
        OLED.print(VDischarge,2);
        OLED.print("V ");
        OLED.print(DischargePercent);
        OLED.print("%");
      }
      
      OLED.setCursor(0,32);
      if(monitorMode == true)
        OLED.print("MONITOR ONLY    ");
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
