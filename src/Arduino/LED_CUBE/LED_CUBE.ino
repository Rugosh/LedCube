
#define DEBUG_OFF

/*
  Pin Settings
 */
const int DS_pin = 4; // D2
const int STCP_pin = 2; // D4
const int SHCP_pin = 0; // D3
const int MR_pin = 5; // D1

/*
  Init the System
 */
void setup(){
  // initialize serial:
  Serial.begin(115200);

  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  pinMode(MR_pin, OUTPUT);

  void writeToShift();
  void writeLED(int stage, int column, int wait);
  void resetLEDs();
  boolean isMode(char value);
  
  void mode_info();
  void mode_loop_over(int delayValue);
  void mode_random();
  void light_all(int delayBetweenStages);
  
  resetLEDs();
}

/*
  Stores the Values of the registers
 */
boolean shiftValues[32];

/*
  Run mode of the LED Cube
*/
char volatile mode = '2';

/*
  Main LOOP
 */
void loop(){ 
  if (mode == 'H'){
    mode_info();
  } else if (mode == '0'){
    mode_loop_over(250);
  } else if(mode == '1'){
    mode_random();} 
  else if(mode == '2'){
    mode_random_flip();
  } else if(mode == '3'){
    light_all(0);
  } else if(mode == '4'){
    light_all(250);
  }
}

/*
  Serial Event Handling
*/
void serialEvent(){
  char serialContent = Serial.read();
  Serial.print("Content read: ");
  Serial.println(serialContent);
  
  if(isMode(serialContent)){
    mode = serialContent;
    
    Serial.print("new mode: ");
    Serial.println(mode);
    
    resetLEDs();
  } else {
     Serial.println("no mode entered"); 
  }
}

/*
  Checks if the given value is an allowed mode key
*/
boolean isMode(char value){
 return (value == 'H' || value == '0' || value == '1' || value == '2' ||value == '3' || value == '4'); 
}
















