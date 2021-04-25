#include "../include/celex5/celex5.h"

class PyCeleX5
{
public:
    PyCeleX5();
    ~PyCeleX5();

    bool openSensor(CeleX5::DeviceType type);
    bool isSensorReady();

private:
    CeleX5 *m_pCeleX5;
}
