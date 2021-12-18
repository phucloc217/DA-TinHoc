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

//Ghi một ma trận kề lên file văn bản.
int Write(char* filename, AdjacencyMatrix g, AirPortList a)
{
    FILE* f;
    fopen_s(&f, filename, "wt");
    if (f == NULL) return 0;
    fprintf(f, "%d", g.n);
    for (int i = 0; i < a.n; i++)
    {
        fprintf(f, "\n");
        fprintf(f, a.ds[i].code);
        fprintf(f, "\n");
        fprintf(f, a.ds[i].name);
        fprintf(f, "\n");
        fprintf(f, a.ds[i].phone);
        fprintf(f, "\n");
        fprintf(f, a.ds[i].addr);
    }

    for (int i = 0; i < g.n; i++)
    {
        fprintf(f, "\n");
        for (int j = 0; j < g.n; j++)
            fprintf(f, "%d\t", g.mt[i][j]);
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

