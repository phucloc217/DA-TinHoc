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

//Đọc một ma trận kề từ file văn bản.
int Read(char* filename, AdjacencyMatrix& g, AirPortList& a)
{
    FILE* f;
    fopen_s(&f, filename, "rt");
    if (f == NULL) return 0;
    fscanf_s(f, "%d", &g.n);
    a.n = g.n;
    int i = 0;
    char tmp[5];
    fgets(tmp, 5, f);
    for (i = 0; i < a.n; i++)
    {
        fgets(a.ds[i].code, 5, f);
        xoaXuongDong(a.ds[i].code);
        fgets(a.ds[i].name, 50, f);
        xoaXuongDong(a.ds[i].name);
        fgets(a.ds[i].phone, 12, f);
        xoaXuongDong(a.ds[i].phone);
        fgets(a.ds[i].addr, 100, f);
        xoaXuongDong(a.ds[i].addr);
    }

    for (i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
        {
            fscanf_s(f, "%d", &g.mt[i][j]);
        }
    fclose(f);
    return 1;
}

void MainWindow::on_btn_Read_clicked()
{

}


void MainWindow::on_btn_OK_clicked()
{

}

void MainWindow::on_btn_Xuat_clicked()
{

}


void MainWindow::on_btn_Add_clicked()
{

}


void MainWindow::on_btn_Nhap_clicked()
{

}


void MainWindow::on_btn_OK_2_clicked()
{


}


void MainWindow::on_btn_Write_clicked()
{

}

