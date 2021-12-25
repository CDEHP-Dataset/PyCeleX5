#!/usr/bin/env python3
# coding=utf-8

from build import PyCeleX5
import cv2
import time

BIN_FILE = "/home/event/Desktop/A0001_P0001_S00.bin"

celex5 = PyCeleX5.PyCeleX5(debug=True)


def showImg():
    while True:
        rgb = celex5.getFullPicBuffer()
        cv2.imshow("rgb", rgb)
        event = celex5.getEventPicBuffer()
        cv2.imshow("event", event)
        cv2.waitKey(1)


def readBinFile():
    # 必须先打开翻录模式
    celex5.startRippingBinFile()
    # 设置图片保存路径
    celex5.enableImageFileOutput("/tmp/test/images/")
    # 设置Event数据保存路径
    celex5.enableEventDataOutput("/tmp/test/event.csv")
    # 然后打开BinFile
    celex5.openBinFile(BIN_FILE)
    # 循环读取到结束
    while not celex5.readBinFileData() or not celex5.rippingBinFileFinished():
        pass
    time.sleep(1)
    # 用好后要结束
    celex5.stopRippingBinFile()


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

    celex5.setEventFrameTime(8333)
    celex5.setRotateType(2)


main()
# showImg()
readBinFile()
