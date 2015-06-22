#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    QDesktopWidget desktop;
    window.setGeometry((desktop.screen()->width() - window.width()) / 2,
                       (desktop.screen()->height() - window.height()) / 2,
                       window.width(), window.height());

    window.show();

    return application.exec();
}
