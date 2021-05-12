#include "../include/celex5/celex5.h"
#include <iostream>
#include <string>

class PyCeleX5
{
public:
    PyCeleX5(bool debug);
    ~PyCeleX5();

    // 2.3.1 openSensor
    bool openSensor(CeleX5::DeviceType type);
    // 2.3.2 isSensorReady
    bool isSensorReady();

    // 2.3.3 getCeleXRawData

    // 2.3.4 setFpnFile
    bool setFpnFile(const std::string &fpnFile);
    // 2.3.5 generateFPN
    void generateFpn(const std::string &fpnFile);

    // 2.3.6 setSensorFixedMode
    void setSensorFixedMode(CeleX5::CeleX5Mode mode);
    // 2.3.7 getSensorFixedMode
    CeleX5::CeleX5Mode getSensorFixedMode();

private:
    CeleX5 *m_pCeleX5;
    bool m_bDebug;

    std::string printDeviceType(CeleX5::DeviceType type);
    std::string printCeleX5Mode(CeleX5::CeleX5Mode mode);
};
