#include "../include/celex5/celex5.h"
#include <iostream>
#include <string>

class PyCeleX5
{
public:
    PyCeleX5(bool debug);
    ~PyCeleX5();

    bool openSensor(CeleX5::DeviceType type);
    bool isSensorReady();

    bool setFpnFile(const std::string &fpnFile);
    void generateFpn(const std::string &fpnFile);

    void setSensorFixedMode(CeleX5::CeleX5Mode mode);
    CeleX5::CeleX5Mode getSensorFixedMode();

private:
    CeleX5 *m_pCeleX5;
    bool m_bDebug;
};
