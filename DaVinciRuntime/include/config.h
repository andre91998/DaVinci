#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

class Config {
public:
    Config();
    ~Config();

    bool load(const std::string& filepath);

    std::string getMQTTBroker() const;
    int getMQTTPort() const;
    std::vector<std::string> getMQTTTopics() const;
    std::string getDatabasePath() const;
    int getGRPCPort() const;

private:
    std::string mqttBroker_;
    int mqttPort_;
    std::vector<std::string> mqttTopics_;
    std::string databasePath_;
    int grpcPort_;
};

#endif // CONFIG_H
