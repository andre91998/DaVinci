#include <gtest/gtest.h>
#include "ShellyPlusDimmerNotificationProcessor.h"
#include "ShellyPlusDimmerData.h"

TEST(ShellyPlusDimmerNotificationProcessorTest, Process) {
    ShellyPlusDimmerNotificationProcessor processor;
    Json::Value json;
    json["params"]["ts"] = 1234567890;
    json["params"]["light:0"]["source"] = "source1";
    json["params"]["light:0"]["brightness"] = 50;
    json["params"]["light:0"]["output"] = true;

    auto result = processor.process(json);
    auto data = std::get<ShellyPlusDimmerData>(result);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getBrightness(), 50);
    EXPECT_TRUE(data.getState());
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}