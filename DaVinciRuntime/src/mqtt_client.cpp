#include "mqtt_client.h"
#include "JSONProcessorFactory.h"
#include <iostream>
//#include "buffers.h"

const std::string CLIENT_ID("DaVinciRuntime");

MQTTClientCallback::MQTTClientCallback(MQTTClient* client) : client_(client) {}

// void MQTTClientCallback::connected(const std::string& cause) {
//     std::cout << cause << std::endl;
// }

// void MQTTClientCallback::connection_lost(const std::string& cause) {
//     std::cout << cause << std::endl;
// }

void MQTTClientCallback::message_arrived(mqtt::const_message_ptr msg) {
    if (client_) {
        client_->on_message(msg->get_topic(), msg->to_string());
    }
}

// void MQTTClientCallback::delivery_complete(mqtt::delivery_token_ptr token) {
//     std::cout << "onDeliveryComplete()" << std::endl;
// }

MQTTClient::MQTTClient(const std::string& broker, int port, const std::vector<std::string>& topics,  const std::string& db)
    : broker_(broker), port_(port), topics_(topics), client_(nullptr), callback_(nullptr), processorFactory_(new JSONProcessorFactory()), db_((Database::getInstance(db))) {}

MQTTClient::~MQTTClient() {
    if (client_) {
        delete client_;
    }
    if (callback_) {
        delete callback_;
    }
    if (processorFactory_) {
        delete processorFactory_;
    }
}

bool MQTTClient::connect() {
    try {
        client_ = new mqtt::client(broker_, CLIENT_ID);
        callback_ = new MQTTClientCallback(this);
        client_->set_callback(*callback_);
        client_->connect();
        on_connect();
        return true;
    } catch (const mqtt::exception& e) {
        std::cerr << "Failed to connect to MQTT broker: " << e.what() << std::endl;
        return false;
    }
}

void MQTTClient::disconnect() {
    if (client_) {
        client_->disconnect();
        on_disconnect();
    }
}

void MQTTClient::start() {
    if (client_) {
        client_->start_consuming();
        for (int i = 0; i < topics_.size(); i++) {
            client_->subscribe(topics_[i], 1);
        }
    }
}

void MQTTClient::stop() {
    if (client_) {
        client_->stop_consuming();
    }
}

void MQTTClient::on_message(const std::string& topic, const std::string& payload) {
    std::cout << "Message received on topic " << topic << ": " << payload << std::endl;
    JSONProcessor* processor = processorFactory_->getProcessor(topic);
    if (processor) {
        Json::CharReaderBuilder builder;
        Json::Value json;
        std::string errs;
        std::istringstream ss(payload);
        if (Json::parseFromStream(builder, ss, &json, &errs)) {
            JSONProcessor::SensorData sensorData = processor->process(json);
            if (processor->getType() == (int) SensorType::SHELLY_DIMMER) {
                auto data = std::get<ShellyPlusDimmerData>(sensorData);
                if (data.getSource().compare("stub") != 0) {
                    db_->execute("INSERT INTO shellyPlusDimmer (source, brightness, state, timestamp) VALUES ('" +
                                data.getSource() + "', " +
                                std::to_string(data.getBrightness()) + ", " +
                                std::to_string(data.getState()) + ", " +
                                std::to_string(data.getTimestamp()) + ")");
                }
            } else if (processor->getType() == (int) SensorType::SHELLY_PLUG) {
                auto data = std::get<ShellyPlusPlugData>(sensorData);
                if (data.getSource().compare("stub") != 0) {
                    db_->execute("INSERT INTO shellyPlusPlug (source, power, timestamp) VALUES ('" +
                                data.getSource() + "', " +
                                std::to_string(data.getPower()) + ", " +
                                std::to_string(data.getTimestamp()) + ")");
                    }
            } else if (processor->getType() == (int) SensorType::SHELLY_TEMP) {
                auto data = std::get<ShellyPlusTemperatureData>(sensorData);
                if (data.getSource().compare("stub") != 0) {
                    db_->execute("INSERT INTO shellyPlusTemperature (source, humidity, temperature, timestamp) VALUES ('" +
                                data.getSource() + "', " +
                                std::to_string(data.getTemperature()) + ", " +
                                std::to_string(data.getHumidity()) + ", " +
                                std::to_string(data.getTimestamp()) + ")");
                }
            }
        } else {
            std::cerr << "Failed to parse JSON: " << errs << std::endl;
        }
    } else {
        std::cerr << "No processor found for topic: " << topic << std::endl;
    }
}

void MQTTClient::on_connect() {
    std::cout << "Connected to MQTT broker" << std::endl;
}

void MQTTClient::on_disconnect() {
    std::cout << "Disconnected from MQTT broker" << std::endl;
}