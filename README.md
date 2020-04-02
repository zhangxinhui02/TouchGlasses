# 触摸式投影眼镜/TouchGlasses

此项目参加第35届宁夏青少年科技创新大赛。<br/>
项目以实体硬件为主，此仓库中主要记录开发相关的代码、记录、经验等。<br/>
涉及内容有：树莓派配置、OpenCV配置、树莓派的程序编写等。
<br/>
***
<br/>

## 配置经验
[树莓派4B的初始化及安装OpenCV的过程](https://github.com/zhangxinhui02/TouchGlasses/blob/master/%E6%A0%91%E8%8E%93%E6%B4%BE4B%E7%9A%84%E5%88%9D%E5%A7%8B%E5%8C%96%E5%8F%8A%E5%AE%89%E8%A3%85OpenCV.md)<br/>

## 程序源码
注：以下程序有一部分借鉴了其他人的程序。
### 树莓派程序
[camera.py](https://github.com/zhangxinhui02/TouchGlasses/blob/master/camera.py)<br/>
[setup.py](https://github.com/zhangxinhui02/TouchGlasses/blob/master/setup.py)<br/>
[keep_connection.sh](https://github.com/zhangxinhui02/TouchGlasses/blob/master/keep_connection.sh)<br/>
以上程序中需要以root用户启动的程序为camera.py和setup.py，keep_connection.sh无需手动启动。
### Arduino程序
[Cilent_sketch.ino](https://github.com/zhangxinhui02/TouchGlasses/blob/master/Cilent_sketch.ino)
