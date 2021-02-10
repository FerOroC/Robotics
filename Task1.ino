#include <math.h>

/*Here we define the global variables*/
int counter=0;
int duration_buzzer=10;
bool R_toggle=false;

float a=0;
float b;
float c;


//void function doesn't return values, return_type functions do.
/* Function for LED Flashing, serial printing the number of times*/
void flash_leds (int delay_ms) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(delay_ms);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(delay_ms);                       // wait for a second
    counter+=1;
    Serial.println(counter);
}

/*Function for beeper playing*/
void play_tone(int volume) {
  analogWrite(6,volume);
  delay(200);
  analogWrite(6,volume);
  counter+=1;
}

// the setup function runs once when you press reset or power the board
void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);     //Used for blinking function
  
  pinMode(6, OUTPUT);

  Serial.begin(9600);                 //Starts a serial communication at 9600 baud rate

  delay(1000);                        //Will print in serial com RESET to signal when the board has been reset. This might happen when low battery/other error behaviours.
  Serial.println("**STARTING**");
}



// the loop function runs over and over again forever
void loop() {
  //Flash LED for a set duration
  /*if (counter<duration_buzzer) {
    flash_leds(500);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  } */


  //Monitor serial comm, if r is input, flash LED continuously.
  /*
  if ( Serial.available() ) {
    char inChar = Serial.read();
    if (inChar=='r') {
      R_toggle=true;
    }

  while (R_toggle==true) {
    flash_leds(500);
  }
  } */

  //Test Serial Plotter
  /*b=sin(a);
  c=cos(a);
  a+=0.1;

  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.print(",");
  Serial.print(c);
  Serial.print("\n");
  delay(50);*/
}
