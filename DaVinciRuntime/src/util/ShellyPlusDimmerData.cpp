#include "ShellyPlusDimmerData.h"

ShellyPlusDimmerData::ShellyPlusDimmerData(const std::string& source, int brightness, bool state, double timestamp)
    : source_(source), brightness_(brightness), state_(state), timestamp_(timestamp) {}


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

void ShellyPlusDimmerData::setSource(const std::string& source) {
    source_ = source_;
}

void ShellyPlusDimmerData::setState(bool state) {
    state_ = state;
}

void ShellyPlusDimmerData::setTimestamp(double timestamp) {
    timestamp_ = timestamp;
}