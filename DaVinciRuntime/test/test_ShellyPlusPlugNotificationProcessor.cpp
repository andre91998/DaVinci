#include <gtest/gtest.h>
#include "ShellyPlusPlugNotificationProcessor.h"
#include "ShellyPlusPlugData.h"

TEST(ShellyPlusPlugNotificationProcessorTest, Process) {
    ShellyPlusPlugNotificationProcessor processor;
    Json::Value json;
    json["source"] = "source1";
    json["power"] = 100.0;
    json["timestamp"] = 1234567890;

    auto result = processor.process(json);
    auto data = std::get<ShellyPlusPlugData>(result);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getPower(), 100.0);
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}