#ifndef UDELETEDWINDOW_H
#define UDELETEDWINDOW_H

#include <QMainWindow>
#include "queue.h"
#include "QTableWidgetItem"

namespace Ui {
class DeletedWindow;
}

class DeletedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeletedWindow(QWidget *parent = 0, Queue *queueDeletedA = 0, Queue *queueDeletedS = 0,
                           Queue* queueRestoreA = 0, Queue* queueRestoreS = 0);
    ~DeletedWindow();

    void uploadTableS();
    void uploadTableA();
private slots:
    void on_tblA_itemClicked(QTableWidgetItem *item);

    void on_tbleS_itemClicked(QTableWidgetItem *item);

    void on_pshBtnOpenA_clicked();

    void on_pshBtnS_clicked();

    void on_pshBtnRestoreA_clicked();

    void on_pshBtnDeleteA_clicked();

    void on_pshBtnRestoreS_clicked();

    void on_pshBtnDeleteS_clicked();

private:
    Ui::DeletedWindow *ui;
    Queue* queueDeletedA;
    Queue* queueDeletedS;
    Queue* queueRestoreA;
    Queue* queueRestoreS;
    int posA;
    int posS;
};

#endif // UDELETEDWINDOW_H
