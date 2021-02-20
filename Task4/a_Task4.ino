//----------------------GLOBAL VARIABLES------------------------

//Sensor pins
#define LINE_LEFT_PIN A4
#define LINE_CENTRE_PIN A3
#define LINE_RIGHT_PIN A2

//Motor pins
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

//Define states for FSM
#define STATE_INITIAL 0
#define STATE_DRIVE_FORWARDS 1
#define STATE_FOUND_LINE 2

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

//int which will hold current state
int state;

//for counting beeps initial
int counter=0;
