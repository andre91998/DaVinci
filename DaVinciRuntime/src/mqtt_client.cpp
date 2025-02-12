#include "mqtt_client.h"
#include "JSONProcessorFactory.h"
#include <iostream>

// TODO: REMOVE
// These are a stub for our future Database
// Fixed-size ring buffers
std::deque<ShellyPlusDimmerData> dimmer_buffer(100);
std::deque<ShellyPlusPlugData> plug_buffer(100);
std::deque<ShellyPlusTemperatureData> temperature_buffer(100);
std::mutex buffer_mutex;

const std::string CLIENT_ID("DaVinciRuntime");

MQTTClientCallback::MQTTClientCallback(MQTTClient* client) : client_(client) {}

void MQTTClientCallback::message_arrived(mqtt::const_message_ptr msg) {
    if (client_) {
        client_->on_message(msg->get_topic(), msg->to_string());
    }
}

MQTTClient::MQTTClient(const std::string& broker, int port, const std::vector<std::string>& topics)
    : broker_(broker), port_(port), topics_(topics), client_(nullptr), callback_(nullptr), processorFactory_(new JSONProcessorFactory()) {}

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
                std::lock_guard<std::mutex> lock(buffer_mutex);
                if (dimmer_buffer.size() >= 100) {
                    dimmer_buffer.pop_front();
                }
                dimmer_buffer.push_back(std::get<ShellyPlusDimmerData>(sensorData));
            } else if (processor->getType() == (int) SensorType::SHELLY_PLUG) {
                std::lock_guard<std::mutex> lock(buffer_mutex);
                if (plug_buffer.size() >= 100) {
                    plug_buffer.pop_front();
                }
                plug_buffer.push_back(std::get<ShellyPlusPlugData>(sensorData));
            } else if (processor->getType() == (int) SensorType::SHELLY_TEMP) {
                std::lock_guard<std::mutex> lock(buffer_mutex);
                if (temperature_buffer.size() >= 100) {
                    temperature_buffer.pop_front();
                }
                temperature_buffer.push_back(std::get<ShellyPlusTemperatureData>(sensorData));
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