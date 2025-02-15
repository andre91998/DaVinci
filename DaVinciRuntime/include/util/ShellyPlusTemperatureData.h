#ifndef SHELLYPLUSTEMPERATUREDATA_H
#define SHELLYPLUSTEMPERATUREDATA_H

#include <string>

class ShellyPlusTemperatureData {
public:
    ShellyPlusTemperatureData();
    ShellyPlusTemperatureData(const std::string& src, double humidity, double tempC, double timestamp);

    ~ShellyPlusTemperatureData();
    
    std::string getSource() const;
    double getTemperature() const;
    double getHumidity() const;
    double getTimestamp() const;

    void setTemperature(double tempC);
    void setHumidity(double humidity);
    void setTimestamp(double timestamp);

private:
    void setSource(const std::string& src);
    std::string source_;
    double temperatureC_;
    double humidity_;
    double timestamp_;
};

#endif // SHELLYPLUSTEMPERATUREDATA_H