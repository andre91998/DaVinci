#include <gtest/gtest.h>
#include "JSONProcessorFactory.h"
#include "json_processor.h"

class MockProcessor : public JSONProcessor {
public:
    MOCK_METHOD(void, process, (const Json::Value& json), (override));
};

TEST(JSONProcessorFactoryTest, TestGetProcessor) {
    JSONProcessorFactory factory;
    
    JSONProcessor* plugProcessor = factory.getProcessor("sensor/ShellyPlus/Plug");
    ASSERT_NE(plugProcessor, nullptr);

    JSONProcessor* dimmerProcessor = factory.getProcessor("sensor/ShellyPlus/Dimmer");
    ASSERT_NE(dimmerProcessor, nullptr);

    JSONProcessor* temperatureProcessor = factory.getProcessor("sensor/ShellyPlus/Temperature");
    ASSERT_NE(temperatureProcessor, nullptr);

    JSONProcessor* unknownProcessor = factory.getProcessor("unknown/topic");
    ASSERT_EQ(unknownProcessor, nullptr);
}