#ifndef USERVERWINDOW_H
#define USERVERWINDOW_H

#include <QMainWindow>
#include "queue.h"
#include <QTableWidgetItem>

namespace Ui {
class serverWindow;
}

class serverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit serverWindow(QWidget *parent = 0, Queue *queueAddressee = 0, Queue *queueSender = 0, Queue *queueDeletedA = 0, Queue *queueDeletedS = 0);
    ~serverWindow();

    void uploadTableA();
    void uploadTableS();
private slots:
    void on_tblAddresse_itemClicked(QTableWidgetItem *item);

    void on_tblSender_itemClicked(QTableWidgetItem *item);

    void on_pshBtnOpenAddressee_clicked();

    void on_pshBtnOpenSender_clicked();

    void on_pshBtnDeleteAddressee_clicked();

    void on_pshBtnDeleteSender_clicked();

    void on_pshBtnNew_clicked();

private:
    Ui::serverWindow *ui;
    Queue* queueAddressee;
    Queue* queueSender;
    Queue* queueDeletedA;
    Queue* queueDeletedS;
    int posA;
    int posS;
};

#endif // USERVERWINDOW_H
