#include <stdint.h>
#include "HardwareSerial.h"
#include "Application.h"

uint8_t State_junction_0[4] = {0x00, 0x01, 0x02, 0x03};
uint8_t action[5] = {4, 4, 4, 4, 4};

void GET_NEW_STATE(uint8_t * State_arr)
{
    if (newDataReceived)
    {

        switch (receivedData[0])
        {
        case 'S':
            SerialBT.write(State_arr, 4);
            break;
        case 'A':
            action[0] = receivedData[1];
            action[1] = receivedData[2];
            Handle_action_green(action[0]);
            timer_seconds(action[1] -2);
            Serial.write("The action is for lane ");
            Serial.print(action[0]);
            Serial.write("For Duration = ");
            Serial.println(action[1]);
        default:
            break;
        }
        newDataReceived = false; // Reset the flag after processing data
    }
}
