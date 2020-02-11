树莓派买来后折腾了好久才摸索熟悉Linux，为了完成这个项目又安装OpenCV，满满的都是坑，参考了子豪兄（特别感谢他的教程）和其他人的教程，但是都各有问题。这里把我摸索出的树莓派4B初始化及安装OpenCV的经验记录下方便查阅。<br/>
注：为了防止出现各种莫名其妙的问题，可以优先选择安装基于Python3的OpenCV，然后再初始配置树莓派及安装Python2的OpenCV。<br/>
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

然后换掉安装源（详见第4个链接）：
<br/>

```
sudo nano /etc/apt/sources.list
```

修改为：

```
deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ buster main contrib non-free rpi
```

<br/>
<br/>

```
sudo nano /etc/apt/sources.list.d/raspi.list
```

修改为：


```
deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ buster main
```

<br/>

进行更新：

```
sudo apt-get update
sudo apt-get upgrade
```

<br/>

树莓派内部设置：

```
sudo raspi-config
```

1 Change User Password修改密码<br/>
4 Localisation Options选择位置<br/>
5 Interfacing Options打开Camera、SSH、VNC、Serial、Remote GPIO<br/>
7 Advanced Options进入选择第一项扩展文件系统，然后重启（不进行这一步安装OpenCV会卡死）<br/>
具体操作见第二个网页。<br/><br/>
安装中文字体<br/>
```
sudo apt-get install fonts-wqy-zenhei
```

<br/>

安装中文输入法<br/>

```
sudo apt-get install fcitx fcitx-googlepinyin fcitx-module-cloudpinyin fcitx-sunpinyin
```

<br/>

重启后如果还是不显示中文，在GUI的系统设置里修改文字编码（随便修改成另一个），然后再改回UTF-8，重启即可。
<br/><br/>

树莓派的3.5英寸屏幕较小，屏幕无法完整显示所有内容，需要调整任务栏最小，字体7号。
## 树莓派4B安装OpenCV
注：为了防止出现各种莫名其妙的问题，可以优先选择安装基于Python3的OpenCV，然后再初始配置树莓派及安装Python2的OpenCV。
基于Python的OpenCV有两种，即Python2和Python3相对应的不同OpenCV。<br/><br/>
### 配置摄像头
如果需要使用摄像头则需要这一步。可以在安装后再配置。<br/>
首先需要在树莓派设置里打开摄像头，参考上面的树莓派初始化。<br/>
输入以下命令：<br/>

```
sudo nano /etc/modules
```


在末尾添加这样一行：<br/>

```
bcm2835-v4l2
```

保存退出即可。<br/>
输入下面命令验证：<br/>

```
vcgencmd get_camera
```

<br/>

如果得到下面的输出则配置成功：<br/>

```
supported=1 detected=1
```

<br/>

亦可以输入下面命令调用摄像头拍一张照片，命名为image.jpg，存储在/pi/home路径，也就是桌面左上角资源管理器一打开显示的那个路径。如果能看到摄像头上红灯亮，目录里面有照片，则进一步说明摄像头配置正确。<br/>

```
raspistill -o image.jpg
```

### 基于Python2的OpenCV
耗时较长（半小时左右）建议在树莓派的命令行中操作而不是使用SSH，防止断线而不能得知完成情况。<br/>
执行下面的命令即可安装：<br/>
```
sudo apt-get install libopencv-dev
sudo apt-get install python-opencv
```
<br/><br/>
安装好后在命令行输入python或python2，然后输入下面命令验证是否安装成功：
<br/><br/>

```
#导入库，无提示即安装成功
import cv2
#查看版本号，显示版本号即安装成功
cv2.__version__
```

<br/>

### 基于Python3的OpenCV
**注：建议先安装此部分再进行其他操作。**<br/><br/>
安装前先保证已经扩展了文件系统，见树莓派初始化。<br/><br/>
输入下面的命令修改数据交互区防止卡死：<br/>
```
sudo nano /etc/dphys-swapfile
```
<br/>

将`CONF_SWAPSIZE`修改为：<br/>
```
CONF_SWAPSIZE=1024
```
<br/>

输入下面的命令重启服务：<br/>
```
sudo /etc/init.d/dphys-swapfile stop && sudo /etc/init.d/dphys-swapfile start
```
<br/><br/>

**以下命令耗时较长建议在树莓派的命令行操作而不是SSH，需要在网络状态好的情况下操作，这也是整个过程最麻烦的部分。**<br/>
安装依赖库，如果有依赖问题则根据相应操作解决：<br/>
```
sudo pip3 install numpy
sudo apt-get install build-essential git cmake pkg-config -y
sudo apt-get install libjpeg8-dev -y
sudo apt-get install libtiff5-dev -y
sudo apt-get install libjasper-dev -y
sudo apt-get install libpng12-dev -y
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev -y
sudo apt-get install libgtk2.0-dev -y
sudo apt-get install libatlas-base-dev gfortran -y
```
下载OpenCV3.4.0安装包：<br/>
```
cd /home/pi/Downloads

wget https://github.com/Itseez/opencv/archive/3.4.0.zip

wget https://github.com/Itseez/opencv_contrib/archive/3.4.0.zip
```
*注：如果网络环境太差请手动下载这两个安装包，放到/home/pi/Downloads路径下。第一个压缩包86.8MB，第二个压缩包54.5MB。下载之后，把第一个压缩包重新命名为opencv-3.4.0.zip，把第二个压缩包重新命名为opencv_contrib-3.4.0.zip。*<br/><br/>
解压压缩包：
```
cd /home/pi/Downloads
unzip opencv-3.4.0.zip
unzip opencv_contrib-3.4.0.zip
```
<br/>

设置编译参数：

```
cd /home/pi/Downloads/opencv-3.4.0
mkdir build
cd build
```

然后复制下面的命令（包括最后的两个点），右键粘贴到命令行，然后回车：

```
cmake -DCMAKE_BUILD_TYPE=RELEASE \
-DCMAKE_INSTALL_PREFIX=/usr/local \
-DINSTALL_C_EXAMPLES=ON \
-DINSTALL_PYTHON_EXAMPLES=ON \
-DOPENCV_EXTRA_MODULES_PATH=/home/pi/Downloads/opencv_contrib-3.4.0/modules \
-DBUILD_EXAMPLES=ON \
-DWITH_LIBV4L=ON \
-DPYTHON3_EXECUTABLE=/usr/bin/python3.7 \
-DPYTHON_INCLUDE_DIR=/usr/include/python3.7 \
-DPYTHON_LIBRARY=/usr/lib/arm-linux-gnueabihf/libpython3.7m.so \
-DPYTHON3_NUMPY_INCLUDE_DIRS=/usr/lib/python3/dist-packages/numpy/core/include \
-DBUILD_opencv_xfeatures2d=OFF \
..
```

*由于树莓派上缺少某些文件所以有一部分会编译失败（参考了某位仁兄的经验，但是他的网页链接已经找不到了，在此感谢！），因此使用了 -DBUILD_opencv_xfeatures2d=OFF 参数不编译这一部分。*<br/>

出现类似下图的界面即配置cmake成功：<br/>

![](https://img-blog.csdnimg.cn/20191026204311519.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYyNjE0,size_16,color_FFFFFF,t_70) 
<br/>
然后输入下面的命令开始编译：<br/>
```
make
```
<br/><br/>
接下来是个漫长的过程，耗时3小时以上，在此期间不要用树莓派做其他事，保证供电充足。<br/>
不出所料的话会有两次报错，一次丢失文件，一次语法错误。解决方法如下：<br/>
#### 丢失文件报错
特别感谢CSDN的qq_43762614的解决方法！<br/>
![](https://img-blog.csdnimg.cn/20191026204517873.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYyNjE0,size_16,color_FFFFFF,t_70)
<br/>
下载这两个文件：<br/>
[opencv_3rdparty-contrib_xfeatures2d_boostdesc.zip](https://github.com/zhangxinhui02/TouchGlasses/raw/master/opencv_3rdparty-contrib_xfeatures2d_boostdesc_20161012.zip) <br/>
[opencv_3rdparty-contrib_xfeatures2d_vgg.zip](https://github.com/zhangxinhui02/TouchGlasses/raw/master/opencv_3rdparty-contrib_xfeatures2d_vgg_20160317.zip)<br/>
将这两个压缩包中所有带i结尾的文件全部都拷贝到 opencv_contrib-3.4.0/modules/xfeatures2d/src/ 路径下即可。<br/>
继续输入make编译。<br/>
#### 语法错误报错
![](https://github.com/zhangxinhui02/TouchGlasses/raw/master/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE(1200).png)
<br/>
显示在opencv-3.4.0/modules/python/src2/cv2.cpp中出现了语法错误。打开该文件，搜索定位到以下行：

```
char* str = PyString_AsString(obj);
```

修改为：

```
char* str = (char*)PyString_AsString(obj);
```

继续输入make编译，应该不会再有问题了。如果仍然有报错，注意看报错内容再想办法解决。<br/><br/><br/>
make命令执行完成后执行下面的命令安装。需要一分钟左右。

```
sudo make install
```

安装完成后将数据交互区改回去：
```
sudo nano /etc/dphys-swapfile
```
<br/>

将`CONF_SWAPSIZE`修改为：<br/>
```
CONF_SWAPSIZE=100
```
<br/>

输入下面的命令重启服务：<br/>
```
sudo /etc/init.d/dphys-swapfile stop && sudo /etc/init.d/dphys-swapfile start
```
<br/><br/>
这样安装基于Python3的OpenCV就完成了。<br/>
在命令行输入`python3`，运行下面的代码测试安装情况：

```
#导入库，如果没有提示则安装成功。
import cv2
#查看版本，若出现版本号则安装成功。
cv2.__version__
```
<br/><br/>
至此OpenCV安装成功。
