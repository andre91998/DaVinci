#ifndef SHELLYPLUSTEMPERATUREDATA_H
#define SHELLYPLUSTEMPERATUREDATA_H

#include <string>

class ShellyPlusTemperatureData {
public:
    ShellyPlusTemperatureData(const std::string& source, double humidity, double tempC, double timestamp);

    std::string getSource() const;
    double getTemperature() const;
    double getHumidity() const;
    double getTimestamp() const;

    void setTemperature(double tempC);
    void setHumidity(double humidity);
    void setTimestamp(double timestamp);

private:
    void setSource(const std::string& source);
    std::string source_;
    double temperatureC_;
    double humidity_;
    double timestamp_;
};

#endif // SHELLYPLUSTEMPERATUREDATA_H