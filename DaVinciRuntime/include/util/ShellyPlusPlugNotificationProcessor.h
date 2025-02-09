#ifndef SHELLY_PLUS_PLUG_PROCESSOR_H
#define SHELLY_PLUS_PLUG_PROCESSOR_H

#include "json_processor.h"
#include "ShellyPlusPlugData.h"
#include <iostream>

class ShellyPlusPlugNotificationProcessor : public JSONProcessor {
public:
    ShellyPlusPlugNotificationProcessor(); // Default constructor 
    virtual ~ShellyPlusPlugNotificationProcessor(); // Default destructor
    void process(const Json::Value& json);

private:
    void logData(ShellyPlusPlugData shellyPlusPlugData);
    void logFullJSON(const Json::Value& json); //meant only for testing
};

#endif // SHELLY_PLUS_PLUG_PROCESSOR_H