#include <pybind11/pybind11.h>
#include "../include/celex5/celex5.h"
#include "pycelex5.h"

namespace py = pybind11;

PYBIND11_MODULE(PyCeleX5, m)
{

    m.doc() = "CelePixel CeleX5-MIPI C++ Wrapper for Python 3";
    m.attr("WIDTH") = PyCeleX5::sm_uiWidth;
    m.attr("HEIGHT") = PyCeleX5::sm_uiHeight;
    m.attr("RESOLUTION") = PyCeleX5::sm_uiResolution;

    // py::class_<CeleX5> celex5(m, "CeleX5");
    py::class_<CeleX5::BinFileAttributes>(m, "BinFileAttributes")
        .def(py::init<>())
        .def_readwrite("dataType", &CeleX5::BinFileAttributes::dataType)
        .def_readwrite("loopAMode", &CeleX5::BinFileAttributes::loopAMode)
        .def_readwrite("loopBMode", &CeleX5::BinFileAttributes::loopBMode)
        .def_readwrite("loopCMode", &CeleX5::BinFileAttributes::loopCMode)
        .def_readwrite("eventDataFormat", &CeleX5::BinFileAttributes::eventDataFormat)
        .def_readwrite("hour", &CeleX5::BinFileAttributes::hour)
        .def_readwrite("minute", &CeleX5::BinFileAttributes::minute)
        .def_readwrite("second", &CeleX5::BinFileAttributes::second)
        .def_readwrite("packageCount", &CeleX5::BinFileAttributes::packageCount);

    py::enum_<CeleX5::DeviceType>(m, "DeviceType")
        .value("Unknown_Devive", CeleX5::DeviceType::Unknown_Devive)
        .value("CeleX5_MIPI", CeleX5::DeviceType::CeleX5_MIPI)
        .value("CeleX5_OpalKelly", CeleX5::DeviceType::CeleX5_OpalKelly)
        .export_values();

    py::enum_<CeleX5::CeleX5Mode>(m, "CeleX5Mode")
        .value("Unknown_Mode", CeleX5::CeleX5Mode::Unknown_Mode)
        .value("Event_Off_Pixel_Timestamp_Mode", CeleX5::CeleX5Mode::Event_Off_Pixel_Timestamp_Mode)
        .value("Event_In_Pixel_Timestamp_Mode", CeleX5::CeleX5Mode::Event_In_Pixel_Timestamp_Mode)
        .value("Event_Intensity_Mode", CeleX5::CeleX5Mode::Event_Intensity_Mode)
        .value("Full_Picture_Mode", CeleX5::CeleX5Mode::Full_Picture_Mode)
        .value("Optical_Flow_Mode", CeleX5::CeleX5Mode::Optical_Flow_Mode)
        .value("Optical_Flow_FPN_Mode", CeleX5::CeleX5Mode::Optical_Flow_FPN_Mode)
        .value("Multi_Read_Optical_Flow_Mode", CeleX5::CeleX5Mode::Multi_Read_Optical_Flow_Mode)
        .export_values();

    py::enum_<CeleX5::EventPicType>(m, "EventPicType")
        .value("EventBinaryPic", CeleX5::EventPicType::EventBinaryPic)
        .value("EventAccumulatedPic", CeleX5::EventPicType::EventAccumulatedPic)
        .value("EventGrayPic", CeleX5::EventPicType::EventGrayPic)
        .value("EventCountPic", CeleX5::EventPicType::EventCountPic)
        .value("EventDenoisedBinaryPic", CeleX5::EventPicType::EventDenoisedBinaryPic)
        .value("EventSuperimposedPic", CeleX5::EventPicType::EventSuperimposedPic)
        .value("EventDenoisedCountPic", CeleX5::EventPicType::EventDenoisedCountPic)
        .value("EventCountDensityPic", CeleX5::EventPicType::EventCountDensityPic)
        .value("EventInPixelTimestampPic", CeleX5::EventPicType::EventInPixelTimestampPic)
        .export_values();

    py::enum_<CeleX5::OpticalFlowPicType>(m, "OpticalFlowPicType")
        .value("OpticalFlowPic", CeleX5::OpticalFlowPicType::OpticalFlowPic)
        .value("OpticalFlowSpeedPic", CeleX5::OpticalFlowPicType::OpticalFlowSpeedPic)
        .value("OpticalFlowDirectionPic", CeleX5::OpticalFlowPicType::OpticalFlowDirectionPic)
        .export_values();

    py::class_<PyCeleX5>(m, "PyCeleX5")
        .def(py::init<bool>(), py::arg("debug") = true)
        .def("setRotateType", &PyCeleX5::setRotateType, "void setRotateType(int type)", py::arg("type"))
        .def("getRotateType", &PyCeleX5::getRotateType, "int getRotateType()")
        .def("openSensor", &PyCeleX5::openSensor, "bool openSensor(DeviceType type)", py::arg("type") = CeleX5::DeviceType::CeleX5_MIPI)
        .def("isSensorReady", &PyCeleX5::isSensorReady, "bool isSensorReady()")
        .def("setFpnFile", &PyCeleX5::setFpnFile, "bool setFpnFile(string fpnFile)", py::arg("fpnFile"))
        .def("generateFpn", &PyCeleX5::generateFpn, "void generateFpn(string fpnFile)", py::arg("fpnFile"))
        .def("setSensorFixedMode", &PyCeleX5::setSensorFixedMode, "void setSensorFixedMode(CeleX5Mode mode)", py::arg("mode"))
        .def("getSensorFixedMode", &PyCeleX5::getSensorFixedMode, "CeleX5Mode getSensorFixedMode()")
        .def("getFullPicBuffer", &PyCeleX5::getFullPicBuffer, "uint8_t[] getFullPicBuffer()")
        .def("getEventPicBuffer", &PyCeleX5::getEventPicBuffer, "uint8_t[] getFullPicBuffer(EventPicType type)", py::arg("type") = CeleX5::EventPicType::EventBinaryPic)
        .def("getOpticalFlowPicBuffer", &PyCeleX5::getOpticalFlowPicBuffer, "uint8_t[] getOpticalFlowPicBuffer(OpticalFlowPicType type)", py::arg("type") = CeleX5::OpticalFlowPicType::OpticalFlowPic)
        .def("getFullPicFrameTime", &PyCeleX5::getFullPicFrameTime, "uint32_t getFullPicFrameTime()")
        .def("setEventFrameTime", &PyCeleX5::setEventFrameTime, "void setEventFrameTime(uint32_t microsecond)", py::arg("microsecond"))
        .def("getEventFrameTime", &PyCeleX5::getEventFrameTime, "uint32_t getEventFrameTime()")
        .def("setOpticalFlowFrameTime", &PyCeleX5::setOpticalFlowFrameTime, "void setOpticalFlowFrameTime(uint32_t millisecond)", py::arg("millisecond"))
        .def("getOpticalFlowFrameTime", &PyCeleX5::getOpticalFlowFrameTime, "uint32_t getOpticalFlowFrameTime()")
        .def("setSensorLoopMode", &PyCeleX5::setSensorLoopMode, "void setSensorLoopMode(CeleX5Mode mode, int loopNum)", py::arg("mode"), py::arg("loopNum"))
        .def("getSensorLoopMode", &PyCeleX5::getSensorLoopMode, "CeleX5Mode getSensorLoopMode(int loopNum)", py::arg("loopNum"))
        .def("setLoopModeEnabled", &PyCeleX5::setLoopModeEnabled, "void setLoopModeEnabled(bool enable)", py::arg("enable"))
        .def("isLoopModeEnabled", &PyCeleX5::isLoopModeEnabled, "bool isLoopModeEnabled()")
        .def("setEventDuration", &PyCeleX5::setEventDuration, "void setEventDuration(uint32_t value)", py::arg("value"))
        .def("setPictureNumber", &PyCeleX5::setPictureNumber, "void setPictureNumber(uint32_t num, CeleX5Mode mode)", py::arg("num"), py::arg("mode"))
        .def("setThreshold", &PyCeleX5::setThreshold, "void setThreshold(uint32_t value)", py::arg("value"))
        .def("getThreshold", &PyCeleX5::getThreshold, "uint32_t getThreshold()")
        .def("setBrightness", &PyCeleX5::setBrightness, "void setBrightness(uint32_t value)", py::arg("value"))
        .def("getBrightness", &PyCeleX5::getBrightness, "uint32_t getBrightness()")
        // .def("setContrast", &PyCeleX5::setContrast, "void setContrast(uint32_t value)", py::arg("value"))
        // .def("getContrast", &PyCeleX5::getContrast, "uint32_t getContrast()")
        .def("setClockRate", &PyCeleX5::setClockRate, "void setClockRate(uint32_t value)", py::arg("value"))
        .def("getClockRate", &PyCeleX5::getClockRate, "uint32_t getClockRate()")
        .def("setEventDataFormat", &PyCeleX5::setEventDataFormat, "void setEventDataFormat(int format)", py::arg("format"))
        .def("getEventDataFormat", &PyCeleX5::getEventDataFormat, "int getEventDataFormat()")
        .def("reset", &PyCeleX5::reset, "void reset()")
        .def("startRecording", &PyCeleX5::startRecording, "void startRecording(string filePath)", py::arg("filePath"))
        .def("stopRecording", &PyCeleX5::stopRecording, "void stopRecording()")
        .def("openBinFile", &PyCeleX5::openBinFile, "bool openBinFile(string filePath)", py::arg("filePath"))
        .def("readBinFileData", &PyCeleX5::readBinFileData, "bool readBinFileData()")
        .def("getBinFileAttributes", &PyCeleX5::getBinFileAttributes, "BinFileAttributes getBinFileAttributes()")
        .def("setRowDisabled", &PyCeleX5::setRowDisabled, "void setRowDisabled(uint8_t rowMask)", py::arg("rowMask"))
        .def("disableFrameModule", &PyCeleX5::disableFrameModule, "void disableFrameModule()")
        .def("enableFrameModule", &PyCeleX5::enableFrameModule, "void enableFrameModule()")
        .def("isFrameModuleEnabled", &PyCeleX5::isFrameModuleEnabled, "bool isFrameModuleEnabled()")
        .def("disableEventStreamModule", &PyCeleX5::disableEventStreamModule, "void disableEventStreamModule()")
        .def("enableEventStreamModule", &PyCeleX5::enableEventStreamModule, "void enableEventStreamModule()")
        .def("isEventStreamEnabled", &PyCeleX5::isEventStreamEnabled, "bool isEventStreamEnabled()")
        .def("disableIMUModule", &PyCeleX5::disableIMUModule, "void disableIMUModule()")
        .def("enableIMUModule", &PyCeleX5::enableIMUModule, "void enableIMUModule()")
        .def("isIMUModuleEnabled", &PyCeleX5::isIMUModuleEnabled, "bool isIMUModuleEnabled()")
        .def("disableEventDenoising", &PyCeleX5::disableEventDenoising, "void disableEventDenoising()")
        .def("enableEventDenoising", &PyCeleX5::enableEventDenoising, "void enableEventDenoising()")
        .def("isEventDenoisingEnabled", &PyCeleX5::isEventDenoisingEnabled, "bool isEventDenoisingEnabled()")
        .def("disableFrameDenoising", &PyCeleX5::disableFrameDenoising, "void disableFrameDenoising()")
        .def("enableFrameDenoising", &PyCeleX5::enableFrameDenoising, "void enableFrameDenoising()")
        .def("isFrameDenoisingEnabled", &PyCeleX5::isFrameDenoisingEnabled, "bool isFrameDenoisingEnabled()")
        .def("disableEventCountSlice", &PyCeleX5::disableEventCountSlice, "void disableEventCountSlice()")
        .def("enableEventCountSlice", &PyCeleX5::enableEventCountSlice, "void enableEventCountSlice()")
        .def("isEventCountSliceEnabled", &PyCeleX5::isEventCountSliceEnabled, "bool isEventCountSliceEnabled()")
        .def("disableEventOpticalFlow", &PyCeleX5::disableEventOpticalFlow, "void disableEventOpticalFlow()")
        .def("enableEventOpticalFlow", &PyCeleX5::enableEventOpticalFlow, "void enableEventOpticalFlow()")
        .def("isEventOpticalFlowEnabled", &PyCeleX5::isEventOpticalFlowEnabled, "bool isEventOpticalFlowEnabled()");
}
