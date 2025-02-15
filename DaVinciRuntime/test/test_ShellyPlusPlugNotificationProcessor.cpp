#include <gtest/gtest.h>
#include "ShellyPlusPlugNotificationProcessor.h"
#include "ShellyPlusPlugData.h"

TEST(ShellyPlusPlugNotificationProcessorTest, Process) {
    ShellyPlusPlugNotificationProcessor processor;
    Json::Value json;
    json["src"] = "source1";
    json["params"]["ts"] = 1234567890;
    json["params"]["switch:0"]["aenergy"]["total"] = 100.0;

    auto result = processor.process(json);
    auto data = std::get<ShellyPlusPlugData>(result);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getPower(), 100.0);
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}