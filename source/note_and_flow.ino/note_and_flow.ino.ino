unsigned long debounceDelay = 50;  // the debounce time; increase if the output flickers

// **CHANGE ME!!**
unsigned long flowCheckPeriod = 50;  // How long to accumulate flow sensor pulses before mapping to a volume

// Button input state
int inputButtonValues[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonStates[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTimes[6] = {0, 0, 0, 0, 0, 0};  // the last time each output pin was toggled

// Flow input state
volatile unsigned long pulses;
unsigned long last_pulseCheck;

// Controller state
int note_playing;
int current_volume;

void setup() {

  Serial.begin(9600);  //baudrate

  // Set pins, indexed top-to-bottom
  pinMode(0, INPUT_PULLDOWN);
  pinMode(1, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
  pinMode(3, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);

  attachInterrupt(6, count_pulse, RISING);

  pulses = 0;
  last_pulseCheck = 0;

  note_playing = 67;  // start open...
  current_volume = 0;  // and off.
}

// New note to play or 'no note change' signal passed, flow state assumed to always be correct
void controller(int note_to_play) {
  if (note_to_play != 0) {
    Serial.print("Controller to play ");
    Serial.print(note_to_play);
    Serial.print(" at ");
    Serial.println(current_volume);
  } else {
    Serial.print("Setting volume to: ");
    Serial.println(current_volume);
  }
}

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

void loop() {

  // These occasionally need to persist - remember to reset them at EoL!
  static bool buttonsChanged = false;
  static bool flowChanged = false;

  /****** BUTTON DETECT ******/
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
        buttonsChanged = true;
      }
    }
    
    lastButtonStates[i] = reading;
  }

  /****** AIRFLOW DETECT ******/
  if (millis() - last_pulseCheck >= flowCheckPeriod) {
    // Map # pulses to a volume (0 -> 127)

    /**
     * Experimental results:
     *  blowing normally yielded ~150 pulses over 1 second
     *  blowing hard yielded ~290 over 1 second
     * 
     */

    unsigned int off_cap = (20 * flowCheckPeriod / 1000);
    unsigned int low_cap= (120 * flowCheckPeriod / 1000);
    unsigned int med_cap = (240 * flowCheckPeriod / 1000);
    
    int vol;
    if (pulses <= off_cap) {
      vol = 0;
    } else if (pulses < low_cap) {
      vol = 40;
    } else if (pulses < med_cap) {
      vol = 65;
    } else {
      vol = 100;
    }

    if (vol != current_volume) {
      flowChanged = true;
      current_volume = vol;
    }
    
    // debug:
//     Serial.print("Pulses: ");
//     Serial.println(pulses);
    
    pulses = 0;
    last_pulseCheck = millis();
  }

  if (buttonsChanged) {
    char note = mapInputsToNote();
    controller(note);
    buttonsChanged = false;
  } else if (flowChanged) {
    // Send 'no note change' signal - controller uses note_playing from state
    controller(0);
    flowChanged = false;
  }
}

void count_pulse() {
  pulses++;
}
