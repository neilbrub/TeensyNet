
void setup() {
  Serial.begin(9600);  //baudrate

  pinMode(5, INPUT);  // top button fist set
  pinMode(4, INPUT);  //
  pinMode(3, INPUT);  //
  pinMode(2, INPUT);  // top button secon set
  pinMode(1, INPUT);  //
  pinMode(0, INPUT);  // bottom button

  attachInterrupt(5, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  attachInterrupt(4, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  attachInterrupt(3, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  attachInterrupt(2, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  attachInterrupt(1, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0
  attachInterrupt(0, whatPin, CHANGE);  //DIGITAL Pin 0: Interrupt 0

}


void loop (){

}

void whatPin (){
  for (int i =0 ; i < 5; i++) {
    if (digitalRead (i) == HIGH) {
      Serial.println("pin is " + i);
    }
  }
}
