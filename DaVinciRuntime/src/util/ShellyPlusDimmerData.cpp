#include "ShellyPlusDimmerData.h"

// Default constructor implementation
ShellyPlusDimmerData::ShellyPlusDimmerData() {
    // Initialization code here if needed
}

// Default destructor definition
ShellyPlusDimmerData::~ShellyPlusDimmerData() {
    // Cleanup code here if needed
}

ShellyPlusDimmerData::ShellyPlusDimmerData(const std::string& src, int brightness, bool state, double timestamp)
    : source_(src), brightness_(brightness), state_(state), timestamp_(timestamp) {}


std::string ShellyPlusDimmerData::getSource() const {
    return source_;
}

int ShellyPlusDimmerData::getBrightness() const {
    return brightness_;
}

bool ShellyPlusDimmerData::getState() const {
    return state_;
}

double ShellyPlusDimmerData::getTimestamp() const {
    return timestamp_;
}

void ShellyPlusDimmerData::setBrightness(int brightness) {
    brightness_ = brightness;
}

void ShellyPlusDimmerData::setSource(const std::string& src) {
    source_ = src;
}

void ShellyPlusDimmerData::setState(bool state) {
    state_ = state;
}

void ShellyPlusDimmerData::setTimestamp(double timestamp) {
    timestamp_ = timestamp;
}