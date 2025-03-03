#include "json_processor.h"
#include "ShellyPlusDimmerData.h"
#include "ShellyPlusDimmerNotificationProcessor.h"
#include <iostream>

// Default constructor implementation
ShellyPlusDimmerNotificationProcessor::ShellyPlusDimmerNotificationProcessor() {
    // Initialization code here if needed
}

// Default destructor definition
ShellyPlusDimmerNotificationProcessor::~ShellyPlusDimmerNotificationProcessor() {
    // Cleanup code here if needed
}

JSONProcessor::SensorData ShellyPlusDimmerNotificationProcessor::process(const Json::Value& json) {
    
    std::cout << "Processing ShellyPlus-Dimmer data: " << json.toStyledString() << std::endl;

    Json::Value params = json["params"];
    std::string source = json["src"].asString();
    double ts = params["ts"].asDouble();
    Json::Value light = params["light:0"];
    double brightness = light["brightness"].asDouble();
    bool output = light["output"].asBool();


    ShellyPlusDimmerData dimmerData(source, brightness, output, ts);
    logData(dimmerData);
    return dimmerData;
}

void ShellyPlusDimmerNotificationProcessor::logData(ShellyPlusDimmerData dimmerData) {
    std::cout << "Source: " << dimmerData.getSource() << std::endl;
    std::cout << "Brightness: " << dimmerData.getBrightness() << std::endl;
    std::cout << "State: " << dimmerData.getState() << std::endl;
    std::cout << "Time: " << dimmerData.getTimestamp() << std::endl;
}

void ShellyPlusDimmerNotificationProcessor::logFullJSON(const Json::Value& json) {
    //Get Each Field
    std::string src = json["src"].asString();
    std::string dst = json["dst"].asString();
    std::string method = json["method"].asString();
    Json::Value params = json["params"];
    double ts = params["ts"].asDouble();
    Json::Value light = params["light:0"];
    int id = light["id"].asInt();
    double brightness = light["brightness"].asDouble();
    bool output = light["output"].asBool();
    std::string source = light["source"].asString();

    // Print or process the extracted data
    std::cout << "Source: " << src << std::endl;
    std::cout << "Destination: " << dst << std::endl;
    std::cout << "Method: " << method << std::endl;
    std::cout << "Timestamp: " << ts << std::endl;
    std::cout << "Light ID: " << id << std::endl;
    std::cout << "Brightness: " << brightness << std::endl;
    std::cout << "Output: " << (output ? "true" : "false") << std::endl;
    std::cout << "Source: " << source << std::endl;
}