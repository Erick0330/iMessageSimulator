#ifndef UFRMMAIN_H
#define UFRMMAIN_H

#include <QMainWindow>
#include "UServerWindow.h"
#include "USentWindow.h"
#include <iostream>
#include "mail.h"
#include "queue.h"
#include "UInfoDialog.h"
#include "UDeletedWindow.h"
using namespace std;

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public slots:
    void FormServerRequested();
    void FormSentRequested();  
    void FormDeletedRequested();
    void saveOnFile();
    void FormInfoRequested();
public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

    void uploadTable();

    void startConnection();
    void loadFiles();

private slots:

    void on_tblInbox_itemClicked(QTableWidgetItem *item);

    void on_pshBtnOpen_clicked();

    void on_pshBtnDelete_clicked();

    void on_pshBtnConnect_clicked();

private:
    Ui::frmMain *ui;
    serverWindow* serverW;
    SentWindow* sentW;
    DeletedWindow* deletedWindow;
    InfoDialog* infoDialog;
    Queue addresseNC;
    Queue addresseC;
    Queue senderNC;
    Queue senderC;
    Queue addresseDeleted;
    Queue senderDeleted;
    int pos;
};

#endif // UFRMMAIN_H
