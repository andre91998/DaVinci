#include <gtest/gtest.h>
#include "config.h"

class ConfigTest : public ::testing::Test {
protected:
    Config config;

    void SetUp() override {
        // Initialize the config with test data if needed
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

// NOTE, this test is based on the example config in config/config.json
// The actual config should be placed in /usr/config/DaVinci as 
// specified in the documentation
TEST_F(ConfigTest, LoadConfigSuccess) {
    EXPECT_TRUE(config.load("config/config.json"));
    EXPECT_EQ(config.getMQTTBroker(), "localhost");
    EXPECT_EQ(config.getMQTTPort(), 1883);
    EXPECT_EQ(config.getDatabasePath(), "davinci.db");
    EXPECT_EQ(config.getGRPCPort(), 50051);
    auto topics = config.getMQTTTopics();
    EXPECT_EQ(topics.size(), 3);
    EXPECT_EQ(topics[0], "shellyplugus-d8132ad47cdc/events/rpc");
}

TEST_F(ConfigTest, LoadConfigFailure) {
    EXPECT_FALSE(config.load("invalid_config.json"));
}

TEST_F(ConfigTest, GetMQTTBroker) {
    config.load("config/config.json");
    EXPECT_EQ(config.getMQTTBroker(), "localhost");
}

TEST_F(ConfigTest, GetMQTTPort) {
    config.load("config/config.json");
    EXPECT_EQ(config.getMQTTPort(), 1883);
}

TEST_F(ConfigTest, GetDatabasePath) {
    config.load("config/config.json");
    EXPECT_EQ(config.getDatabasePath(), "davinci.db");
}

TEST_F(ConfigTest, GetGRPCPort) {
    config.load("config/config.json");
    EXPECT_EQ(config.getGRPCPort(), 50051);
}

TEST_F(ConfigTest, GetMQTTTopics) {
    config.load("config/config.json");
    auto topics = config.getMQTTTopics();
    EXPECT_EQ(topics.size(), 3);
    EXPECT_EQ(topics[0], "shellyplugus-d8132ad47cdc/events/rpc");
}