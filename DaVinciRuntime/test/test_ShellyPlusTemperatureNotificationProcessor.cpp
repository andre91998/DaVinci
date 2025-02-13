#include <gtest/gtest.h>
#include "ShellyPlusTemperatureNotificationProcessor.h"
#include "ShellyPlusTemperatureData.h"

TEST(ShellyPlusTemperatureNotificationProcessorTest, Process) {
    ShellyPlusTemperatureNotificationProcessor processor;
    Json::Value json;
    json["source"] = "source1";
    json["temperature"] = 25.0;
    json["humidity"] = 60.0;
    json["timestamp"] = 1234567890;

    auto result = processor.process(json);
    auto data = std::get<ShellyPlusTemperatureData>(result);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getTemperature(), 25.0);
    EXPECT_EQ(data.getHumidity(), 60.0);
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}