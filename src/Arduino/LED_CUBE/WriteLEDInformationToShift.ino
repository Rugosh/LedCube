/*
  Writes the content of the shift register value array out.
 */
void writeColumnsToShift(){
  if(isDebug){
    Serial.println("-->writeShift");
    Serial.print("-->");
  }

  //digitalWrite(SHCP_pin, LOW);
  digitalWrite(STCP_pin, LOW);

  for(int i = 31; i >= 0; i--){
    if(isDebug){
      Serial.print(columValues[i]);
    }

    //digitalWrite(STCP_pin, LOW);
    digitalWrite(SHCP_pin, LOW);
    digitalWrite(DS_pin, columValues[i]);
    digitalWrite(SHCP_pin, HIGH);
    delay(10);
  }

  if(isDebug){
    Serial.println("");
  }

  digitalWrite(STCP_pin, HIGH);
}

/*
  Sets one LED with the given stage/ level and column on for a given time(wait)
*/
void writeLED(int stage, int column, int wait){
  if(isDebug){
    Serial.println("writeLED");
    Serial.print("column Value ");
    Serial.println(column);
    Serial.print("stage value ");
    Serial.println(stage);
    Serial.print("delay time ");
    Serial.println(wait);
  }

  columValues[column] = HIGH;
  columValues[stage] = HIGH;

  writeColumnsToShift();
  delay(wait);

  columValues[column] = LOW;
  columValues[stage] = LOW;
}

/*
  resets the shift register Values => LEDs off and mode specific values
*/
void resetLEDs(){
  // Reset the shift registers
  digitalWrite(MR_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  
  // reset test mode values
  lastColumn = -1;
  lastLevel = 27;
}
