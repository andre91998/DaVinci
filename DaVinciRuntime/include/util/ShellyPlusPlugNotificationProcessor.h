#ifndef SHELLY_PLUS_PLUG_PROCESSOR_H
#define SHELLY_PLUS_PLUG_PROCESSOR_H

#include "json_processor.h"
#include <iostream>

/**
* Implement the JSONProcessor interface for specific JSON schema 
*/
class ShellyPlusPlugNotificationProcessor : public JSONProcessor {
public:
    void process(const Json::Value& json) override {
        std::cout << "Processing ShellyPlus-Plug data: " << json.toStyledString() << std::endl;

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
};

#endif // SHELLY_PLUS_PLUG_PROCESSOR_H