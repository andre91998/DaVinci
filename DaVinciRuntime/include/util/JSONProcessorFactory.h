#ifndef JSON_PROCESSOR_FACTORY_H
#define JSON_PROCESSOR_FACTORY_H

#include "json_processor.h"
#include "ShellyPlusPlugNotificationProcessor.h"
#include "ShellyPlusDimmerNotificationProcessor.h"
#include "ShellyPlusTemperatureNotificationProcessor.h"
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
        registerProcessor(std::regex("^shellypluswdus-.*?/events/rpc$"), std::make_unique<ShellyPlusDimmerNotificationProcessor>());
        registerProcessor(std::regex("^shellyplugus-.*?/events/rpc$"), std::make_unique<ShellyPlusPlugNotificationProcessor>());
        registerProcessor(std::regex("^shellyhtg3-.*?/events/rpc$"), std::make_unique<ShellyPlusTemperatureNotificationProcessor>());
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