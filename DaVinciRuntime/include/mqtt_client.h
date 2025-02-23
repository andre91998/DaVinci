#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <mqtt/client.h>
#include <string>
#include <vector>
#include <mutex>
#include "JSONProcessorFactory.h"
#include "database.h"

class MQTTClient;

class MQTTClientCallback : public virtual mqtt::callback {
public:
    explicit MQTTClientCallback(MQTTClient* client);

    // void connected(const std::string& cause) override;
    // void connection_lost(const std::string& cause) override;
    void message_arrived(mqtt::const_message_ptr msg) override;
    // void delivery_complete(mqtt::delivery_token_ptr token) override;

private:
    MQTTClient* client_;
};

class MQTTClient {
public:
    MQTTClient(const std::string& broker, int port, const std::vector<std::string>& topics, const std::string& db);
    ~MQTTClient();

    bool connect();
    void disconnect();
    void start();
    void stop();

    void on_message(const std::string& topic, const std::string& payload);

private:
    std::string broker_;
    int port_;
    std::vector<std::string> topics_;
    mqtt::client* client_;
    MQTTClientCallback* callback_;
    JSONProcessorFactory* processorFactory_;
    Database* db_;  // Change to pointer

    void on_connect();
    void on_disconnect();
};

#endif // MQTT_CLIENT_H