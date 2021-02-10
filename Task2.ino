//Motor movement
/*DC motor driver requires two inputs, a Digital DIR (0V, 5V) which tells the driver to rotate either anti-clockwise, or clockwise, respectively. The other signal it 
 * needs is an Analogue PWM (0V-5V range) which drives power to the motor based on the duty ratio of the PWM wave. Duty Ratio not necessarily directly proportional 
 * to the motor speed (check datasheet for this).
 *
 *DIR being LOW means forward movement, DIR being HIGH means backward movement.
 *
 *When a byte goes over 255 limit, goes back down to 0.
 *
 *Forward deadband: Duty ratio (1-7)/255.
 *Backward deadband: Duty ratio (1-9)/255.
 *Left and right wheel varies
  */

// Pin definitions, to make the
// code easier to read.
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255
float l_power;
float r_power;

bool L_DIR_FWD;
bool R_DIR_FWD;

//This will be used to slowly increment speed
int counter_L=0;
int counter_R=0;
int L_P=0;
int R_P=0;

//This one used for increase L_power every 3rd loop. *All counters can be used in one.
int counter=0;

//This will be used to go forward, then backward
float StartTime;
float MidPoint;

void setLeftMotorPower(int power) {
  if (power<0) {
    l_power=-(power);
    L_DIR_FWD=HIGH;
  } else if (power>0)  {
    l_power=power;
    L_DIR_FWD=LOW;
  } else if (power>255) {
    l_power=255;
    L_DIR_FWD=LOW;
}}


void setRightMotorPower(int power) {
  if (power<0) {
    r_power=-(power);
    R_DIR_FWD=HIGH;
  } else if (power>0)  {
    r_power=power;
    R_DIR_FWD=LOW;
  } else if (power>255) {
    r_power=255;
    R_DIR_FWD=LOW;
  }
}

void turnDirection(char Dir) {
  if (Dir=="Left") {
    L_DIR_FWD=HIGH;
    R_DIR_FWD=LOW;
  } else if (Dir=="Right") {
    L_DIR_FWD=LOW;
    R_DIR_FWD=HIGH;
  }
}

// Setup, only runs once when powered on.
void setup() {

  // Set our motor driver pins as outputs.
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );

  // Set initial l_power and r_power values.
  l_power = 0;
  r_power = 0;

  // Start up the Serial for debugging.
  Serial.begin(9600);
  delay(1000);
  // Print reset so we can catch any reset error.
  Serial.println(" ***Reset*** ");

  // Send power PWM to pins, to motor drivers.
  setLeftMotorPower(20);
  setRightMotorPower(20);

  StartTime=millis();
}


// put your main code here, to run repeatedly:
void loop() {
  MidPoint=millis();

//This is to accelerate slowly, output to motor drive L_P
  /*if (counter_L<l_power) {
    L_P=counter_L;
    counter_L+=1;
  } else if (counter_L>=l_power)  {
    L_P=l_power;
  }
  if (counter_R<r_power) {
    R_P=counter_R;
    counter_R+=1;
  } else if (counter_R>=r_power)  {
    R_P=r_power;
  }*/

//This is to account for the deviation
  if (counter%3==0){
    l_power+=1.0;
  } else {
    l_power-=0.5;       //why not -1/2?
  } 
  
//This is to return to starting point  
  /*if ((MidPoint-StartTime)<=10000){
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
  } else if ((MidPoint-StartTime)<=20000){
    L_DIR_FWD=HIGH;
    R_DIR_FWD=HIGH;
  } else {
    l_power=0;
    r_power=0;
  } */
  
//This is to turn, hard-coded rectangle

  if ((millis()-StartTime)<=5000){
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
  } else if ((millis()-StartTime)<=6600){
    L_DIR_FWD=HIGH;
    R_DIR_FWD=LOW;
  } else if ((millis()-StartTime)<=11600){
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
  } else if ((millis()-StartTime)<=13200){
    L_DIR_FWD=HIGH;
    R_DIR_FWD=LOW;
  } else if ((millis()-StartTime)<=18200){
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
  } else if ((millis()-StartTime)<=19800){
    L_DIR_FWD=HIGH;
    R_DIR_FWD=LOW;
  } else if ((millis()-StartTime)<=24800){
    L_DIR_FWD=LOW;
    R_DIR_FWD=LOW;
  } else {
    l_power=0;
    r_power=0;
  }   
  
  digitalWrite( L_DIR_PIN, L_DIR_FWD);
  digitalWrite( R_DIR_PIN,  R_DIR_FWD);
  
  analogWrite( L_PWM_PIN, l_power);
  analogWrite( R_PWM_PIN, r_power ); 
  
  // Brief pause
  Serial.println(l_power);
  Serial.println(counter%3);

  counter+=1;
  delay(250);

}
