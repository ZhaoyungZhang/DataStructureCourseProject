#include<bits/stdc++.h>
#include"graph.h"
#include"solution1.h"
#include"solution2.h"
using namespace std;

//性能分析
void test() {
	cout << "正在生成性能对比数据...\n";
	solution1_nojpg();
	solution2_nojpg();
	cout << "生成数据完成,对比结果已经展示在图表!\n";
	system("testtime.py");
	system("testroom.py");
}

void data1() {
	cout << "正在测试solution1(回溯)...\n";
	solution1();
	cout << "正在测试solution2(分支定界)...\n";
	solution2();
	

}
void data2()
{
	cout << "请输入 输入文件路径\n";
	string path; cin >> path;
	ifstream fin(path);
	DAG g;
	g.topsort();
	//g.backtracking(1, 0);
	g.branch_bound();
	cout << g.best_ans << "\n";//*/
	g.output_bst();

}
void data3()
{
	cout << "请输入数据:\n";
	DAG g;
	g.topsort();
	//g.backtracking(1, 0);
	g.branch_bound();
	cout << g.best_ans << "\n";//*/
	g.output_bst();
	
}

void welcome() {
	cout << "*****石油放大器网络*****\n";
	cout << "***DATA1 测试100个样例***\n";
	cout << "***DATA2 测试指定数据集***\n";
	cout << "***DATA3 手动输入数据测试***\n";
	while (1) {
		string op; cin >> op;
		if (op == "DATA1") {
			data1();
		}
		else if (op == "DATA2") {
			data2();
		}
		else if (op == "DATA3") {
			data3();
		}
		else {
			cout << "输入有无，请重新输入\n";
		}
	}
}

int main() {
	welcome();
	return 0;
}