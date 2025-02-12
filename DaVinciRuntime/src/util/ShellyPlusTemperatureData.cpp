#include "ShellyPlusTemperatureData.h"


// Default constructor implementation
ShellyPlusTemperatureData::ShellyPlusTemperatureData() {
    // Initialization code here if needed
}

// Default destructor definition
ShellyPlusTemperatureData::~ShellyPlusTemperatureData() {
    // Cleanup code here if needed
}

ShellyPlusTemperatureData::ShellyPlusTemperatureData(const std::string& source, double temperature, 
    double humidity, double timestamp)
    : temperatureC_(temperature), humidity_(humidity), timestamp_(timestamp) {}

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

void ShellyPlusTemperatureData::setSource(const std::string& source) {
    source_ = source;
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