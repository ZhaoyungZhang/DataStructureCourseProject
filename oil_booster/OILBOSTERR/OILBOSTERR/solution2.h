#pragma once

#include<bits/stdc++.h>
#include"graph.h"

using namespace std;


void solution2() {
	for (int i = 1; i <= 100; i++) {
		string iin = "C:\\Users\\12042\\Desktop\\dagData\\input\\input";
		iin += to_string(i) + ".in";
		string iout = "C:\\Users\\12042\\Desktop\\dagData\\output2\\";
		iout += to_string(i) + ".out";
		fin.open(iin);
		fout.open(iout);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "文件打开失败！\n";
		}

		DAG g;
		g.topsort();
		g.branch_bound();
		fout << g.best_ans << "\n";
		fin.close();
		fout.close();
		cout << "正在生成可视化图片 " << i << "\n";
		//g.visualize2(i);
		cout << "生成完毕\n";
	}
	cout << "正在进行进行对拍...\n";
	check();
}


void solution2_nojpg() {
	for (int i = 1; i <= 100; i++) {
		LARGE_INTEGER start_time; //开始时间
		LARGE_INTEGER end_time;   //结束时间
		double dqFreq;            //计时器频率
		LARGE_INTEGER freq;       //计时器频率
		QueryPerformanceFrequency(&freq);
		dqFreq = (double)freq.QuadPart;

		string iin = "C:\\Users\\12042\\Desktop\\dagData\\input\\input";
		iin += to_string(i) + ".in";
		string iout = "C:\\Users\\12042\\Desktop\\dagData\\output2\\";
		iout += to_string(i) + ".out";
		fin.open(iin);
		fout.open(iout);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "文件打开失败！\n";
		}
		QueryPerformanceCounter(&start_time); //计时开始

		DAG g;
		g.topsort();
		g.branch_bound();
		fout << g.best_ans << "\n";

		QueryPerformanceCounter(&end_time); //计时开始
		fin.close();
		fout.close();
		ofstream fo("cost2.txt", ios::app);
		double run_time = (end_time.QuadPart - start_time.QuadPart) / dqFreq * 1000;
		fo << i << " " << run_time << "\n";
		fo.close();

		//空间 第2种 分支定界
		ofstream foo("room2.txt", ios::app);
		//int 4     btnode   
		ll romcost = 32 * g.n + 4 * g.m;
		foo << i << " " << romcost << "\n";
		foo.close();

	}
}