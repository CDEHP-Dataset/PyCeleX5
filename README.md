# PyCeleX5

CelePixel [CeleX5-MIPI](https://github.com/CelePixel/CeleX5-MIPI) C++ API Wrapper for Python 3  
[English](https://github.com/CDEHP-Dataset/PyCeleX5/blob/main/README.md) [简体中文](https://github.com/CDEHP-Dataset/PyCeleX5/blob/main/README_zh-Hans.md)

## Environment

* Compile or install precompiled `OpenCV 3.3.0`
* Install all dependencies used by `libCeleX.so`, use `ldd lib/libCeleX.so` or [Dependencies](https://github.com/lucasg/Dependencies) in Windows

## Compile

### Linux

```bash
git clone git@github.com:kuretru/PyCeleX5.git --recurse-submodules
mkdir build
cd build
cmake ..
make
```

### Windows

* Install `Visual Studio` with `Desktop development with C++`
* Install [CMake](https://cmake.org/download/)
* Install [OpenCV 3.3.0](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.3.0/opencv-3.3.0-vc14.exe)

```bash
git clone git@github.com:kuretru/PyCeleX5.git --recurse-submodules
mkdir build
cd build
cmake-gui.exe ..

# Add entry: OpenCV_DIR: some_path/opencv/build/x64/vc14/lib
# Configure -> Generate -> Open Project
# Use Visual Studio build
```

Make sure the following files exist in the same directory:

* `PyCeleX5.cp310-win_amd64.pyd`: Compiled in the previous step, located in `PyCeleX5\build\Release`
* `CeleX.dll`: from CelePixel [official SDK](https://github.com/CelePixel/CeleX5-MIPI/tree/master/API/lib/Windows/x64/release)，located in `API\lib\Windows\x64\release`
* `opencv_world330.dll`：from [OpenCV](https://github.com/opencv/opencv/releases/tag/3.3.0)，located in `opencv\build\x64\vc14\bin`
* `libusb-1.0.dll`：from [libusb](https://github.com/libusb/libusb)，located in `VS2015-x64\dll\libusb-1.0.dll`

If there is still problem like `ImportError: DLL load failed while importing PyCeleX5: 找不到指定的模块。`, please use [Dependencies](https://github.com/lucasg/Dependencies) to find missing dependencies.

## Test

```bash
sudo python3 demo.py
```

## Added interfaces other than the official API

| Method                                              |                  Feature                  |                              Description                              |
| :-------------------------------------------------- | :---------------------------------------: | :-------------------------------------------------------------------: |
| `void setRotateType(int type)`                      |              Set rotate type              | `type&1==1` --> Flip up and down, `type&2==2` --> Flip left and right |
| `int getRotateType()`                               |              Get rotate type              |                                                                       |
| `void startRippingBinFile()`                        |          Start ripping bin file           |                                                                       |
| `void stopRippingBinFile()`                         |           Stop ripping bin file           |                                                                       |
| `void enableImageFileOutput(string &directoryPath)` |       Generate image during ripping       |               directoryPath: Directory for saving image               |
| `void enableEventDataOutput(string &filePath)`      |     Generate csv file during ripping      |                  filePath:  Filename for saving data                  |
| `bool rippingBinFileFinished()`                     | Determine whether the ripping is complete |                                                                       |
