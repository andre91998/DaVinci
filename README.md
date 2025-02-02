# DaVinci
An open source project for IOT and XR enthusiasts

## Setup

### Raspberry Pi
Our reference configuration uses a Raspberry Pi 5 running Ubuntu. If you are configuring a recently purchased Raspberry Pi, follow the next steps. If not, jump to the next section. 

**Note:** A Raspberry Pi was used for cost purposes, but any linux machine should do.

**Note II:** Raspberry Pi 5 runs a aarch64 architecture. If your linux machine is running on another architecture, please make sure you compile dependencies and our source code for your specific architecture.

### HiveMQ MQTT Broker
To setup a HiveMQ MQTT broker on your linux machine follow the documented setup process [here](https://docs.hivemq.com/hivemq/latest/user-guide/install-hivemq.html#linux)

**Note:** Once setup, you can access the HiveMQ Control Center via browser at *your.linux.server.ip:8080* and can login with username *admin* and password *hivemq*

### Sensor Connection
Your Sensor configuration will vary based on what sensors you are using, but the most important thing is to configure them to submit data to the HiveMQ Broker setup in the previous step. Some very important details include:

- Configuring the topic that the sensor is submitting to
- Configuring the IP and port the sensor is submitting to: will be *your.linux.server.ip:1883* if you use the HiveMQ default configurations

### Running the DaVinci Runtime

### Running the DaVinci Hub

## Building From Source
If you want to contribute to the project or fork it and develop something on your own, you will need to follow the steps below:

### Installing Dependencies
#### Runtime
Thee following dependencies must be compiled from source for your architecture if you are planning to contribute to the project or build DaVinci from source. Below is the process to do so.

**Note:** we recommend installing all these dependencies in a consolidated dependencies folder. For the following documentation, the dependencies are located at *~/dependencies/*


-  **PahoMqttCpp:**

```
$ sudo apt-get install build-essential gcc make cmake
$ sudo apt-get install libssl-dev
$ sudo apt-get install doxygen graphviz
```
Then build Paho for C++ and C from source:
```
$ git clone https://github.com/eclipse/paho.mqtt.cpp
$ cd paho.mqtt.cpp
$ git co v1.5.0

$ git submodule init
$ git submodule update

$ cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON
$ sudo cmake --build build/ --target install
```

- **gRPC:**
Follow the setup instructions located [here](https://grpc.io/docs/languages/cpp/quickstart/#setup)

- **gTest:**

- **python:**
python3 installation
python -m venv .

#### Hub

## Scripts and Utilities

In the *Scripts* we have included scripts that you might find usefull when verifying your environment is good to go
