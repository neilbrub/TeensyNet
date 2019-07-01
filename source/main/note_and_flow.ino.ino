int mapInputsToNote() {
  // Setup some shorthands
  int val0 = inputButtonValues[0];
  int val1 = inputButtonValues[1];
  int val2 = inputButtonValues[2];
  int val3 = inputButtonValues[3];
  int val4 = inputButtonValues[4];
  int val5 = inputButtonValues[5];

  // Invalid symbol -1
  int note = -1;

  // Here we go! Top to bottom for now, in two groups.
  if (!val3 && !val4 && !val5) {
    // Top group only
    if (!val0 && !val1 && !val2) note = 67;  // G
    else if (!val0 && val1 && !val2) note = 66;  // F#
    else if (val0 && !val1 && !val2) note = 64;  // E
    else if (val0 && val1 && !val2) note = 62;  // D
    else if (val0 && val1 && val2) note = 60;  // Middle C
  } else if (val0 && val1 && val2) {
    // Bottom group (given top all pressed)
    if (!val3 && val4 && !val5) note = 59;  // B
    else if (val3 &&!val4 && !val5) note = 58;  // Bb
    else if (val3 && val4 && !val5) note = 57;  // A
    else if (val3 && val4 && val5) note = 55;  // G
  }

  return note;
}

void count_pulse() {
  pulses++;
}
