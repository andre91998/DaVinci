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

    mqttBroker_ = root["mqtt_broker"].asString();
    mqttPort_ = root["mqtt_port"].asInt();
    mqttTopic_ = root["mqtt_topic"].asString();
    databasePath_ = root["database_path"].asString();
    grpcPort_ = root["grpc_port"].asInt();

    return true;
}

std::string Config::getMQTTBroker() const {
    return mqttBroker_;
}

int Config::getMQTTPort() const {
    return mqttPort_;
}

std::string Config::getMQTTTopic() const {
    return mqttTopic_;
}

std::string Config::getDatabasePath() const {
    return databasePath_;
}

int Config::getGRPCPort() const {
    return grpcPort_;
}
