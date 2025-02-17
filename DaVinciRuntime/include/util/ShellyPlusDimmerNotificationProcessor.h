#ifndef SHELLY_PLUS_DIMMER_PROCESSOR_H
#define SHELLY_PLUS_DIMMER_PROCESSOR_H

#include "json_processor.h"
#include "sensor_types.h"
#include "ShellyPlusDimmerData.h"
#include <iostream>

class ShellyPlusDimmerNotificationProcessor : public JSONProcessor {
public:
    ShellyPlusDimmerNotificationProcessor(); // Default constructor 
    virtual ~ShellyPlusDimmerNotificationProcessor(); // Default destructor
    JSONProcessor::SensorData process(const Json::Value& json);
    int getType() const override {
        return (int) SensorType::SHELLY_DIMMER;
    };

private:
    void logData(ShellyPlusDimmerData shellyPlusDimmerData);
    void logFullJSON(const Json::Value& json); //meant only for debugging
    friend class ShellyPlusDimmerNotificationProcessorTest;
};

#endif // SHELLY_PLUS_DIMMER_PROCESSOR_H