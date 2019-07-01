int mapInputsToNote() {
  // Setup some shorthands
  int val0 = inputButtonValues[5];
  int val1 = inputButtonValues[4];
  int val2 = inputButtonValues[3];
  int val3 = inputButtonValues[2];
  int val4 = inputButtonValues[1];
  int val5 = inputButtonValues[0];

  // Invalid symbol -1  
  int note = -1;

  // Here we go! Top to bottom for now, in two groups.
  if (!val3 && !val4 && !val5) {
    // Top group only
    if (!val0 && !val1 && !val2) note = 77;  // F5
     else if (!val0 && val1 && !val2) note = 76;  // E
     else if (val0 && !val1 && !val2) note = 74;  // D
     else if (val0 && val1 && !val2) note = 72;  // C
     else if (val0 && val1 && val2) note = 70;  // Bb
   } else if (val0 && val1 && val2) {
     // Bottom group (given top all pressed)
     if (!val3 && val4 && !val5) note = 69;  // A4
     else if (val3 &&!val4 && !val5) note = 68;  // Ab
     else if (val3 && val4 && !val5) note = 67;  // G
     else if (val3 && val4 && val5) note = 65;  // F4
  }

  return note;
}
