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

TEST_F(ConfigTest, LoadConfigSuccess) {
    EXPECT_TRUE(config.load("config.json"));
    EXPECT_EQ(config.getMQTTBroker(), "localhost");
    EXPECT_EQ(config.getMQTTPort(), 1883);
    EXPECT_EQ(config.getDatabasePath(), "/path/to/database");
    EXPECT_EQ(config.getGRPCPort(), 50051);
    auto topics = config.getMQTTTopics();
    EXPECT_EQ(topics.size(), 3);
    EXPECT_EQ(topics[0], "DaVinci-Plug-1/events/rpc");
}

TEST_F(ConfigTest, LoadConfigFailure) {
    EXPECT_FALSE(config.load("invalid_config.json"));
}

TEST_F(ConfigTest, GetMQTTBroker) {
    config.load("config.json");
    EXPECT_EQ(config.getMQTTBroker(), "localhost");
}

TEST_F(ConfigTest, GetMQTTPort) {
    config.load("config.json");
    EXPECT_EQ(config.getMQTTPort(), 1883);
}

TEST_F(ConfigTest, GetDatabasePath) {
    config.load("config.json");
    EXPECT_EQ(config.getDatabasePath(), "/path/to/database");
}

TEST_F(ConfigTest, GetGRPCPort) {
    config.load("config.json");
    EXPECT_EQ(config.getGRPCPort(), 50051);
}

TEST_F(ConfigTest, GetMQTTTopics) {
    config.load("config.json");
    auto topics = config.getMQTTTopics();
    EXPECT_EQ(topics.size(), 3);
    EXPECT_EQ(topics[0], "DaVinci-Plug-1/events/rpc");
}