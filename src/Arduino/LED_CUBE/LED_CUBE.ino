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
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  void writeColumnsToShift();
  void writeLED(int stage, int column, int wait);
}

/*
  Stores the Values of the registers
 */
boolean volatile columValues[32];
char volatile mode = 'H';

/*
  Main LOOP
 */
void loop(){
  // Reset the shift registers
  digitalWrite(MR_pin, LOW);
  digitalWrite(MR_pin, HIGH);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);

  if (Serial.available() > 0) {
    mode = Serial.read(); 
    Serial.print("new mode: ");
    Serial.println(mode);
  }
  
  if (mode == 'H'){
    Serial.println("Welcome to LED CUBE Control");
    Serial.println("The following commands are supported:");
    Serial.println("H - Information and help");
    Serial.println("T - test all LEDs via loop over all of them");
    Serial.println("R - random LED blinking with random delay time");
    
    mode = '0';
  } else if (mode == 'T'){
    for(int i = 27; i <= 32; i++){
      for(int j = 0; j < 25; j++){
        writeLED(i, j, 250);
      } 
    }
  } else if(mode == 'R'){
    writeLED(random(27,32), random(24), random(100, 1000));
  }
}
















