#include <BluetoothSerial.h>
#include <LiquidCrystal.h>
#include <esp32-hal-adc.h>
#include <driver/adc.h>

// Bluetooth Serial instance
BluetoothSerial SerialBT;

const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Buffer to hold received data
String receivedData = "";
// Flag to check if new data has been received
bool newDataReceived = false;

uint8_t Phase_one = 0;
uint8_t Phase_two = 0;

// Callback function to handle incoming Bluetooth data and events
void myBluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t* param) {
  // Check the event type
  if (event == ESP_SPP_DATA_IND_EVT) {
    // This event indicates data has been received
    // Access the data and its length
    uint8_t* data = param->data_ind.data;
    uint16_t length = param->data_ind.len;

    // Convert the data to a string
    receivedData = "";
    for (uint16_t i = 0; i < length; i++) {
      receivedData += (char)data[i];
    }

    // Set flag to indicate new data has been received
    newDataReceived = true;

    // Print the received data
    Serial.print("Received data: ");
    Serial.println(receivedData);
  } else if (event == ESP_SPP_OPEN_EVT) {
    // Handle the event when a connection is opened
    Serial.println("Bluetooth connection opened.");
  } else if (event == ESP_SPP_CLOSE_EVT) {
    // Handle the event when a connection is closed
    Serial.println("Bluetooth connection closed.");
  }
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");  // Start Bluetooth and name it "ESP32_BT"
  Serial.println("Bluetooth started. Waiting for connections...");

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("LCD Initialized");

  // Register the callback function for Bluetooth events
  SerialBT.register_callback(myBluetoothCallback);
  randomSeed(analogRead(ADC1_CHANNEL_4));
}

void loop() {
  // Call the Extrac_phases function only if new data has been received
  if (newDataReceived) {
    delay(100); // Add a small delay to stabilize serial output
    // Reset the flag after processing data
    lcd.clear();
    
    check_Data();
    // Operation(& Phase_one, & Phase_two);
    // Initialize the LCD
    Serial.println(Phase_one);
    Serial.println(Phase_two);
    lcd.clear();
    lcd.begin(16, 2);
    lcd.print("Phase one : ");
    lcd.print(Phase_one);
    lcd.setCursor(0, 1);
    lcd.print("Phase two : ");
    lcd.print(Phase_two);
    newDataReceived = false;
  }
}

// void Extrac_phases(String Recieved_String, unsigned char* number1, unsigned char* number2) {
//   int comma_index = Recieved_String.indexOf(',');

//   if (comma_index != -1) {
//     String num1Str = Recieved_String.substring(0, comma_index);
//     // Convert the string to an integer
//     *number1 = num1Str.toInt();
//     lcd.setCursor(0, 0);
//     lcd.print("Phase one = ");
//     lcd.print(*number1);

//     // Extract the second number as a substring after the comma
//     String num2Str = Recieved_String.substring(comma_index + 1);
//     // Convert the string to an integer
//     *number2 = num2Str.toInt();
//     lcd.setCursor(0, 1);
//     lcd.print("Phase two = ");
//     lcd.print(*number2);
//   }
// }

void Operation(uint8_t * Number_one,uint8_t * Number_two)
{
  // Debugging print statements for `Phase_one` and `Phase_two`
    Serial.print("Operation - Phase one: ");
    Serial.println(* Number_one);
    Serial.print("Operation - Phase two: ");
    Serial.println(* Number_two);
  
  
  lcd.setCursor(0, 0);
  lcd.print("Phase one = ");
  lcd.print(*Number_one);

  lcd.setCursor(0, 1);
  lcd.print("Phase two = ");
  lcd.print(*Number_two);
  
}

void check_Data() {
  // Handle data that starts with 'R'
  uint8_t arr_1[4] ;
  uint32_t action_value = 0;
  switch (receivedData.charAt(0))
  {
  case 82 :
    switch (receivedData.charAt(1))
    {
    case 1:
      Create_Random_Arr(arr_1,4);
      SerialBT.write(sizeof(arr_1));
      SerialBT.write((uint8_t*)arr_1, sizeof(arr_1));
      // You may also want to print a message for debugging purposes
      Serial.println("Sent array_one with four numbers via Bluetooth.");
      break;
    case 2:
      Create_Random_Arr(arr_1,4);
      SerialBT.write(sizeof(arr_1));
      SerialBT.write((uint8_t*)arr_1, sizeof(arr_1));
      // You may also want to print a message for debugging purposes
      Serial.println("Sent array_two with four numbers via Bluetooth.");
      break;  
    
    default:
      Serial.println(receivedData.charAt(1) + '0');
      Serial.println("I get data do not represnt junction");
      break;
    }
    break;
  case 87 :
    action_value = receivedData.charAt(2);
    switch (receivedData.charAt(1))
    {
    case 1:
      Phase_one = action_value;
      Serial.println(Phase_one);
      break;
    case 2:
      Phase_two = action_value;
      Serial.println(Phase_two);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  // if (receivedData.startsWith("R")) {
    
  //   else {
  //     Create_Random_Arr(arr_1,4);
  //     SerialBT.write(sizeof(arr_1));
  //     SerialBT.write((uint8_t*)arr_1, sizeof(arr_1));
  //     // You may also want to print a message for debugging purposes
  //     Serial.println("Sent dataToSend_two with four numbers via Bluetooth.");
  //   }
  // }
  // // Handle other data
  // else {
  //   // Perform desired operations for data that doesn't start with 'R'
  //   // e.g., call a function or handle data accordingly
  //   // Your code goes here
  //   lcd.clear();
  //   uint8_t Phase_one;
  //   uint8_t Phase_two;
  //   Extrac_phases(receivedData, &Phase_one, &Phase_two);
  // }
}




void Create_Random_Arr(uint8_t *arr, uint8_t legnth) {
  for (uint8_t i = 0; i < legnth; i++) {
    arr[i] = random(0, 15);
  }
}
