#include "UErrorDialog.h"
#include "ui_UErrorDialog.h"
#include <string>
using namespace std;

ErrorDialog::ErrorDialog(QWidget *parent, bool text) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
    if(text){
        string temp = "The addressee has to be idserver@iduser";
        QString q(temp.c_str());
        ui->lblErrorMsg->setText(q);
    }
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::on_pushButton_clicked()
{
    close();
}
