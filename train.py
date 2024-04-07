from __future__ import absolute_import
from __future__ import print_function

import os
import sys
import time
import optparse
import random
import serial
import numpy as np
import torch
import torch.optim as optim
import torch.nn.functional as F
import torch.nn as nn
import matplotlib.pyplot as plt
import traci
import time


# we need to import python modules from the $SUMO_HOME/tools directory
if "SUMO_HOME" in os.environ:
    tools = os.path.join(os.environ["SUMO_HOME"], "tools")
    sys.path.append(tools)
else:
    sys.exit("please declare environment variable 'SUMO_HOME'")

from sumolib import checkBinary  # noqa
import traci  # noqa

def generate_random_number():
    return random.randint(0, 15)

def delay_ms(milliseconds):
    time.sleep(milliseconds / 1000.0)

def Read_From_MC(port='COM2', baud_rate=9600, number=0):
    def send_start_flag(ser):
        ser.write(b'S')  # Send start flag as a byte
        # delay_ms(10)     # Send number that represent Index of the junction
        ser.write(number.to_bytes(1, byteorder='big'))  # Send number as a byte

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

            if data_length != 4:
                print("Error: Invalid data length received")
                return None
            else:
                received_data = receive_data(ser, data_length)
                # Perform additional processing based on the 'number' argument
                # processed_data = received_data * number
                # print(f"Received data: {received_data}")
                # delay_ms(15)
                return replace_characters(received_data)
                

    except serial.SerialException as e:
        print(f"Error: {e}")
        return None


def send_data_to_arduino(data_list, arduino_port, baud_rate):
    try:
        # Open a serial connection to the Arduino
        ser = serial.Serial(arduino_port, baud_rate, timeout=1)
        print(f"Connected to Arduino on {arduino_port}.")

        # Convert the list to a string and send it to the Arduino
        data_string = ','.join(map(str, data_list))
        ser.write(data_string.encode())
        print(f"Sent data to Arduino: {data_list}")

        # Close the serial connection
        ser.close()

    except Exception as e:
        print(f"Error: {e}")

def get_vehicle_numbers(lanes):
    vehicle_per_lane = dict()
    received_data = ser.read(4)
    vehicle_per_lane = list(received_data)
    # print(vehicle_per_lane)
    return vehicle_per_lane


def get_waiting_time(lanes):
    waiting_time = 0
    for lane in lanes:
        waiting_time += traci.lane.getWaitingTime(lane)
    return waiting_time


def get_CO2Emission(lanes):
    CO2Emissio_value = 0
    for lane in lanes:
        CO2Emissio_value += traci.lane.getCO2Emission(lane)
    return CO2Emissio_value


def phaseDuration(junction, phase_time, phase_state):
    traci.trafficlight.setRedYellowGreenState(junction, phase_state)
    traci.trafficlight.setPhaseDuration(junction, phase_time)


def get_phase_index(red_yellow_green_state):
    """
    Converts the red-yellow-green state string to a corresponding phase index.

    Args:
        red_yellow_green_state (str): The RYG state string from traci.trafficlight.getRedYellowGreenState()

    Returns:
        int: The corresponding phase index (0, 1, 2, or 3)
    """

    phase_map = {
        "GGGrrrrrrrrr": 0,
        "rrrGGGrrrrrr": 1,
        "rrrrrrGGGrrr": 2,
        "rrrrrrrrrGGG": 3,
    }

    return phase_map.get(red_yellow_green_state, None)  # Return None for unknown states


def get_phase_indices_for_junctions(junction_ids):
    """
    Retrieves the phase indices for multiple junctions in the desired string format.

    Args:
        junction_ids (list): A list of traffic light IDs.

    Returns:
        str: A comma-separated string of junction index.phase index pairs.
    """

    phase_indices_str = []
    for index, junction_id in enumerate(junction_ids, start=1):
        current_phase_string = traci.trafficlight.getRedYellowGreenState(junction_id)
        phase_index = get_phase_index(current_phase_string)
        phase_indices_str.append(f"{index}.{phase_index}")  # Format as string

    return ",".join(phase_indices_str)  # Join strings with commas




junction_ids = ['gneJ3', 'gneJ7','gneJ11']

class Model(nn.Module):
    def __init__(self, lr, input_dims, fc1_dims, fc2_dims, n_actions):
        super(Model, self).__init__()
        self.lr = lr
        self.input_dims = input_dims
        self.fc1_dims = fc1_dims
        self.fc2_dims = fc2_dims
        self.n_actions = n_actions

        self.linear1 = nn.Linear(self.input_dims, self.fc1_dims)
        self.linear2 = nn.Linear(self.fc1_dims, self.fc2_dims)
        self.linear3 = nn.Linear(self.fc2_dims, self.n_actions)

        self.optimizer = optim.Adam(self.parameters(), lr=self.lr)
        self.loss = nn.MSELoss()
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.to(self.device)

    def forward(self, state):
        x = F.relu(self.linear1(state))
        x = F.relu(self.linear2(x))
        actions = self.linear3(x)
        return actions


class Agent:
    def __init__(
        self,
        gamma,
        epsilon,
        lr,
        input_dims,
        fc1_dims,
        fc2_dims,
        batch_size,
        n_actions,
        junctions,
        max_memory_size=100000,
        epsilon_dec=5e-4,
        epsilon_end=0.05,
    ):
        self.gamma = gamma
        self.epsilon = epsilon
        self.lr = lr
        self.batch_size = batch_size
        self.input_dims = input_dims
        self.fc1_dims = fc1_dims
        self.fc2_dims = fc2_dims
        self.n_actions = n_actions
        self.action_space = [i for i in range(n_actions)]
        self.junctions = junctions
        self.max_mem = max_memory_size
        self.epsilon_dec = epsilon_dec
        self.epsilon_end = epsilon_end
        self.mem_cntr = 0
        self.iter_cntr = 0
        self.replace_target = 100

        self.Q_eval = Model(
            self.lr, self.input_dims, self.fc1_dims, self.fc2_dims, self.n_actions
        )
        self.memory = dict()
        for junction in junctions:
            self.memory[junction] = {
                "state_memory": np.zeros(
                    (self.max_mem, self.input_dims), dtype=np.float32
                ),
                "new_state_memory": np.zeros(
                    (self.max_mem, self.input_dims), dtype=np.float32
                ),
                "reward_memory":np.zeros(self.max_mem, dtype=np.float32),
                "action_memory": np.zeros(self.max_mem, dtype=np.int32),
                "terminal_memory": np.zeros(self.max_mem, dtype=bool),
                "mem_cntr": 0,
                "iter_cntr": 0,
            }


    def store_transition(self, state, state_, action,reward, done,junction):
        index = self.memory[junction]["mem_cntr"] % self.max_mem
        self.memory[junction]["state_memory"][index] = state
        self.memory[junction]["new_state_memory"][index] = state_
        self.memory[junction]['reward_memory'][index] = reward
        self.memory[junction]['terminal_memory'][index] = done
        self.memory[junction]["action_memory"][index] = action
        self.memory[junction]["mem_cntr"] += 1

    def choose_action(self, observation):
        state = torch.tensor([observation], dtype=torch.float).to(self.Q_eval.device)
        if np.random.random() > self.epsilon:
            actions = self.Q_eval.forward(state)
            action = torch.argmax(actions).item()
        else:
            action = np.random.choice(self.action_space)
        return action
    
    def reset(self,junction_numbers):
        for junction_number in junction_numbers:
            self.memory[junction_number]['mem_cntr'] = 0

    def save(self,model_name):
        torch.save(self.Q_eval.state_dict(),f'models/{model_name}.bin')

    def learn(self, junction):
        self.Q_eval.optimizer.zero_grad()

        batch= np.arange(self.memory[junction]['mem_cntr'], dtype=np.int32)

        state_batch = torch.tensor(self.memory[junction]["state_memory"][batch]).to(
            self.Q_eval.device
        )
        new_state_batch = torch.tensor(
            self.memory[junction]["new_state_memory"][batch]
        ).to(self.Q_eval.device)
        reward_batch = torch.tensor(
            self.memory[junction]['reward_memory'][batch]).to(self.Q_eval.device)
        terminal_batch = torch.tensor(self.memory[junction]['terminal_memory'][batch]).to(self.Q_eval.device)
        action_batch = self.memory[junction]["action_memory"][batch]

        q_eval = self.Q_eval.forward(state_batch)[batch, action_batch]
        q_next = self.Q_eval.forward(new_state_batch)
        q_next[terminal_batch] = 0.0
        q_target = reward_batch + self.gamma * torch.max(q_next, dim=1)[0]
        loss = self.Q_eval.loss(q_target, q_eval).to(self.Q_eval.device)

        loss.backward()
        self.Q_eval.optimizer.step()

        self.iter_cntr += 1
        self.epsilon = (
            self.epsilon - self.epsilon_dec
            if self.epsilon > self.epsilon_end
            else self.epsilon_end
        )


def run(train=True,model_name="model",epochs=50,steps=500,ard=False):
    if ard:
        arduino = serial.Serial(port='COM1', baudrate=9600, timeout=.1)
        def write_read(x):
            arduino.write(bytes(str(x), 'utf-8'))
            time.sleep(0.05)
            data = arduino.readline()
            return data
    """execute the TraCI control loop"""
    epochs = epochs
    steps = steps
    best_time = np.inf
    total_time_list = list()
    CO2Emission_list = list()
    traci.start(
        [checkBinary("sumo"), "-c", "configuration.sumocfg", "--tripinfo-output", "maps/tripinfo.xml"]
    )
    all_junctions = traci.trafficlight.getIDList()
    junction_numbers = list(range(len(all_junctions)))

    brain = Agent(
        gamma=0.99,
        epsilon=0.0,
        lr=0.1,
        input_dims=4,
        # input_dims = len(all_junctions) * 4,
        fc1_dims=256,
        fc2_dims=256,
        batch_size=1024,
        n_actions=4,
        junctions=junction_numbers,
    )

    if not train:
        brain.Q_eval.load_state_dict(torch.load(f'models/{model_name}.bin',map_location=brain.Q_eval.device))

    print(brain.Q_eval.device)
    traci.close()
    for e in range(epochs):
        if train:
            traci.start(
            [checkBinary("sumo"), "-c", "configuration.sumocfg", "--tripinfo-output", "tripinfo.xml"]
            )
        else:
            traci.start(
            [checkBinary("sumo-gui"), "-c", "configuration.sumocfg", "--tripinfo-output", "tripinfo.xml"]
            )

        print(f"epoch: {e}")
        select_lane = [
            ["yyyrrrrrrrrr", "GGGrrrrrrrrr"],
            ["rrryyyrrrrrr", "rrrGGGrrrrrr"],
            ["rrrrrryyyrrr", "rrrrrrGGGrrr"],
            ["rrrrrrrrryyy", "rrrrrrrrrGGG"],
        ]

        # select_lane = [
        #     ["yyyyrrrrrrrrrrrr", "GGGGrrrrrrrrrrrr"],
        #     ["rrrryyyyrrrrrrrr", "rrrrGGGGrrrrrrrr"],
        #     ["rrrrrrrryyyyrrrr", "rrrrrrrrGGGGrrrr"],
        #     ["rrrrrrrrrrrryyyy", "rrrrrrrrrrrrGGGG"],
        # ]

        step = 0
        total_time = 0
        total_CO2Emission = 0
        min_duration = 5
        
        traffic_lights_time = dict()
        prev_wait_time = dict()
        prev_vehicles_per_lane = dict()
        prev_action = dict()
        all_lanes = list()
        states = dict()
        List_Selected_Lanes = [0,0,0,0]
        for junction_number, junction in enumerate(all_junctions):
            prev_wait_time[junction] = 0
            prev_action[junction_number] = 0
            traffic_lights_time[junction] = 0
            prev_vehicles_per_lane[junction_number] = [0] * 4
            # prev_vehicles_per_lane[junction_number] = [0] * (len(all_junctions) * 4) 
            all_lanes.extend(list(traci.trafficlight.getControlledLanes(junction)))

        while step <= steps:
            traci.simulationStep()
            for junction_number, junction in enumerate(all_junctions):
                controled_lanes = traci.trafficlight.getControlledLanes(junction)
                waiting_time = get_waiting_time(controled_lanes)
                total_time += waiting_time
                CO2Emissio_value = get_CO2Emission(controled_lanes)
                total_CO2Emission += CO2Emissio_value
                if traffic_lights_time[junction] == 0:
                    states = Read_From_MC(port='COM2', baud_rate=9600,number=junction_number)
                    if(None == states):
                        vehicles_per_lane = [0,0,0,0]
                    else :
                        vehicles_per_lane = states
                    # vehicles_per_lane = get_vehicle_numbers(all_lanes)
                    delay_ms(15)
                    print(f"vehicles_per_lane from MC for Junction {junction_number} = {vehicles_per_lane}")
                    #storing previous state and current state
                    reward = -1 *  waiting_time
                    state_ =  vehicles_per_lane
                    state = prev_vehicles_per_lane[junction_number]
                    prev_vehicles_per_lane[junction_number] = state_
                    brain.store_transition(state, state_, prev_action[junction_number],reward,(step==steps),junction_number)
                    
                    #selecting new action based on current state
                    lane = brain.choose_action(state_)
                    # print(f"Junction number = {junction_number}")
                    # if (lane == 1):
                    #    List_Selected_Lanes[junction_number] = 1
                    # elif (lane == 2):
                    #    List_Selected_Lanes[junction_number] = 2
                    # elif (lane == 3):
                    #    List_Selected_Lanes[junction_number] = 3
                    # elif (lane == 0):
                    #    List_Selected_Lanes[junction_number] = 0
                    # else :
                    #     print(f"lane = {lane}")           
                    prev_action[junction_number] = lane
                    phaseDuration(junction, 6, select_lane[lane][0])
                    phaseDuration(junction, min_duration + 10, select_lane[lane][1])
                    if (junction_number == 4):
                        selected_lanes_list = list(prev_action.values())
                        # send_data_to_arduino(data_list=selected_lanes_list,arduino_port="COM1",baud_rate=9600)        
                        print(f"Selected Lanes = {selected_lanes_list}")
                    if ard:
                            phase_indices_by_junction = get_phase_indices_for_junctions(junction_ids)
                            write_read(phase_indices_by_junction)
                            write_read("\n")
                            print(phase_indices_by_junction)
                    traffic_lights_time[junction] = min_duration + 10
                    if train:
                        brain.learn(junction_number)    
                else:
                    traffic_lights_time[junction] -= 1 
            
            step += 1
        print("total_time",total_time)
        print("Total_emssiom",total_CO2Emission)
        total_time_list.append(total_time)
        CO2Emission_list.append(total_CO2Emission)

        if total_time < best_time:
            best_time = total_time
            if train:
                brain.save(model_name)

        traci.close()
        sys.stdout.flush()
        if not train:
            break
    if train:
        # Plot the first curve
        plt.plot(list(range(len(total_time_list))), total_time_list)
        plt.xlabel("epochs")
        plt.ylabel("total time")
        plt.title("Total Time vs Epochs")  # Add a title for clarity
        plt.grid(True)  # Add grid for better visualization
        plt.savefig(f'plots/time_vs_epoch_{model_name}.png')
        plt.close()  # Close the current figure to create a new one for the next curve

        # Plot the second curve
        plt.plot(list(range(len(CO2Emission_list))), CO2Emission_list)
        plt.xlabel("epochs")
        plt.ylabel("CO2Emission")
        plt.title("CO2 Emission vs Epochs")  # Add a title for clarity
        plt.grid(True)  # Add grid for better visualization
        plt.savefig(f'plots/CO2Emission_vs_epoch_{model_name}.png')
        plt.show()  # Optional: Show the plot for visual inspection

def get_options():
    optParser = optparse.OptionParser()
    optParser.add_option(
        "-m",
        dest='model_name',
        type='string',
        default="model",
        help="name of model",
    )
    optParser.add_option(
        "--train",
        action = 'store_true',
        default=False,
        help="training or testing",
    )
    optParser.add_option(
        "-e",
        dest='epochs',
        type='int',
        default=50,
        help="Number of epochs",
    )
    optParser.add_option(
        "-s",
        dest='steps',
        type='int',
        default=500,
        help="Number of steps",
    )
    optParser.add_option(
       "--ard",
        action='store_true',
        default=False,
        help="Connect Arduino", 
    )
    options, args = optParser.parse_args()
    return options


# this is the main entry point of this script
if __name__ == "__main__":
    options = get_options()
    model_name = options.model_name
    train = options.train
    epochs = options.epochs
    steps = options.steps
    ard = options.ard
    run(train=train,model_name=model_name,epochs=epochs,steps=steps,ard=ard)