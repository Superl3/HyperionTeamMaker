#include "TeamMatching.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TeamMatching w;
    w.show();
    return a.exec();
}
