#ifndef JSON_PROCESSOR_FACTORY_H
#define JSON_PROCESSOR_FACTORY_H

#include "json_processor.h"
#include <map>
#include <memory>

/**
* JSONProcessorFactory class returns the 
* appropriate JSONProcessor based on the topic
 */
class JSONProcessorFactory {
public:
    JSONProcessorFactory() {
        // Register processors for specific topics
        processors_["sensor/ShellyPlus/Plug"] = std::make_unique<SensorTypeAProcessor>();
        processors_["sensor/ShellyPlus/Dimmer"] = std::make_unique<SensorTypeBProcessor>();
        processors_["sensor/ShellyPlus/Temperature"] = std::make_unique<SensorTypeBProcessor>();
    }

    JSONProcessor* getProcessor(const std::string& topic) {
        if (processors_.find(topic) != processors_.end()) {
            return processors_[topic].get();
        }
        return nullptr;
    }

private:
    std::map<std::string, std::unique_ptr<JSONProcessor>> processors_;
};

#endif // JSON_PROCESSOR_FACTORY_H
