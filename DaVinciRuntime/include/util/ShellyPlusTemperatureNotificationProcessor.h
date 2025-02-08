#ifndef SHELLY_PLUS_TEMPERATURE_PROCESSOR_H
#define SHELLY_PLUS_TEMPERATURE_PROCESSOR_H

#include "json_processor.h"
#include <iostream>

class ShellyPlusTemperatureNotificationProcessor : public JSONProcessor {
public:
    void process(const Json::Value& json) override {
        std::cout << "Processing ShellyPlus-Temperature data: " << json.toStyledString() << std::endl;

        std::string src = json["src"].asString();
        std::string dst = json["dst"].asString();
        std::string method = json["method"].asString();
        Json::Value params = json["params"];
        double ts = params["ts"].asDouble();

        // Handle different methods
        if (method == "NotifyFullStatus") {
            processFullStatus(params);
        } else if (method == "NotifyStatus") {
            processStatus(params);
        } else {
            std::cerr << "Unknown method: " << method << std::endl;
        }
    }

private:
    void processFullStatus(const Json::Value& params) {
        Json::Value devicePower = params["devicepower:0"];
        int id = devicePower["id"].asInt();
        Json::Value battery = devicePower["battery"];
        double voltage = battery["V"].asDouble();
        int percent = battery["percent"].asInt();
        bool externalPresent = devicePower["external"]["present"].asBool();

        Json::Value humidity = params["humidity:0"];
        double rh = humidity["rh"].asDouble();

        Json::Value temperature = params["temperature:0"];
        double tempC = temperature["tC"].asDouble();
        double tempF = temperature["tF"].asDouble();

        // Print or process the extracted data
        std::cout << "DevicePower ID: " << id << std::endl;
        std::cout << "Battery Voltage: " << voltage << std::endl;
        std::cout << "Battery Percent: " << percent << std::endl;
        std::cout << "External Present: " << externalPresent << std::endl;
        std::cout << "Humidity: " << rh << std::endl;
        std::cout << "Temperature (C): " << tempC << std::endl;
        std::cout << "Temperature (F): " << tempF << std::endl;
    }

    void processStatus(const Json::Value& params) {
        bool mqttConnected = params["mqtt"]["connected"].asBool();

        // Print or process the extracted data
        std::cout << "MQTT Connected: " << mqttConnected << std::endl;
    }
};

#endif // SHELLY_PLUS_TEMPERATURE_PROCESSOR_H