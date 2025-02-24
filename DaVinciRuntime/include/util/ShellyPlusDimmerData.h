#ifndef SHELLYPLUSDIMMERDATA_H
#define SHELLYPLUSDIMMERDATA_H

#include <string>

class ShellyPlusDimmerData {
public:
    ShellyPlusDimmerData();
    ShellyPlusDimmerData(const std::string& src, int brightness,
         bool state, double timestamp);

    ~ShellyPlusDimmerData();

    std::string getSource() const;
    int getBrightness() const;
    bool getState() const;
    double getTimestamp() const;

    void setBrightness(int brightness);
    void setState(bool state);
    void setTimestamp(double timestamp);

private:
    void setSource(const std::string& src);
    std::string source_;
    int brightness_;
    bool state_;
    double timestamp_;
};

#endif // SHELLYPLUSDIMMERDATA_H