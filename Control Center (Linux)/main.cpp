#include "controlcenter.h"

#include <QApplication>

/*
 * Calculator
 * Task Manager
 *
 *
*/

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ControlCenter cc{};

    cc.RunProcess();
    cc.show();

    return a.exec();
}
