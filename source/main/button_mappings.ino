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

  if (!val1 && !val2 && !val4 && !val5) note = 70; //Bb4
  else if (val1 && !val2 && !val4 && !val5) note = 69; //A4
  else if (!val1 && val2 && val4 && !val5) note = 68;
  else if (val1 && val2 && !val4 && !val5) note = 67; //G4
  else if (val1 && !val2 && val4 && !val5) note = 66;
  else if (val1 && val2 && val4 && !val5) note = 65; //F4
  else if (!val1 && val2 && !val4 && val5) note = 64; //E4
  else if (!val1 && !val2 && !val4 && val5) note = 63;
  else if (val1 && !val2 && !val4 && val5) note = 62; //D4
  else if (!val1 && !val2 && val4 && val5) note = 61;
  else if (val1 && val2 && !val4 && val5) note = 60; //C4
  else if (val1 && !val2 && val4 && val5) note = 59;
  else if (val1 && val2 && val4 && val5) note = 58; //Bb3

  if (val3) 
    note += 12;
  if (val6)
    note -= 12;

  return note;
}
