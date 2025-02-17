#include <iostream>
#include <thread>
#include "config.h"
#include "mqtt_client.h"
#include "davinci_server.h"

int main(int argc, char** argv) {

    Config config;
    if (!config.load("/usr/config/DaVinci/config.json")) {
        std::cerr << "Failed to load configuration" << std::endl;
        return 1;
    }

    // TODO: Initialize the SQLite database
    Database* db = Database::getInstance(config.getDatabasePath());
    // if (!db.connect()) {
    //     std::cerr << "Failed to connect to the database." << std::endl;
    //     return 1;
    // }
    
    try {
    // Initialize the MQTT client
    MQTTClient mqttClient(config.getMQTTBroker(), config.getMQTTPort(), config.getMQTTTopics(), config.getDatabasePath());
    if (!mqttClient.connect()) {
        std::cerr << "Failed to connect to the MQTT broker." << std::endl;
        return 1;
    }

    // Start the gRPC server in a separate thread
    std::thread grpcServerThread([&]() {
        RunServer(std::to_string(config.getGRPCPort()), db);
    });

    // Start the MQTT client in the main thread
    mqttClient.start();

    // TODO: Wait for the gRPC server thread to finish
    //grpcServerThread.join();

    while(true) {
            //do nothing
    }

    // Stop GRPCServer
    grpcServerThread.~thread();

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
