#include <pybind11/pybind11.h>
#include "pycelex5.h"
#include "../include/celex5/celex5.h"

namespace py = pybind11;

PYBIND11_MODULE(PyCeleX5, m)
{
    m.doc() = "CelePixel CeleX5-MIPI C++ Wrapper for Python 3";

    // py::class_<CeleX5> celex5(m, "CeleX5");

    py::enum_<CeleX5::DeviceType>(m, "DeviceType")
        .value("Unknown_Devive", CeleX5::DeviceType::Unknown_Devive)
        .value("CeleX5_MIPI", CeleX5::DeviceType::CeleX5_MIPI)
        .value("CeleX5_OpalKelly", CeleX5::DeviceType::CeleX5_OpalKelly)
        .export_values();

    py::enum_<CeleX5::CeleX5Mode>(m, "Celex5Mode")
        .value("Unknown_Mode", CeleX5::CeleX5Mode::Unknown_Mode)
        .value("Event_Off_Pixel_Timestamp_Mode", CeleX5::CeleX5Mode::Event_Off_Pixel_Timestamp_Mode)
        .value("Event_In_Pixel_Timestamp_Mode", CeleX5::CeleX5Mode::Event_In_Pixel_Timestamp_Mode)
        .value("Event_Intensity_Mode", CeleX5::CeleX5Mode::Event_Intensity_Mode)
        .value("Full_Picture_Mode", CeleX5::CeleX5Mode::Full_Picture_Mode)
        .value("Optical_Flow_Mode", CeleX5::CeleX5Mode::Optical_Flow_Mode)
        .value("Optical_Flow_FPN_Mode", CeleX5::CeleX5Mode::Optical_Flow_FPN_Mode)
        .value("Multi_Read_Optical_Flow_Mode", CeleX5::CeleX5Mode::Multi_Read_Optical_Flow_Mode)
        .export_values();

    py::class_<PyCeleX5>(m, "PyCeleX5")
        .def(py::init<bool>(), py::arg("debug") = true)
        .def("openSensor", &PyCeleX5::openSensor, "bool openSensor(DeviceType type)", py::arg("type") = CeleX5::DeviceType::CeleX5_MIPI)
        .def("isSensorReady", &PyCeleX5::isSensorReady, "bool isSensorReady()")
        .def("setFpnFile", &PyCeleX5::setFpnFile, "bool setFpnFile(string fpnFile)", py::arg("fpnFile"))
        .def("generateFpn", &PyCeleX5::generateFpn, "void generateFpn(string fpnFile)", py::arg("fpnFile"))
        .def("setSensorFixedMode", &PyCeleX5::setSensorFixedMode, "void setSensorFixedMode(CeleX5Mode mode)", py::arg("mode"))
        .def("getSensorFixedMode", &PyCeleX5::getSensorFixedMode, "CeleX5Mode getSensorFixedMode");
}
