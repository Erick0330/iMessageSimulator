#include "UfrmMain.h"
#include <QApplication>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    frmMain w;
    w.show();

    return a.exec();




}
