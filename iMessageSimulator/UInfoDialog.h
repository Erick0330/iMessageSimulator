#ifndef UINFODIALOG_H
#define UINFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InfoDialog *ui;
};

#endif // UINFODIALOG_H
