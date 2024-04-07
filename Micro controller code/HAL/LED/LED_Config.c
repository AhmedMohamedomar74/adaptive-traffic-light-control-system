#include "LED_Config.h"
// please enter the the id of all leds in these enum
typedef enum
{
    led0,
    led1,
    led2,
    legnth,
}LED_ID_t;
u8 NumberOfLeds = legnth;
// please enter the the specs of leds
LED_T Arr_Leds[legnth] = {
    {led0, LED_PORT0, LED_PIN0},
    {led1, LED_PORT0, LED_PIN1},
    {led2, LED_PORT0, LED_PIN2}};
