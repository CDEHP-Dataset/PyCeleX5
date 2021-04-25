#include "pycelex5.h"
#include <iostream>

PyCeleX5::PyCeleX5()
{
    std::cout << "PyCeleX5: PyCeleX5()" << std::endl;
}

PyCeleX5::~PyCeleX5()
{
    std::cout << "PyCeleX5: ~PyCeleX5()" << std::endl;
}

bool PyCeleX5::openSensor(CeleX5::DeviceType type)
{
    return m_pCeleX5->openSensor(type);
}

bool PyCeleX5::isSensorReady()
{
    return m_pCeleX5->isSensorReady();
}
