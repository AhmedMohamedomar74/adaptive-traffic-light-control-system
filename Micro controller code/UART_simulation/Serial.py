import serial
import time

def Read_From_MC(port='COM2', baud_rate=9600):
    def send_start_flag(ser):
        ser.write(b'S')  # Send start flag as a byte

    def receive_data_length(ser):
        length = ser.read(1)  # Read 1 byte for the data length
        return int.from_bytes(length, byteorder='big')

    def receive_data(ser, length):
        data = ser.read(length)  # Read the specified number of bytes for data
        return [int(byte) for byte in data]
    
    def replace_characters(data_list):
        replacements = {'@': 16, '?': 15, '>': 14, '=': 13, '<': 12, ';': 11, ':': 10}
        replaced_list = [replacements.get(str(value), value) for value in data_list]
        return replaced_list
    
    try:
        with serial.Serial(port, baud_rate, timeout=0.1) as ser:
            send_start_flag(ser)
            # time.sleep(1)  # Wait for Arduino to process and respond

            data_length = receive_data_length(ser)
            print(f"Received data length: {data_length} bytes")

            if data_length <= 0:
                print("Error: Invalid data length received")
                return None
            else:
                received_data = receive_data(ser, data_length)
                # print(f"Received data: {received_data}")
                return replace_characters(received_data)

    except serial.SerialException as e:
        print(f"Error: {e}")
        return None

def Write_To_MC(data_list, port='COM2', baud_rate=9600):
    def send_start_flag(ser):
        ser.write(b'W')  # Send start flag as a byte

    def send_data_length(ser, length):
        ser.write(length.to_bytes(1, byteorder='big'))  # Send 1 byte for the data length

    def send_data(ser, data_list):
        for value in data_list:
            ser.write(bytes([value]))  # Send each value as a single byte

    try:
        with serial.Serial(port, baud_rate, timeout=0.1) as ser:
            send_start_flag(ser)
            # time.sleep(1)  # Wait for Arduino to process and respond

            data_length = len(data_list)
            print(f"Sending data length: {data_length} bytes")
            send_data_length(ser, data_length)

            print(f"Sending data: {data_list}")
            send_data(ser, data_list)

    except serial.SerialException as e:
        print(f"Error: {e}")
if __name__ == "__main__":
# this way to recieve data from MC to Machine learning model   
    
    # received_data = Read_From_MC(port='COM2', baud_rate=9600)
    # # Use the received_data as needed
    # print(received_data)
    
    data_to_send = [4, 6, 7, 255]
    Write_To_MC(data_to_send, port='COM2', baud_rate=9600) 
