#include <gtest/gtest.h>
#include "mqtt_client.h"

TEST(MQTTClientTest, TestConnection) {
    std::vector<std::string> topics = {"test/topic1", "test/topic2"};
    MQTTClient client("localhost", 1883, topics);
    EXPECT_TRUE(client.connect());
    client.disconnect();
}

TEST(MQTTClientTest, TestSubscription) {
    std::vector<std::string> topics = {"test/topic1", "test/topic2"};
    MQTTClient client("localhost", 1883, topics);
    client.connect();
    client.start();
    // Add more test logic for subscription here
    client.stop();
    client.disconnect();
}

TEST(MQTTClientTest, TestMessageArrived) {
    // Mocking the MQTTClientCallback and message_arrived behavior
}

TEST(MQTTClientTest, TestOnMessage) {
    std::vector<std::string> topics = {"test/topic1"};
    MQTTClient client("localhost", 1883, topics);
    client.connect();
    client.start();
    client.on_message("test/topic1", "{\"key\":\"value\"}");
    // Add more assertions based on the expected behavior of on_message
    client.stop();
    client.disconnect();
}