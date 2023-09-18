#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 让Qt程序适配高分辨率屏幕，解决软件界面错乱异常
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}
