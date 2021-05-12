#include "pycelex5.h"

using std::cout;
using std::endl;

PyCeleX5::PyCeleX5(bool debug)
{
    this->m_pCeleX5 = new CeleX5();
    this->m_bDebug = debug;
    cout << "PyCeleX5.PyCeleX5(): " << (debug ? "in debug mode" : "") << endl;
}

PyCeleX5::~PyCeleX5()
{
    delete this->m_pCeleX5;
    cout << "PyCeleX5.~PyCeleX5()" << endl;
}

bool PyCeleX5::openSensor(CeleX5::DeviceType type)
{
    bool result = m_pCeleX5->openSensor(type);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.openSensor(): device type " << printDeviceType(type) << endl;
        cout << "PyCeleX5.openSensor(): open sensor " << (result ? "successful" : "failed") << endl;
    }
    return result;
}

bool PyCeleX5::isSensorReady()
{
    bool result = this->m_pCeleX5->isSensorReady();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isSensorReady(): sensor " << (result ? "is" : "is not") << " ready" << endl;
    }
    return result;
}

bool PyCeleX5::setFpnFile(const std::string &fpnFile)
{
    bool result = this->m_pCeleX5->setFpnFile(fpnFile);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setFpnFile(): " << fpnFile << endl;
        cout << "PyCeleX5.setFpnFile(): set FPN file " << (result ? "successful" : "failed") << endl;
    }
    return result;
}

void PyCeleX5::generateFpn(const std::string &fpnFile)
{
    this->m_pCeleX5->generateFPN(fpnFile);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.generateFpn(): " << fpnFile << endl;
    }
}

void PyCeleX5::setSensorFixedMode(CeleX5::CeleX5Mode mode)
{
    this->m_pCeleX5->setSensorFixedMode(mode);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setSensorFixedMode(): mode " << printCeleX5Mode(mode) << endl;
    }
}

CeleX5::CeleX5Mode PyCeleX5::getSensorFixedMode()
{
    CeleX5::CeleX5Mode result = this->m_pCeleX5->getSensorFixedMode();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getSensorFixedMode(): mode " << printCeleX5Mode(mode) << endl;
    }
    return result;
}

std::string PyCeleX5::printDeviceType(CeleX5::DeviceType type)
{
    std::string result;
    switch (type)
    {
    case CeleX5::DeviceType::Unknown_Devive:
        result = "Unknown_Devive";
        break;
    case CeleX5::DeviceType::CeleX5_MIPI:
        result = "CeleX5_MIPI";
        break;
    case CeleX5::DeviceType::CeleX5_OpalKelly:
        result = "CeleX5_OpalKelly";
        break;
    default:
        result = "Wrong DeviceType";
        break;
    }
    result += "(" + type + ")";
    return result;
}

std::string PyCeleX5::printCeleX5Mode(CeleX5::CeleX5Mode mode)
{
    std::string result;
    switch (type)
    {
    case CeleX5::CeleX5Mode::Unknown_Mode:
        result = "Unknown_Mode";
        break;
    case CeleX5::CeleX5Mode::Event_Off_Pixel_Timestamp_Mode:
        result = "Event_Off_Pixel_Timestamp_Mode";
        break;
    case CeleX5::CeleX5Mode::Event_In_Pixel_Timestamp_Mode:
        result = "Event_In_Pixel_Timestamp_Mode";
        break;
    case CeleX5::CeleX5Mode::Event_Intensity_Mode:
        result = "Event_Intensity_Mode";
        break;
    case CeleX5::CeleX5Mode::Full_Picture_Mode:
        result = "Full_Picture_Mode";
        break;
    case CeleX5::CeleX5Mode::Optical_Flow_Mode:
        result = "Optical_Flow_Mode";
        break;
    case CeleX5::CeleX5Mode::Multi_Read_Optical_Flow_Mode:
        result = "Multi_Read_Optical_Flow_Mode";
        break;
    default:
        result = "Wrong CeleX5Mode";
        break;
    }
    result += "(" + type + ")";
    return result;
}
