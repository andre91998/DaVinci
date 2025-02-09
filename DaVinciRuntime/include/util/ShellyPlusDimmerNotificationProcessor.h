#ifndef SHELLY_PLUS_DIMMER_PROCESSOR_H
#define SHELLY_PLUS_DIMMER_PROCESSOR_H

#include "json_processor.h"
#include "ShellyPlusDimmerData.h"
#include <iostream>

class ShellyPlusDimmerNotificationProcessor : public JSONProcessor {
public:
    ShellyPlusDimmerNotificationProcessor(); // Default constructor 
    virtual ~ShellyPlusDimmerNotificationProcessor(); // Default destructor
    void process(const Json::Value& json);

private:
    void logData(ShellyPlusDimmerData shellyPlusDimmerData);
    void logFullJSON(const Json::Value& json); //meant only for testing
};

#endif // SHELLY_PLUS_DIMMER_PROCESSOR_H