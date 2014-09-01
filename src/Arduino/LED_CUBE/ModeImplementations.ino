void mode_info(){
  Serial.println("Welcome to LED CUBE Control");
  Serial.println("The following commands are supported:");
  Serial.println("H - Information and help");
  Serial.println("T - test all LEDs via loop over all of them");
  Serial.println("R - random LED blinking with random delay time");
  Serial.println("A - light all LED");
  
  mode = '0';
}

int lastColumn = -1;
int lastLevel = 27;

void mode_loop_over(int delayValue){
  if(lastColumn == 24){
    lastColumn = 0;
    if(lastLevel == 31){
      lastLevel = 27;
    } else {
      lastLevel++;
    }
  } else {
     lastColumn++;
  }
  
  // at this point current values := last values
  writeLED(lastLevel, lastColumn, delayValue);
}

void mode_random(){
  writeLED(random(27,32), random(24), random(100, 1000));
}
