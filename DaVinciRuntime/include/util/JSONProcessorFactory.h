#ifndef JSON_PROCESSOR_FACTORY_H
#define JSON_PROCESSOR_FACTORY_H

#include "json_processor.h"
#include "ShellyPlusPlugProcessor.h"
#include "ShellyPlusDimmerProcessor.h"
#include "ShellyPlusTemperatureProcessor.h"
#include <map>
#include <memory>
#include <regex>

/**
* JSONProcessorFactory class returns the 
* appropriate JSONProcessor based on the topic
 */
class JSONProcessorFactory {
public:
    JSONProcessorFactory() {
        // Register processors for specific topics
        registerProcessor(std::regex("DaVinci-Plug-\\d+/events/rpc"), std::make_unique<ShellyPlusPlugProcessor>());
        registerProcessor(std::regex("DaVinci-Dimmer-\\d+/events/rpc"), std::make_unique<ShellyPlusPlugProcessor>());
        registerProcessor(std::regex("DaVinci-Temperature-\\d+/events/rpc"), std::make_unique<ShellyPlusPlugProcessor>());
    }

    JSONProcessor* getProcessor(const std::string& topic) {
        for (const auto& entry : processors_) {
            if (std::regex_match(topic, entry.first)) {
                return entry.second.get();
            }
        }
        return nullptr;
    }

private:
    void registerProcessor(const std::regex& pattern, std::unique_ptr<JSONProcessor> processor) {
        processors_.emplace_back(pattern, std::move(processor));
    }

    std::vector<std::pair<std::regex, std::unique_ptr<JSONProcessor>>> processors_;

};

#endif // JSON_PROCESSOR_FACTORY_H