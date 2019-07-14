/***************************************************
 This example reads from the pressure sensor.
 ****************************************************/
volatile double pressure;
void setup() {
  Serial.begin(9600);  //baudrate
  pressure = 0;
  pinMode(A1, INPUT);
  analogReadResolution(13);
}
void loop() {
  pressure = analogRead(A1);
  Serial.print("pressure reading:");
  Serial.println(pressure);
  Serial.println("   ");
  delay(500);
}
