#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mqtt_client.h"
#include "JSONProcessorFactory.h"
#include <string>
#include <vector>

using ::testing::_;
using ::testing::Invoke;

class MockMQTTClientCallback : public MQTTClientCallback {
public:
    MockMQTTClientCallback(MQTTClient* client) : MQTTClientCallback(client) {}

    MOCK_METHOD1(message_arrived, void(mqtt::const_message_ptr msg));
};

class MockMQTTClient : public MQTTClient {
public:
    MockMQTTClient(const std::string& broker, int port, const std::vector<std::string>& topics)
        : MQTTClient(broker, port, topics) {}

    MOCK_METHOD0(on_connect, void());
    MOCK_METHOD0(on_disconnect, void());
    MOCK_METHOD2(on_message, void(const std::string& topic, const std::string& payload));
};

class MQTTClientTest : public ::testing::Test {
protected:
    MockMQTTClient* client;
    MockMQTTClientCallback* callback;

    void SetUp() override {
        client = new MockMQTTClient("broker.hivemq.com", 1883, {"test/topic"});
        callback = new MockMQTTClientCallback(client);
    }

    void TearDown() override {
        delete client;
        delete callback;
    }
};

// TEST_F(MQTTClientTest, ConnectSuccess) {
//     EXPECT_CALL(*client, on_connect()).Times(1);
//     EXPECT_TRUE(client->connect());
// }

TEST_F(MQTTClientTest, ConnectFailure) {
    // Simulate a connection failure by setting an invalid broker address
    MockMQTTClient invalidClient("invalid_broker", 1883, {"test/topic"});
    EXPECT_CALL(invalidClient, on_connect()).Times(0);
    EXPECT_FALSE(invalidClient.connect());
}

// TEST_F(MQTTClientTest, DisconnectSuccess) {
//     EXPECT_CALL(*client, on_disconnect()).Times(1);
//     client->connect();
//     client->disconnect();
// }

// TEST_F(MQTTClientTest, MessageArrived) {
//     mqtt::const_message_ptr msg = mqtt::make_message("test/topic", "payload");
//     EXPECT_CALL(*client, on_message("test/topic", "payload")).Times(1);
//     callback->message_arrived(msg);
// }

TEST_F(MQTTClientTest, StartAndStop) {
    client->connect();
    client->start();
    client->stop();
}