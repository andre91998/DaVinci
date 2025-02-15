#include <gtest/gtest.h>
#include "ShellyPlusTemperatureNotificationProcessor.h"
#include "ShellyPlusTemperatureData.h"

TEST(ShellyPlusTemperatureNotificationProcessorTest_FullStatus, Process) {
    ShellyPlusTemperatureNotificationProcessor processor;
    Json::Value json;
    json["method"] = "NotifyFullStatus";
    json["src"] = "source1";
    json["params"]["ts"] = 1234567890;
    json["params"]["temperature:0"]["tC"] = 25.0;
    json["params"]["humidity:0"]["rh"] = 60.0;

    auto result = processor.process(json);
    auto data = std::get<ShellyPlusTemperatureData>(result);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getTemperature(), 25.0);
    EXPECT_EQ(data.getHumidity(), 60.0);
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}

TEST(ShellyPlusTemperatureNotificationProcessorTest_NotifyStatus, Process) {
    ShellyPlusTemperatureNotificationProcessor processor;
    Json::Value json;
    json["method"] = "NotifyStatus";
    json["src"] = "source1";
    json["params"]["mqtt"]["connected"] = 1;

    json["params"]["temperature:0"]["tC"] = 25.0;
    json["params"]["humidity:0"]["rh"] = 60.0;

    auto result = processor.process(json);
    auto data = std::get<ShellyPlusTemperatureData>(result);

    EXPECT_EQ(data.getSource(), "stub");
    EXPECT_EQ(data.getTemperature(), 0);
    EXPECT_EQ(data.getHumidity(), 0);
    EXPECT_EQ(data.getTimestamp(), 0);
}