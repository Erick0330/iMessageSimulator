#include "UfrmMain.h"
#include "ui_UFrmMain.h"
#include "UServerWindow.h"
#include "UMailDialog.h"
#include "UConectDialog.h"
#include "UDeletedWindow.h"
#include "fstream"

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain),
    serverW(0),
    sentW(0),
    deletedWindow(0),
    infoDialog(0)
{
    ui->setupUi(this);
    connect(ui->actionServer, SIGNAL(triggered()), this,
            SLOT(FormServerRequested()));
    connect(ui->actionSent, SIGNAL(triggered()), this,
            SLOT(FormSentRequested()));
    connect(ui->actionDeleted_Mails, SIGNAL(triggered()), this,SLOT(FormDeletedRequested()));
    connect(ui->actionSave_Mails, SIGNAL(triggered()), this, SLOT(saveOnFile()));
    connect(ui->actionInfo_about_the_app, SIGNAL(triggered()), this, SLOT(FormInfoRequested()));
    QStringList titulos;
    titulos <<"Server ID" << "User ID";
    ui->tblInbox->setColumnCount(2);
    ui->tblInbox->setHorizontalHeaderLabels(titulos);
    ui->tblInbox->setColumnWidth(0, (ui->tblInbox->width()/2)-1);
    ui->tblInbox->setColumnWidth(1, (ui->tblInbox->width()/2)-1);
    ui->tblInbox->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    pos = -1;
    loadFiles();
    uploadTable();

}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::FormServerRequested()
{
    serverW = new serverWindow(this, &addresseC, &senderNC, &addresseDeleted, &senderDeleted);
    serverW->show();
}
void frmMain::FormInfoRequested()
{
    infoDialog = new InfoDialog(this);
    infoDialog->show();
}

void frmMain::FormSentRequested()
{
    sentW = new SentWindow(this, &addresseNC, &addresseDeleted);
    sentW->show();
}

void frmMain::FormDeletedRequested()
{
    deletedWindow = new DeletedWindow(this, &addresseDeleted, &senderDeleted, &addresseNC, &senderNC);
    deletedWindow->show();
}


void frmMain::uploadTable(){
    int tempL = senderC.getLength();
    void** temp = new void*[tempL];

    for(int i = 0; i < tempL; i++){
        temp[i] = senderC.Extract();
        QString qs1((*(Mail*)temp[i]).getServer().getName().c_str());
        QString qs2((*(Mail*)temp[i]).getUser().getName().c_str());
        ui->tblInbox->insertRow(ui->tblInbox->rowCount());
        ui->tblInbox->setItem(ui->tblInbox->rowCount()-1, 0, new QTableWidgetItem(qs1));
        ui->tblInbox->setItem(ui->tblInbox->rowCount()-1, 1, new QTableWidgetItem(qs2));
    }
    for(int i = 0; i< tempL; i++)
        senderC.EnQueue(temp[i]);
}

void frmMain::on_tblInbox_itemClicked(QTableWidgetItem *item)
{
    pos = item->row();
}

void frmMain::on_pshBtnOpen_clicked()
{
    if(pos != -1 && senderC.getLength() > 0){
        int tempL = senderC.getLength();
        void** temp = new void*[tempL];
        for(int i = 0; i < pos; i++)
            temp[i] = senderC.Extract();

        void* ptr = senderC.Extract();

        Mail m1(*(Mail*)ptr);
        MailDialog md(this, &m1);
        md.setWindowTitle("Mail");
        md.exec();

        temp[pos] = ptr;
        for(int i = pos+1; i < tempL; i++)
            temp[i] = senderC.Extract();
        for(int i = 0; i < tempL; i++)
            senderC.EnQueue(temp[i]);
    }
}

void frmMain::on_pshBtnDelete_clicked()
{
    if(pos != -1 && senderC.getLength() > 0){
        int tempL = senderC.getLength()-1;
        void** temp = new void*[tempL];
        for(int i = 0; i < pos; i++)
            temp[i] = senderC.Extract();
        senderDeleted.EnQueue(senderC.Extract());
        for(int i = pos; i < tempL; i++)
            temp[i] = senderC.Extract();
        for(int i = 0; i < tempL; i++)
            senderC.EnQueue(temp[i]);


        ui->tblInbox->removeRow(pos);
    }
}

void frmMain::on_pshBtnConnect_clicked()
{
    bool connect = false;
    ConectDialog c(this, &connect);
    c.setWindowTitle("Conecting");
    c.exec();
    if(connect){
        startConnection();
        FormServerRequested();
        uploadTable();
    }
}

void frmMain::startConnection(){
    int tempL = addresseNC.getLength();
    for(int i = 0; i < tempL; i++)
        addresseC.EnQueue(addresseNC.Extract());

    tempL = senderNC.getLength();
    for(int i = 0; i < tempL; i++)
        senderC.EnQueue(senderNC.Extract());
}

void frmMain::saveOnFile(){

    int tempL = addresseC.getLength();
    void** temp = new void*[tempL];
    std::ofstream file_outAC;
    file_outAC.open("addresseC.txt");
    file_outAC<< tempL << endl;
    for(int i = 0; i <tempL; i++){
        temp[i] = addresseC.Extract();
        Mail* ptr = (Mail*) temp[i];
        string s = ptr->getServer().getName(), u = ptr->getUser().getName(), t = ptr->getText();
        file_outAC << s << ","
                   << u << ","
                   << t << "`";
    }
    for(int i = 0; i < tempL; i++)
        addresseC.EnQueue(temp[i]);
    delete [] temp;
    file_outAC.close();

    tempL = addresseNC.getLength();
    std::ofstream file_outANC;
    file_outANC.open("addresseNC.txt");
    file_outANC<< tempL << endl;
    for(int i = 0; i <tempL; i++){
        temp[i] = addresseNC.Extract();
        Mail* ptr = (Mail*) temp[i];
        string s = ptr->getServer().getName(), u = ptr->getUser().getName(), t = ptr->getText();
        file_outANC << s << ","
                    << u << ","
                    << t << "`";
    }
    for(int i = 0; i < tempL; i++)
        addresseNC.EnQueue(temp[i]);
    delete [] temp;
    file_outANC.close();

    tempL = senderC.getLength();
    std::ofstream file_outSC;
    file_outSC.open("senderC.txt");
    file_outSC<< tempL << endl;
    for(int i = 0; i <tempL; i++){
        temp[i] = senderC.Extract();
        Mail* ptr = (Mail*) temp[i];
        string s = ptr->getServer().getName(), u = ptr->getUser().getName(), t = ptr->getText();
        file_outSC << s << ","
                   << u << ","
                   << t << "`";
    }
    for(int i = 0; i < tempL; i++)
        senderC.EnQueue(temp[i]);
    delete [] temp;
    file_outSC.close();

    tempL = senderNC.getLength();
    std::ofstream file_outSNC;
    file_outSNC.open("senderNC.txt");
    file_outSNC<< tempL << endl;
    for(int i = 0; i <tempL; i++){
        temp[i] = senderNC.Extract();
        Mail* ptr = (Mail*) temp[i];
        string s = ptr->getServer().getName(), u = ptr->getUser().getName(), t = ptr->getText();
        file_outSNC << s << ","
                    << u << ","
                    << t << "`";
    }
    for(int i = 0; i < tempL; i++)
        senderNC.EnQueue(temp[i]);
    delete [] temp;
    file_outSNC.close();

    tempL = addresseDeleted.getLength();
    std::ofstream file_outDA;
    file_outDA.open("deletedA.txt");
    file_outDA<< tempL << endl;
    for(int i = 0; i <tempL; i++){
        temp[i] = addresseDeleted.Extract();
        Mail* ptr = (Mail*) temp[i];
        string s = ptr->getServer().getName(), u = ptr->getUser().getName(), t = ptr->getText();
        file_outDA << s << ","
                   << u << ","
                   << t << "`";
    }
    for(int i = 0; i < tempL; i++)
        addresseDeleted.EnQueue(temp[i]);
    delete [] temp;
    file_outDA.close();

    tempL = senderDeleted.getLength();
    std::ofstream file_outDS;
    file_outDS.open("deletedS.txt");
    file_outDS<< tempL << endl;
    for(int i = 0; i <tempL; i++){
        temp[i] = senderDeleted.Extract();
        Mail* ptr = (Mail*) temp[i];
        string s = ptr->getServer().getName(), u = ptr->getUser().getName(), t = ptr->getText();
        file_outDS << s << ","
                   << u << ","
                   << t << "`";
    }
    for(int i = 0; i < tempL; i++)
        senderDeleted.EnQueue(temp[i]);
    delete [] temp;
    file_outDS.close();
}


void frmMain::loadFiles(){

    const int SIZE = 300;
    char buffer[SIZE];

    std::ifstream file_inAC;
    file_inAC.open("addresseC.txt");
    file_inAC.getline(buffer, SIZE, '\n');
    int cont = atoi(buffer);
    while(cont > 0){
        file_inAC.getline(buffer, SIZE, ',');
        string server = buffer;
        file_inAC.getline(buffer, SIZE, ',');
        string user = buffer;
        file_inAC.getline(buffer, SIZE, '`');
        string text = buffer;
        Mail* ptr = new Mail(server, user, text);
        addresseC.EnQueue(ptr);
        --cont;
    }
    file_inAC.close();

    std::ifstream file_inANC;
    file_inANC.open("addresseNC.txt");
    file_inANC.getline(buffer, SIZE, '\n');
    cont = atoi(buffer);
    while(cont > 0){
        file_inANC.getline(buffer, SIZE, ',');
        string server = buffer;
        file_inANC.getline(buffer, SIZE, ',');
        string user = buffer;
        file_inANC.getline(buffer, SIZE, '`');
        string text = buffer;
        Mail* ptr = new Mail(server, user, text);
        addresseNC.EnQueue(ptr);
        --cont;
    }
    file_inANC.close();

    std::ifstream file_inSC;
    file_inSC.open("senderC.txt");
    file_inSC.getline(buffer, SIZE,'\n');
    cont = atoi(buffer);
    while(cont > 0){
        file_inSC.getline(buffer, SIZE, ',');
        string server = buffer;
        file_inSC.getline(buffer, SIZE, ',');
        string user = buffer;
        file_inSC.getline(buffer, SIZE, '`');
        string text = buffer;
        Mail* ptr = new Mail(server, user, text);
        senderC.EnQueue(ptr);
        --cont;
    }
    file_inSC.close();

    std::ifstream file_inSNC;
    file_inSNC.open("senderNC.txt");
    file_inSNC.getline(buffer, SIZE, '\n');
    cont = atoi(buffer);
    while(cont > 0){
        file_inSNC.getline(buffer, SIZE, ',');
        string server = buffer;
        file_inSNC.getline(buffer, SIZE, ',');
        string user = buffer;
        file_inSNC.getline(buffer, SIZE, '`');
        string text = buffer;
        Mail* ptr = new Mail(server, user, text);
        senderNC.EnQueue(ptr);
        --cont;
    }
    file_inSNC.close();


    std::ifstream file_inDA;
    file_inDA.open("deletedA.txt");
    file_inDA.getline(buffer, SIZE, '\n');
    cont = atoi(buffer);
    while(cont > 0){
        file_inDA.getline(buffer, SIZE, ',');
        string server = buffer;
        file_inDA.getline(buffer, SIZE, ',');
        string user = buffer;
        file_inDA.getline(buffer, SIZE, '`');
        string text = buffer;
        Mail* ptr = new Mail(server, user, text);
        addresseDeleted.EnQueue(ptr);
        --cont;
    }
    file_inDA.close();


    std::ifstream file_inDS;
    file_inDS.open("deletedS.txt");
    file_inDS.getline(buffer, SIZE, '\n');
    cont = atoi(buffer);
    while(cont > 0){
        file_inDS.getline(buffer, SIZE, ',');
        string server = buffer;
        file_inDS.getline(buffer, SIZE, ',');
        string user = buffer;
        file_inDS.getline(buffer, SIZE, '`');
        string text = buffer;
        Mail* ptr = new Mail(server, user, text);
        senderDeleted.EnQueue(ptr);
        --cont;
    }
    file_inDS.close();
}
