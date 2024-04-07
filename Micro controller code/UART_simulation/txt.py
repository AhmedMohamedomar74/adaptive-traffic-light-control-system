
import serial

def receive_data(serial_port, start_flag):
    received_data = bytearray()
    start_flag_received = False
    # Open serial port
    with serial.Serial(serial_port, 9600, timeout=0.1) as ser:
        while not start_flag_received:
            write_dat = ser.write(1)
            received_byte = ser.read(1)
            if received_byte == start_flag:
                start_flag_received = True
                print("Start flag received. Waiting for data...")
                received_byte = ser.read(1)
                if received_byte >= 0x00 :
                    print(f"The length of data = {received_byte}")
                    # Receive 20 bytes after start flag
                    print(f"Receiving {received_byte} bytes of data...")
                    for _ in range(received_byte):
                        received_byte = ser.read(1)
                        received_data.extend(received_byte)
                    print(f"Received data: {received_data}")
                else:
                    print(f"the legnth of data is unknown,received_byte = {received_byte}")    
# Replace 'COM2' with your Arduino's serial port
serial_port = 'COM2'
start_flag = b'\x01'  # Replace with your specific start flag

receive_data(serial_port, start_flag)
