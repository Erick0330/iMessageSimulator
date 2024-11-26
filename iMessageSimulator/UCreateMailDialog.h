#ifndef UCREATEMAILDIALOG_H
#define UCREATEMAILDIALOG_H

#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
class CreateMailDialog;
}

class CreateMailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMailDialog(QWidget *parent = 0);
    ~CreateMailDialog();
    string getText() const;
    string getServer() const;
    string getUser() const;
    bool isCorrect() const;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateMailDialog *ui;
};

#endif // UCREATEMAILDIALOG_H
