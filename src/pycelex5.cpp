#include "pycelex5.h"

using std::cout;
using std::endl;

PyCeleX5::PyCeleX5(bool debug)
{
    m_pCeleX5 = new CeleX5();
    this->m_bDebug = debug;
    cout << "PyCeleX5.PyCeleX5(): " << (debug ? "in debug mode" : "") << endl;
}

PyCeleX5::~PyCeleX5()
{
    cout << "PyCeleX5.~PyCeleX5()" << endl;
}

bool PyCeleX5::openSensor(CeleX5::DeviceType type)
{
    bool result = m_pCeleX5->openSensor(type);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.openSensor(): open sensor " << (result ? "successful" : "failed") << endl;
    }
    return result;
}

bool PyCeleX5::isSensorReady()
{
    bool result = m_pCeleX5->isSensorReady();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isSensorReady(): sensor " << (result ? "is" : "is not") << " ready" << endl;
    }
    return result;
}

bool PyCeleX5::setFpnFile(const std::string &fpnFile)
{
    bool result = m_pCeleX5->setFpnFile(fpnFile);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setFpnFile(): " << fpnFile << endl;
        cout << "PyCeleX5.setFpnFile(): set FPN file " << (result ? "successful" : "failed") << endl;
    }
    return result;
}

void PyCeleX5::generateFpn(const std::string &fpnFile)
{
    m_pCeleX5->generateFPN(fpnFile);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setFpnFile(): called" << endl;
    }
}

void setSensorFixedMode(CeleX5::CeleX5Mode mode)
{
    m_pCeleX5->setSensorFixedMode(mode);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setSensorFixedMode(): called" << endl;
    }
}

Celex5::CeleX5Mode getSensorFixedMode()
{
    CeleX5::CeleX5Mode result = m_pCeleX5->getSensorFixedMode();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getSensorFixedMode(): called" << endl;
    }
    return result;
}
