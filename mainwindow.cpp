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

bool checkCode(char* code)
{

}

void MainWindow::on_btn_OK_2_clicked()
{


}


void MainWindow::on_btn_Write_clicked()
{

}

