# DaVinci
An open source project for IOT and XR enthusiasts

## Setup

### Raspberry Pi
Our reference configuration uses a Raspberry Pi 5 running Ubuntu. If you are configuring a recently purchased Raspberry Pi, follow the next steps. If not, jump to the next section. 

**Note:** A Raspberry Pi was used for cost purposes, but any linux machine should do.

**Note II:** Raspberry Pi 5 runs a aarch64 architecture. If your linux machine is running on another architecture, please make sure you compile dependencies and our source code for your specific architecture.

### HiveMQ MQTT Broker
To setup a HiveMQ MQTT broker on your linux machine follow the process below. (For more info, see [here](https://docs.hivemq.com/hivemq/latest/user-guide/install-hivemq.html#linux))

**Note:** Once setup, you can access the HiveMQ Control Center via browser at *your.linux.server.ip:8080* and can login with username *admin* and password *hivemq*

- On the [HiveMQ Download](https://www.hivemq.com/download/) page of the official HiveMQ website, enter your email address, read and accept the terms of service, and select Download.zip to download the latest version of HiveMQ.
- Log in to your system as root user.
- Move the ZIP download file to the directory where you want to install HiveMQ. In this example, we use /opt.

```
cd /opt
```

- Extract the files from the ZIP archive:

```
unzip hivemq-<version>.zip
```

- Create a HiveMQ symbolic link (symlink)

```
ln -s /opt/hivemq-<version> /opt/hivemq
```

- Create a HiveMQ user:

```
useradd -d /opt/hivemq hivemq
```

- Make scripts executable and change the owner to hivemq user:

```
chown -R hivemq:hivemq /opt/hivemq-<version>
chown -R hivemq:hivemq /opt/hivemq
cd /opt/hivemq
chmod +x ./bin/run.sh
```

- Register HiveMQ as a systemd service:

```
cp /opt/hivemq/bin/init-script/hivemq.service /etc/systemd/system/hivemq.service
```

- To Start the HiveMQ systemmd service on boot, run:
```
systemctl enable hivemq
```

### Sensor Connection
Your Sensor configuration will vary based on what sensors you are using, but the most important thing is to configure them to submit data to the HiveMQ Broker setup in the previous step. Some very important details include:

- Configuring the topic that the sensor is submitting to
- Configuring the IP and port the sensor is submitting to: will be *your.linux.server.ip:1883* if you use the HiveMQ default configurations

- **Example Sensor Configuration:**
The following example is for how we configured the *Shelly Plus Plug US*

    - Open the Shelly app: Launch the Shelly Smart Control app on your phone. 
    - Select "Add Device": Navigate to the option to add a new device within the app. 
    - Choose your Wi-Fi network: Select your home Wi-Fi network and enter the password. 
    - Discover Shelly device: The app will scan for nearby Shelly devices, identify your Shelly Plus. 
    - Connect to Shelly device: You might need to temporarily connect your phone to the Shelly Plus's dedicated Wi-Fi network to access its configuration settings. 
    - Enter Wi-Fi details: Input your home Wi-Fi network details on the Shelly Plus device through the app. 
    - Enable MQTT: In the app, go to the Shelly Plus Plug US network settings, and under MQTT, select enable enter the following information, and select save.
        - Check the *RPC status notification over MQTT* box
        - Set the MQTT prefix to DaVinci-Plug-1
        - Set the ip of the MQTT broker (*your.linux.server.ip:1883*)
        - Set the ClientId to DaVinci-Plug-1
        - Provide the Linux server username and password
    - Reboot the Sensor for the settings to take effect

### Running the DaVinci Runtime
The DaVinciRuntime executable is named: DaVinciRuntime. It is manually runnable as follows:

```
./DaVinciRuntime
```

However, it does require a config.json to be able to start properly. This file must be placed in:

```
/usr/config/DaVinci
```

That directory most likely does not exist for you, so you will likely need to:

```
sudo mkdir /usr/config
sudo mkdir /usr/config/DaVinci
```

and then place your *config.json* file in that directory.

**Enabling the Runtime to start automatically on boot:**

```
cd /etc/systemd/system
sudo touch davinci_runtime.service
vim davinci_runtime.service
```
Place the following contents into the *davinci_runtime.service* file:

```
[Unit]
Description=DaVinci Runtime
After=network-online.target
StartLimitIntervalSec=0

[Service]
ExecStart=/home/andre/projects/DaVinci/DaVinciRuntime/cmake/build/DaVinciRuntime
WorkingDirectory=/home/andre/projects/DaVinci/DaVinciRuntime/cmake/build
User=andre
Restart=on-failure
RestartSec=5
Type=simple

[Install]
WantedBy=default.target
```

Now, run the following commands:

```
sudo systemctl enable davinci_runtime.service
sudo systemctl start davinci_runtime.service
```

After this process is completed, you can now also use the *daVinciRuntime\*.sh* scripts in the project's /Scripts directory to interact with the running systemctl davinci_runtime process!
