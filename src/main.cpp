#include "config.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Arduino.h"
#include "main.h"

#define DEBUG_OFF

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
  Sets one LED with the given stage/ level and column to the given status
*/
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

    for(int i=0; i<5; i++){
        memmove(ledMatrix[i],allOffLeds[i],32);
    }
}

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
    writeLED(lastLevel, lastColumn, LOW);
    delay(delayValue);
    writeLED(lastLevel, lastColumn, HIGH);
}

void mode_random(){
    int row = random(27,32);
    int cloumn = random(24);
    writeLED(row, cloumn, LOW);
    delay(random(500, 5000));
    writeLED(row, cloumn, HIGH);
}

void mode_random_flip(){
    int row = random(4);
    int cloumn = random(24);
    ledMatrix[row][cloumn] = !ledMatrix[row][cloumn];
    showMatrixForTime(random(500, 5000));
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
    bool isMode(char value);

    void mode_info();
    void mode_loop_over(int delayValue);
    void mode_random();
    void light_all(int delayBetweenStages);

    resetLEDs();

    ArduinoOTA.setHostname("ledCube");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA.onStart([]() {
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

/*
    Main LOOP
*/
void loop(){
    ArduinoOTA.handle();
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
bool isMode(char value){
    return (value == 'H' || value == '0' || value == '1' || value == '2' ||value == '3' || value == '4');
}
