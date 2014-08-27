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

  writeShift();
}

/*
  Stores the Values of the registers
*/
boolean shiftRegValues[32];

/*
  Writes the content of the shift register value array out.
*/
void writeShift(){
  Serial.println("-->writeShift");
  Serial.print("-->");
  
  digitalWrite(SHCP_pin, LOW);
  
  for(int i = 31; i >= 0; i--){
    Serial.print(shiftRegValues[i]);
    
    digitalWrite(STCP_pin, LOW);
    digitalWrite(DS_pin, shiftRegValues[i]);
    digitalWrite(STCP_pin, HIGH);
  }
  
  Serial.println("");
  
  digitalWrite(SHCP_pin, HIGH);
}

/*
  Main LOOP
*/
void loop(){
  // Reset the shift registers
  digitalWrite(MR_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  
  for(int i = 27; i < 32; i++){
    shiftRegValues[i] = HIGH;
    for(int j = 0; j < 27; j++){
     shiftRegValues[j] = HIGH;
       writeShift();
       delay(500);
     shiftRegValues[j] = LOW;
   } 
   shiftRegValues[i] = LOW;
  }

}





