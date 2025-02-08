################################# 
# confirm that mqtt sensors are 
# connected to the MQTT Broker
# #################################
# INTEGRATION
# #################################

import paho.mqtt.client as mqtt
import time
import sys
import os
import requests

#TODO: make this test use the topics from config.json
def main():
    return_code = 0
    
    # Define the URL for the POST request
    plugUrl = f"http://192.168.86.66/rpc"
    dimmerUrl = f"http://192.168.86.25/rpc"
    ## Temp sensor only wakes up and connects to submit data, so we skip it
    #tempUrl = f"http://192.168.86.55/rpc"

    sensorUrls = [plugUrl, dimmerUrl]

    # Define the payload
    payload = {
    "id": 1,
    "method": "Mqtt.GetStatus"
    }

    # Set headers to mimic curl's behavior
    headers = {
        'Content-Type': 'application/json'
    }

    for url in sensorUrls:
        # Make the POST request
        response = requests.post(url, json=payload, headers=headers)
        # Print the response
        print("Status Code:", response.status_code)
        print("Response JSON:", response.json())
        connected = response.json()['result']['connected']
        if not connected:
            return_code = 1

    if return_code == 1:
        print("MQTT Sensor Enablement Test: FAILED!")
    else:
        print("MQTT Sensor Enablement Test: PASSED!")
    sys.exit(return_code)

if __name__ == "__main__":
    main()