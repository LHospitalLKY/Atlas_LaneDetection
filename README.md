# LaneDetection
cpp version

## 算法原理
本车道线识别算法基于UdaCity自动驾驶课程中的车道线识别算法。采用传统CV中的阈值过滤来识别车道线。

本算法输入为一张图像，可以得到左右车道在图像中的二次拟合曲线、当前车辆位置与车道中央的偏移。偏移量可提供给PID控制模块，进行横向控制，保持车在车道中。

算法的步骤为：
1. 图像预处理
2. 车道线拟合与偏移计算

### 图像预处理
图像预处理步骤代码在```ImageHandle.h/ImageHandle.cc```中，构建了一个类```ImageHandle```，主要功能为进行阈值过滤和透视变换。

* 阈值过滤与二值化： 本算法中使用hls阈值过滤，hls格式的image中选择一个channel，当该channel上的像素值大于某个阈值时，就将其设置为255,小于该阈值时设置为0
* 透视变换：透视变换通过透视变换矩阵，将图像中“相交”的车道投影为平行线

图像预处理类```ImageHandle```，可无参数构造，也可传入一个图像处理参数结构体来进行初始化，无参数构造时，使用默认的参数，这个参数可能并不适合当前的环境，建议传入图像处理参数结构体来进行初始化。

该类的使用请参见main.cpp。

### 车道线拟合与偏移计算
车道线拟合与偏移计算接收图像预处理得到的二值化图像，利用滑动窗口来寻找车道区域。找出车道区域之后，利用二次拟合来计算出车道的拟合曲线，并根据左右拟合到的曲线来计算出车辆距离车道中心的偏移。这部分的代码在```LaneFitting.h/cc```与```CurveFit.h/CurveFit.cc```中。

这部分分为两个类：```LaneFitting```与```QuadFitting```，前者将上述提到的过程封装起来，后者提供一个二次曲线拟合的工具。

LaneFitting类采用无参数构造，其中```findLane(cv::Mat image_pres)函数```接收```ImageHandle```处理之后的图像，利用滑动窗口法找出车道线区域。```laneFitting()```函数接受```ImageHandle```处理之后的图像，调用```findLane()```函数，在找到车道线区域之后，拟合出左右车道线的二次曲线，计算出距离中心的偏移。

// TODO: ```LaneFitting```类中还有两个私有函数，需要使用这两个私有函数来将```fineLane```函数来进一步结构化，使得函数代码不那么冗长

```QuadFitting```类采用手写VIO课程中提供的非线性优化器，用于求解最小二乘法。该求解器的原理来源于谷歌的g2o框架。实际上，这个求解器是g2o的简化版本。```QuadFitting```类位于```CurveFit.h/cc```文件中。该文件构建了二次曲线拟合的图优化顶点、图优化超边，在```QuadFitting```类中，利用顶点和超边，构建和求解二次曲线拟合问题。

```QuadFitting```类的构建函数参数为自变量vector和因变量vector的引用，函数```solve()```接收二次函数系数组成的vector的引用，拟合出的结果填入该vector中。

非线性优化框架的使用可以参见```3rdParty/CurveFitting_LM_TEST.cc```文件中的内容。

// TODO: 在适当的时候可以重构求解器，或将其换成ceres、g2o，ceres貌似比g2o要快。

## 文件结构
* 3rdParty中为非线性优化求解器的源码
* include中为头文件
* src中为include文件夹中头文件对应的```.cc```文件，此外，还有```QuadFitting```类的测试文件``CurveFit_TEST.cc`，以及整个车道线识别算法的测试文件```main.cpp```。

## 编译与运行
本项目所需的操作系统为Linux系列，可在PC、Atlas-200DK、RasberryPi、Nvidia Jetson系列嵌入式开发板上编译运行。

### 依赖环境
本部分编译运行所依赖的环境包括以下几个工具与第三方库：
1. cmake工具连，用于C++工程项目的构建，版本需要2.8以上
2. OpenCV，用于计算机视觉的处理，版本建议3.4.8
3. Eigen，矩阵计算库

上述依赖环境请自行安装。

### 编译运行
#### 更改图片路径
在编译之前，要更改main.cc中的图片路径：
```shell
# 在project dir下
vim src/main.cpp
```
将代码第12行中```imread()```读取图片的路径改为自己环境下的图片路径：
```cpp
superman = cv::imread("/home/lho/MyProgramm/Dev/LaneDetection/TEST_Date/lane4.jpg");
```

#### 编译
执行如下命令，编译程序：

1. 构建cmake工程
```shell
mkdir build
cd build
cmake..
```

2. 编译
上一步成功之后，执行：
```shell
make
```
若显示编译成功，则编译成功。

3. 运行
编译成功之后，执行以下指令来运行车道线识别算法的测试：
```shell
./LaneDetection_TEST
```


