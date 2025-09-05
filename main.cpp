#include "managerdb.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ManagerDB w;
    w.show();


    return a.exec();
}
