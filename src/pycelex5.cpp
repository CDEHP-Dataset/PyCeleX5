#include "pycelex5.h"

using std::cout;
using std::endl;

namespace py = pybind11;

uint32_t PyCeleX5::sm_uiWidth = 1280;
uint32_t PyCeleX5::sm_uiHeight = 800;
uint32_t PyCeleX5::sm_uiResolution = PyCeleX5::sm_uiWidth * PyCeleX5::sm_uiHeight;

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
        cout << "PyCeleX5.getSensorFixedMode(): mode " << printCeleX5Mode(result) << endl;
    }
    return result;
}

py::array_t<uint8_t> PyCeleX5::getFullPicBuffer()
{
    unsigned char *pBuffer1 = new unsigned char[PyCeleX5::sm_uiResolution];
    this->m_pCeleX5->getFullPicBuffer(pBuffer1);
    py::array_t<uint8_t> result = py::array_t<uint8_t>({PyCeleX5::sm_uiHeight, PyCeleX5::sm_uiWidth}, pBuffer1);
    delete pBuffer1;
    return result;
}

py::array_t<uint8_t> PyCeleX5::getEventPicBuffer(CeleX5::EventPicType type)
{
    unsigned char *pBuffer1 = new unsigned char[PyCeleX5::sm_uiResolution];
    this->m_pCeleX5->getEventPicBuffer(pBuffer1, type);
    py::array_t<uint8_t> result = py::array_t<uint8_t>({PyCeleX5::sm_uiHeight, PyCeleX5::sm_uiWidth}, pBuffer1);
    delete pBuffer1;
    return result;
}

py::array_t<uint8_t> PyCeleX5::getOpticalFlowPicBuffer(CeleX5::OpticalFlowPicType type)
{
    unsigned char *pBuffer1 = new unsigned char[PyCeleX5::sm_uiResolution];
    this->m_pCeleX5->getOpticalFlowPicBuffer(pBuffer1, type);
    py::array_t<uint8_t> result = py::array_t<uint8_t>({PyCeleX5::sm_uiHeight, PyCeleX5::sm_uiWidth}, pBuffer1);
    delete pBuffer1;
    return result;
}

uint32_t PyCeleX5::getFullPicFrameTime()
{
    uint32_t result = this->m_pCeleX5->getFullPicFrameTime();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getFullPicFrameTime(): " << result << endl;
    }
    return result;
}

void PyCeleX5::setEventFrameTime(uint32_t microsecond)
{
    this->m_pCeleX5->setEventFrameTime(microsecond);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setEventFrameTime(): " << microsecond << endl;
    }
}

uint32_t PyCeleX5::getEventFrameTime()
{
    uint32_t result = this->m_pCeleX5->getEventFrameTime();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getEventFrameTime(): " << result << endl;
    }
    return result;
}

void PyCeleX5::setOpticalFlowFrameTime(uint32_t millisecond)
{
    this->m_pCeleX5->setOpticalFlowFrameTime(millisecond);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setOpticalFlowFrameTime(): " << millisecond << endl;
    }
}

uint32_t PyCeleX5::getOpticalFlowFrameTime()
{
    uint32_t result = this->m_pCeleX5->getOpticalFlowFrameTime();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getOpticalFlowFrameTime(): " << result << endl;
    }
    return result;
}

void PyCeleX5::setSensorLoopMode(CeleX5::CeleX5Mode mode, int loopNum)
{
    this->m_pCeleX5->setSensorLoopMode(mode, loopNum);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setSensorLoopMode(): loop " << loopNum << " in mode " << printCeleX5Mode(mode) << endl;
    }
}

CeleX5::CeleX5Mode PyCeleX5::getSensorLoopMode(int loopNum)
{
    CeleX5::CeleX5Mode result = this->m_pCeleX5->getSensorLoopMode(loopNum);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getSensorLoopMode(): loop " << loopNum << " in mode " << printCeleX5Mode(result) << endl;
    }
    return result;
}

void PyCeleX5::setLoopModeEnabled(bool enable)
{
    this->m_pCeleX5->setLoopModeEnabled(enable);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setLoopModeEnabled(): set loop mode " << (enable ? "enable" : "disable") << endl;
    }
}

bool PyCeleX5::isLoopModeEnabled()
{
    bool result = this->m_pCeleX5->isLoopModeEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isLoopModeEnabled(): loop mode is " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::setEventDuration(uint32_t value)
{
    this->m_pCeleX5->setEventDuration(value);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setEventDuration(): " << value << endl;
    }
}

void PyCeleX5::setPictureNumber(uint32_t num, CeleX5::CeleX5Mode mode)
{
    this->m_pCeleX5->setPictureNumber(num, mode);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setPictureNumber(): mode " << printCeleX5Mode(mode) << " number " << num << endl;
    }
}

void PyCeleX5::setThreshold(uint32_t value)
{
    this->m_pCeleX5->setThreshold(value);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setThreshold(): " << value << endl;
    }
}

uint32_t PyCeleX5::getThreshold()
{
    uint32_t result = this->m_pCeleX5->getThreshold();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getThreshold(): " << result << endl;
    }
    return result;
}

void PyCeleX5::setBrightness(uint32_t value)
{
    this->m_pCeleX5->setBrightness(value);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setBrightness(): " << value << endl;
    }
}

uint32_t PyCeleX5::getBrightness()
{
    uint32_t result = this->m_pCeleX5->getBrightness();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getBrightness(): " << result << endl;
    }
    return result;
}

// void PyCeleX5::setContrast(uint32_t value)
// {
//     this->m_pCeleX5->setContrast(value);
//     if (this->m_bDebug)
//     {
//         cout << "PyCeleX5.setContrast(): " << value << endl;
//     }
// }

// uint32_t PyCeleX5::getContrast()
// {
//     uint32_t result = this->m_pCeleX5->getContrast();
//     if (this->m_bDebug)
//     {
//         cout << "PyCeleX5.getContrast(): " << result << endl;
//     }
//     return result;
// }

void PyCeleX5::setClockRate(uint32_t value)
{
    this->m_pCeleX5->setClockRate(value);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setClockRate(): " << value << endl;
    }
}

uint32_t PyCeleX5::getClockRate()
{
    uint32_t result = this->m_pCeleX5->getClockRate();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getClockRate(): " << result << endl;
    }
    return result;
}

void PyCeleX5::setEventDataFormat(int format)
{
    this->m_pCeleX5->setEventDataFormat(format);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setEventDataFormat(): " << format << endl;
    }
}

int PyCeleX5::getEventDataFormat()
{
    uint32_t result = this->m_pCeleX5->getEventDataFormat();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getEventDataFormat(): " << result << endl;
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
    result += "(" + std::to_string(type) + ")";
    return result;
}

std::string PyCeleX5::printCeleX5Mode(CeleX5::CeleX5Mode mode)
{
    std::string result;
    switch (mode)
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
    result += "(" + std::to_string(mode) + ")";
    return result;
}

std::string PyCeleX5::printEventPicType(CeleX5::EventPicType type)
{
    std::string result;
    switch (type)
    {
    case CeleX5::EventPicType::EventBinaryPic:
        result = "EventBinaryPic";
        break;
    case CeleX5::EventPicType::EventAccumulatedPic:
        result = "EventAccumulatedPic";
        break;
    case CeleX5::EventPicType::EventGrayPic:
        result = "EventGrayPic";
        break;
    case CeleX5::EventPicType::EventCountPic:
        result = "EventCountPic";
        break;
    case CeleX5::EventPicType::EventDenoisedBinaryPic:
        result = "EventDenoisedBinaryPic";
        break;
    case CeleX5::EventPicType::EventSuperimposedPic:
        result = "EventSuperimposedPic";
        break;
    case CeleX5::EventPicType::EventDenoisedCountPic:
        result = "EventDenoisedCountPic";
        break;
    case CeleX5::EventPicType::EventCountDensityPic:
        result = "EventCountDensityPic";
        break;
    case CeleX5::EventPicType::EventInPixelTimestampPic:
        result = "EventInPixelTimestampPic";
        break;
    default:
        result = "Wrong EventPicType";
        break;
    }
    result += "(" + std::to_string(type) + ")";
    return result;
}

std::string PyCeleX5::printOpticalFlowPicType(CeleX5::OpticalFlowPicType type)
{
    std::string result;
    switch (type)
    {
    case CeleX5::OpticalFlowPicType::OpticalFlowPic:
        result = "OpticalFlowPic";
        break;
    case CeleX5::OpticalFlowPicType::OpticalFlowSpeedPic:
        result = "OpticalFlowSpeedPic";
        break;
    case CeleX5::OpticalFlowPicType::OpticalFlowDirectionPic:
        result = "OpticalFlowDirectionPic";
        break;
    default:
        result = "Wrong EventPicType";
        break;
    }
    result += "(" + std::to_string(type) + ")";
    return result;
}
