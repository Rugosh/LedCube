/*
  Writes the content of the shift register value array out.
 */
void writeToShift(){
#ifdef DEBUG
    Serial.println("-->writeShift");
    Serial.print("-->");
#endif

  //digitalWrite(SHCP_pin, LOW);
  digitalWrite(STCP_pin, LOW);

  for(int i = 31; i >= 0; i--){
#ifdef DEBUG
      Serial.print(shiftValues[i]);
#endif

    //digitalWrite(STCP_pin, LOW);
    digitalWrite(SHCP_pin, LOW);
    digitalWrite(DS_pin, shiftValues[i]);
    digitalWrite(SHCP_pin, HIGH);
  }

#ifdef DEBUG
    Serial.println("");
#endif

  digitalWrite(STCP_pin, HIGH);
}

/*
  Sets one LED with the given stage/ level and column on for a given time(wait)
*/
void writeLED(int stage, int column, int wait){
#ifdef DEBUG
    Serial.println("writeLED");
    Serial.print("column Value ");
    Serial.println(column);
    Serial.print("stage value ");
    Serial.println(stage);
    Serial.print("delay time ");
    Serial.println(wait);
#endif

  shiftValues[column] = HIGH;
  shiftValues[stage] = HIGH;

  writeToShift();
  delay(wait);

  shiftValues[column] = LOW;
  shiftValues[stage] = LOW;
}

/*
  resets the shift register Values => LEDs off and mode specific values
*/
void resetLEDs(){
  // Reset the shift registers
  digitalWrite(MR_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  
  // reset test mode values
  for(int i = 0; i<32; i++){
    shiftValues[i] = LOW;
  }
  lastColumn = -1;
  lastLevel = 27;
}
