#include "shiftControl.h"

const int DS_pin = 4; // D2
const int STCP_pin = 2; // D4
const int SHCP_pin = 0; // D3
const int MR_pin = 5; // D1

bool ledMatrix[5][32] = {
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH}};

bool allOffLeds[5][32] = {
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW},
    {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH}};

bool allOnLeds[5][32] = {
    {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},
    {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},
    {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,HIGH,LOW,LOW},
    {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW,HIGH,LOW},
    {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW,LOW,LOW,HIGH}};

/*
    Stores the Values of the registers
*/
bool shiftValues[32];

int lastColumn = -1;
int lastLevel = 27;

void initShift(){
    pinMode(DS_pin, OUTPUT);
    pinMode(STCP_pin, OUTPUT);
    pinMode(SHCP_pin, OUTPUT);
    pinMode(MR_pin, OUTPUT);

    resetLEDs();
}

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

void writeLED(int stage, int column, bool statusValue){
#ifdef DEBUG
    Serial.println("writeLED");
    Serial.print("column Value ");
    Serial.println(column);
    Serial.print("stage value ");
    Serial.println(stage);
#endif

    shiftValues[column] = statusValue;
    shiftValues[stage] = statusValue;

    writeToShift();
}

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

    for(int i=0; i<5; i++){
        memmove(ledMatrix[i],allOffLeds[i],32);
    }
}

void showMatrixForTime(int timeInMilli){
#ifdef DEBUG
    Serial.println(timeInMilli);
#endif
    unsigned long currentMillis = millis();
    while(millis() <= currentMillis + timeInMilli){
        for(int i=0; i<5; i++){
            memmove(shiftValues,ledMatrix[i],32);
            writeToShift();
            delay(1);
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
