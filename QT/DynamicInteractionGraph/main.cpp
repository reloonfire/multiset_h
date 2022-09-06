#include "dynamicinteractiongraph.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DynamicInteractionGraph w;
    w.show();
    return a.exec();
}
