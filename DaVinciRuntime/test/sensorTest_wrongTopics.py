################################# 
# confirm that mqtt sensors are 
# submitting data properly to 
# hivemq broker 
# #################################
# INTEGRATION
# #################################

import paho.mqtt.client as mqtt
import time
import sys

#TODO: make this test use the topics from config.json
def main():
    global msgReceived
    msgReceived = False
    
    # Define the MQTT broker details
    broker = "localhost"
    port = 1883
    plugTopic = "shellyplugus-d8132ad47cdc/events/wrongTopic"
    dimmerTopic = "shellypluswdus-b0b21c121f1c/events/wrongTopic"
    tempTopic = "shellyhtg3-3030f9e711e4/events/wrongTopic"

    # Set max test wait time (seconds)
    duration = 20

    # Callback function when a message is received
    def on_message(client, userdata, message):
        print(f"Message received: {message.payload.decode()} on topic {message.topic}")
        print("MQTT Sensor Wrong Topics Test: FAILED!")
        global msgReceived
        msgReceived = True

    # Callback function when the client connects to the broker
    def on_connect(client, userdata, flags, rc, properties=None):
        if rc == 0:
            print("Connected to broker")
            client.subscribe(plugTopic)
            client.subscribe(dimmerTopic)
            client.subscribe(tempTopic)
        else:
            print(f"Connection failed with code {rc}")

    # Create an MQTT client instance
    client = mqtt.Client()

    # Assign the callback functions
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to the broker
    client.connect(broker, port, 60)

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
        print("MQTT Sensor Wrong Topics Test: PASSED!")

    # Stop the loop
    client.loop_stop()
    if msgReceived:
        return_code = 0
    else:
        return_code = 1
    
    sys.exit(return_code)

if __name__ == "__main__":
    main()