#include "ShellyPlusPlugData.h"

// Default constructor implementation
ShellyPlusPlugData::ShellyPlusPlugData() {
    // Initialization code here if needed
    source_ = "";
    power_ = 0;
    timestamp_ = 0;
}

// Default destructor definition
ShellyPlusPlugData::~ShellyPlusPlugData() {
    // Cleanup code here if needed
}

ShellyPlusPlugData::ShellyPlusPlugData(const std::string& src, double power, double timestamp)
    : source_(src), power_(power), timestamp_(timestamp) {}

std::string ShellyPlusPlugData::getSource() const {
    return source_;
}

double ShellyPlusPlugData::getPower() const {
    return power_;
}

double ShellyPlusPlugData::getTimestamp() const {
    return timestamp_;
}

void ShellyPlusPlugData::setPower(double power) {
    power_ = power;
}

void ShellyPlusPlugData::setTimestamp(double timestamp) {
    timestamp_ = timestamp;
}