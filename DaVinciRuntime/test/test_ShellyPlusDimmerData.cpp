#include <gtest/gtest.h>
#include "ShellyPlusDimmerData.h"

TEST(ShellyPlusDimmerDataTest, DefaultConstructor) {
    ShellyPlusDimmerData dimmer;
    EXPECT_EQ(dimmer.getBrightness(), 0);
    EXPECT_FALSE(dimmer.getState());
    EXPECT_EQ(dimmer.getSource(), "");
    EXPECT_DOUBLE_EQ(dimmer.getTimestamp(), 0.0);
}

TEST(ShellyPlusDimmerDataTest, ParameterizedConstructor) {
    ShellyPlusDimmerData dimmer("source", 75, true, 1625097600.0);
    EXPECT_EQ(dimmer.getSource(), "source");
    EXPECT_EQ(dimmer.getBrightness(), 75);
    EXPECT_TRUE(dimmer.getState());
    EXPECT_DOUBLE_EQ(dimmer.getTimestamp(), 1625097600.0);
}

TEST(ShellyPlusDimmerDataTest, SetBrightness) {
    ShellyPlusDimmerData dimmer;
    dimmer.setBrightness(75);
    EXPECT_EQ(dimmer.getBrightness(), 75);
}

TEST(ShellyPlusDimmerDataTest, SetState) {
    ShellyPlusDimmerData dimmer;
    dimmer.setState(true);
    EXPECT_TRUE(dimmer.getState());
}

TEST(ShellyPlusDimmerDataTest, SetTimestamp) {
    ShellyPlusDimmerData dimmer;
    dimmer.setTimestamp(1625097600.0);
    EXPECT_DOUBLE_EQ(dimmer.getTimestamp(), 1625097600.0);
}