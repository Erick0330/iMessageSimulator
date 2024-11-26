#ifndef UCONECTDIALOG_H
#define UCONECTDIALOG_H

#include <QDialog>
#include "stdbool.h"

namespace Ui {
class ConectDialog;
}

class ConectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConectDialog(QWidget *parent = 0, bool *connect = 0);
    ~ConectDialog();

    void progress();
    void changeText();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ConectDialog *ui;
    bool change;
    bool* connect;
};

#endif // UCONECTDIALOG_H
