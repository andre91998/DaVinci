#ifndef JSON_PROCESSOR_H
#define JSON_PROCESSOR_H

#include <string>
#include <jsoncpp/json/json.h>
#include <variant>
#include "ShellyPlusPlugData.h"
#include "ShellyPlusTemperatureData.h"
#include "ShellyPlusDimmerData.h"

/**
* The JSONProcessor class defines the interface for processing JSON data.
*/
class JSONProcessor {
public:
    virtual ~JSONProcessor() = default;
    using SensorData = std::variant<ShellyPlusPlugData, ShellyPlusTemperatureData, ShellyPlusDimmerData>;
    virtual SensorData process(const Json::Value& json) = 0;
    virtual int getType() const = 0;

private:
    std::string type_;
};

#endif // JSON_PROCESSOR_H
