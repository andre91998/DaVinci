#ifndef JSON_PROCESSOR_H
#define JSON_PROCESSOR_H

#include <string>
#include <jsoncpp/json/json.h>

/**
* The JSONProcessor class defines the interface for processing JSON data.
*/
class JSONProcessor {
public:
    virtual ~JSONProcessor() = default;
    virtual void process(const Json::Value& json) = 0;
};

#endif // JSON_PROCESSOR_H
