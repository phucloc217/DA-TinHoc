#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "struct.h"
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_Read_clicked();
    void on_btn_OK_clicked();


    void on_btn_Xuat_clicked();

    void on_btn_Add_clicked();

    void on_btn_Nhap_clicked();

    void on_btn_OK_2_clicked();

    void on_btn_Write_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
