#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>
#include <vector>
#include <mqtt/client.h>
#include "json_processor.h"
#include "sensor_types.h"

// Forward declaration of JSONProcessorFactory
class JSONProcessorFactory;

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
    MQTTClient(const std::string& broker, int port, const std::vector<std::string>& topics);
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

    void on_connect();
    void on_disconnect();
};

#endif // MQTT_CLIENT_H