# Building From Source
If you want to contribute to the project or fork it and develop something on your own, you will need to follow the steps below:

## Installing Dependencies
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

- **libjsoncpp-dev:**
Run:
```
sudo apt-get install  
```

- **SQLite 3:**
Run:
```
sudo apt-get install libsqlite3-dev
```

- **gTest:**
Run:
```
sudo apt-get install libgtest-dev
```

- **gMock:**
Run:
```
sudo apt-get install libgmock-dev
```

- **python:**
    - python3 installation
    - ```python -m venv .```
    - ```source bin/activate```
    - ```pip install requests```
    - ```pip install art```

## Compiling
If you are also running on a aarch64 linux machine like the RPi 5, then all you need to do to is run the build.sh script located in the DaVinciRuntime directory:
```
./build.sh
```


## Running Tests
- **gTest Unit tests:** run the *runTests* executable that can be found in the *cmake/build* folder after compiling the DaVinciRuntime project:
    - Run all unit tests: ```./cmake/build/runTests```
- **Python Integration tests**: run the *runAllPy.py* scripts in the tests directory:
    - Start the Runtime: ``` ./cmake/build/DaVinciRuntime```
    - Enter the test directory: ``` cd DaVinciRuntime/test```
    - Run all integration tests: ``` python3 runAllPy.py```

## Viewing Code Coverage Reports
The code coverage reports are generated automatically when running the unit test suites. To view the report, open the *index.html* file in cmake/build/coverage

## Scripts and Utilities

In the *Scripts* we have included scripts that you might find useful when verifying your environment is good to go