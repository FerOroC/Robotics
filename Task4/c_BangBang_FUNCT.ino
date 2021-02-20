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
}
