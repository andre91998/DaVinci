#include <gtest/gtest.h>
#include "ShellyPlusPlugData.h"

TEST(ShellyPlusPlugDataTest, DefaultConstructor) {
    ShellyPlusPlugData plugData;
    EXPECT_EQ(plugData.getSource(), "");
    EXPECT_EQ(plugData.getPower(), 0);
    EXPECT_EQ(plugData.getTimestamp(), 0);
}

TEST(ShellyPlusPlugDataTest, ParameterizedConstructor) {
    std::string source = "test_source";
    double power = 100.5;
    double timestamp = 1617181910.0;
    ShellyPlusPlugData plugData(source, power, timestamp);
    EXPECT_EQ(plugData.getSource(), source);
    EXPECT_EQ(plugData.getPower(), power);
    EXPECT_EQ(plugData.getTimestamp(), timestamp);
}

TEST(ShellyPlusPlugDataTest, Constructor) {
    ShellyPlusPlugData data("source1", 100.0, 1234567890);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getPower(), 100.0);
    EXPECT_EQ(data.getTimestamp(), 1234567890);
}

TEST(ShellyPlusPlugDataTest, SettersAndGetters) {
    ShellyPlusPlugData data("source1", 100.0, 1234567890);
    data.setPower(50.0);
    data.setTimestamp(987654321);

    EXPECT_EQ(data.getSource(), "source1");
    EXPECT_EQ(data.getPower(), 50.0);
    EXPECT_EQ(data.getTimestamp(), 987654321);
}