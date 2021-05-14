# PyCeleX5

## 环境

* 编译并安装好OpenCV 3.3
* 确保`ldd lib/libCeleX.so`中的所有库可以正确找到

## 编译

```bash
git clone git@github.com:kuretru/PyCeleX5.git --recurse-submodules
mkdir build
cd build
cmake ..
make
```

## 测试

```bash
sudo python3 main.py
```

## 文档

| 方法                           |         功能         |                     说明                     |
| :----------------------------- | :------------------: | :------------------------------------------: |
| `void setRotateType(int type)` |   设置图像翻转类型   | 若type&1==1则上下翻转，若type&2==2则左右翻转 |
| `int getRotateType()`          | 获取当前图像翻转类型 |                                              |
