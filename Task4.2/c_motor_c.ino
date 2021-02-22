class motor_c {
  
  public:
    int pin_dir;
    int pin_pwr;
    float power;
    bool dir;
    
    motor_c( int pin1, int pin2 ) {
       pin_pwr = pin1;
       pin_dir = pin2;
       power = 0;
       dir = LOW;

       pinMode( pin_pwr, OUTPUT );
       pinMode( pin_dir, OUTPUT );
       digitalWrite( pin_dir, dir);
       analogWrite( pin_pwr, power );
    };
    
    void stop_motor();
    void move_motor(int newpwr, bool newdir);
    void operate();
  };

void motor_c::stop_motor(){
  power=0;
  operate();
}

void motor_c::move_motor(int newpwr, bool newdir) {
  power = newpwr;
  dir = newdir;
  operate();
}

void motor_c::operate() {
  digitalWrite( pin_dir, dir);
  analogWrite( pin_pwr, power );
}

motor_c LeftMotor(L_PWM_PIN, L_DIR_PIN);
motor_c RightMotor(R_PWM_PIN, R_DIR_PIN);
