#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

// Function prototypes
void timer_setup();
void timer_seconds(int seconds);
bool isTimerElapsed();

#endif // TIMER_H
