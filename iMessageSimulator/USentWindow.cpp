#include "USentWindow.h"
#include "ui_USentWindow.h"
#include "UCreateMailDialog.h"
#include <iostream>
#include "UMailDialog.h"
#include "UErrorDialog.h"
#include "iscorrectstring.h"

SentWindow::SentWindow(QWidget *parent, Queue *queue, Queue *queueDeleted) :
    QMainWindow(parent),
    ui(new Ui::SentWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    QStringList titulos;
    titulos <<"Server ID" << "User ID";
    ui->tblAddressee->setColumnCount(2);
    ui->tblAddressee->setHorizontalHeaderLabels(titulos);
    ui->tblAddressee->setColumnWidth(0, (ui->tblAddressee->width()/2)-1);
    ui->tblAddressee->setColumnWidth(1, (ui->tblAddressee->width()/2)-1);
    ui->tblAddressee->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->queue = queue;
    this->queueDeleted = queueDeleted;
    uploadTable();
    pos = -1;
}

SentWindow::~SentWindow()
{
    delete ui;
}

void SentWindow::on_pshBtnNew_clicked()
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
                queue->EnQueue(mPTr);

                QString qs1((*(Mail*)mPTr).getServer().getName().c_str());
                QString qs2((*(Mail*)mPTr).getUser().getName().c_str());
                ui->tblAddressee->insertRow(ui->tblAddressee->rowCount());
                ui->tblAddressee->setItem(ui->tblAddressee->rowCount()-1, 0, new QTableWidgetItem(qs1));
                ui->tblAddressee->setItem(ui->tblAddressee->rowCount()-1, 1, new QTableWidgetItem(qs2));
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

void SentWindow::on_pshBtnOpenSender_clicked()
{
    if(pos != -1 && queue->getLength() > 0){
        int tempL = queue->getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < pos; i++)
            temp[i] = queue->Extract();

        void* ptr = queue->Extract();

        Mail m1(*(Mail*)ptr);
        MailDialog md(this, &m1);
        md.setWindowTitle("Mail");
        md.exec();

        temp[pos] = ptr;
        for(int i = pos+1; i < tempL; i++)
            temp[i] = queue->Extract();
        for(int i = 0; i < tempL; i++)
            queue->EnQueue(temp[i]);

        pos = -1;
    }
}

void SentWindow::on_tblAddressee_itemClicked(QTableWidgetItem *item)
{
    pos = item->row();
}

void SentWindow::on_pshBtnDeleteSender_clicked()
{
    if(pos != -1 && queue->getLength() > 0){
        int tempL = queue->getLength()-1;
        void** temp = new void*[tempL];
        for(int i = 0; i < pos; i++)
            temp[i] = queue->Extract();
        queueDeleted->EnQueue(queue->Extract());
        for(int i = pos; i < tempL; i++)
            temp[i] = queue->Extract();
        for(int i = 0; i < tempL; i++)
            queue->EnQueue(temp[i]);


        ui->tblAddressee->removeRow(pos);
        pos = -1;
    }

}

void SentWindow::uploadTable(){
    int tempL = queue->getLength();
    void** temp = new void*[tempL];

    for(int i = 0; i < tempL; i++){
        temp[i] = queue->Extract();
        QString qs1((*(Mail*)temp[i]).getServer().getName().c_str());
        QString qs2((*(Mail*)temp[i]).getUser().getName().c_str());
        ui->tblAddressee->insertRow(ui->tblAddressee->rowCount());
        ui->tblAddressee->setItem(ui->tblAddressee->rowCount()-1, 0, new QTableWidgetItem(qs1));
        ui->tblAddressee->setItem(ui->tblAddressee->rowCount()-1, 1, new QTableWidgetItem(qs2));
    }
    for(int i = 0; i< tempL; i++)
        queue->EnQueue(temp[i]);
}
