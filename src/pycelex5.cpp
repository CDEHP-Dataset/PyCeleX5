#include <iostream>
#include <vector>
#include <pybind11/stl.h>
#include "pycelex5.h"

using std::cout;
using std::endl;
using std::vector;

namespace py = pybind11;

uint32_t PyCeleX5::sm_uiWidth = 1280;
uint32_t PyCeleX5::sm_uiHeight = 800;
uint32_t PyCeleX5::sm_uiResolution = PyCeleX5::sm_uiWidth * PyCeleX5::sm_uiHeight;

PyCeleX5::PyCeleX5(bool debug)
{
    this->m_pCeleX5 = new CeleX5();
    this->m_pBinFileObserver = NULL;
    this->m_bDebug = debug;
    this->m_bFileOpend = false;
    cout << "PyCeleX5.PyCeleX5(): " << (debug ? "in debug mode" : "") << endl;
    // SDK not yet implemented
    // cout << "PyCeleX5.PyCeleX5(): serial number " << this->m_pCeleX5->getSerialNumber() << endl;
    // cout << "PyCeleX5.PyCeleX5(): firmware version " << this->m_pCeleX5->getFirmwareVersion() << endl;
    // cout << "PyCeleX5.PyCeleX5(): firmware date " << this->m_pCeleX5->getFirmwareDate() << endl;
}

PyCeleX5::~PyCeleX5()
{
    this->stopRippingBinFile();
    delete this->m_pCeleX5;
    cout << "PyCeleX5.~PyCeleX5()" << endl;
}

void PyCeleX5::setRotateType(int type)
{
    this->m_pCeleX5->setRotateType(type);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setRotateType(): " << type << endl;
    }
}

int PyCeleX5::getRotateType()
{
    int result = this->m_pCeleX5->getRotateType();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getRotateType(): " << result << endl;
    }
    return result;
}

void PyCeleX5::startRippingBinFile()
{
    if (this->m_pBinFileObserver)
    {
        cout << "PyCeleX5.startRippingBinFile(): already start ripping bin file" << endl;
        return;
    }
    this->m_pBinFileObserver = new BinFileObserver(this->m_pCeleX5->getSensorDataServer(), this->m_pCeleX5);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.startRippingBinFile(): called" << endl;
    }
}

void PyCeleX5::stopRippingBinFile()
{
    if (!this->m_pBinFileObserver)
    {
        cout << "PyCeleX5.stopRippingBinFile(): already stop ripping bin file" << endl;
        return;
    }
    this->m_pBinFileObserver->close();
    delete this->m_pBinFileObserver;
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.stopRippingBinFile(): called" << endl;
    }
}

bool PyCeleX5::rippingBiFileFinished()
{
    if (!this->m_pBinFileObserver)
    {
        cout << "PyCeleX5.rippingBiFileFinished(): ripping bin file not start" << endl;
        return true;
    }
    bool result = this->m_pBinFileObserver->finished();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.rippingBiFileFinished(): " << (result ? "" : "not ") << "finished" << endl;
    }
    return result;
}

void PyCeleX5::enableImageFileOutput(const std::string &directoryPath)
{
    if (!this->m_pBinFileObserver)
    {
        cout << "PyCeleX5.enableImageFileOutput(): ripping bin file not start" << endl;
        return;
    }
    this->m_pBinFileObserver->enableImageFileOutput(directoryPath);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableImageFileOutput(): " << directoryPath << endl;
    }
}

void PyCeleX5::enableEventDataOutput(const std::string &filePath)
{
    if (!this->m_pBinFileObserver)
    {
        cout << "PyCeleX5.stopRippingBinFile(): ripping bin file not start" << endl;
        return;
    }
    this->m_pBinFileObserver->enableEventDataOutput(filePath);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableEventDataOutput(): " << filePath << endl;
    }
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

py::list PyCeleX5::getEventDataVector()
{
    vector<EventData> vecEvent;
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getEventDataVector(): called" << endl;
    }
    bool status = this->m_pCeleX5->getEventDataVector(vecEvent);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getEventDataVector(): " << (status ? "successful" : "failed") << endl;
        cout << "PyCeleX5.getEventDataVector(): event count " << vecEvent.size() << endl;
    }
    py::list result = py::cast(vecEvent);
    vecEvent.clear();
    // delete &vecEvent;
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

void PyCeleX5::reset()
{
    this->m_pCeleX5->reset();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.reset(): called" << endl;
    }
}

void PyCeleX5::startRecording(std::string &filePath)
{
    this->m_pCeleX5->startRecording(filePath);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.startRecording(): recording to " << filePath << endl;
    }
}

void PyCeleX5::stopRecording()
{
    this->m_pCeleX5->stopRecording();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.stopRecording(): called" << endl;
    }
}

bool PyCeleX5::openBinFile(std::string &filePath)
{
    bool result = this->m_pCeleX5->openBinFile(filePath);
    this->m_bFileOpend = result;
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.openBinFile(): " << filePath << endl;
        cout << "PyCeleX5.openBinFile(): open file " << (result ? "successful" : "failed") << endl;
    }
    return result;
}

bool PyCeleX5::readBinFileData()
{
    if (!this->m_bFileOpend)
    {
        cout << "PyCeleX5.readBinFileData(): file not opend" << endl;
        return true;
    }
    bool result = this->m_pCeleX5->readBinFileData();
    if (this->m_bDebug)
    {
        if (result)
            cout << "PyCeleX5.readBinFileData(): file has no more data" << endl;
        else
            cout << '.';
    }
    return result;
}

CeleX5::BinFileAttributes PyCeleX5::getBinFileAttributes()
{
    CeleX5::BinFileAttributes result = this->m_pCeleX5->getBinFileAttributes();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.getBinFileAttributes(): called" << endl;
    }
    return result;
}

void PyCeleX5::setRowDisabled(uint8_t rowMask)
{
    this->m_pCeleX5->setRowDisabled(rowMask);
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.setRowDisabled(): " << rowMask << endl;
    }
}

void PyCeleX5::disableFrameModule()
{
    this->m_pCeleX5->disableFrameModule();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableFrameModule(): called" << endl;
    }
}

void PyCeleX5::enableFrameModule()
{
    this->m_pCeleX5->enableFrameModule();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableFrameModule(): called" << endl;
    }
}

bool PyCeleX5::isFrameModuleEnabled()
{
    bool result = this->m_pCeleX5->isFrameModuleEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isFrameModuleEnabled(): " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::disableEventStreamModule()
{
    this->m_pCeleX5->disableEventStreamModule();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableEventStreamModule(): called" << endl;
    }
}

void PyCeleX5::enableEventStreamModule()
{
    this->m_pCeleX5->enableEventStreamModule();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableEventStreamModule(): called" << endl;
    }
}

bool PyCeleX5::isEventStreamEnabled()
{
    bool result = this->m_pCeleX5->isEventStreamEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isEventStreamEnabled(): " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::disableIMUModule()
{
    this->m_pCeleX5->disableIMUModule();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableIMUModule(): called" << endl;
    }
}

void PyCeleX5::enableIMUModule()
{
    this->m_pCeleX5->enableIMUModule();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableIMUModule(): called" << endl;
    }
}

bool PyCeleX5::isIMUModuleEnabled()
{
    bool result = this->m_pCeleX5->isEventStreamEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isEventStreamEnabled(): " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::disableEventDenoising()
{
    this->m_pCeleX5->disableEventDenoising();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableEventDenoising(): called" << endl;
    }
}

void PyCeleX5::enableEventDenoising()
{
    this->m_pCeleX5->enableEventDenoising();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableEventDenoising(): called" << endl;
    }
}

bool PyCeleX5::isEventDenoisingEnabled()
{
    bool result = this->m_pCeleX5->isEventDenoisingEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isEventDenoisingEnabled(): " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::disableFrameDenoising()
{
    this->m_pCeleX5->disableFrameDenoising();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableFrameDenoising(): called" << endl;
    }
}

void PyCeleX5::enableFrameDenoising()
{
    this->m_pCeleX5->enableFrameDenoising();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableFrameDenoising(): called" << endl;
    }
}

bool PyCeleX5::isFrameDenoisingEnabled()
{
    bool result = this->m_pCeleX5->isFrameDenoisingEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isFrameDenoisingEnabled(): " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::disableEventCountSlice()
{
    this->m_pCeleX5->disableEventCountSlice();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableEventCountSlice(): called" << endl;
    }
}

void PyCeleX5::enableEventCountSlice()
{
    this->m_pCeleX5->enableEventCountSlice();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableEventCountSlice(): called" << endl;
    }
}

bool PyCeleX5::isEventCountSliceEnabled()
{
    bool result = this->m_pCeleX5->isEventCountSliceEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isEventCountSliceEnabled(): " << (result ? "enabled" : "disabled") << endl;
    }
    return result;
}

void PyCeleX5::disableEventOpticalFlow()
{
    this->m_pCeleX5->disableEventOpticalFlow();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.disableEventOpticalFlow(): called" << endl;
    }
}

void PyCeleX5::enableEventOpticalFlow()
{
    this->m_pCeleX5->enableEventOpticalFlow();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.enableEventOpticalFlow(): called" << endl;
    }
}

bool PyCeleX5::isEventOpticalFlowEnabled()
{
    bool result = this->m_pCeleX5->isEventOpticalFlowEnabled();
    if (this->m_bDebug)
    {
        cout << "PyCeleX5.isEventOpticalFlowEnabled(): " << (result ? "enabled" : "disabled") << endl;
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
