class lineSensor_c {
  
  public:

    int pin;
    //Here we create class value for average_SensorRead from 10 collections
    float average_SensorRead;

    float sensorValue;

    float calibratedSensor;

    // Constructor, accepts a pin number as
    // argument and sets this as input. Similar to setup() for a class.
    lineSensor_c( int which_pin ) {

       // Record which pin we used.
       pin = which_pin;

       // Set this pin to input.
       pinMode( pin, INPUT );
    };
    
    // Class function defined later
    float sensorRead();

    //Here we call function calibrate
    float averageSensorValue();

    float readCalibrated();

    bool onLine();

  };


float lineSensor_c::sensorRead(){
  float value;
  value=analogRead(pin);
  sensorValue=value;
  return value;
}
//-----* global array lengrh 10, add 1 during loop()

float lineSensor_c::averageSensorValue() {
  float value;
  int countCalibration=0;
  float sum=0;

  do{
    value=analogRead(pin);
    sum+=value;
    countCalibration+=1;
  } while (countCalibration<10);
  
  float sumAverageRead=sum/10;
  average_SensorRead=sumAverageRead;
  return average_SensorRead;
}


float lineSensor_c::readCalibrated() {
  calibratedSensor=sensorValue-average_SensorRead;
  return calibratedSensor;
}

bool lineSensor_c::onLine() {
  if (sensorValue<400) {
    return false;
  } else {
    return true;
  }
}

lineSensor_c LeftSensor(LINE_LEFT_PIN);
lineSensor_c CentreSensor(LINE_CENTRE_PIN);
lineSensor_c RightSensor(LINE_RIGHT_PIN);
