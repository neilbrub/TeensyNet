/***************************************************
 This example reads Water flow sensor Sensor.
 ****************************************************/
volatile double currentAirFlow;
volatile double previousAirFlow;
void setup() {
  Serial.begin(9600);  //baudrate
  currentAirFlow = 0;
  previousAirFlow = 0;
  attachInterrupt(0, pulse, RISING);  //DIGITAL Pin 2: Interrupt 0
}
void loop() {
  Serial.print("airFlow:");
  Serial.println(2 * (currentAirFlow - previousAirFlow));
  previousAirFlow = currentAirFlow;
  Serial.println("   L");
  delay(500);
}

void pulse()   //measure the quantity of square wave
{
  currentAirFlow += 1.0 / 588.0;
}
