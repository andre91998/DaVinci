#ifndef SHELLY_PLUS_PLUG_PROCESSOR_H
#define SHELLY_PLUS_PLUG_PROCESSOR_H

#include "json_processor.h"
#include "sensor_types.h"
#include "ShellyPlusPlugData.h"
#include <iostream>

class ShellyPlusPlugNotificationProcessor : public JSONProcessor {
public:
    ShellyPlusPlugNotificationProcessor(); // Default constructor 
    virtual ~ShellyPlusPlugNotificationProcessor(); // Default destructor
    JSONProcessor::SensorData process(const Json::Value& json);
    int getType() const override {
        return (int) SensorType::SHELLY_PLUG;
    };

private:
    void logData(ShellyPlusPlugData shellyPlusPlugData);
    void logFullJSON(const Json::Value& json); //meant only for testing
};

#endif // SHELLY_PLUS_PLUG_PROCESSOR_H