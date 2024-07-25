#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <Arduino.h>
#include "BluetoothHandler.h"
#include "TrafficLights.h"
#include "timer.h"
#include "street_functions.h"

extern uint8_t action[5];

void GET_NEW_STATE(uint8_t *State_arr);

#endif