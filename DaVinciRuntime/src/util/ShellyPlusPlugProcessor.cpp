#include "json_processor.h"
#include <iostream>

/**
* Implement the JSONProcessor interface for specific JSON schema 
*/
class ShellyPlusPlugProcessor : public JSONProcessor {
public:
    void process(const Json::Value& json) override {
        // Process JSON data specific to Sensor Type A
        std::cout << "Processing Sensor Type ShellyPlus-Plug data: " << json.toStyledString() << std::endl;
    }
};
