#include "timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

TimerHandle_t timerHandle = NULL;
volatile bool timeElapsed = false; // Flag to indicate if timer has elapsed
volatile unsigned long targetSeconds = 1; // Target seconds for the timer

// Timer callback function
void timerCallback(TimerHandle_t xTimer) {
  // Set the flag to true when the timer expires
  timeElapsed = true;
}

void timer_setup() {
  // Create a software timer
  timerHandle = xTimerCreate("Timer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, timerCallback);

  if (timerHandle == NULL) {
    Serial.println("Failed to create timer!");
  }
}

void timer_seconds(int seconds) {
  // Set the target seconds for the timer
  targetSeconds = seconds;
  
  // Reset the flag
  timeElapsed = false;
  
  // Stop and delete the timer if it exists
  if (timerHandle != NULL) {
    xTimerStop(timerHandle, portMAX_DELAY);
    xTimerDelete(timerHandle, portMAX_DELAY);
    timerHandle = NULL;
  }

  // Create a new timer with the specified duration
  timerHandle = xTimerCreate("Timer", pdMS_TO_TICKS(seconds * 1000), pdFALSE, (void *)0, timerCallback);
  
  // Start the timer
  if (timerHandle != NULL) {
    if (xTimerStart(timerHandle, portMAX_DELAY) != pdPASS) {
      Serial.println("Failed to start timer!");
    }
  } else {
    Serial.println("Failed to create timer!");
  }
}

bool isTimerElapsed() {
  return timeElapsed;
}
