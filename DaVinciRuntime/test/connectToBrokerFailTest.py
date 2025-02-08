#################################
# confirm that an MQTT Client will
# fail to connect to the HiveMQ 
# mqtt broker on the wrong port
#################################
# INTEGRATION
#################################

import paho.mqtt.client as mqtt
import time
import sys

def main():
    global clientConnected
    clientConnected = False

    # Define the MQTT broker details
    broker = "localhost"
    port = 1888
    topic = "your/test/topic"

    # Set max test wait time (seconds)
    duration = 10

    # Callback function when the client connects to the broker
    def on_connect(client, userdata, flags, rc):
        global clientConnected
        if rc == 0:
            print("Connected to broker")
            client.subscribe(topic)
            clientConnected = True
            print("MQTT Sensor Enablement Test: FAILED!")
        else:
            print(f"Connection failed with code {rc}")

    # Create an MQTT client instance
    client = mqtt.Client()

    # Assign the callback functions
    client.on_connect = on_connect

    # Connect to the broker
    try:   
        client.connect(broker, port, 60)
    except ConnectionRefusedError:
        print("Received Connection Refused Error as expected")
    

# Start the loop to process received messages
    # Start the loop
    start_time = time.time()
    client.loop_start()

    while not clientConnected:
        if time.time() - start_time < duration:
            pass
        else:
            break

    if not clientConnected:
        print("MQTT Sensor Enablement Test: PASSED!")

    # Stop the loop
    client.loop_stop()
    if clientConnected:
        return_code = 0
    else:
        return_code = 1
    
    sys.exit(return_code)

if __name__ == "__main__":
    main()