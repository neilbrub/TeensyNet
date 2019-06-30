int inputButtonValues [6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonStates [6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTimes [6] = {0, 0, 0, 0, 0, 0};  // the last time each output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {

  Serial.begin(9600);  //baudrate

  // Set pins, indexed top-to-bottom
  pinMode(0, INPUT_PULLDOWN);
  pinMode(1, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
  pinMode(3, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);

}

void controller(char note_to_play) {
  Serial.print("Controller to play ");
  Serial.println(note_to_play);
}

char mapInputsToNote() {
  // Setup some shorthands
  int val0 = inputButtonValues[0];
  int val1 = inputButtonValues[1];
  int val2 = inputButtonValues[2];
  int val3 = inputButtonValues[3];
  int val4 = inputButtonValues[4];
  int val5 = inputButtonValues[5];

  // Invalid symbol '0'
  char note = '0';

  // Here we go! Top to bottom for now, in two groups.
  if (!val3 && !val4 && !val5) {
    // Top group only
    if (!val0 && !val1 && !val2) note = 'G';
    else if (!val0 && val1 && !val2) note = 'F';  // actually want F#
    else if (val0 && !val1 && !val2) note = 'E';
    else if (val0 && val1 && !val2) note = 'D';
    else if (val0 && val1 && val2) note = 'C';
  } else if (val0 && val1 && val2) {
    // Bottom group (given top)
    if (!val3 && val4 && !val5) note = 'B';
    // Bb - val3 &&!val4 && !val5
    else if (val3 && val4 && !val5) note = 'A';
    else if (val3 && val4 && val5) note = 'G';
  }

  return note;
}

void loop() {

  bool inputStateChanged = false;
  for (int i = 0; i < 6; i++) {
    int reading = digitalRead(i);
    
    if (reading != lastButtonStates[i]) {
      //reset the debouncing timer
      lastDebounceTimes[i] = millis();
    }
     
    if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state

      // if the button state has changed:
      if (reading != inputButtonValues[i]) {
        inputButtonValues[i] = reading;
        inputStateChanged = true;
      }
    }
    
    lastButtonStates[i] = reading;
  }

  if (inputStateChanged) {
    char note = mapInputsToNote();
    controller(note);
  }
  
}
