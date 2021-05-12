#include "../include/celex5/celex5.h"
#include <iostream>
#include <string>

namespace py = pybind11;

class PyCeleX5
{
public:
    static uint32_t sm_uiWidth;
    static uint32_t sm_uiHeight;
    static uint32_t sm_uiResolution;

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

    // 2.3.8 getFullPicBuffer
    py::array_t<uint8_t> getFullPicBuffer();
    // 2.3.9 getFullPicMat

    // 2.3.10 getEventPicBuffer
    py::array_t<uint8_t> getEventPicBuffer(CeleX5::EventPicType type);
    // 2.3.11 getEventPicMat

    // 2.3.12 getEventDataVector

    // 2.3.13 getOpticalFlowPicBuffer
    py::array_t<uint8_t> getOpticalFlowPicBuffer(CeleX5::OpticalFlowPicType type);
    // 2.3.14 getOpticalFlowPicMat

private:
    CeleX5 *m_pCeleX5;
    bool m_bDebug;

    std::string printDeviceType(CeleX5::DeviceType type);
    std::string printCeleX5Mode(CeleX5::CeleX5Mode mode);
    std::string printEventPicType(CeleX5::EventPicType type);
    std::string printOpticalFlowPicType(CeleX5::OpticalFlowPicType type);
};
