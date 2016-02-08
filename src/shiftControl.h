#include "global.h"
#include "Arduino.h"

/*
    Pin Settings
*/
extern const int DS_pin;
extern const int STCP_pin;
extern const int SHCP_pin;
extern const int MR_pin;

extern bool ledMatrix[5][32];
extern bool allOffLeds[5][32];
extern bool allOnLeds[5][32];

/*
    Stores the Values of the registers
*/
extern bool shiftValues[32];

extern int lastColumn;
extern int lastLevel;

void initShift();

/*
      Writes the content of the shift register value array out.
*/
void writeToShift();

/*
    Sets one LED with the given stage/ level and column to the given status
*/
void writeLED(int stage, int column, bool statusValue);

/*
    resets the shift register Values => LEDs off and mode specific values
*/
void resetLEDs();

void showMatrixForTime(int timeInMilli);
void light_all(int delayBetweenStages);
