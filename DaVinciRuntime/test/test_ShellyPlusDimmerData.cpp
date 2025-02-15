#include <gtest/gtest.h>
#include "ShellyPlusDimmerData.h"

TEST(ShellyPlusDimmerDataTest, Constructor) {
    ShellyPlusDimmerData data("source1", 50, true, 1234567890);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getBrightness(), 50);
    EXPECT_TRUE(data.getState());
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}

TEST(ShellyPlusDimmerDataTest, SettersAndGetters) {
    ShellyPlusDimmerData data("source1", 50, true, 1234567890);
    data.setBrightness(25);
    data.setState(false);
    data.setTimestamp(987654321);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getBrightness(), 25);
    EXPECT_FALSE(data.getState());
    EXPECT_EQ(data.getTimestamp(), 987654321);
}