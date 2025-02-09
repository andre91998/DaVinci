#ifndef SHELLY_PLUS_TEMPERATURE_PROCESSOR_H
#define SHELLY_PLUS_TEMPERATURE_PROCESSOR_H

#include "json_processor.h"
#include "ShellyPlusTemperatureData.h"
#include <iostream>

class ShellyPlusTemperatureNotificationProcessor : public JSONProcessor {
public:
ShellyPlusTemperatureNotificationProcessor(); // Default constructor 
    virtual ~ShellyPlusTemperatureNotificationProcessor(); // Default destructor
    void process(const Json::Value& json);

private:
    void processStatus(const Json::Value& json);
    void processFullStatus(const Json::Value& json, const std::string& src);
    void logData(ShellyPlusTemperatureData ShellyPlusTemperatureData);
    void logFullJSON(const Json::Value& json); //meant only for testing
};

#endif // SHELLY_PLUS_TEMPERATURE_PROCESSOR_H