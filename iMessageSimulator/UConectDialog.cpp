#include "UConectDialog.h"
#include "ui_UConectDialog.h"
#include "windows.h"
#include  "stdbool.h"

ConectDialog::ConectDialog(QWidget *parent, bool *connect) :
    QDialog(parent),
    ui(new Ui::ConectDialog)
{
    ui->setupUi(this);
    change = true;
    this->connect = connect;
}

ConectDialog::~ConectDialog()
{
    delete ui;
}

void ConectDialog::progress(){

    for(int i = 0;i < 100; i++){
        if(i%5 == 0)
            changeText();
        ui->pgBrProgress->setValue(i);
        Sleep(50);
    }
    close();
}

void ConectDialog::on_pushButton_clicked()
{
    *connect = true;
    progress();
}

void ConectDialog::changeText(){
    if(change){
        QString qs("Conecting.");
        ui->lblConectando->setText(qs);
        change = false;
    }
    else{
        QString qs("Conecting...");
        ui->lblConectando->setText(qs);
        change = true;
    }
}
