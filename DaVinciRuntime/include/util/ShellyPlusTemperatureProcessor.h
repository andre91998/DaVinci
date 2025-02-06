#ifndef SHELLY_PLUS_TEMPERATURE_PROCESSOR_H
#define SHELLY_PLUS_TEMPERATURE_PROCESSOR_H

#include "json_processor.h"
#include <iostream>

/**
* Implement the JSONProcessor interface for specific JSON schema 
*/
class ShellyPlusTemperatureProcessor : public JSONProcessor {
public:
    void process(const Json::Value& json) override {
        // Process JSON data specific to Sensor Type C
        std::cout << "Processing Sensor Type ShellyPlus-Temperature data: " << json.toStyledString() << std::endl;
    }
};

#endif // SHELLY_PLUS_TEMPERATURE_PROCESSOR_H