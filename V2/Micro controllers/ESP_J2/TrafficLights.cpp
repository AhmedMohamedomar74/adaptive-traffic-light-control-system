#include "esp32-hal-gpio.h"
#include "TrafficLights.h"

// Variables to keep track of timing
unsigned long startTime = 0;
unsigned long greenDuration = 0;
const unsigned long yellowDuration = 2000; // 2 seconds for yellow light
bool isGreen = false;
bool isYellow = false;
char currentLight = ' ';

// Function to set traffic light state
void setTrafficLight(int redPin, int yellowPin, int greenPin, bool redState, bool yellowState, bool greenState) {
    digitalWrite(redPin, redState);
    digitalWrite(yellowPin, yellowState);
    digitalWrite(greenPin, greenState);
}

void Handle_action_green(char lane)
{
  setTrafficLight(A_RED, A_YELLOW, A_GREEN, HIGH, LOW, LOW);
  setTrafficLight(B_RED, B_YELLOW, B_GREEN, HIGH, LOW, LOW);
  setTrafficLight(C_RED, C_YELLOW, C_GREEN, HIGH, LOW, LOW);
  setTrafficLight(D_RED, D_YELLOW, D_GREEN, HIGH, LOW, LOW);
  switch (lane) {
    case 0:
      setTrafficLight(A_RED, A_YELLOW, A_GREEN, LOW, LOW, HIGH);
      break;
    case 1:
      setTrafficLight(B_RED, B_YELLOW, B_GREEN, LOW, LOW, HIGH);
      break;
    case 2:
      setTrafficLight(C_RED, C_YELLOW, C_GREEN, LOW, LOW, HIGH);
      break;
    case 3:
      setTrafficLight(D_RED, D_YELLOW, D_GREEN, LOW, LOW, HIGH);
      break;
  }
}

void Handle_action_yellow(char lane)
{
  switch (lane) {
    case 0:
      setTrafficLight(A_RED, A_YELLOW, A_GREEN, LOW, HIGH, LOW);
      break;
    case 1:
      setTrafficLight(B_RED, B_YELLOW, B_GREEN,  LOW, HIGH, LOW);
      break;
    case 2:
      setTrafficLight(C_RED, C_YELLOW, C_GREEN,  LOW, HIGH, LOW);
      break;
    case 3:
      setTrafficLight(D_RED, D_YELLOW, D_GREEN, LOW, HIGH, LOW);
      break;
  }
}

void setupTrafficLights() {
    // Initialize all the traffic light pins as outputs
    pinMode(A_RED, OUTPUT);
    pinMode(A_YELLOW, OUTPUT);
    pinMode(A_GREEN, OUTPUT);

    pinMode(B_RED, OUTPUT);
    pinMode(B_YELLOW, OUTPUT);
    pinMode(B_GREEN, OUTPUT);

    pinMode(C_RED, OUTPUT);
    pinMode(C_YELLOW, OUTPUT);
    pinMode(C_GREEN, OUTPUT);

    pinMode(D_RED, OUTPUT);
    pinMode(D_YELLOW, OUTPUT);
    pinMode(D_GREEN, OUTPUT);

    // Set all lights to red initially
    setTrafficLight(A_RED, A_YELLOW, A_GREEN, HIGH, LOW, LOW);
    setTrafficLight(B_RED, B_YELLOW, B_GREEN, HIGH, LOW, LOW);
    setTrafficLight(C_RED, C_YELLOW, C_GREEN, HIGH, LOW, LOW);
    setTrafficLight(D_RED, D_YELLOW, D_GREEN, HIGH, LOW, LOW);
}

