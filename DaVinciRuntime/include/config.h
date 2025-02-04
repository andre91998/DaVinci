#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
public:
    Config();
    ~Config();

    bool load(const std::string& filepath);

    std::string getMQTTBroker() const;
    int getMQTTPort() const;
    std::string getMQTTTopic() const;
    std::string getDatabasePath() const;
    int getGRPCPort() const;

private:
    std::string mqttBroker_;
    int mqttPort_;
    std::string mqttTopic_;
    std::string databasePath_;
    int grpcPort_;
};

#endif // CONFIG_H
