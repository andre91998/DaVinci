#include <gtest/gtest.h>
#include <mqtt/client.h>
#include <thread>
#include <filesystem>
#include "mqtt_client.h"
#include "database.h"

class MQTTClientTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a test database
        test_db_path = "test_mqtt_client.db";
        // Use getInstance method to get the Database instance
        db = Database::getInstance(test_db_path);

        // Initialize the database with some test data
        db->execute("CREATE TABLE IF NOT EXISTS shellyDimmerData (source TEXT, brightness INTEGER, state INTEGER, timestamp INTEGER)");
        db->execute("CREATE TABLE IF NOT EXISTS shellyPlugData (source TEXT, power REAL, timestamp INTEGER)");
        db->execute("CREATE TABLE IF NOT EXISTS shellyTemperatureData (source TEXT, temperature REAL, humidity REAL, timestamp INTEGER)");

        db->execute("INSERT INTO shellyDimmerData (source, brightness, state, timestamp) VALUES ('source1', 50, 1, 1234567890)");
        db->execute("INSERT INTO shellyPlugData (source, power, timestamp) VALUES ('source1', 100.0, 1234567890)");
        db->execute("INSERT INTO shellyTemperatureData (source, temperature, humidity, timestamp) VALUES ('source1', 25.0, 60.0, 1234567890)");

        // Initialize the MQTT client
        mqtt_client = new MQTTClient("localhost", 1883, {"test/topic"}, test_db_path);
    }

    void TearDown() override {
        // Cleanup
        delete mqtt_client;
        db->destroyInstance();
        std::filesystem::remove(test_db_path);
    }

    Database* db;
    MQTTClient* mqtt_client;
    std::string test_db_path;
};

TEST_F(MQTTClientTest, Connect) {
    ASSERT_TRUE(mqtt_client->connect());
}

TEST_F(MQTTClientTest, ConnectFailure) {
    MQTTClient faulty_client("tcp://invalid_host", 1883, {"test/topic"}, test_db_path);
    ASSERT_FALSE(faulty_client.connect());
}

TEST_F(MQTTClientTest, Disconnect) {
    mqtt_client->connect();
    mqtt_client->disconnect();
    SUCCEED();
}

TEST_F(MQTTClientTest, StartStop) {
    mqtt_client->connect();
    mqtt_client->start();
    mqtt_client->stop();
    mqtt_client->disconnect();
    SUCCEED();
}

TEST_F(MQTTClientTest, StartAndStop) {
    mqtt_client->connect();
    mqtt_client->start();
    mqtt_client->stop();
    SUCCEED();
}

TEST_F(MQTTClientTest, OnMessage) {
    mqtt_client->connect();
    mqtt_client->start();
    mqtt_client->on_message("test/topic", "{\"source\":\"source1\", \"brightness\":75, \"state\":1, \"timestamp\":1234567890}");
    mqtt_client->stop();
    mqtt_client->disconnect();
    SUCCEED();
}