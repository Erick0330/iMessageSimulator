#include "UCreateMailDialog.h"
#include "ui_UCreateMailDialog.h"
#include <string>
using namespace std;

CreateMailDialog::CreateMailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateMailDialog)
{
    ui->setupUi(this);
}

CreateMailDialog::~CreateMailDialog()
{
    delete ui;
}

void CreateMailDialog::on_buttonBox_accepted()
{
    accepted();
}

void CreateMailDialog::on_buttonBox_rejected()
{
    rejected();
}


string CreateMailDialog::getUser() const
{
    string s = ui->lnEditAddressee->text().toStdString();
    char array[20] = {0};
    bool found = false;
    int pos;
    for(size_t i = 0; i < s.length() && !found; i++){
        if(s[i] == '@'){
            found = true;
            pos = i+ 1;
        }
    }


    for(size_t i = pos, j = 0; i < s.length(); i++, j++){
        array[j] = s[i];
        pos = j;
    }



    string user(array);

    return user;
}

string CreateMailDialog::getServer() const
{
    string s = ui->lnEditAddressee->text().toStdString();
    char array[20];
    for(size_t i = 0; i < s.length(); i++){
        if(s[i] != '@')
            array[i] = s[i];
    }

    string server(array);

    return server;
}


string CreateMailDialog::getText() const
{
    return ui->txtEditText->toPlainText().toStdString();
}

bool CreateMailDialog::isCorrect() const
{
    bool found = false;
    string s = ui->lnEditAddressee->text().toStdString();

    for(size_t i = 0; i < s.length() && !found; i++){
        if(s[i] == '@' && !found && i > 0){
            found = true;
        }
    }

    return found;
}
