#include "ShellyPlusTemperatureData.h"


// Default constructor implementation
ShellyPlusTemperatureData::ShellyPlusTemperatureData() {
    // Initialization code here if needed
    source_ = "";
    temperatureC_ = 0;
    humidity_ = 0;
    timestamp_ = 0;
}

// Default destructor definition
ShellyPlusTemperatureData::~ShellyPlusTemperatureData() {
    // Cleanup code here if needed
}

ShellyPlusTemperatureData::ShellyPlusTemperatureData(const std::string& src, double humidity, 
    double temperature, double timestamp)
    : source_(src), temperatureC_(temperature), humidity_(humidity), timestamp_(timestamp) {}

std::string ShellyPlusTemperatureData::getSource() const {
    return source_;
}

double ShellyPlusTemperatureData::getTemperature() const {
    return temperatureC_;
}

double ShellyPlusTemperatureData::getHumidity() const {
    return humidity_;
}

double ShellyPlusTemperatureData::getTimestamp() const {
    return timestamp_;
}

void ShellyPlusTemperatureData::setSource(const std::string& src) {
    source_ = src;
}
void ShellyPlusTemperatureData::setTemperature(double temperature) {
    temperatureC_ = temperature;
}

void ShellyPlusTemperatureData::setHumidity(double humidity) {
    humidity_ = humidity;
}

void ShellyPlusTemperatureData::setTimestamp(double timestamp) {
    timestamp_ = timestamp;
}