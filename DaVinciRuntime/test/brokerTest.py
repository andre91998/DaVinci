#################################
# confirm that HiveMQ mqtt broker
# is running and able to receive 
# data and be read from
#################################
# INTEGRATION
#################################

import paho.mqtt.client as mqtt
import threading
import time
import sys

def main():
    global msgReceived
    msgReceived = False

    # Define the MQTT broker details
    broker = "localhost"
    port = 1883
    topic = "your/test/topic"

    # Set max test wait time (seconds)
    duration = 10

    # Function to simulate sensor data publishing
    def simulate_sensor_data():
        sensor_client = mqtt.Client()
        sensor_client.connect(broker, port, 60)
        while not msgReceived:
            sensor_data = "Sensor data: " + str(time.time())
            sensor_client.publish(topic, sensor_data)
            time.sleep(5)  # Simulate sensor data every 5 seconds
        print("Thread Exiting")
        sensor_client.disconnect()

    # Callback function when a message is received
    def on_message(client, userdata, message):
        print(f"Message received: {message.payload.decode()} on topic {message.topic}")
        print("MQTT Broker Enablement Test: PASSED!")
        global msgReceived
        msgReceived = True

    # Callback function when the client connects to the broker
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to broker")
            client.subscribe(topic)
        else:
            print(f"Connection failed with code {rc}")

    # Create an MQTT client instance
    client = mqtt.Client()

    # Assign the callback functions
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to the broker
    client.connect(broker, port, 60)

    # Start the sensor data simulation in a separate thread
    sensor_thread = threading.Thread(target=simulate_sensor_data).start()

# Start the loop to process received messages
    # Start the loop
    start_time = time.time()
    client.loop_start()

    while not msgReceived:
        if time.time() - start_time < duration:
            pass
        else:
            break

    if not msgReceived:
        print("MQTT Broker Enablement Test: FAILED!")

    # Stop the loop
    client.loop_stop()
    if msgReceived:
        return_code = 1
    else:
        return_code = 0
    
    sys.exit(return_code)

if __name__ == "__main__":
    main()