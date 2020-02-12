﻿# 触摸式投影眼镜/TouchGlasses

此项目参加第35届宁夏青少年科技创新大赛。<br/>
项目以实体硬件为主，此仓库中主要记录开发相关的代码、记录、经验等。<br/>
涉及内容有：树莓派配置、OpenCV配置等。
<br/>
***
<br/>
[树莓派4B的初始化及安装OpenCV](https://github.com/zhangxinhui02/TouchGlasses/blob/master/%E6%A0%91%E8%8E%93%E6%B4%BE4B%E7%9A%84%E5%88%9D%E5%A7%8B%E5%8C%96%E5%8F%8A%E5%AE%89%E8%A3%85OpenCV.md)<br/>
## 触摸式投影眼镜设计的理想目标:<br/>
在眼镜上安装树莓派4B主板、小型投影仪、摄像头和超声波测距模块，配套的手部设备安装蓝牙、激光测距模块。<br>
树莓派内置图形化操作系统，且视频输出至投影仪。超声波模块检测前方障碍物的距离，小于一定值则打开投影仪，并通过距离值自动调焦。手部设备上激光测距模块检测手指与障碍物间的距离，小于一定值则表明被按下，通过蓝牙通知树莓派。树莓派通过摄像头锁定手部设备上的标记，确定坐标，在树莓派系统中相应的响应点击动作。
<br/>
## 目前的实际困难和当前目标：<br/>
视频接口不兼容，放弃用树莓派输出视频。无小型投影仪，使用略大的投影仪，使用数据线连接安卓手机，进行安卓投屏。点击操作由树莓派远程连接手机的ADB服务执行。
