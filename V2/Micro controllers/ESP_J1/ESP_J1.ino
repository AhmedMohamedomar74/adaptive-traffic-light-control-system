#include "Application.h"

void setup()
{
  Serial.begin(9600);
  Bluetooth_setup();
  setupTrafficLights();
  timer_setup();
}

void loop()
{
  State_setup();
  uint8_t *stateArray = getStateArray();
  GET_NEW_STATE(stateArray);
  if (isTimerElapsed())
  {
    Serial.println("I am under Condiaton");
    Handle_action_yellow(action[0]);
  }
  Serial.print("this is state = {");
  Serial.print(stateArray[0]);
  Serial.print(",");
  Serial.print(stateArray[1]);
  Serial.print(",");
  Serial.print(stateArray[2]);
  Serial.print(",");
  Serial.print(stateArray[3]);
  Serial.println("}");
}
