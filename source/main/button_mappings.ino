int mapInputsToNote() {
  // Setup some shorthands
  int val1 = inputButtonValues[0];
  int val2 = inputButtonValues[1];
  int val3 = inputButtonValues[2];
  int val4 = inputButtonValues[3];
  int val5 = inputButtonValues[4];
  int val6 = inputButtonValues[5];

  // Invalid symbol -1  
  int note = -1;
  
  // EVI Fingering, with low F open  
  if (val1 && val2 && !val3 && val4 && !val5 && !val6) note = 76; //E5
  else if (val1 && !val2 && !val3 && val4 && val5 && !val6) note = 75;
  else if (val1 && val2 && !val3 && !val4 && val5 && !val6) note = 74; //D5
  else if (val1 && val2 && !val3 && val4 && val5 && !val6) note = 73;
  else if (!val1 && !val2 && !val3 && !val4 && !val5 && !val6) note = 72; //C4
  else if (!val1 && !val2 && !val3 && val4 && !val5 && !val6) note = 71; //B4
  else if (!val1 && val2 && !val3 && !val4 && !val5 && !val6) note = 70;
  else if (!val1 && val2 && !val3 && val4 && !val5 && !val6) note = 69; //A4
  else if (!val1 && !val2 && !val3 && val4 && val5 && !val6) note = 68;
  else if (val1 && !val2 && !val3 && val4 && val5 && !val6) note = 67; //G4
  else if (val1 && !val2 && !val3 && val4 && !val5 && !val6) note = 66;
  else if (val1 && val2 && !val3 && !val4 && !val5 && !val6) note = 65; //F4

  return note;
}
