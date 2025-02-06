#ifndef SHELLY_PLUS_DIMMER_PROCESSOR_H
#define SHELLY_PLUS_DIMMER_PROCESSOR_H

#include "json_processor.h"
#include <iostream>

class ShellyPlusDimmerNotificationProcessor : public JSONProcessor {
public:
    void process(const Json::Value& json) override {
        std::cout << "Processing ShellyPlus-Dimmer data: " << json.toStyledString() << std::endl;

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
};

#endif // SHELLY_PLUS_DIMMER_PROCESSOR_H