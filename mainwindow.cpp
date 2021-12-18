#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <fstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
}
int stt=0;


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawTable(AdjacencyMatrix ds)
{
    ui->tb_1->setColumnCount(ds.n);
    ui->tb_1->setRowCount(ds.n);
    ui->tb_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ds.n;i++)
        ui->tb_1->setColumnWidth(i,10);
    for(int i=0; i<ds.n;i++)
        for(int j=0;j<ds.n;j++)
        {
            char num_char[10 + sizeof(char)];
            std::sprintf(num_char, "%d", ds.mt[i][j]);
            ui->tb_1->setItem(i,j,new QTableWidgetItem(num_char));
        }
}

void MainWindow::infoAirPort(AirPortList ds)
{
    ui->tb_2->setColumnCount(4);
    ui->tb_2->setRowCount(ds.n);
    QStringList title;
    title<<"MaSB"<<"TenSB"<<"DienThoai"<<"DiaChi";
    ui->tb_2->setHorizontalHeaderLabels(title);
    for(int i=0;i<ds.n;i++)
    {
        char num_char[10 + sizeof(char)];
        std::sprintf(num_char, "%s", ds.ds[i].code);
        ui->tb_2->setItem(i,0,new QTableWidgetItem(num_char));
        std::sprintf(num_char, "%s", ds.ds[i].name);
        ui->tb_2->setItem(i,1,new QTableWidgetItem(num_char));
        std::sprintf(num_char, "%s", ds.ds[i].phone);
        ui->tb_2->setItem(i,2,new QTableWidgetItem(num_char));
        std::sprintf(num_char, "%s", ds.ds[i].addr);
        ui->tb_2->setItem(i,3,new QTableWidgetItem(num_char));
    }
}
void MainWindow::on_btn_Read_clicked()
{
    stt=1;
    ui->txt_FileName->setEnabled(true);
    ui->btn_OK->setEnabled(true);

}


void MainWindow::on_btn_OK_clicked()
{
    if(stt==1)
    {

        QString a;
        a = ui->txt_FileName->text();
        QByteArray ba = a.toLocal8Bit();
        const char *str = ba.data();
        QString b = QString::number(Read((char*)str,am,sb));
        //ui->label_2->setText(b);
        drawTable(am);
        infoAirPort(sb);
        ui->txt_FileName->setEnabled(false);
        ui->btn_OK->setEnabled(false);
        stt=0;
    }
    else if(stt==2)
    {
        QString a;
        a = ui->txt_FileName->text();
        QByteArray ba = a.toLocal8Bit();
        const char *str = ba.data();
        QString b = QString::number(Write((char*)str,am,sb));
        ui->label_2->setText(b);
        ui->txt_FileName->setEnabled(false);
        ui->btn_OK->setEnabled(false);
        stt=0;
    }
}

void MainWindow::on_btn_Xuat_clicked()
{

}


void MainWindow::on_btn_Add_clicked()
{

}


void MainWindow::on_btn_Nhap_clicked()
{
    ui->txt_Code->setEnabled(true);
    ui->txt_Name->setEnabled(true);
    ui->txt_Phone->setEnabled(true);
    ui->txt_Addr->setEnabled(true);
    ui->btn_OK_2->setEnabled(true);
}


void MainWindow::on_btn_OK_2_clicked()
{

    QString a;
    a = ui->txt_Code->text();
    QByteArray ba = a.toLocal8Bit();
    const char *str = ba.data();
    char temp[5];
    strncpy(temp,str,5);
    if(checkCode(temp)==true)
        ui->label_2->setText("Ma SB da ton tai!");
    else
    {
        strcpy(sb.ds[sb.n].code,temp);
        //ten
        a=ui->txt_Name->text();
        ba=a.toLocal8Bit();
        str=ba.data();
        char tmpName[50];
        strncpy(tmpName,str,50);
        strcpy(sb.ds[sb.n].name,tmpName);
        //dien thoai
        a=ui->txt_Phone->text();
        ba=a.toLocal8Bit();
        str=ba.data();
        char tmpPhone[12];
        strncpy(tmpPhone,str,12);
        strcpy(sb.ds[sb.n].phone,tmpPhone);
        //dia chi
        a=ui->txt_Addr->text();
        ba=a.toLocal8Bit();
        str=ba.data();
        char tmpAddr[100];
        strncpy(tmpAddr,str,100);
        strcpy(sb.ds[sb.n].addr,tmpAddr);
        sb.n++;
        am.n++;
        //khoi tao dong moi cho ma tran
        for(int i=0;i<am.n;i++)
            am.mt[am.n-1][i]=0;
        ui->label_2->setText("Them thanh cong!");
        drawTable(am);
        infoAirPort(sb);
    }
}


void MainWindow::on_btn_Write_clicked()
{
    stt=2;
    ui->txt_FileName->setEnabled(true);
    ui->btn_OK->setEnabled(true);
}

