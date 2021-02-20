void initialisingBeeps() {
  int currentTime;
  currentTime=millis();
  l_power=0;
  r_power=0;
  if ( counter<5 ){
    analogWrite(6,40);
    delay(50);
    analogWrite(6,0);
    delay(950);
    counter+=1;
    analogWrite(6,40);
    delay(50);
    analogWrite(6,0);
    delay(950);
    counter+=1;
    analogWrite(6,40);
    delay(50);
    analogWrite(6,0);
    delay(950);
    counter+=1;
    analogWrite(6,40);
    delay(50);
    analogWrite(6,0);
    delay(950);
    counter+=1;
    analogWrite(6,40);
    delay(50);
    analogWrite(6,0);
    delay(950);
    counter+=1;    
    /*if ( (currentTime%1000)==0 ) {
      counter+=1;
      analogWrite(6,40);
      delay(50);
      analogWrite(6,0);
    }*/
  } else if ( counter>=5 ) {
    state=STATE_DRIVE_FORWARDS;
  }
  }
