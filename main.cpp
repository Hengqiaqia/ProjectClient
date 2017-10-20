#include "MainWindow.h"
#include <QApplication>
#include "LoginWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow lw;
    lw.show();

#if 0
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
