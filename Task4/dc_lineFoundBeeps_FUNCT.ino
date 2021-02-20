void foundLineBeeps() {
  int currentTime;
  currentTime=millis();
  l_power=0;
  r_power=0;
  if ( (currentTime%1000)==0 ) {
    analogWrite(6,40);
    delay(50);
  }
}
