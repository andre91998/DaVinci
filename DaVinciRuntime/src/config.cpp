#include "config.h"
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>

Config::Config() : mqttPort_(0), grpcPort_(0) {}

Config::~Config() {}

bool Config::load(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open config file: " << filepath << std::endl;
        return false;
    }

    Json::Value root;
    file >> root;

    if (root.isNull()) {
        std::cerr << "Failed to parse config file: " << filepath << std::endl;
        return false;
    }

    mqttBroker_ = root["mqtt_broker"].asString();
    mqttPort_ = root["mqtt_port"].asInt();
    databasePath_ = root["database_path"].asString();
    grpcPort_ = root["grpc_port"].asInt();
    const Json::Value stringArray = root["mqtt_topics"];
    for (const auto& item : stringArray) {
        mqttTopics_.push_back(item.asString());
    }

    std::cout << "Config loaded successfully from " << filepath << std::endl;
    std::cout << "MQTT Broker: " << mqttBroker_ << std::endl;
    std::cout << "MQTT Port: " << mqttPort_ << std::endl;
    std::cout << "Database Path: " << databasePath_ << std::endl;
    std::cout << "gRPC Port: " << grpcPort_ << std::endl;
    std::cout << "MQTT Topics: ";
    for (const auto& topic : mqttTopics_) {
        std::cout << topic << " ";
    }
    std::cout << std::endl;

    return true;
}

std::string Config::getMQTTBroker() const {
    return mqttBroker_;
}

int Config::getMQTTPort() const {
    return mqttPort_;
}

std::vector<std::string> Config::getMQTTTopics() const {
    return mqttTopics_;
}

std::string Config::getDatabasePath() const {
    return databasePath_;
}

int Config::getGRPCPort() const {
    return grpcPort_;
}