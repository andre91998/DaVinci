#ifndef SHELLYPLUSPLUGDATA_H
#define SHELLYPLUSPLUGDATA_H

#include <string>

class ShellyPlusPlugData {
public:
    ShellyPlusPlugData();
    ShellyPlusPlugData(const std::string& src, double power, double timestamp);

    ~ShellyPlusPlugData();

    std::string getSource() const;
    double getPower() const;
    double getTimestamp() const;

    void setPower(double power);
    void setTimestamp(double timestamp);

private:
    void setSource(const std::string& src);
    
    std::string source_;
    double power_;
    double timestamp_;
};

#endif // SHELLYPLUSPLUGDATA_H