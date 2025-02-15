#ifndef SHELLY_PLUS_TEMPERATURE_PROCESSOR_H
#define SHELLY_PLUS_TEMPERATURE_PROCESSOR_H

#include "json_processor.h"
#include "sensor_types.h"
#include "ShellyPlusTemperatureData.h"
#include <iostream>

class ShellyPlusTemperatureNotificationProcessor : public JSONProcessor {
public:
    ShellyPlusTemperatureNotificationProcessor(); // Default constructor 
    virtual ~ShellyPlusTemperatureNotificationProcessor(); // Default destructor
    JSONProcessor::SensorData process(const Json::Value& json);
    int getType() const override {
        return (int) SensorType::SHELLY_TEMP;
    };

private:
JSONProcessor::SensorData processStatus(const Json::Value& json);
    JSONProcessor::SensorData processFullStatus(const Json::Value& json, const std::string& src);
    void logData(ShellyPlusTemperatureData ShellyPlusTemperatureData);
    void logFullJSON(const Json::Value& json); //meant only for testing
};

#endif // SHELLY_PLUS_TEMPERATURE_PROCESSOR_H