#include "learnOpenGL.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LearnOpenGL w;
    w.show();

    return a.exec();
}
