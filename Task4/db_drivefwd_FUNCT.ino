void driveForwards() {
    /*if (LeftSensor.onLine() && RightSensor.onLine()) {
    BangBang(100, LeftCalibrated, CentreCalibrated, RightCalibrated);
    Serial.print("on line");
  } else {
    driveStraight(15,15);
    Serial.print("Not on line");*/
    if ( LeftSensor.onLine() && RightSensor.onLine() ) {
      state=STATE_FOUND_LINE;
    } else {
      driveStraight(15,15);
    }
}
