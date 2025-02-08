#include <iostream>
#include <thread>
#include "config.h"
#include "mqtt_client.h"

int main(int argc, char** argv) {

    //TODO: Change where config lives to something more scalable
    Config config;
    config.load("/usr/config/DaVinci/config.json");

    // TODO: Initialize the SQLite database
    // Database db(config.getDatabasePath());
    // if (!db.connect()) {
    //     std::cerr << "Failed to connect to the database." << std::endl;
    //     return 1;
    // }
    
    try {
    // Initialize the MQTT client
    MQTTClient mqttClient(config.getMQTTBroker(), config.getMQTTPort(), config.getMQTTTopics());
    if (!mqttClient.connect()) {
        std::cerr << "Failed to connect to the MQTT broker." << std::endl;
        return 1;
    }

    // TODO: Start the gRPC server in a separate thread
    // std::thread grpcServerThread([&]() {
    //     GRPCServer grpcServer(config.getGRPCPort());
    //     grpcServer.start();
    // });

    // Start the MQTT client in the main thread
    mqttClient.start();

    // TODO: Wait for the gRPC server thread to finish
    //grpcServerThread.join();

    while(true) {
            //do nothing
    }

    // Disconnect From MQTT Client
    mqttClient.disconnect();

    //TODO: Close database connection
    //db.disconnect()
    std::cout << "Disconnected" << std::endl;

    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
