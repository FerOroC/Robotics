class controller_c {
  
  public:
    int state;
    float left_sensor;
    float centre_sensor;
    float right_sensor;
    float measurement;

    controller_c() {
      state = STATE_INITIAL;
    };
    
    void get_measurement();
    void control();
};

void controller_c::get_measurement(){
  left_sensor = LeftSensor.readCalibrated();
  centre_sensor = CentreSensor.readCalibrated();
  right_sensor = RightSensor.readCalibrated();
  Serial.print(left_sensor);
  Serial.print(", ");
  Serial.print(centre_sensor);
  Serial.print(", ");
  Serial.print(right_sensor);
  Serial.print("\n");
  float total_calibrated = left_sensor + right_sensor + centre_sensor;
  float proportional_left = left_sensor/total_calibrated;
  float proportional_centre = centre_sensor/total_calibrated;
  float proportional_right = right_sensor/total_calibrated;
  measurement = proportional_left - proportional_right;
}

void controller_c::control(){
  switch(state){
   case STATE_INITIAL:
    Beeper.beep_initial();
    if (LeftSensor.onLine() && RightSensor.onLine()){
      Beeper.beep_line();
      state = STATE_FOUND_LINE;
    }else{
      RightMotor.move_motor(20, R_DIR_FWD);
      LeftMotor.move_motor(20, L_DIR_FWD);
      state = STATE_DRIVE_FORWARDS;
    }
   break;
   case STATE_DRIVE_FORWARDS:
    Serial.println("hello");
    if (LeftSensor.onLine() && RightSensor.onLine()){
      Beeper.beep_line();
      state = STATE_FOUND_LINE;
    }
   break;
   case STATE_FOUND_LINE:
    get_measurement();
    if (measurement <- 0.04) {
      RightMotor.move_motor( (100*(-measurement))+9, R_DIR_BWD );
      LeftMotor.move_motor( (100*(-measurement))+9, L_DIR_FWD );
    } else if (measurement > 0.04) {
      RightMotor.move_motor( (100*(measurement))+9, R_DIR_FWD );
      LeftMotor.move_motor( (100*(measurement))+9, L_DIR_BWD );
    } else {
      RightMotor.move_motor(20, R_DIR_FWD);
      LeftMotor.move_motor(20, L_DIR_FWD);
    }

    if (!LeftSensor.onLine() && !RightSensor.onLine()){
      Beeper.beep_stop();
      state = STATE_DRIVE_FORWARDS;
    }
   break;
  }
}

controller_c BangBang;
