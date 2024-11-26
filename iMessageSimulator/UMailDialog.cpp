#include "UMailDialog.h"
#include "ui_UMailDialog.h"
#include "mail.h"

MailDialog::MailDialog(QWidget *parent, Mail *m) :
    QDialog(parent),
    ui(new Ui::MailDialog)
{
    ui->setupUi(this);
    QString t(m->getText().c_str());
    ui->txtBrwserText->setText(t);
    Server ser = m->getServer();
    QString s(ser.getName().c_str());
    ui->lblInServer->setText(s);
    QString u(m->getUser().getName().c_str());
    ui->lblInUser->setText(u);
}

MailDialog::~MailDialog()
{
    delete ui;
}

void MailDialog::on_pshBtnOk_clicked()
{
    close();
}
