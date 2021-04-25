#include <pybind11/pybind11.h>
#include "pycelex5.h"
#include "../include/celex5/celex5.h"

namespace py = pybind11;

PYBIND11_MODULE(PyCeleX5, m)
{
    m.doc() = "CelePixel CeleX5-MIPI C++ Wrapper for Python 3";

    py::class_<PyCeleX5>(m, "PyCeleX5")
        .def(py::init())
        .def("openSensor", &PyCeleX5::openSensor, "bool openSensor(DeviceType type)", py::arg("type") = CeleX5::DeviceType::CeleX5_MIPI)
        .def("isSensorReady", &PyCeleX5::isSensorReady, "bool isSensorReady()");

    py::class_<CeleX5> celex5(m, "CeleX5");

    py::enum_<CeleX5::DeviceType>(celex5, "DeviceType")
        .value("Unknown_Devive", CeleX5::DeviceType::Unknown_Devive)
        .value("CeleX5_MIPI", CeleX5::DeviceType::CeleX5_MIPI)
        .value("CeleX5_OpalKelly", CeleX5::DeviceType::CeleX5_OpalKelly)
        .export_values();
}
