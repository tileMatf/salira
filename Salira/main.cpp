#include "salira.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salira w;

    // Check git push from Qt
    w.show();


    return a.exec();
}
