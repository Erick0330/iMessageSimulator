#include <iostream>
#include <QApplication>
#include <string>
#include <iostream>
#include "integer.h"
using namespace std;

int main(){

    QString qs = "Hello World!";
    string s;

    s = qs.toStdString();

    cout<<s<<endl;

    return 0;
}
