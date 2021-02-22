class lineSensor_c {
  
  public:
    int pin;
    float average_SensorRead;
    float sensorValue;
    float calibratedSensor;

    lineSensor_c( int which_pin ) {
        pin = which_pin;
        pinMode( pin, INPUT );
        float sum=0;
      
        for (int i = 0; i<10; i++){
          sensorValue=analogRead(pin);
          sum+=sensorValue;
        }
        
        float sumAverageRead=sum/10;
        average_SensorRead=sumAverageRead;
    };
    
    float sensorRead();
    float readCalibrated();
    bool onLine();
};

float lineSensor_c::sensorRead(){
  sensorValue = analogRead(pin);
}

float lineSensor_c::readCalibrated() {
  sensorRead();
  calibratedSensor=sensorValue-average_SensorRead;
  return calibratedSensor;
}

bool lineSensor_c::onLine() {
  sensorRead();
  if (sensorValue<500) {
    return false;
  } else {
    return true;
  }
}

lineSensor_c LeftSensor(LINE_LEFT_PIN);
lineSensor_c CentreSensor(LINE_CENTRE_PIN);
lineSensor_c RightSensor(LINE_RIGHT_PIN);
