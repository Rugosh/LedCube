
#define DEBUG_OFF

/*
  Pin Settings
 */
const int DS_pin = 8;
const int STCP_pin = 9;
const int SHCP_pin = 10;
const int MR_pin = 7;


/*
  Init the System
 */
void setup(){
  // initialize serial:
  Serial.begin(9600);

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
char volatile mode = 'H';

/*
  Main LOOP
 */
void loop(){  
  if (mode == 'H'){
    mode_info();
  } else if (mode == 'T'){
    mode_loop_over(250);
  } else if(mode == 'R'){
    mode_random();
  } else if(mode == 'A'){
    light_all(0);
  } else if(mode == 'L'){
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
 return (value == 'H' || value == 'T' || value == 'R' || value == 'A' || value == 'L'); 
}
















