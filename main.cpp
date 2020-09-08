#include "cardswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CardsWindow w;
    w.show();

    return a.exec();
}
