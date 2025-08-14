# jaka_show
JAKA Robot Arm Driver and End-Effector Serial Communication

## Description
This package is designed for connecting and controlling the JAKA robotic arm, enabling it to move to specified positions. It also supports 485 communication through the end-effector interface.

## Requirements
- Ubuntu 20.04

## Setup Instructions

0. **Upgrade 485 Communication Functionality for the Controller Cabinet**

The stable version of the app does not currently support the 485 communication interface. You need to install a patch package.
   ```
   APP Main Interface > Settings > Upgrade > Upload Upgrade Package
   ```

1. **Create the Build Directory**
   ```shell
   mkdir build
   cd build
   ```


2. **Compile the Package Using CMake in the Build Directory**
   ```
   cmake ..
   make
   ```

3. **Configure 485 Communication on the JAKA App**
If 485 communication is required, set it up in the JAKA App as follows:
   ```
   APP Main Interface > Settings > Hardware and Communication > IO > Tool Side > Digital Output
   ```

Click on the digital output port name and configure the communication parameters such as baud rate, data bits, parity, etc., based on your pre-defined settings.

4. **Enable 12V/24V Power Supply for the End-Effector (if needed)**

If the end-effector requires a DC voltage for power, enable 12V/24V as follows:
   ```
   APP Main Interface > Settings > Hardware and Communication > IO > Tool Side > 12V/24V Power Supply
   ```
   Click on 12V/24V enable and select 12V or 24V based on your requirements.


5. **Run the Application**
   ```shell
   ./dlltest
   ```


## Additional Notes

The 485 communication functionality is currently in testing and has not been officially released in the stable version. There are a few known issues that have not yet been addressed:

- Communication is non-blocking. To ensure the transmitted signals are correctly executed, you must estimate the time required for the communication to be received and for the end effector (e.g., the robotic hand) to start moving. Make sure to implement an appropriate delay in the program, or the communication might fail.

- After each communication attempt, the app will report the following error: **"Receive TIO RS485 command feedback timeout"**. This issue has not been resolved by JAKA so far. However, the error does not have any practical impact on functionality. Simply press the "OK" button to dismiss the error.

The folder also contains a plastic cover for the connection flange between the robotic arm and the MiniCobot. This cover is used to hide the abstract connection point.

## Demo Videos

- [JAKA Robotic Arm + Human-Like Hand + RealSense Grasping Test](https://www.bilibili.com/video/BV1NtbazxEJS/)
- [JAKA MiniCobot Robotic Arm + Gripper Grasping Test](https://www.bilibili.com/video/BV1Rr4y1L72G/)




# jaka_show
节卡JAKA机械臂驱动及末端串口通信

## 功能描述
连接、启动节卡机械臂。控制机械臂在指定位置移动。使用机械手末端接口进行485通信

## 运行环境
- Ubuntu20.04

## 操作步骤

0. **为控制柜升级485通信功能**

稳定版的APP里尚没有开放485通信接口，需要安装补丁包。

```
APP主界面-设置-升级-上传升级包
```
1. **新建build文件夹**

```
mkdir build
cd build
```
2. **在build下使用cmake工具编译该功能包**
 
```
cmake ..
make
```
3. **如果需要进行485通信，需要在JAKA APP上设置：**
 

```
APP主界面-设置-硬件与通讯-IO-工具端-数字输出
```

点击数字输出的端口名字，按照预先设定的通信波特率、字节数、奇偶校验等设置485通信。
4. **如果需要末端提供一个直流电压供电，则需要设置末端12V/24V使能：**


```
APP主界面
```


5. **运行之**

```
./dlltest
```

## 补充说明

节卡485通信目前是测试功能，尚未在正式版本中发布，该功能存在一些问题，尚未被修复：

- 通信为非阻塞的。为了保证发出的通信信号可以被正确执行，需要预估从开始通信到末端机构（如机械手）接收到信息开始运动之间的时间，并在程序中等待相应的时间。否则，这货会通信失败.

- 每次通信之后APP端会报错：**接收TIO RS485指令反馈超时**。 到目前为止节卡从未解决这个问题。好在报错没有什么实质上的影响，请使用指尖按下确定按钮关闭报错。

文件夹里是机械手和minicob机械臂连接法兰的塑料外壳。由于连接处较为抽象，这里搞了个外壳做遮挡。

## 演示视频

[节卡机械臂+仿人手+realsense抓取测试](https://www.bilibili.com/video/BV1NtbazxEJS/)

[JAKA节卡minicobot机械臂+机械手抓取测试](https://www.bilibili.com/video/BV1Rr4y1L72G/)
