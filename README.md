## 简介

中山大学计算机图形学课程，小组合作仓库

## 配置

我是按照这个链接搞的
https://blog.csdn.net/m0_50695988/article/details/134497796

## 环境

IDE：VSCode
MINGW：32位
gcc：9.2.0 
gdb：7.6.1
opengl: 4.6
glad：0.1.36
GLFW：3.3
stb_image：2.30
GLM：1.0.1

## 使用

在**根目录**打开终端输入：`make run dir=path`

> 注意path为相对源文件`src`的路径，不需要加`src/`
> 如运行texture中texture1的main.cpp就是`make run dir=texture/texture1`
> **一定是根目录**，不能是源文件的目录

## 修改窗口名字

我把初始化glad和glfw都封装在init头文件里，只需要在这里修改就可以了，然后在源文件中调用即可