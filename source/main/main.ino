/** CONFIG **/
unsigned long debounceDelay = 50;  // The debounce time; increase if the output flickers.
unsigned long flowCheckPeriod = 50;  // How long to accumulate flow sensor pulses before mapping to a volume.
int squeak_note = 86;  // MIDI value to produce a 'squeak' sound.

bool AUTOPLAY = false;
double pressure = 0;

/** Button input state **/
int inputButtonValues[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonStates[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTimes[6] = {0, 0, 0, 0, 0, 0};  // the last time each output pin was toggled

/** Flow input state **/
volatile unsigned long pulses;
unsigned long last_pulseCheck;

/** Controller state **/
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

  //attachInterrupt(6, count_pulse, RISING);

  pulses = 0;
  last_pulseCheck = 0;

  note_playing = 65;  // start open...
  current_volume = 0;  // and off.
  
  //Pressure testing
  pressure = 0;
  pinMode(A1, INPUT);
  analogReadResolution(13);
  
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
  if (!AUTOPLAY && millis() - last_pulseCheck >= flowCheckPeriod) {

    /**
     * Map # pulses to a volume (0 -> 127).
     * 
     * Experimental results:
     *  blowing normally yielded ~150 pulses over 1 second
     *  blowing hard yielded ~290 over 1 second
     * 
     */

    double off_cap = 500.0;  //(20 * flowCheckPeriod / 1000);
    double low_cap = 700.0;  //(120 * flowCheckPeriod / 1000);
    double med_cap = 900.0;  //(240 * flowCheckPeriod / 1000);
    pressure = analogRead(A1);
    
    int vol;
    if (pressure <= off_cap) {
      vol = 0;
    } else if (pressure < low_cap) {
      vol = 50;
    } else if (pressure < med_cap) {
      vol = 75;
    } else {
      vol = 105;
    }

    if (vol != current_volume) {
      flowChanged = true;
      current_volume = vol;
    }
    
    pulses = 0;
    last_pulseCheck = millis();
  }

  if (buttonsChanged) {
    int note = mapInputsToNote();
    controller(note);
    buttonsChanged = false;
  } else if (flowChanged) {
    // Send 'no note change' signal - controller uses note_playing from state
    controller(0);
    flowChanged = false;
  }
}
