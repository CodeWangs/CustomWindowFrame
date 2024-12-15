### 软件介绍

一个基于QFrame类的自定义窗口框架；

![image-20241215203003952](C:\Users\wangs\AppData\Roaming\Typora\typora-user-images\image-20241215203003952.png)
![image](https://github.com/user-attachments/assets/87b6e6b6-c629-4309-9f68-2cbc87415031)


### 开发环境

QT版本: Qt 5.15.2
编译器: msvc2019_64

### 功能说明:

1. 实现了窗口基本的最大化、最小化、关闭功能；
2. 实现了窗口8个方向的边框拖动改变窗口大小的功能；
3. 实现了双击标题栏最大化和最小化窗口的功能；
4. 实现了最大化时拖动标题栏，窗口会恢复正常大小的功能；

注：考虑到Qt的跨平台特性，窗口贴边功能需要调用windows的系统API，故并未实现，有需要的可以自行实现；

注：标题栏的搜索、设置等功能需自行定义信号槽进行实现；

### 软件架构

框体由自定义的标题栏CTitleBar类和中心窗体的QWidget类组成；后续使用只需要调用预留的 

```c++
void setCentralWidget(QWidget* widget); 
```

方法设置中心窗体即可；另外还有一个qss文件，可以自定义窗体框架的样式；



项目参考：bottod
