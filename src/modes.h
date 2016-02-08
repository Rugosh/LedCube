#include "global.h"
#include "shiftControl.h"

/*
    Run mode of the LED Cube
*/
extern char volatile mode;

void handle_mode();

void mode_info();
void mode_loop_over(int delayValue);
void mode_random();
void mode_random_flip();

/*
    Checks if the given value is an allowed mode key
*/
bool isMode(char value);
