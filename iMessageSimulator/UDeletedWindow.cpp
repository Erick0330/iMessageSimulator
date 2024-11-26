#include "UDeletedWindow.h"
#include "ui_UDeletedWindow.h"
#include <string>
#include "mail.h"
#include "UMailDialog.h"
#include "UCreateMailDialog.h"
#include "queue.h"

DeletedWindow::DeletedWindow(QWidget *parent, Queue *queueDeletedA, Queue *queueDeletedS, Queue *queueRestoreA,
                             Queue *queueRestoreS) :
    QMainWindow(parent),
    ui(new Ui::DeletedWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    this->queueDeletedA = queueDeletedA;
    this->queueDeletedS = queueDeletedS;
    this->queueRestoreA = queueRestoreA;
    this->queueRestoreS = queueRestoreS;
    QStringList titulos;
    titulos <<"Server ID" << "User ID";
    ui->tblA->setColumnCount(2);
    ui->tblA->setHorizontalHeaderLabels(titulos);
    ui->tblA->setColumnWidth(0, (ui->tblA->width()/2)-1);
    ui->tblA->setColumnWidth(1, (ui->tblA->width()/2)-1);

    ui->tbleS->setColumnCount(2);
    ui->tbleS->setHorizontalHeaderLabels(titulos);
    ui->tbleS->setColumnWidth(0, (ui->tbleS->width()/2)-1);
    ui->tbleS->setColumnWidth(1, (ui->tbleS->width()/2)-1);
    ui->tblA->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tbleS->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    uploadTableA();
    uploadTableS();
}

DeletedWindow::~DeletedWindow()
{
    delete ui;
}

void DeletedWindow::uploadTableA(){
    int tempL = queueDeletedA->getLength();
    void** temp = new void*[tempL];

    for(int i = 0; i < tempL; i++){
        temp[i] = queueDeletedA->Extract();
        QString qs1((*(Mail*)temp[i]).getServer().getName().c_str());
        QString qs2((*(Mail*)temp[i]).getUser().getName().c_str());
        ui->tblA->insertRow(ui->tblA->rowCount());
        ui->tblA->setItem(ui->tblA->rowCount()-1, 0, new QTableWidgetItem(qs1));
        ui->tblA->setItem(ui->tblA->rowCount()-1, 1, new QTableWidgetItem(qs2));
    }
    for(int i = 0; i< tempL; i++)
        queueDeletedA->EnQueue(temp[i]);
}

void DeletedWindow::uploadTableS(){
    int tempL = queueDeletedS->getLength();
    void** temp = new void*[tempL];

    for(int i = 0; i < tempL; i++){
        temp[i] = queueDeletedS->Extract();
        QString qs1((*(Mail*)temp[i]).getServer().getName().c_str());
        QString qs2((*(Mail*)temp[i]).getUser().getName().c_str());
        ui->tbleS->insertRow(ui->tbleS->rowCount());
        ui->tbleS->setItem(ui->tbleS->rowCount()-1, 0, new QTableWidgetItem(qs1));
        ui->tbleS->setItem(ui->tbleS->rowCount()-1, 1, new QTableWidgetItem(qs2));
    }
    for(int i = 0; i< tempL; i++)
        queueDeletedS->EnQueue(temp[i]);
}

void DeletedWindow::on_tblA_itemClicked(QTableWidgetItem *item)
{
    posA = item->row();
}

void DeletedWindow::on_tbleS_itemClicked(QTableWidgetItem *item)
{
    posS = item->row();
}

void DeletedWindow::on_pshBtnOpenA_clicked()
{
    if(posA != -1 && queueDeletedA->getLength() > 0){
        int tempL = queueDeletedA->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < posA; i++)
            temp[i] = queueDeletedA->Extract();

        void* ptr = queueDeletedA->Extract();

        Mail m1(*(Mail*)ptr);
        MailDialog md(this, &m1);
        md.setWindowTitle("Mail");
        md.exec();

        temp[posA] = ptr;
        for(int i = posA+1; i < tempL; i++)
            temp[i] = queueDeletedA->Extract();
        for(int i = 0; i < tempL; i++)
            queueDeletedA->EnQueue(temp[i]);
    }
}

void DeletedWindow::on_pshBtnS_clicked()
{
    if(posS != -1 && queueDeletedS->getLength() > 0){
        int tempL = queueDeletedS->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < posS; i++)
            temp[i] = queueDeletedS->Extract();

        void* ptr = queueDeletedS->Extract();

        Mail m1(*(Mail*)ptr);
        MailDialog md(this, &m1);
        md.setWindowTitle("Mail");
        md.exec();

        temp[posS] = ptr;
        for(int i = posS+1; i < tempL; i++)
            temp[i] = queueDeletedS->Extract();
        for(int i = 0; i < tempL; i++)
            queueDeletedS->EnQueue(temp[i]);
    }
}

void DeletedWindow::on_pshBtnRestoreA_clicked()
{
    if(posA != -1 && queueDeletedA->getLength() > 0){
        int tempL = queueDeletedA->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < posA; i++)
            temp[i] = queueDeletedA->Extract();


        queueRestoreA->EnQueue(queueDeletedA->Extract());

        ui->tblA->removeRow(posA);

        for(int i = posA; i < tempL-1; i++)
            temp[i] = queueDeletedA->Extract();
        for(int i = 0; i < tempL-1; i++)
            queueDeletedA->EnQueue(temp[i]);
    }
}

void DeletedWindow::on_pshBtnDeleteA_clicked()
{
    if(posA != -1 && queueDeletedA->getLength() > 0){
        int tempL = queueDeletedA->getLength()-1;
        void** temp = new void*[tempL];
        for(int i = 0; i < posA; i++)
            temp[i] = queueDeletedA->Extract();
        queueDeletedA->Extract();
        for(int i = posA; i < tempL; i++)
            temp[i] = queueDeletedA->Extract();
        for(int i = 0; i < tempL; i++)
            queueDeletedA->EnQueue(temp[i]);


        ui->tblA->removeRow(posA);
    }
}

void DeletedWindow::on_pshBtnRestoreS_clicked()
{
    if(posS != -1 && queueDeletedS->getLength() > 0){
        int tempL = queueDeletedS->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < posS; i++)
            temp[i] = queueDeletedS->Extract();


        queueRestoreS->EnQueue(queueDeletedS->Extract());

        ui->tbleS->removeRow(posS);

        for(int i = posS; i < tempL - 1; i++)
            temp[i] = queueDeletedS->Extract();
        for(int i = 0; i < tempL - 1; i++)
            queueDeletedS->EnQueue(temp[i]);
    }
}

void DeletedWindow::on_pshBtnDeleteS_clicked()
{
    if(posS != -1 && queueDeletedS->getLength() > 0){
        int tempL = queueDeletedS->getLength()-1;
        void** temp = new void*[tempL];
        for(int i = 0; i < posS; i++)
            temp[i] = queueDeletedS->Extract();
        queueDeletedS->Extract();
        for(int i = posS; i < tempL; i++)
            temp[i] = queueDeletedS->Extract();
        for(int i = 0; i < tempL; i++)
            queueDeletedS->EnQueue(temp[i]);


        ui->tbleS->removeRow(posS);
    }
}
