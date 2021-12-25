#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "../include/celex5/celex5.h"
#include "../include/celextypes.h"
#include "binfileobserver.h"

namespace py = pybind11;

class PyCeleX5
{
public:
    static uint32_t sm_uiWidth;
    static uint32_t sm_uiHeight;
    static uint32_t sm_uiResolution;

    PyCeleX5(bool debug);
    ~PyCeleX5();

    // &0x1->上下，&0x2->左右
    void setRotateType(int type);
    int getRotateType();

    // 开始翻录Bin文件
    void startRippingBinFile();
    // 结束翻录Bin文件
    void stopRippingBinFile();
    // 是否完成翻录文件
    bool rippingBinFileFinished();
    // 启用翻录时保存图片文件(存放图片的目录)
    void enableImageFileOutput(const std::string &directoryPath);
    // 启用翻录时保存RAW事件数据(存放数据的文件)
    void enableEventDataOutput(const std::string &filePath);

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
    py::list getEventDataVector();

    // 2.3.13 getOpticalFlowPicBuffer
    py::array_t<uint8_t> getOpticalFlowPicBuffer(CeleX5::OpticalFlowPicType type);
    // 2.3.14 getOpticalFlowPicMat

    // 2.3.15 getFullPicFrameTime
    uint32_t getFullPicFrameTime();

    // 2.3.16 setEventFrameTime
    void setEventFrameTime(uint32_t microsecond);
    // 2.3.17 getEventFrameTime
    uint32_t getEventFrameTime();

    // 2.3.18 setOpticalFlowFrameTime
    void setOpticalFlowFrameTime(uint32_t millisecond);
    // 2.3.19 getOpticalFlowFrameTime
    uint32_t getOpticalFlowFrameTime();

    // 2.3.20 setSensorLoopMode
    void setSensorLoopMode(CeleX5::CeleX5Mode mode, int loopNum);
    // 2.3.21 getSensorLoopMode
    CeleX5::CeleX5Mode getSensorLoopMode(int loopNum);

    // 2.3.22 setLoopModeEnabled
    void setLoopModeEnabled(bool enable);
    // 2.3.23 isLoopModeEnabled
    bool isLoopModeEnabled();

    // 2.3.24 setEventDuration
    void setEventDuration(uint32_t value);
    // 2.3.25 setPictureNumber
    void setPictureNumber(uint32_t num, CeleX5::CeleX5Mode mode);

    // 2.3.26 setThreshold
    void setThreshold(uint32_t value);
    // 2.3.27 getThreshold
    uint32_t getThreshold();

    // 2.3.28 setBrightness
    void setBrightness(uint32_t value);
    // 2.3.29 getBrightness
    uint32_t getBrightness();

    // API未实现
    // 2.3.30 setContrast
    // void setContrast(uint32_t value);
    // 2.3.31 getContrast
    // uint32_t getContrast();

    // 2.3.32 setClockRate
    void setClockRate(uint32_t value);
    // 2.3.33 getClockRate
    uint32_t getClockRate();

    // 2.3.34 setEventDataFormat
    void setEventDataFormat(int format);
    // 2.3.35 getEventDataFormat
    int getEventDataFormat();

    // 2.3.36 reset
    void reset();

    // 2.3.37 startRecording
    void startRecording(std::string &filePath);
    // 2.3.38 stopRecording
    void stopRecording();

    // 2.3.39 open Bin File
    bool openBinFile(std::string &filePath);
    // 2.3.40 read BinFile Data
    bool readBinFileData();
    // 2.3.41 get BinFile Attributes
    CeleX5::BinFileAttributes getBinFileAttributes();

    // 2.3.42 get IMUData

    // 2.3.43 setRowDisabled
    void setRowDisabled(uint8_t rowMask);

    // 2.3.44 disableFrameModule
    void disableFrameModule();
    // 2.3.45 enableFrameModule
    void enableFrameModule();
    // 2.3.46 isFrameModuleEnabled
    bool isFrameModuleEnabled();

    // 2.3.47 disableEventStreamModule
    void disableEventStreamModule();
    // 2.3.48 enableEventStreamModule
    void enableEventStreamModule();
    // 2.3.49 is EventStream Enabled
    bool isEventStreamEnabled();

    // 2.3.50 disableIMUModule
    void disableIMUModule();
    // 2.3.51 enableIMUModule
    void enableIMUModule();
    // 2.3.52 isIMUModuleEnabled
    bool isIMUModuleEnabled();

    // 2.3.53 disableEventDenoising
    void disableEventDenoising();
    // 2.3.54 enableEventDenoising
    void enableEventDenoising();
    // 2.3.55 isEventDenoisingEnabled
    bool isEventDenoisingEnabled();

    // 2.3.56 disableFrameDenoising
    void disableFrameDenoising();
    // 2.3.57 enableFrameDenoising
    void enableFrameDenoising();
    // 2.3.58 isFrameDenoisingEnabled
    bool isFrameDenoisingEnabled();

    // 2.3.59 disableEventCount Density
    void disableEventCountSlice();
    // 2.3.60 enableEventCount Density
    void enableEventCountSlice();
    // 2.3.61 isEventCount Density Enabled
    bool isEventCountSliceEnabled();

    // 2.3.62 disableEventOpticalFlow
    void disableEventOpticalFlow();
    // 2.3.63 enableEventOpticalFlow
    void enableEventOpticalFlow();
    // 2.3.64 isE ventOpticalFlowEnabled
    bool isEventOpticalFlowEnabled();

private:
    CeleX5 *m_pCeleX5;
    BinFileObserver *m_pBinFileObserver;
    bool m_bDebug;
    bool m_bFileOpend;

    std::string printDeviceType(CeleX5::DeviceType type);
    std::string printCeleX5Mode(CeleX5::CeleX5Mode mode);
    std::string printEventPicType(CeleX5::EventPicType type);
    std::string printOpticalFlowPicType(CeleX5::OpticalFlowPicType type);
};
