/** CONFIG **/
unsigned long debounceDelay = 50;  // The debounce time; increase if the output flickers.
unsigned long pressureCheckPeriod = 10;  // How long to poll pressure sensor for current reading
int squeak_note = 86;  // MIDI value to produce a 'squeak' sound.

bool AUTOPLAY = false;
double pressure = 0;

/** Button input state **/
int inputButtonValues[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonStates[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTimes[6] = {0, 0, 0, 0, 0, 0};  // the last time each output pin was toggled

/** Flow input state **/
//volatile unsigned long pulses;
unsigned long last_pressure_check;

/** Controller state **/
int note_playing;
int current_volume;

int ports [6] = {2, 9, 0, 3, 4, 7};


void setup() {

  Serial.begin(9600);  //baudrate

  // Set pins, indexed top-to-bottom
  pinMode(0, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
  pinMode(3, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLDOWN);
  pinMode(9, INPUT_PULLDOWN);

  note_playing = 65;  // start open...
  current_volume = 0;  // and off.
  
  //Pressure testing
  pressure = 0;
  last_pressure_check = 0;
  pinMode(A1, INPUT);
  analogReadResolution(13);
  
}

void loop() {

  // These occasionally need to persist - remember to reset them at EoL!
  static bool buttonsChanged = false;
  static bool flowChanged = false;

  /****** BUTTON DETECT ******/
  for (int i = 0; i < 6; i++) {
    int reading = digitalRead(ports[i]);
    
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
  if (!AUTOPLAY && millis() - last_pressure_check >= pressureCheckPeriod) {

    double off_cap = 650.0;
    double low_cap = 1000.0;
    double med_cap = 1500.0;
    pressure = analogRead(A1);
    
    int vol;
    if (pressure <= off_cap) {
      vol = 0;
    } else if (pressure < low_cap) {
      vol =127;
    } else if (pressure < med_cap) {
      vol = 127;
    } else {
      vol = 127;
    }

    if (vol != current_volume) {
      flowChanged = true;
      current_volume = vol;
    }
    
    last_pressure_check = millis();
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
