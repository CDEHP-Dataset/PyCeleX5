#!/usr/bin/env python3
# coding=utf-8

from build import PyCeleX5


def main():
    celex5 = PyCeleX5.PyCeleX5(debug=True)
    celex5.openSensor(PyCeleX5.DeviceType.CeleX5_MIPI)
    celex5.isSensorReady()
    celex5.getSensorFixedMode()
    celex5.getSensorLoopMode(1)
    celex5.getSensorLoopMode(2)
    celex5.getSensorLoopMode(3)
    celex5.isLoopModeEnabled()
    celex5.getEventFrameTime()
    celex5.getOpticalFlowFrameTime()
    celex5.getThreshold()
    celex5.getBrightness()
    # celex5.getContrast()
    celex5.getClockRate()
    celex5.getEventDataFormat()
    celex5.isFrameModuleEnabled()
    celex5.isEventStreamEnabled()
    celex5.isIMUModuleEnabled()
    celex5.isEventDenoisingEnabled()
    celex5.isFrameDenoisingEnabled()
    celex5.isEventCountDensityEnabled()
    celex5.isEventOpticalFlowEnabled()



main()
