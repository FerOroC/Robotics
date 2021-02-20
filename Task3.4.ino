#define LINE_LEFT_PIN A4
#define LINE_CENTRE_PIN A3
#define LINE_RIGHT_PIN A2

//Motor stuff
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255


bool L_DIR_FWD=LOW;
bool R_DIR_FWD=LOW;

int l_power=0;
int r_power=0;
float LeftCalibrated;
float CentreCalibrated;
float RightCalibrated;

float TotalCalibrated;
float ProportionalLeft;
float ProportionalCentre;
float ProportionalRight;
float MeasurementControl;

int Threshold;

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


void BangBang(int Threshold, float LeftCalibrated, float CentreCalibrated, float RightCalibrated) {
  //Its above Threshold when its on black, below when on white.
  TotalCalibrated=LeftCalibrated+CentreCalibrated+RightCalibrated;
  ProportionalLeft=LeftCalibrated/TotalCalibrated;
  ProportionalCentre=CentreCalibrated/TotalCalibrated;
  ProportionalRight=RightCalibrated/TotalCalibrated;

  MeasurementControl=ProportionalLeft-ProportionalRight;

  //High value sensor read = black tape
  L_DIR_FWD=LOW;
  R_DIR_FWD=LOW;
  
  //When ProportionalRight>ProportionalLeft, M<1, black tpe under right but not left
  if (MeasurementControl<-0.04) {
    r_power=(50*(-MeasurementControl))+9;
    l_power=(50*(-MeasurementControl))+9;
    L_DIR_FWD=HIGH;
    R_DIR_FWD=LOW;
  }
  else if (MeasurementControl>0.04) {
    l_power=(50*(MeasurementControl))+9;
    r_power=(50*(MeasurementControl))+9;
    L_DIR_FWD=LOW ;
    R_DIR_FWD=HIGH;
  }
  else {
    l_power=12;
    r_power=12;
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
  }
  
  Serial.print(MeasurementControl);
  Serial.print(", ");
  Serial.print(l_power);
  Serial.print(", ");
  Serial.print(r_power);
  Serial.print("\n");
}

void driveStraight(float LeftPower, float RightPower) {
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
    l_power=LeftPower;
    r_power=RightPower;
}


lineSensor_c LeftSensor(LINE_LEFT_PIN);
lineSensor_c CentreSensor(LINE_CENTRE_PIN);
lineSensor_c RightSensor(LINE_RIGHT_PIN);

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
}

void loop() {

  float Left=LeftSensor.sensorRead();
  float Centre=CentreSensor.sensorRead();
  float Right=RightSensor.sensorRead();

  float LeftCalibrated=LeftSensor.readCalibrated();
  float CentreCalibrated=CentreSensor.readCalibrated();
  float RightCalibrated=RightSensor.readCalibrated();
  
  if (LeftSensor.onLine() && RightSensor.onLine()) {
    BangBang(100, LeftCalibrated, CentreCalibrated, RightCalibrated);
    Serial.print("on line");
  } else {
    driveStraight(15,15);
    Serial.print("Not on line");
  }

  digitalWrite( L_DIR_PIN, L_DIR_FWD);
  digitalWrite( R_DIR_PIN,  R_DIR_FWD);
  
  analogWrite( L_PWM_PIN, l_power);
  analogWrite( R_PWM_PIN, r_power ); 
  

  /*float LeftSensorRead = analogRead(LINE_LEFT_PIN);
  float CentreSensorRead=analogRead(LINE_CENTRE_PIN);
  float RightSensorRead=analogRead(LINE_RIGHT_PIN);*/

  /*Serial.print(LeftCalibrated);
  Serial.print(", ");
  Serial.print(CentreCalibrated);
  Serial.print(", ");
  Serial.print(RightCalibrated);
  Serial.print(", ");
  Serial.print(LeftMotorDrive);
  Serial.print(", ");
  Serial.print(RightMotorDrive);
  Serial.print("\n");*/
}
