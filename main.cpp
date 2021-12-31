#include "mainwindow.h"

#include <QApplication>
MainWindow * window;
QApplication* app;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app=&a;
    MainWindow w;
    window = &w;
    //去掉标题栏
    //重写mouseMoveEvent,mousePressEvent,mouseReleaseEvent 等事件
    w.setWindowFlag(Qt::FramelessWindowHint);

    w.show();
    return a.exec();
}
