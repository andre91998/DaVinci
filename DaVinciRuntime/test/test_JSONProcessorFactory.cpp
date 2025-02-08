#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "util/JSONProcessorFactory.h"
#include "json_processor.h"

class MockJSONProcessor : public JSONProcessor {
public:
    MOCK_METHOD(void, process, (const Json::Value& json), (override));
};

class JSONProcessorFactoryTest : public ::testing::Test {
protected:
    JSONProcessorFactory* factory;

    void SetUp() override {
        factory = new JSONProcessorFactory();
    }

    void TearDown() override {
        delete factory;
    }
};

TEST_F(JSONProcessorFactoryTest, GetProcessorForDimmerNotification) {
    std::string topic = "shellypluswdus-1234/events/rpc";
    JSONProcessor* processor = factory->getProcessor(topic);
    EXPECT_NE(processor, nullptr);
}

TEST_F(JSONProcessorFactoryTest, GetProcessorForPlugNotification) {
    std::string topic = "shellyplugus-1234/events/rpc";
    JSONProcessor* processor = factory->getProcessor(topic);
    EXPECT_NE(processor, nullptr);
}

TEST_F(JSONProcessorFactoryTest, GetProcessorForTemperatureNotification) {
    std::string topic = "shellyhtg3-1234/events/rpc";
    JSONProcessor* processor = factory->getProcessor(topic);
    EXPECT_NE(processor, nullptr);
}

TEST_F(JSONProcessorFactoryTest, GetProcessorForUnknownTopic) {
    std::string topic = "unknown-1234/events/rpc";
    JSONProcessor* processor = factory->getProcessor(topic);
    EXPECT_EQ(processor, nullptr);
}

// TEST_F(JSONProcessorFactoryTest, ProcessJSON) {
//     MockJSONProcessor mockProcessor;
//     Json::Value json;
//     json["key"] = "value";

//     EXPECT_CALL(mockProcessor, process(testing::Eq(json))).Times(1);

//     std::string topic = "shellypluswdus-1234/events/rpc";
//     JSONProcessor* processor = factory->getProcessor(topic);
//     ASSERT_NE(processor, nullptr);
//     processor->process(json);
// }