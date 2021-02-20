void loop() {

  float Left=LeftSensor.sensorRead();
  float Centre=CentreSensor.sensorRead();
  float Right=RightSensor.sensorRead();

  float LeftCalibrated=LeftSensor.readCalibrated();
  float CentreCalibrated=CentreSensor.readCalibrated();
  float RightCalibrated=RightSensor.readCalibrated();

  if ( state==STATE_INITIAL ) {
    initialisingBeeps();
  } else if ( state==STATE_DRIVE_FORWARDS ) {
    driveForwards();
  } else if ( state==STATE_FOUND_LINE ) {
    foundLineBeeps();
  } else {
    Serial.print("system error: Unknown State: ");
    Serial.println( state );
  }
  
  
  /*if (LeftSensor.onLine() && RightSensor.onLine()) {
    BangBang(100, LeftCalibrated, CentreCalibrated, RightCalibrated);
    Serial.print("on line");
  } else {
    driveStraight(15,15);
    Serial.print("Not on line");
  }*/ //-* code above shows how to run BangBang, run it when STATE_FOUND_LINE
  
  delay(2);
}
