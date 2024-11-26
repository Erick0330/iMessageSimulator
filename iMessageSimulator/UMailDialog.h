#ifndef UMAILDIALOG_H
#define UMAILDIALOG_H

#include <QDialog>
#include "mail.h"

namespace Ui {
class MailDialog;
}

class MailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MailDialog(QWidget *parent = 0, Mail* m = 0);
    ~MailDialog();

private slots:
    void on_pshBtnOk_clicked();

private:
    Ui::MailDialog *ui;

};

#endif // UMAILDIALOG_H
