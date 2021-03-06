#include "modes.h"

/*
    Run mode of the LED Cube
*/
char volatile mode = '2';

void handle_mode(){
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

bool isMode(char value){
    return (value == 'H' || value == '0' || value == '1' || value == '2' ||value == '3' || value == '4');
}
