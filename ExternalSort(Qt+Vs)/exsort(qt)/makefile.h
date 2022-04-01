#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include<fstream>
#include"minlosertree.h"
#include <bits/stdc++.h>
#include<QMessageBox>
using namespace std;

void make_num(long int max_n, ofstream &fout)
{
    fout << sizeof_file << endl;
    srand((unsigned)time(NULL));
    for (int i = 0; i < sizeof_file; i++)
        fout << rand()%max_n << " ";

    QMessageBox msgBox;
    msgBox.setText("The file has been Created!!! Go Sort!!!");
    msgBox.exec();
    return;
}
void make_file()
{//文件名字自己起
    //cout << "请输入文件的名字、数据量、最大值 例如：data10 10000 500000\n";
    //cin >> file_name; cin >> sizeof_file; cin >> max_n;
    string input_file = path + "\\" + file_name + ".txt";//输入文件
    std::ofstream fout(input_file);
    /*if (fout.is_open())
    {//文件不存在 新文件
       
    }
    else
    {//已有文件 不可以
        do
        {
            cout << "文件已经存在 请重新命名！" << endl;
            cin >> file_name;
            input_file = path + "\\" + file_name + ".txt";//输入文件
            fout.open(input_file,ios::_Noreplace);
        } while (!fout.is_open());
    }*/
    make_num(max_n, fout);
}


