# Advanced Traffic Light Management System with Embedded I2C Networking

This repository houses an innovative traffic light management system that leverages Reinforcement Learning (RL) and integrates an embedded solution using I2C networking to simulate traffic light control at intersections. This advanced system aims to minimize vehicle wait times at traffic signals by dynamically adjusting green light durations in response to real-time traffic conditions.

## Overview

The system models a city grid with multiple traffic light nodes. Each node represents a traffic signal at an intersection. By utilizing an embedded network of microcontrollers interconnected via I2C, the system simulates complex traffic flow scenarios. Each junction's microcontroller communicates its state to a central master controller via I2C. The master controller then sends this aggregated data to the RL model using UART. The model processes this information to determine the optimal light sequence to minimize wait times.

### System Architecture

![System Architecture Diagram](documentation\final_version.gif)

*Diagram illustrating the embedded I2C network and communication flow between microcontrollers and the RL model, facilitated by UART.*

## Embedded I2C and UART Network Integration

The system employs an I2C network where each traffic junction is equipped with a microcontroller acting as an I2C slave. These slave microcontrollers collect local traffic data and report it to a central master microcontroller. The master microcontroller acts as the I2C master, collecting data from each junction and sending it to the RL model using UART for processing.

### Components

- **Microcontrollers**: Each junction is equipped with a microcontroller functioning as an I2C slave.
- **Master Controller**: Serves as the I2C master, collecting data from all junctions and communicating with the RL model via UART.
- **Reinforcement Learning Model**: Analyzes traffic data to determine optimal traffic light configurations.
- **Communication Protocol**: Utilizes I2C for intra-controller communication and UART for interfacing with the RL model.

## Getting Started

To deploy and test this system, follow these setup steps:

### Prerequisites

- SUMO (Simulation of Urban MObility) for traffic simulation.
- Python 3.8 and necessary libraries (see `requirements.txt` for dependencies).
- Appropriate microcontrollers and setup for the I2C network.
- UART interface for communication between the master microcontroller and the machine learning model.

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/AhmedMohamedomar74/Graduation-broject.git

2. **Install Dependencies**

   ```bash
   pip install -r requirements.txt

3. **SUMO GUI**

   Download and install the SUMO GUI from [the official website](https://sumo.dlr.de/docs/Downloads.php) if you 
   haven't already.

### Configuring the Network

1. **Microcontroller Setup**

   Configure each microcontroller as an I2C slave for your traffic junctions, with one microcontroller designated as the master. Detailed instructions for this setup are beyond the scope of this document but can be found in the `Micro controller code` folder.

2. **Traffic Simulation**

   Use SUMO to create your traffic network and generate simulation scenarios. Place your network and route files in the `maps` directory.

3. **Running Simulations**

   After configuring your embedded network and preparing your simulation environment, you can train your model using the provided scripts.

   ```bash
   python train.py --train -e 50 -m model_name -s 500
  
### Embedded System Description

For detailed information about the embedded system setup and configuration, please refer to the `Microcontroller_code` folder. Inside this folder, you will find documentation and code related to the configuration of microcontrollers for the embedded system used in this project.  