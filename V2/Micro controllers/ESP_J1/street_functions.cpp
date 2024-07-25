#include "street_functions.h"

// Variables
int streetCarsCounter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool flags[8] = {false, false, false, false, false, false, false, false};
int arr[4];
uint8_t State_arr[4];

void streetFunction(int streetNumber, int entryPin, int exitPin)
{
    int copy = streetNumber;
    int entrySensorValue = analogRead(entryPin); // Read entry LDR value
    int exitSensorValue = analogRead(exitPin);   // Read exit LDR value

    streetNumber = streetNumber << 1;
    int entryId = streetNumber - 2;
    int exitId = streetNumber - 1;

    // Check if a car is entering
    if (entrySensorValue < 2800 && flags[entryId])
    {
        streetCarsCounter[entryId]++;
        flags[entryId] = false;
    }

    // Check if a car is exiting
    if (exitSensorValue < 2800 && flags[exitId])
    {
        streetCarsCounter[exitId]++; // Increment exit count
        flags[exitId] = false;
    }

    if (exitSensorValue > 2800)
    {
        flags[exitId] = true;
    }
    if (entrySensorValue > 2800)
    {
        flags[entryId] = true;
    }
}

void cast_char_Arr(int *int_arr, uint8_t *State_arr)
{
    for (int i = 0; i < 4; i++)
    {
        arr[i] = streetCarsCounter[i << 1] - streetCarsCounter[i * 2 + 1];
        if (arr[i] < 0){
          streetCarsCounter[i*2 + 1 ] = streetCarsCounter[i << 1];
          arr[i] = streetCarsCounter[i << 1] - streetCarsCounter[i * 2 + 1];
        }
        State_arr[i] = (uint8_t)int_arr[i];
    }
}

uint8_t *getStateArray()
{
    cast_char_Arr(arr, State_arr);
    return State_arr;
}

void State_setup()
{
  streetFunction(1, 36, 39);
  streetFunction(2, 34, 35);
  streetFunction(3, 32, 33);
  streetFunction(4, 25, 26);
}
