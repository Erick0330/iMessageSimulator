#ifndef UERRORDIALOG_H
#define UERRORDIALOG_H

#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = 0, bool text = 0);
    ~ErrorDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorDialog *ui;
};

#endif // UERRORDIALOG_H
