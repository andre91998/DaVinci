#include "mqtt_client.h"

const std::string LOCALHOST("localhost:1883");
const std::string USERNAME("andre");

const std::string CLIENT_ID("DaVinciRuntime");
const std::string TEMP_TOPIC("DaVinci-Temp-1/events/rpc");
const std::string PLUG_TOPIC("DaVinci-Plug-1/events/rpc");
const std::string DIMMER_TOPIC("DaVinci-Dimmer-1/events/rpc");

#include "mqtt_client.h"
#include <iostream>

MQTTClientCallback::MQTTClientCallback(MQTTClient* client) : client_(client) {}

void MQTTClientCallback::message_arrived(mqtt::const_message_ptr msg) {
    if (client_) {
        client_->on_message(msg->get_topic(), msg->to_string());
    }
}

MQTTClient::MQTTClient(const std::string& broker, int port, const std::string& topic)
    : broker_(broker), port_(port), topic_(topic), client_(nullptr), callback_(nullptr) {}

MQTTClient::~MQTTClient() {
    if (client_) {
        delete client_;
    }
    if (callback_) {
        delete callback_;
    }
}

bool MQTTClient::connect() {
    try {
        client_ = new mqtt::client(broker_, "client_id");
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
        client_->subscribe(topic_, 1);
    }
}

void MQTTClient::stop() {
    if (client_) {
        client_->stop_consuming();
    }
}

void MQTTClient::on_message(const std::string& topic, const std::string& payload) {
    std::cout << "Message received on topic " << topic << ": " << payload << std::endl;
}

void MQTTClient::on_connect() {
    std::cout << "Connected to MQTT broker" << std::endl;
}

void MQTTClient::on_disconnect() {
    std::cout << "Disconnected from MQTT broker" << std::endl;
}



// int init() {
//     mqtt::async_client client(LOCALHOST, CLIENTID);
    
//     // Set the callback to handle incoming messages
//     std::cout << "Setting Client Subscribe Callback" << std::endl;
//     Callback cb;
//     client.set_callback(cb);

//     mqtt::connect_options connOpts;
//     connOpts.set_keep_alive_interval(20);
//     connOpts.set_clean_session(true);
//     connOpts.set_user_name(USERNAME);
//     connOpts.set_password(u8"Am8586792278");
//     connOpts.set_ssl(mqtt::ssl_options());
//     try {
//         // Connect to the MQTT broker
//         std::cout << "Connecting to the MQTT broker..." << std::endl;
//         client.connect(connOpts)->wait();

//         // Publish a message
//         //mqtt::message msg(TOPIC, "Hello World from C++ Paho!", 1, false);
//         //client.publish(msg);
//         //std::cout << "Message published" << std::endl;

//         // Set the callback to handle incoming messages
//         std::cout << "Setting Client Subscribe Callback" << std::endl;
//         client.set_callback(*cb);

//         // Subscribe to the all topics
//         std::cout << "Subscribing to topic: " << PLUG_TOPIC << std::endl;
//         client.subscribe(PLUG_TOPIC, 1)->wait();
//         std::cout << "Subscribed" << std::endl;

//         while(true) {
//                 //do nothing
//         }

//         // Disconnect
//         client.disconnect();
//         std::cout << "Disconnected" << std::endl;
//     } catch (const mqtt::exception& exc) {
//         std::cerr << "Error: " << exc.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }