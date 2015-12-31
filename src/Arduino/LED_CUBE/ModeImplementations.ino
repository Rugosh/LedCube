long const clockLoopsPerMilli = 16777; 

boolean ledMatrix[5][32] = {
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH}};

boolean allOffLeds[5][32] = {
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW},
  {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH}};

boolean allOnLeds[5][32] = {
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,HIGH,LOW,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW,HIGH,LOW},
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW,LOW,HIGH}};

void mode_info(){
  Serial.println("Welcome to LED CUBE Control");
  Serial.println("The following commands are supported:");
  Serial.println("H - Information and help");
  Serial.println("0 - test all LEDs via loop over all of them");
  Serial.println("1 - random LED blinking with random delay time");
  Serial.println("2 - random LED flip in status with random delay time");
  Serial.println("3 - light all LED");
  Serial.println("4 - light up all levels with an short delay between each level");
  
  mode = 'X';
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
  writeLED(lastLevel, lastColumn, HIGH);
  delay(delayValue);
  writeLED(lastLevel, lastColumn, LOW);
}

void mode_random(){
  int row = random(27,32);
  int cloumn = random(24);
  writeLED(row, cloumn, HIGH);
  delay(random(500, 5000));
  writeLED(row, cloumn, LOW);
}

void mode_random_flip(){
  int row = random(4);
  int cloumn = random(24);
  ledMatrix[row][cloumn] = !ledMatrix[row][cloumn];
  showMatrixForTime(random(500, 5000));
}

void showMatrixForTime(int timeInMilli){
  Serial.println(timeInMilli);
  long clockToWait = clockLoopsPerMilli*timeInMilli/25000;
  for(int c=0; c<clockToWait; c++){
    for(int i=0; i<5; i++){
      memmove(shiftValues,ledMatrix[i],32);
      writeToShift();
    }
  }
}
  
void light_all(int delayBetweenStages){
  for(int i=0; i<5; i++){
    memmove(shiftValues,allOnLeds[i],32);
    writeToShift();
    delay(delayBetweenStages);
  }
}
