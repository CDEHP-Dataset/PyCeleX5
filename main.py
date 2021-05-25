#!/usr/bin/env python3
# coding=utf-8

from build import PyCeleX5
import cv2
import time

celex5 = PyCeleX5.PyCeleX5(debug=True)


def showImg():
    while True:
        rgb = celex5.getFullPicBuffer()
        cv2.imshow("rgb", rgb)
        event = celex5.getEventPicBuffer()
        cv2.imshow("event", event)
        cv2.waitKey(1)


def readBinFile():
    file = input()
    observer = celex5.getBinFileObserver()
    celex5.openBinFile(file)
    while not celex5.readBinFileData():
        time.sleep(0.01)
    del observer


def main():
    print("{} * {} = {}".format(PyCeleX5.WIDTH, PyCeleX5.HEIGHT, PyCeleX5.RESOLUTION))
    celex5.openSensor(PyCeleX5.DeviceType.CeleX5_MIPI)
    celex5.isSensorReady()
    celex5.getRotateType()
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
    celex5.isEventCountSliceEnabled()
    celex5.isEventOpticalFlowEnabled()

    celex5.setRotateType(2)


main()
showImg()
