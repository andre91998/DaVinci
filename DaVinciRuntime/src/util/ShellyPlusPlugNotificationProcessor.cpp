#include "ShellyPlusPlugNotificationProcessor.h"

// Default constructor implementation
ShellyPlusPlugNotificationProcessor::ShellyPlusPlugNotificationProcessor() {
    // Initialization code here if needed
}

// Default destructor definition
ShellyPlusPlugNotificationProcessor::~ShellyPlusPlugNotificationProcessor() {
    // Cleanup code here if needed
}

void ShellyPlusPlugNotificationProcessor::process(const Json::Value& json) {
    
    std::cout << "Processing ShellyPlus-Plug data: " << json.toStyledString() << std::endl;

    std::string src = json["src"].asString();
    Json::Value params = json["params"];
    double ts = params["ts"].asDouble();
    Json::Value switch0 = params["switch:0"];
    Json::Value aenergy = switch0["aenergy"];
    double total = aenergy["total"].asDouble();

    ShellyPlusPlugData plugData(src, total, ts);
    logData(plugData);
}

void ShellyPlusPlugNotificationProcessor::logData(ShellyPlusPlugData plugData) {
    std::cout << "Source: " << plugData.getSource() << std::endl;
    std::cout << "Power: " << plugData.getPower() << std::endl;
    std::cout << "Time: " << plugData.getTimestamp() << std::endl;
}

void ShellyPlusPlugNotificationProcessor::logFullJSON(const Json::Value& json) {
    //Get Each Field
    std::string src = json["src"].asString();
    std::string dst = json["dst"].asString();
    std::string method = json["method"].asString();
    Json::Value params = json["params"];
    double ts = params["ts"].asDouble();
    Json::Value switch0 = params["switch:0"];
    int id = switch0["id"].asInt();
    Json::Value aenergy = switch0["aenergy"];
    Json::Value by_minute = aenergy["by_minute"];
    int minute_ts = aenergy["minute_ts"].asInt();
    double total = aenergy["total"].asDouble();

    // Print or process the extracted data
    std::cout << "Source: " << src << std::endl;
    std::cout << "Destination: " << dst << std::endl;
    std::cout << "Method: " << method << std::endl;
    std::cout << "Timestamp: " << ts << std::endl;
    std::cout << "Switch ID: " << id << std::endl;
    std::cout << "Energy by minute: " << by_minute << std::endl;
    std::cout << "Minute timestamp: " << minute_ts << std::endl;
    std::cout << "Total energy: " << total << std::endl;
}
