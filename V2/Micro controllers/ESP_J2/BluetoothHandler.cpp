#include "BluetoothHandler.h"

BluetoothSerial SerialBT;
uint8_t receivedData[3];
bool newDataReceived = false;

void myBluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    // Check the event type
    if (event == ESP_SPP_DATA_IND_EVT)
    {
        // This event indicates data has been received
        // Access the data and its length
        uint8_t *data = param->data_ind.data;
        uint16_t length = param->data_ind.len;
        for (uint16_t i = 0; i < length && i < sizeof(receivedData); i++)
        {
            receivedData[i] = data[i];
        }
        // Set flag to indicate new data has been received
        newDataReceived = true;
    }
    else if (event == ESP_SPP_OPEN_EVT)
    {
        // Handle the event when a connection is opened
        Serial.println("Bluetooth connection opened.");
    }
    else if (event == ESP_SPP_CLOSE_EVT)
    {
        // Handle the event when a connection is closed
        Serial.println("Bluetooth connection closed.");
    }
}

void Bluetooth_setup()
{
    SerialBT.begin("J2"); // Start Bluetooth and name it "ESP32_BT"
    Serial.println("Bluetooth started. Waiting for connections...");
    // Register the callback function for Bluetooth events
    SerialBT.register_callback(myBluetoothCallback);
}

void sendArrayOverBluetooth(uint8_t *array, size_t length)
{
    SerialBT.write(array, length);
}
