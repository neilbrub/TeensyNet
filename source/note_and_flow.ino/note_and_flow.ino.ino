unsigned long debounceDelay = 50;  // the debounce time; increase if the output flickers

// **CHANGE ME!!**
unsigned long flowCheckPeriod = 500;  // How long to accumulate flow sensor pulses before mapping to a volume

// Button input state
int inputButtonValues[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonStates[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTimes[6] = {0, 0, 0, 0, 0, 0};  // the last time each output pin was toggled

// Flow input state
volatile unsigned long pulses;
unsigned long last_pulseCheck;
double last_volume;

// Controller state
char note_in_play;
float output_volume;

void setup() {

  Serial.begin(9600);  //baudrate

  // Set pins, indexed top-to-bottom
  pinMode(0, INPUT_PULLDOWN);
  pinMode(1, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
  pinMode(3, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);

  attachInterrupt(6, count_pulse, RISING)

  pulses = 0;
  last_pulseCheck = 0;
  last_volume = 0.0;

  note_in_play = 'G';  // start open...
  output_volume = 0.0;  // and off.
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

  /****** BUTTON DETECT ******/
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

  /****** AIRFLOW DETECT ******/
  if (millis() - last_pulseCheck >= flowCheckPeriod) {
    // map number of pulses to a volume
    // compare calculated value to last_volume; if changed:
    //  - save the new volume to output_volume state
    //  - invoke the controller to update the note being played

    // debug:
    Serial.print("Pulses: ");
    Serial.println(pulses);
    
    pulses = 0;
    last_pulseCheck = millis();
  }

  if (inputStateChanged) {
    char note = mapInputsToNote();
    controller(note);
  }
}

void count_pulse() {
  pulses++;
}
