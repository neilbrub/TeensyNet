
int inputButtonValue [6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonState [6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTime [6] = {0, 0, 0, 0, 0, 0};  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers
int ports [6] = {2, 9, 0, 3, 4, 7};


void setup() {
  Serial.begin(9600);  //baudrate

  pinMode(0, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
  pinMode(3, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLDOWN);
  pinMode(9, INPUT_PULLDOWN);

  // Interrupts
  //attachInterrupt(digitalPinToInterrupt(5), whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(digitalPinToInterrupt(4), whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(digitalPinToInterrupt(3), whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(digitalPinToInterrupt(2), whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(digitalPinToInterrupt(1), whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(digitalPinToInterrupt(0), whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0

}


void loop (){
  bool changed;

  changed = false;
  for (int i = 0; i <= 5; i++) {
    int reading = digitalRead(ports[i]);
    
    if (reading != lastButtonState[i]) {
      //reset the debouncing timer
      lastDebounceTime[i] = millis();
    }
     
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state

      // if the button state has changed:
      if (reading != inputButtonValue[i]) {
        inputButtonValue[i] = reading;
        changed = true;

        // Debug
        if (inputButtonValue[i] == HIGH) {
          Serial.print("pin High: ");
          Serial.println(i);
        } else if (inputButtonValue[i] == LOW) {
          Serial.print("pin Low: ");
          Serial.println(i);
        }
      }
    }
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState[i] = reading;
  }

  // Debug
  if (changed) {
    Serial.println("New State: ");
    for (int i = 0; i <= 5; i++) {
      Serial.print(inputButtonValue[i]);
      Serial.print(", ");
    }
    Serial.println("\n");
  }
}

// ISR
//void whatPin (){
//  for (int i =0 ; i <= 5; i++) {
//    if (digitalRead (i) == HIGH) {
//      inputButtonValue[i] = true;
//    }
//  }
//}
