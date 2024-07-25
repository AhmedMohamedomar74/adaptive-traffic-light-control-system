#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <BluetoothSerial.h>

extern BluetoothSerial SerialBT;
extern uint8_t receivedData[3];
extern bool newDataReceived;

void myBluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
void Bluetooth_setup();
void sendArrayOverBluetooth(uint8_t *array, size_t length);

#endif // BLUETOOTH_HANDLER_H
