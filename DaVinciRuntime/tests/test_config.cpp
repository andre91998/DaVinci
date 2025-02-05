#include <gtest/gtest.h>
#include "config.h"

TEST(ConfigTest, TestLoadConfigFileSuccess) {
    Config config;
    EXPECT_TRUE(config.load("path/to/valid/config.json"));
    EXPECT_EQ(config.getMQTTBroker(), "expected_broker");
    EXPECT_EQ(config.getMQTTPort(), expected_port);
    EXPECT_EQ(config.getDatabasePath(), "expected_db_path");
    EXPECT_EQ(config.getGRPCPort(), expected_grpc_port);
    std::vector<std::string> expected_topics = {"topic1", "topic2"};
    EXPECT_EQ(config.getMQTTTopics(), expected_topics);
}

TEST(ConfigTest, TestLoadConfigFileFailure) {
    Config config;
    EXPECT_FALSE(config.load("path/to/invalid/config.json"));
}