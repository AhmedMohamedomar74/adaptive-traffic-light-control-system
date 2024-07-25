
```mermaid
graph TD;
    A[Setup] -->|Initialize serial communication| B(Serial.begin(9600));
    A -->|Initialize Bluetooth| C(Bluetooth_setup);
    A -->|Setup Traffic Lights| D(setupTrafficLights);
    A -->|Setup Timer| E(timer_setup);

    F[Loop] -->|Setup State| G(State_setup);
    F -->|Get State Array| H(getStateArray);
    F -->|Get New State| I(GET_NEW_STATE(stateArray));
    F -->|Check Timer| J{isTimerElapsed};

    J -->|Timer Elapsed| K[Handle Action Yellow(action[0])];
    J -->|Print State Array| L[Serial.print("this is state = {", stateArray[0], ",", stateArray[1], ",", stateArray[2], ",", stateArray[3], "}");];

    I -->|New Data Received| M{receivedData[0]};
    M -->|State| N[SerialBT.write(State_arr, 4)];
    M -->|Action| O[Handle Action Green(action[0])];
    O -->|Set Timer| P[timer_seconds(action[1] - 2)];
    O -->|Serial Write| Q[Serial.write("The action is for lane ")];
    O -->|Serial Print| R[Serial.print(action[0])];
    O -->|Serial Write Duration| S[Serial.write("For Duration = ")];
    O -->|Serial Print Duration| T[Serial.println(action[1])];

    style A fill:#f9f,stroke:#333,stroke-width:4px;
    style F fill:#ff9,stroke:#333,stroke-width:4px;
    style J fill:#9f9,stroke:#333,stroke-width:4px;
    style M fill:#9ff,stroke:#333,stroke-width:4px;
