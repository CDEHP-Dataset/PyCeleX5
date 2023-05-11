# PyCeleX5

使用Python调用CelePixel [CeleX5-MIPI](https://github.com/CelePixel/CeleX5-MIPI)的官方 C++ API  
[English](https://github.com/CDEHP-Dataset/PyCeleX5/blob/main/README.md) [简体中文](https://github.com/CDEHP-Dataset/PyCeleX5/blob/main/README_zh-Hans.md)

## 环境

* 编译或并安装预编译的`OpenCV 3.3.0`
* 确保`libCeleX.so`所依赖的库都已被正确安装，使用`ldd lib/libCeleX.so`查看，Windows系统下使用[Dependencies](https://github.com/lucasg/Dependencies)查看

## 编译

### Linux

```bash
git clone git@github.com:kuretru/PyCeleX5.git --recurse-submodules
mkdir build
cd build
cmake ..
make
```

### Windows

* 安装`Visual Studio`且包含`使用C++的桌面开发`
* 安装[CMake](https://cmake.org/download/)
* 安装[OpenCV 3.3.0](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.3.0/opencv-3.3.0-vc14.exe)

```bash
git clone git@github.com:kuretru/PyCeleX5.git --recurse-submodules
mkdir build
cd build
cmake-gui.exe ..

# Add entry: OpenCV_DIR: some_path/opencv/build/x64/vc14/lib
# Configure -> Generate -> Open Project
# Use Visual Studio build
```

使用时，需要确保有以下文件，并处于相同目录中：

* `PyCeleX5.cp310-win_amd64.pyd`：上一步编译出来的，位于`PyCeleX5\build\Release`
* `CeleX.dll`：来自[官方SDK](https://github.com/CelePixel/CeleX5-MIPI/tree/master/API/lib/Windows/x64/release)，位于`API\lib\Windows\x64\release`
* `opencv_world330.dll`：来自[OpenCV](https://github.com/opencv/opencv/releases/tag/3.3.0)，位于`opencv\build\x64\vc14\bin`
* `libusb-1.0.dll`：来自[libusb](https://github.com/libusb/libusb)，位于`VS2015-x64\dll\libusb-1.0.dll`

如果仍旧存在`ImportError: DLL load failed while importing PyCeleX5: 找不到指定的模块。`问题，请自行使用[Dependencies](https://github.com/lucasg/Dependencies)软件查找缺少的依赖。

## 测试

```bash
sudo python3 demo.py
```

## 文档

| 方法                                                |         功能         |                     说明                     |
| :-------------------------------------------------- | :------------------: | :------------------------------------------: |
| `void setRotateType(int type)`                      |   设置图像翻转类型   | 若type&1==1则上下翻转，若type&2==2则左右翻转 |
| `int getRotateType()`                               | 获取当前图像翻转类型 |                                              |
| `void startRippingBinFile()`                        |   开始翻录Bin文件    |                                              |
| `void stopRippingBinFile()`                         |   结束翻录Bin文件    |                                              |
| `void enableImageFileOutput(string &directoryPath)` |    翻录时生成图片    |         应传入一个用于存放图片的目录         |
| `void enableEventDataOutput(string &filePath)`      |  翻录时生成csv文件   |       应传入一个用于保存事件数据的文件       |
| `bool rippingBinFileFinished()`                     |   判断翻录是否完成   |                                              |
