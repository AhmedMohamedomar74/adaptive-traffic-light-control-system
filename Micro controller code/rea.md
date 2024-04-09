# Adaptive Traffic Light Control Embedded System

## Overview
This project implements an adaptive traffic light control system using an embedded solution. The system utilizes an I2C network with multiple slaves representing junctions and a single master to coordinate traffic flow. Each slave node collects data on the number of cars at its respective junction and communicates this information to the master node. The master node then sends this data to a reinforcement machine learning model via UART for decision-making on traffic light timings. Additionally, the master node sends random states to three slaves via UART for simulation purposes.

## System Architecture
The system architecture consists of the following components:
- Embedded microcontroller boards for master and slave nodes
- I2C communication protocol for interconnecting the nodes
- UART communication for linking the master node with the reinforcement machine learning model and sending random states to three slaves
- Reinforcement machine learning model for adaptive traffic light control

## Simulation Image (Proteus)
*Insert simulation image here*

![Proteus Simulation](insert_proteus_image_url_here)

## Model Actions
The reinforcement machine learning model takes input from the microcontrollers and generates actions based on the states received. The following images illustrate the actions taken by the model:

1. State: Number of cars in each of the four ways in the junction
   Action: Which way should be open
   *Insert image of action here*

   ![Action](insert_action_image_url_here)

2. Action 1 (for the first two states, which are the same)
   *Insert image of action 1 here*

   ![Action 1](insert_action_1_image_url_here)

3. Action 1 (for the first two states, which are the same)
   *Insert image of action 1 here*

   ![Action 1](insert_action_1_image_url_here)

4. Action 2 (for the rest of the states)
   *Insert image of action 2 here*

   ![Action 2](insert_action_2_image_url_here)

5. Action 3 (for the rest of the states)
   *Insert image of action 3 here*

   ![Action 3](insert_action_3_image_url_here)
