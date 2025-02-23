#include <gtest/gtest.h>
#include "ShellyPlusTemperatureData.h"

TEST(ShellyPlusTemperatureDataTest, DefaultConstructor) {
    ShellyPlusTemperatureData tempData;
    EXPECT_EQ(tempData.getSource(), "");
    EXPECT_DOUBLE_EQ(tempData.getTemperature(), 0.0);
    EXPECT_DOUBLE_EQ(tempData.getHumidity(), 0.0);
    EXPECT_DOUBLE_EQ(tempData.getTimestamp(), 0.0);
}

TEST(ShellyPlusTemperatureDataTest, ParameterizedConstructor) {
    ShellyPlusTemperatureData tempData("source", 55.5, 22.5, 1625097600.0);
    EXPECT_EQ(tempData.getSource(), "source");
    EXPECT_DOUBLE_EQ(tempData.getTemperature(), 22.5);
    EXPECT_DOUBLE_EQ(tempData.getHumidity(), 55.5);
    EXPECT_DOUBLE_EQ(tempData.getTimestamp(), 1625097600.0);
}

TEST(ShellyPlusTemperatureDataTest, SetTemperature) {
    ShellyPlusTemperatureData tempData;
    tempData.setTemperature(25.5);
    EXPECT_DOUBLE_EQ(tempData.getTemperature(), 25.5);
}

TEST(ShellyPlusTemperatureDataTest, SetHumidity) {
    ShellyPlusTemperatureData tempData;
    tempData.setHumidity(60.0);
    EXPECT_DOUBLE_EQ(tempData.getHumidity(), 60.0);
}

TEST(ShellyPlusTemperatureDataTest, SetTimestamp) {
    ShellyPlusTemperatureData tempData;
    tempData.setTimestamp(1625097600.0);
    EXPECT_DOUBLE_EQ(tempData.getTimestamp(), 1625097600.0);
}