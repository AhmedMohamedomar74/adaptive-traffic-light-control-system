import random
import serial

def Send_To_MC(data, port='COM1', baud_rate=9600, start_flag='W', response_expected='R'):
    def send_start_flag(ser):
        ser.write(start_flag.encode())

    def send_data(ser, data):
        if isinstance(data, int):
            data = [data]

        data_length = len(data)
        ser.write(bytes([data_length]))
        for number in data:
            ser.write(bytes([number]))

    def receive_response(ser):
        response = ser.read(1)  # Adjust the buffer size if needed
        if response == response_expected.encode():
            print(f"Received '{response_expected}' signal from the microcontroller")
            return True
        else:
            print(f"Unexpected response: {response.decode()}")
            return False

    try:
        with serial.Serial(port, baud_rate, timeout=0.1) as ser:
            send_start_flag(ser)
            while not receive_response(ser):  # Wait until the expected response is received
                pass
            send_data(ser, data)
    except serial.SerialException as e:
        print(f"Error: {e}")
        return None

while True:
    # Example 1: Send a single number
    # Send_To_MC(data=9, port='COM1', baud_rate=9600)
    # Example 2: Send a list of four random numbers
    random_numbers = [random.randint(0, 16) for _ in range(4)]
    Send_To_MC(data=random_numbers, port='COM3', baud_rate=9600)