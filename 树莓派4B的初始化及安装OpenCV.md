树莓派买来后折腾了好久才摸索熟悉Linux，为了完成这个项目又安装OpenCV，慢慢的都是坑。这里把树莓派4B初始化及安装OpenCV的经验记录下方便查阅。<br/>
参考了以下页面：<br/>
- [树莓派开机教程](https://github.com/TommyZihao/Zihao-Blog/blob/master/01%E6%A0%91%E8%8E%93%E6%B4%BE%E5%BC%80%E6%9C%BA%E6%95%99%E7%A8%8B.md)
- [一劳永逸配置树莓派](https://github.com/TommyZihao/Zihao-Blog/blob/master/02%E4%B8%80%E5%8A%B3%E6%B0%B8%E9%80%B8%E9%85%8D%E7%BD%AE%E6%A0%91%E8%8E%93%E6%B4%BE.md)
- [子豪兄教你在树莓派上安装OpenCV](https://www.jianshu.com/p/56929416b4a1)
- [未满足的依赖关系……](https://www.jianshu.com/p/946964725967)
- [树莓派编译安装OpenCV](https://www.jianshu.com/p/fcc319d1ddd4)
- [树莓派4B 安装opencv完整教程基于python3（各种错误解决）](https://blog.csdn.net/qq_43762614/article/details/102760414)
## 树莓派初始化
首先使用Win32 Disk Imager烧录系统img镜像到内存卡（推荐16GB，class 10）。<br/><br/>
*注：我使用的是淘宝亚博店买的树莓派4B，因为同时买了个3.5英寸屏幕想以后用到，所以刷入了亚博店家提供的系统镜像（包含屏幕驱动）。因为有屏幕所以方便查看和点击，如果没有屏幕进行初始化点击上面第一个网址查看。*<br/><br/>
插入内存卡，通入5V 3A电源。<br/><br/>
*注：经测试5V 1A，5V 2.1A都可以开机，但是时常会出现供电不足且不稳定。树莓派发热大，建议配置散热片。<br/><br/>*
开机后先给pip换源：<br/>
```
sudo mkdir ~/.pip
ls .pip
sudo nano pip.conf
```
修改为：
```
[global]
timeout = 10
index-url =  http://mirrors.aliyun.com/pypi/simple/
extra-index-url= http://pypi.douban.com/simple/
[install]
trusted-host=
    mirrors.aliyun.com
    pypi.douban.com
```
<br/><br/>
然后换掉安装源（详见第4个链接）：<br/>
`sudo nano /etc/apt/sources.list`
<br/>
修改为：<br/>
`deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ buster main contrib non-free rpi`
<br/>
<br/>
`sudo nano /etc/apt/sources.list.d/raspi.list`
<br/>
修改为：<br/>
`deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ buster main`
<br/>
<br/>
进行更新：
```
sudo apt-get update
sudo apt-get upgrade
```
<br/><br/>
树莓派内部设置：
`sudo raspi-config`<br/>
1 Change User Password修改密码<br/>
4 Localisation Options选择位置<br/>
5 Interfacing Options打开Camera、SSH、VNC、Serial、Remote GPIO<br/>
7 Advanced Options进入选择第一项扩展空间，然后重启<br/>
具体操作见第二个网页。<br/><br/>
安装中文字体<br/>
`sudo apt-get install fonts-wqy-zenhei`<br/>
安装中文输入法<br/>
`sudo apt-get install fcitx fcitx-googlepinyin fcitx-module-cloudpinyin fcitx-sunpinyin`<br/>
