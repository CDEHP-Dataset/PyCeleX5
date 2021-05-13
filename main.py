#!/usr/bin/env python3
# coding=utf-8

from build import PyCeleX5


def main():
    celex5 = PyCeleX5.PyCeleX5(debug=True)
    celex5.openSensor(PyCeleX5.DeviceType.CeleX5_MIPI)
    celex5.isSensorReady()
    celex5.getSensorFixedMode()
    celex5.getSensorLoopMode()
    celex5.isLoopModeEnabled()
    celex5.getEventFrameTime()
    celex5.getOpticalFlowTime()
    celex5.getThreshold()
    celex5.getBrightness()
    celex5.getContrast()
    celex5.getClockRate()
    celex5.getEventDataFormat()



main()
