#ifndef UNEWTEXTDIALOG_H
#define UNEWTEXTDIALOG_H

#include <QDialog>
#include "server.h"
#include "user.h"

namespace Ui {
class NewTextDialog;
}

class NewTextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTextDialog(QWidget *parent = 0);
    ~NewTextDialog();

    QString getText() const;
    QString getServer() const;
    QString getUser() const;

private slots:
    void on_pshBtnSave_clicked();

    void on_pshBtnCancel_clicked();

private:
    Ui::NewTextDialog *ui;

};

#endif // UNEWTEXTDIALOG_H
