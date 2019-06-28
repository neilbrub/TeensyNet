
int inputButtonValue [5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState [5] = {LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers


void setup() {
  Serial.begin(9600);  //baudrate

  pinMode(5, INPUT_PULLDOWN);  // top button fist set //jank
  pinMode(4, INPUT_PULLDOWN);  //
  pinMode(3, INPUT_PULLDOWN);  //
  pinMode(2, INPUT_PULLDOWN);  // top button secon set
  pinMode(1, INPUT_PULLDOWN);  //
  pinMode(0, INPUT_PULLDOWN);  // bottom button // jank 

  //attachInterrupt(5, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(4, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(3, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(2, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(1, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  //attachInterrupt(0, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0

}


void loop (){
  for (int i = 0 ; i <= 5; i++) {
    int reading = digitalRead(i);
    //Serial.println(reading);
    if (reading != lastButtonState [i]) {
      //reset the debouncing timer
      lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != inputButtonValue [i]) {
      inputButtonValue [i] = reading;

      // only toggle the LED if the new button state is HIGH
      if (inputButtonValue [i] == HIGH) {
        Serial.print("pin High: ");
        Serial.println(i);
      }
     }
    }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState [i] = reading;
  }    
}

void whatPin (){
  for (int i =0 ; i <= 5; i++) {
    if (digitalRead (i) == HIGH) {
      inputButtonValue [i] = true;
    }
  }
}
