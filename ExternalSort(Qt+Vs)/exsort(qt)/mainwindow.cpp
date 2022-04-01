#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include<QString>
#include"minlosertree.h"
#include"minlosertree.cpp"
#include"makefile.h"
#include"externalSorter.h"
#include<string>
#include<iostream>
#include<math.h>
#include<fstream>
#include<QMessageBox>
#include <QButtonGroup>
using namespace std;
QString res;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{//生成文件
    if(ui->radioButton->isChecked())
    {
        disk_times=0;
        path=ui->lineEdit->text().toStdString();
        file_name=ui->lineEdit_2->text().toStdString();
        max_n=ui->lineEdit_3->text().toInt();
        sizeof_file=ui->lineEdit_4->text().toInt();
        make_file();
    }
    else
    {
        disk_times=0;
        path=ui->lineEdit->text().toStdString();
        file_name=ui->lineEdit_2->text().toStdString();
        //max_n=ui->lineEdit_3->text().toInt();
        //sizeof_file=ui->lineEdit_4->text().toInt();

        QMessageBox msgBox;
        msgBox.setText("The file has been Ready!!! Go Sort!!!");
        msgBox.exec();
    }




}

void MainWindow::on_pushButton_2_clicked()
{//进行外排序
    disk_times = 0;
        max_run = 0;//看一共多少个顺串
        all_temps = 0;//临时文件

    int k;
    k=ui->lineEdit_6->text().toInt();
    sizeof_MM=ui->lineEdit_5->text().toInt();

    ff_name = path + "\\" + file_name;//用来命名文件
    string input_file = path + "\\" + file_name + ".txt";//输入文件
        fstream fin(input_file);
        if (!fin.is_open()) {
            QMessageBox msgBox;
            msgBox.setText("The file can't been opened!!!");
            msgBox.exec();
            return;
        }
    fin>>sizeof_file;
    Player* players = new Player[sizeof_MM + 1];
        for (int i = 1; i <= sizeof_MM; i++)
        {
            fin >> players[i].element;
            players[i].num = 1;//初始化
            disk_times++;
        }
        minLoserTree<Player> mt(players, sizeof_MM);

        res+=exsortt(mt,k, fin);
        res+="------------------------------";
        ui->textBrowser->setText(res);
}
