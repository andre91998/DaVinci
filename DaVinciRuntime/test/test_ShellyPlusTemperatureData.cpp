#include <gtest/gtest.h>
#include "ShellyPlusTemperatureData.h"

TEST(ShellyPlusTemperatureDataTest, Constructor) {
    ShellyPlusTemperatureData data("source1", 25.0, 60.0, 1234567890);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getHumidity(), 25.0);
    EXPECT_EQ(data.getTemperature(), 60.0);
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}

TEST(ShellyPlusTemperatureDataTest, SettersAndGetters) {
    ShellyPlusTemperatureData data("source1", 25.0, 60.0, 1234567890);
    data.setHumidity(12.0);
    data.setTemperature(30.0);
    data.setTimestamp(987654321);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getHumidity(), 12.0);
    EXPECT_EQ(data.getTemperature(), 30.0);
    EXPECT_EQ(data.getTimestamp(), 987654321);
}