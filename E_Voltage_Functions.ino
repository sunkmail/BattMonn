




unsigned long VRawTOmV(int RawData){
  // Convert the Analog Reading (which goes from 0 - 1023) to a voltage (0 - 85V):
  //Do multiplication first to keep accurate. Long because 1023 * 85000 (85V * 1000 mV/V) is to big for an int.
  
  unsigned long _voltageInMv = (RawData * (MaxVRange*1000));  // Multiple Raw by max mV Value possible, Then
  _voltageInMv = (_voltageInMv / 1024);                       // Divide by Max ADC value to get mVs

  return _voltageInMv;
}



float mVToVolts(unsigned long RawData){         // Takes a long time - Try to avoid using Float.  Here for easier testing
  float _voltage = float((RawData / 1000));
  return _voltage;
}


// ------------------------------------------------------------------
// calcBatteryPercent     calcBatteryPercent      calcBatteryPercent      calcBatteryPercent
// ------------------------------------------------------------------

 byte calcBatteryPercent(unsigned long mVsMeasured){
  float _BatteryPercent;
  
  switch(voltageMode){                // Formulas based on Linear regression algorythm from www.xuru.org/rt/LR.asp & Charge chart found on EBR Forums
    case 0:      // 36V Pack
      _BatteryPercent = ((8.333333333e-3 * mVsMeasured) - 250);
    break;
    
    case 1:      // 48V Pack
      _BatteryPercent = ((6.414311974e-3 * mVsMeasured) - 250.1898004);
    break;
    
    case 2:      // 52V Pack
      _BatteryPercent = ((5.948529412e-3 * mVsMeasured) - 249.8058824);
    break;
    
    case 3:      // 60V Pack
      _BatteryPercent = ((5.211037129e-3 * mVsMeasured) - 250.1557386);
    break;
    
    case 4:      // 72V Pack
      _BatteryPercent = ((4.166666667e-3 * mVsMeasured) - 250);
    break;
    
    default:
      _BatteryPercent = 0;    // If outside known packs, default to 0%
  }
  return byte(_BatteryPercent);
  
}
