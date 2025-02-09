#include "ShellyPlusTemperatureNotificationProcessor.h"

// Default constructor implementation
ShellyPlusTemperatureNotificationProcessor::ShellyPlusTemperatureNotificationProcessor() {
    // Initialization code here if needed
}

// Default destructor definition
ShellyPlusTemperatureNotificationProcessor::~ShellyPlusTemperatureNotificationProcessor() {
    // Cleanup code here if needed
}

void ShellyPlusTemperatureNotificationProcessor::process(const Json::Value& json) {
    std::cout << "Processing ShellyPlus-Temperature data: " << json.toStyledString() << std::endl;

    std::string src = json["src"].asString();
    std::string dst = json["dst"].asString();
    std::string method = json["method"].asString();
    Json::Value params = json["params"];
    double ts = params["ts"].asDouble();

    // Handle different methods
    if (method == "NotifyFullStatus") {
        processFullStatus(json, src);
    } else if (method == "NotifyStatus") {
        processStatus(json);
    } else {
        std::cerr << "Unknown method: " << method << std::endl;
    }
}

void ShellyPlusTemperatureNotificationProcessor::processStatus(const Json::Value& json) {
    bool mqttConnected = json["params"]["mqtt"]["connected"].asBool();

    // For now, do nothing (Place Holder)
    // Print or process the extracted data
    //std::cout << "MQTT Connected: " << mqttConnected << std::endl;
}

void ShellyPlusTemperatureNotificationProcessor::processFullStatus(const Json::Value& json, const std::string& src) {
    Json::Value devicePower = json["params"]["devicepower:0"];
    int id = devicePower["id"].asInt();
    Json::Value battery = devicePower["battery"];
    double voltage = battery["V"].asDouble();
    int percent = battery["percent"].asInt();
    bool externalPresent = devicePower["external"]["present"].asBool();

    Json::Value humidity = json["params"]["humidity:0"];
    double rh = humidity["rh"].asDouble();

    Json::Value temperature = json["params"]["temperature:0"];
    double tempC = temperature["tC"].asDouble();
    double tempF = temperature["tF"].asDouble();

    double ts = json["params"]["ts"].asDouble();

    ShellyPlusTemperatureData temperatureData(src, rh, tempC, ts);
    logData(temperatureData);
}

void ShellyPlusTemperatureNotificationProcessor::logData(ShellyPlusTemperatureData temperatureData) {
    std::cout << "Source: " << temperatureData.getSource() << std::endl;
    std::cout << "Brightness: " << temperatureData.getHumidity() << std::endl;
    std::cout << "State: " << temperatureData.getTemperature() << std::endl;
    std::cout << "Time: " << temperatureData.getTimestamp() << std::endl;
}

void ShellyPlusTemperatureNotificationProcessor::logFullJSON(const Json::Value& params) {
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