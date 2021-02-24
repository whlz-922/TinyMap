/*项目名称：光谷区域飞速达地图
* 项目功能：提供光谷广场附近著名区域之间路径信息
* 开发环境：window10
* 开发工具：qt5
* 开发语言：c/c++
* 源码参考：https://github.com/douzujun/MyMapView
*/
#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <windows.h>
#include <QFont>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //窗口启动画面设置 字体设置
    QPixmap pixmap(":/resource/StartIcon.jpg");
    //程序启动窗口 窗口启动图片在此显示
    QSplashScreen splash(pixmap);
    splash.show();
    //等待2秒再启动主窗口加载地图
    Sleep(2000);
    //设置程序在显示启动画面时也能响应鼠标等其它事件
    a.processEvents();
    //字体
    QFont font("APRL KaitiM GB", 8);
    font.setBold(true);
    a.setFont(font);

    qDebug() << "Run.........";

    MainWindow w;
    w.show();

    //主窗口完成初始化后，结束启动画面
    splash.finish(&w);

    return a.exec();
}
