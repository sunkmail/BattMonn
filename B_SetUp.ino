

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
  
  
  digitalWrite(ChargeOn_PIN, false);      // Default Charger state to off.
  pinMode(ChargeOn_PIN, OUTPUT);          // charger on = Mosfet activation
  
  
  pinMode(VCharge_PIN, INPUT);            // Analog input for Charge voltage
  pinMode(VDischarge_PIN, INPUT);         // Analog input from discharge port
  pinMode(Icharge_PIN, INPUT);            // Analog input for current measurement
  

  
  
  // **************************************************************
  // ********************** Misc Setup ****************************
  
  // 0.91" OLED display module  128x32
  OLED.begin();                             // Start the OLED display Object/Library
//  OLED.setFont(u8g2_font_logisoso32_tr);    // Set the (initial?) font for 32 Pixel high
//  OLED.setCursor(0,32);                     // Set cursor to prepare for first write

 

/*
OLED.firstPage();     // Pixel Check - Fill All pixels and pause for a delay
  do {
  OLED.drawBox(0,0,228,132);
  } while ( OLED.nextPage() );
delay(2500);
*/

/*

// ADC settings - try to improve readings
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  
  // uncomment as required
  
//  ADCSRA |= bit (ADPS0);                               //   2  
//  ADCSRA |= bit (ADPS1);                               //   4  
//  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  
//  ADCSRA |= bit (ADPS2);                               //  16 
//  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 
//  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128
*/

  delay(100);         // Let everything settle for 100 ms on boot-up

  attachInterrupt(digitalPinToInterrupt(EncodeA_PIN), isr_EncoderKnob, LOW);     // Attach interrupt for encoder
  
  // Ready to go!
  debugPrint("Setup finished successfully.",1);

}
