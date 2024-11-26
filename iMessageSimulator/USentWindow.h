#ifndef USENTWINDOW_H
#define USENTWINDOW_H

#include <QMainWindow>
#include "UNewTextDialog.h"
#include "server.h"
#include "user.h"
#include "mail.h"
#include "queue.h"
#include <QTableWidgetItem>

namespace Ui {
class SentWindow;
}

class SentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SentWindow(QWidget *parent = 0, Queue *queue = 0, Queue *queueDeleted = 0);
    ~SentWindow();


    void uploadTable();
private slots:
    void on_pshBtnNew_clicked();
    void on_pshBtnOpenSender_clicked();

    void on_tblAddressee_itemClicked(QTableWidgetItem *item);

    void on_pshBtnDeleteSender_clicked();

private:
    Ui::SentWindow *ui;
    Queue* queue;
    Queue* queueDeleted;
    int pos;
};

#endif // USENTWINDOW_H
