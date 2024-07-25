#ifndef STREET_FUNCTIONS_H
#define STREET_FUNCTIONS_H

#include <Arduino.h>

// Function declarations
void streetFunction(int streetNumber, int entryPin, int exitPin);
void cast_char_Arr(int *int_arr, uint8_t *State_arr);
uint8_t *getStateArray();
uint8_t* updateAndGetState();
void State_setup();

#endif // STREET_FUNCTIONS_H
