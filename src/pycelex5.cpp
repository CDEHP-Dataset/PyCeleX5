#include "pycelex5.h"

bool PyCeleX5::openSensor(CeleX5::DeviceType type)
{
    return m_pCeleX5->openSensor(type);
}

bool PyCeleX5::isSensorReady()
{
    return m_pCeleX5->isSensorReady();
}
