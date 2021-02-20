void setup() {

  // Start up the Serial for debugging.
  Serial.begin(9600);
  delay(1000);
  // Print reset so we can catch any reset error.
  Serial.println(" ***Reset*** ");

//Used to calibrate
  float Left=RightSensor.averageSensorValue();
  float Centre=CentreSensor.averageSensorValue();
  float Right=LeftSensor.averageSensorValue();

  state=STATE_INITIAL;
}
