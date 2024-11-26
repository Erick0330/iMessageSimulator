#include "UServerWindow.h"
#include "ui_UServerWindow.h"
#include <string>
#include "mail.h"
#include "UMailDialog.h"
#include "UCreateMailDialog.h"
#include "UErrorDialog.h"
#include "iscorrectstring.h"
using namespace std;

serverWindow::serverWindow(QWidget *parent, Queue *queueAddressee, Queue *queueSender, Queue *queueDeletedA, Queue *queueDeletedS) :
    QMainWindow(parent),
    ui(new Ui::serverWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    this->queueAddressee = queueAddressee;
    this->queueSender = queueSender;
    this->queueDeletedA = queueDeletedA;
    this->queueDeletedS = queueDeletedS;
    QStringList titulos;
    titulos <<"Server ID" << "User ID";
    ui->tblAddresse->setColumnCount(2);
    ui->tblAddresse->setHorizontalHeaderLabels(titulos);
    ui->tblAddresse->setColumnWidth(0, (ui->tblAddresse->width()/2)-1);
    ui->tblAddresse->setColumnWidth(1, (ui->tblAddresse->width()/2)-1);

    ui->tblSender->setColumnCount(2);
    ui->tblSender->setHorizontalHeaderLabels(titulos);
    ui->tblSender->setColumnWidth(0, (ui->tblSender->width()/2)-1);
    ui->tblSender->setColumnWidth(1, (ui->tblSender->width()/2)-1);
    ui->tblAddresse->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tblSender->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    uploadTableA();
    uploadTableS();
    posA = -1;
    posS = -1;
}

serverWindow::~serverWindow()
{
    delete ui;
}

void serverWindow::uploadTableA(){
    int tempL = queueAddressee->getLength();
    void** temp = new void*[tempL];

    for(int i = 0; i < tempL; i++){
        temp[i] = queueAddressee->Extract();
        QString qs1((*(Mail*)temp[i]).getServer().getName().c_str());
        QString qs2((*(Mail*)temp[i]).getUser().getName().c_str());
        ui->tblAddresse->insertRow(ui->tblAddresse->rowCount());
        ui->tblAddresse->setItem(ui->tblAddresse->rowCount()-1, 0, new QTableWidgetItem(qs1));
        ui->tblAddresse->setItem(ui->tblAddresse->rowCount()-1, 1, new QTableWidgetItem(qs2));
    }
    for(int i = 0; i< tempL; i++)
        queueAddressee->EnQueue(temp[i]);
}

void serverWindow::uploadTableS(){
    int tempL = queueSender->getLength();
    void** temp = new void*[tempL];

    for(int i = 0; i < tempL; i++){
        temp[i] = queueSender->Extract();
        QString qs1((*(Mail*)temp[i]).getServer().getName().c_str());
        QString qs2((*(Mail*)temp[i]).getUser().getName().c_str());
        ui->tblSender->insertRow(ui->tblSender->rowCount());
        ui->tblSender->setItem(ui->tblSender->rowCount()-1, 0, new QTableWidgetItem(qs1));
        ui->tblSender->setItem(ui->tblSender->rowCount()-1, 1, new QTableWidgetItem(qs2));
    }
    for(int i = 0; i< tempL; i++)
        queueSender->EnQueue(temp[i]);
}

void serverWindow::on_tblAddresse_itemClicked(QTableWidgetItem *item)
{
    posA = item->row();
}

void serverWindow::on_tblSender_itemClicked(QTableWidgetItem *item)
{
    posS = item->row();
}

void serverWindow::on_pshBtnOpenAddressee_clicked()
{
    if(posA != -1 && queueAddressee->getLength() > 0){
        int tempL = queueAddressee->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < posA; i++)
            temp[i] = queueAddressee->Extract();

        void* ptr = queueAddressee->Extract();

        Mail m1(*(Mail*)ptr);
        MailDialog md(this, &m1);
        md.setWindowTitle("Mail");
        md.exec();

        temp[posA] = ptr;
        for(int i = posA+1; i < tempL; i++)
            temp[i] = queueAddressee->Extract();
        for(int i = 0; i < tempL; i++)
            queueAddressee->EnQueue(temp[i]);

        posA = -1;
    }
}

void serverWindow::on_pshBtnOpenSender_clicked()
{
    if(posS != -1 && queueSender->getLength() > 0){
        int tempL = queueSender->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < posS; i++)
            temp[i] = queueSender->Extract();

        void* ptr = queueSender->Extract();

        Mail m1(*(Mail*)ptr);
        MailDialog md(this, &m1);
        md.setWindowTitle("Mail");
        md.exec();

        temp[posS] = ptr;
        for(int i = posS+1; i < tempL; i++)
            temp[i] = queueSender->Extract();
        for(int i = 0; i < tempL; i++)
            queueSender->EnQueue(temp[i]);

        posS = -1;
    }
}

void serverWindow::on_pshBtnDeleteAddressee_clicked()
{
    if(posA != -1 && queueAddressee->getLength() > 0){
        int tempL = queueAddressee->getLength()-1;
        void** temp = new void*[tempL];
        for(int i = 0; i < posA; i++)
            temp[i] = queueAddressee->Extract();
        queueDeletedA->EnQueue(queueAddressee->Extract());
        for(int i = posA; i < tempL; i++)
            temp[i] = queueAddressee->Extract();
        for(int i = 0; i < tempL; i++)
            queueAddressee->EnQueue(temp[i]);


        ui->tblAddresse->removeRow(posA);

        posA = -1;
    }
}

void serverWindow::on_pshBtnDeleteSender_clicked()
{
    if(posS != -1 && queueSender->getLength() > 0){
        int tempL = queueSender->getLength()-1;
        void** temp = new void*[tempL];
        for(int i = 0; i < posS; i++)
            temp[i] = queueSender->Extract();
        queueDeletedS->EnQueue(queueSender->Extract());
        for(int i = posS; i < tempL; i++)
            temp[i] = queueSender->Extract();
        for(int i = 0; i < tempL; i++)
            queueSender->EnQueue(temp[i]);


        ui->tblSender->removeRow(posS);

        posS = -1;
    }
}

void serverWindow::on_pshBtnNew_clicked()
{
    int res;
    CreateMailDialog n(this);
    n.setWindowTitle("New Mail");
    res = n.exec();
    if(res == QDialog::Accepted){

        if(n.isCorrect()){

            string ss = n.getServer(), su = n.getUser();
            string st = n.getText();
            IsCorrectString is;

            if(is.verify(ss) && is.verify(su) && is.verify(st)){
                Mail* mPTr = new Mail(ss, su, st);
                queueSender->EnQueue(mPTr);

                QString qs1((*(Mail*)mPTr).getServer().getName().c_str());
                QString qs2((*(Mail*)mPTr).getUser().getName().c_str());
                ui->tblSender->insertRow(ui->tblSender->rowCount());
                ui->tblSender->setItem(ui->tblSender->rowCount()-1, 0, new QTableWidgetItem(qs1));
                ui->tblSender->setItem(ui->tblSender->rowCount()-1, 1, new QTableWidgetItem(qs2));
            }
            else {
                ErrorDialog e(this);
                e.setWindowTitle("Error");
                e.exec();
            }
        }
        else{
            ErrorDialog e(this, true);
            e.setWindowTitle("Error");
            e.exec();
        }
    }
}
