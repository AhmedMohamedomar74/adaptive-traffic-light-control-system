#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H

#include <Arduino.h>

// Define pins for Traffic Lights A, B, C, and D
#define A_RED 27
#define A_YELLOW 14
#define A_GREEN 12

#define B_RED 15
#define B_YELLOW 22
#define B_GREEN 23

#define C_RED 5
#define C_YELLOW 18
#define C_GREEN 19

#define D_RED 4
#define D_YELLOW 16
#define D_GREEN 17

// Function declarations
void setTrafficLight(int redPin, int yellowPin, int greenPin, bool redState, bool yellowState, bool greenState);
void manageTrafficLight(char light, int duration);
void setupTrafficLights();
void updateTrafficLights();
void Handle_action_green(char lane);
void Handle_action_yellow(char lane);

#endif
