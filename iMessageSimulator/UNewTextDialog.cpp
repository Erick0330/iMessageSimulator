#include "UNewTextDialog.h"
#include "ui_UNewTextDialog.h"

NewTextDialog::NewTextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTextDialog)
{
    ui->setupUi(this);
}

NewTextDialog::~NewTextDialog()
{
    delete ui;
}



void NewTextDialog::on_pshBtnSave_clicked()
{
    accepted();

}

void NewTextDialog::on_pshBtnCancel_clicked()
{
    rejected();
}



