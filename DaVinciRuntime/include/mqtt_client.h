#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>
#include "mqtt/client.h"
#include "mqtt/async_client.h"

// Forward declaration of MQTTClient
class MQTTClient;

class MQTTClientCallback : public virtual mqtt::callback {
public:
    MQTTClientCallback(MQTTClient* client);
    void message_arrived(mqtt::const_message_ptr msg) override;

private:
    MQTTClient* client_;
};

class MQTTClient {
public:
    MQTTClient(const std::string& broker, int port, const std::string& topic);
    ~MQTTClient();

    bool connect();
    void disconnect();
    void start();
    void stop();

    void on_message(const std::string& topic, const std::string& payload);

private:
    std::string broker_;
    int port_;
    std::string topic_;
    mqtt::client* client_;
    MQTTClientCallback* callback_;

    void on_connect();
    void on_disconnect();
};

#endif // MQTT_CLIENT_H
