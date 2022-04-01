#include<iostream>
#include <fstream>
#include<sstream>
#include<cstdio>
#include"SKIPLIST.h"
#include"SKIPLIST.cpp"
#include<algorithm>
using namespace std;

void input_data(int i)
{
	FILE* stream1;
	string sin = "input_";
	string sout = "output_";
	char c = i + '0';
	sin += c;
	sout += c;
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	//fclose(stream1);
	freopen_s(&stream1, sout.c_str(), "w", stdout);
}

void input_datanon(int i)
{
	FILE* stream1;
	string sin = "ninput_";
	string sout = "noutput_";
	char c = i + '0';
	sin += c;
	sout += c;
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	freopen_s(&stream1, sout.c_str(), "w", stdout);
}

void input_data_db(int i)
{
	FILE* stream1;
	string sin = "dbinput_";
	string sout = "dboutput_";
	char c = i + '0';
	sin += c;
	sout += c;
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	freopen_s(&stream1, sout.c_str(), "w", stdout);
}

void input_data_any()
{//任意数据
	FILE* stream1;
	string sin, sout;;
	cout << "请输入txt文件路径！(如：d:\\123.txt (txt不需要输入))" << endl;
	cin >> sin;
	sout = sin+"-output";
	sin += ".txt";
	sout += ".txt";
	freopen_s(&stream1, sin.c_str(), "r", stdin);
	freopen_s(&stream1, sout.c_str(), "w", stdout);

}

bool cmp(int a, int b)
{
	return a > b;
}

void func1(string ans)
{
	int count = 10;
	cout << "是否需要中途进行重构  ？？？(0/1)" << endl;
	int flag = 0; cin >> flag;
	while (count)
	{
		int n, m;
		skipList<int, int> sl(1000000, 10000, 0.5);
		sl.need_reform = flag;
		if (ans == "Y")//初始化为严格跳表
		{
			input_data(--count);
			cin >> n >> m;//n为操作次数 m为初始化元素
			int* a = new int[m];//数组暂存
			for (int i = 0; i < m; i++)
			{
				cin >> a[i];
			}
			sort(a, a + m, cmp);//升序排
			sl.ideal_initial(a, m);
			cout << "初始化严格跳表如下 :" << endl;
			sl.output();
		}
		else
		{
			input_data(--count);
			cin >> n >> m;//n为操作次数 m为初始化元素
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl.insert(p);
				
			}
			cout << "-----------------------------------------------------" << endl;
			cout << "初始化非严格跳表如下 :" << endl;
			sl.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "所有元素异或和为 : ";
				sl.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "错误操作指令！请输入正确的操作指令以及数据！！！" << endl;
				break;
			}
			}
		}
	}
	
	
}

void func2( string ans)
{
	int count = 10;
	cout << "是否需要中途进行重构  ？？？(0/1)" << endl;
	int flag = 0; cin >> flag;
	while (count)
	{
		int n, m;
		skipList<int, int> sl(1000000, 10000, 0.5);
		sl.need_reform = flag;
		if (ans == "Y")//初始化为严格跳表
		{
			input_datanon(--count);
			cin >> n >> m;//n为操作次数 m为初始化元素
			int* a = new int[m];//数组暂存
			for (int i = 0; i < m; i++)
			{
				cin >> a[i];
			}
			sort(a, a + m, cmp);//升序排
			sl.ideal_initial(a, m);
			cout << "初始化严格跳表如下 :" << endl;
			sl.output();
		}
		else
		{
			input_datanon(--count);
			cin >> n >> m;//n为操作次数 m为初始化元素
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl.insert(p);

			}
			cout << "-----------------------------------------------------" << endl;
			cout << "初始化非严格跳表如下 :" << endl;
			sl.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "所有元素异或和为 : ";
				sl.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "错误操作指令！请输入正确的操作指令以及数据！！！" << endl;
				break;
			}
			}
		}
	}
	//cout << "输入成功 请查看文件！！！" << endl;

}

void func3()
{
	int n, m;
	string ans;
	cout << "请输入操作次数 元素个数 " << endl;
	cin >> n >> m;//n为操作次数 m为初始化元素
	cout << "是否需要初始化为严格跳表？？(Y/N)" << endl;
	cin >> ans;
	skipList<int, int> sl(1000000, 10000, 0.5);
	cout << "是否需要中途进行重构  ？？？(0/1)" << endl;
	int flag = 0; cin >> flag;
	sl.need_reform = flag;
	cout << "请输入 "<<m<<" 个数据" << endl;
	if (ans == "Y")//初始化为严格跳表
	{
		int* a = new int[m];//数组暂存
		for (int i = 0; i < m; i++)
		{
			cin >> a[i];
		}
		sort(a, a + m, cmp);//升序排
		sl.ideal_initial(a, m);
		cout << "初始化严格跳表如下 :" << endl;
		sl.output();
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			int temp;
			cin >> temp;
			pair<int, int> p = make_pair(temp, temp);
			sl.insert(p);
		}
		cout << "-----------------------------------------------------" << endl;
		cout << "初始化非严格跳表如下 :" << endl;
		sl.output();
		cout << "-----------------------------------------------------" << endl;
	}
	//op n次 不是n-1次
	for (int i = 0; i < n; i++)
	{
		cout << "请选择 要进行的操作 : " << endl;
		cout << "还有 " << n - i << " 次操作" << endl;
		cout << "op 1 : 查找某元素 " << endl;
		cout << "op 2 : 插入元素" << endl;
		cout << "op 3 : 删除元素" << endl;
		cout << "op 4 : 删除最小元素 " << endl;
		cout << "op 5 : 删除最大元素" << endl;
		cout << "op 6 : 输出所有元素异或和" << endl;
		int op;
		cin >> op;
		int num;
		switch (op)
		{
		case 1:
		{
			cout << "请输入要查找的元素" << endl;
			cout << "---------------------------------------------------------\n";
			cin >> num;
			sl.find(num);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 2:
		{
			cout << "请输入要插入的元素" << endl;
			cout << "---------------------------------------------------------\n";
			cin >> num;
			pair<int, int> p = make_pair(num, num);
			sl.insert(p);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 3:
		{
			cout << "请输入要删除的元素" << endl;
			cin >> num;
			sl.erase(num);
			break;
		}
		case 4:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_min();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 5:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_max();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 6:
		{
			cout << "---------------------------------------------------------\n";
			cout << "所有元素异或和为 : ";
			sl.op_xor();
			cout << "---------------------------------------------------------\n";
			break;
		}
		default:
		{
			cout << "错误操作指令！请输入正确的操作指令以及数据！！！" << endl;
			break;
		}
		}
	}
}

void func4(string ans)
{//输入的每个数据集 每次输入两边 第一次是带重构 第二次不带
	int count = 10;
	cout << "进行对比，第一次不重构，第二次重构！！！" << endl;

	while (count)
	{
		int n, m;
		skipList<int, int> sl(1000000, 10000, 0.5);
		skipList<int, int> sl2(1000000, 10000, 0.5);
		sl.need_reform = 0;
		sl2.need_reform = 1;
		if (ans == "Y")//初始化为严格跳表
		{
			input_data_db(--count);
			cin >> n >> m;//n为操作次数 m为初始化元素
			int* a = new int[m];//数组暂存
			for (int i = 0; i < m; i++)
			{
				cin >> a[i];
			}
			sort(a, a + m, cmp);//升序排
			sl.ideal_initial(a, m);
			cout << "初始化严格跳表如下 :" << endl;
			sl.output();
		}
		else
		{
			input_data_db(--count);
			cin >> n >> m;//n为操作次数 m为初始化元素
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl.insert(p);

			}
			cout << "-----------------------------------------------------" << endl;
			cout << "初始化非严格跳表如下 :" << endl;
			sl.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "所有元素异或和为 : ";
				sl.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "错误操作指令！请输入正确的操作指令以及数据！！！" << endl;
				break;
			}
			}
		}
		cout << "不重构的时间如下：\n";
		sl.analyse();
		if (ans == "Y")//初始化为严格跳表
		{
			int* b = new int[m];//数组暂存
			for (int i = 0; i < m; i++)
			{
				cin >> b[i];
			}
			sort(b, b + m, cmp);//升序排
			sl2.ideal_initial(b, m);
			cout << "初始化严格跳表如下 :" << endl;
			sl2.output();
		}
		else
		{
			for (int i = 0; i < m; i++)
			{
				int temp;
				cin >> temp;
				pair<int, int> p = make_pair(temp, temp);
				sl2.insert(p);

			}
			cout << "-----------------------------------------------------" << endl;
			cout << "初始化非严格跳表如下 :" << endl;
			sl2.output();
			cout << "-----------------------------------------------------" << endl;
		}
		//op
		for (int i = 0; i < n - 1; i++)
		{
			int op;
			cin >> op;
			int num;
			switch (op)
			{
			case 1:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				sl2.find(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				cout << "---------------------------------------------------------\n";
				cin >> num;
				pair<int, int> p = make_pair(num, num);
				sl2.insert(p);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 3:
			{
				cin >> num;
				cout << "---------------------------------------------------------\n";
				sl2.erase(num);
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 4:
			{
				cout << "---------------------------------------------------------\n";
				sl2.erase_min();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 5:
			{
				cout << "---------------------------------------------------------\n";
				sl2.erase_max();
				cout << "---------------------------------------------------------\n";
				break;
			}
			case 6:
			{
				cout << "---------------------------------------------------------\n";
				cout << "所有元素异或和为 : ";
				sl2.op_xor();
				cout << "---------------------------------------------------------\n";
				break;
			}
			default:
			{
				cout << "错误操作指令！请输入正确的操作指令以及数据！！！" << endl;
				break;
			}
			}
		}
		cout << "重构的时间如下：\n";
		sl2.analyse();
	}
}

void func5(string ans)
{
	cout << "是否需要中途进行重构  ？？？(0/1)" << endl;
	int flag = 0; cin >> flag;

	int n, m;
	skipList<int, int> sl(1000000, 10000, 0.5);
	sl.need_reform = flag;
	if (ans == "Y")//初始化为严格跳表
	{
		input_data_any();
		cin >> n >> m;//n为操作次数 m为初始化元素
		int* a = new int[m];//数组暂存
		for (int i = 0; i < m; i++)
		{
			cin >> a[i];
		}
		sort(a, a + m, cmp);//升序排
		sl.ideal_initial(a, m);
		cout << "初始化严格跳表如下 :" << endl;
		sl.output();
	}
	else
	{
		input_data_any();
		cin >> n >> m;//n为操作次数 m为初始化元素
		for (int i = 0; i < m; i++)
		{
			int temp;
			cin >> temp;
			pair<int, int> p = make_pair(temp, temp);
			sl.insert(p);

		}
		cout << "-----------------------------------------------------" << endl;
		cout << "初始化非严格跳表如下 :" << endl;
		sl.output();
		cout << "-----------------------------------------------------" << endl;
	}
	//op
	for (int i = 0; i < n - 1; i++)
	{
		int op;
		cin >> op;
		int num;
		switch (op)
		{
		case 1:
		{
			cout << "---------------------------------------------------------\n";
			cin >> num;
			sl.find(num);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 2:
		{
			cout << "---------------------------------------------------------\n";
			cin >> num;
			pair<int, int> p = make_pair(num, num);
			sl.insert(p);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 3:
		{
			cin >> num;
			cout << "---------------------------------------------------------\n";
			sl.erase(num);
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 4:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_min();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 5:
		{
			cout << "---------------------------------------------------------\n";
			sl.erase_max();
			cout << "---------------------------------------------------------\n";
			break;
		}
		case 6:
		{
			cout << "---------------------------------------------------------\n";
			cout << "所有元素异或和为 : ";
			sl.op_xor();
			cout << "---------------------------------------------------------\n";
			break;
		}
		default:
		{
			cout << "错误操作指令！请输入正确的操作指令以及数据！！！" << endl;
			break;
		}
		}
	}

}


void welcome()
{
	while (1)
	{
		string ans;//问答
		cout << "*****************************************************" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "请选择 输入数据方式:" << endl;
		cout << "option 1 : 输入十个重复数据集合" << endl;
		cout << "option 2 : 输入十个不重复数据集合" << endl;
		cout << "option 3 : 自己输入数据" << endl;
		cout << "option 4 : 输入十个数据集合进行重构对比" << endl;
		cout << "option 5 : 输入指定路径的数据" << endl;
		cout << "quit  (q): 退出" << endl;
		cin >> ans;
		if (ans == "1")
		{
			cout << "是否需要初始化为严格跳表？？(Y/N)" << endl;
			cin >> ans;
			func1(ans);
		}
		else if (ans == "2")
		{
			int num = 0;
			cout << "是否需要初始化为严格跳表？？(Y/N)" << endl;
			cin >> ans;
			func2(ans);
		}
		else if (ans == "3")
		{
			func3();
		}
		else if (ans == "4")
		{
			cout << "是否需要初始化为严格跳表？？(Y/N)" << endl;
			cin >> ans;
			func4(ans);
		}
		else if (ans == "5")
		{
			cout << "是否需要初始化为严格跳表？？(Y/N)" << endl;
			cin >> ans;
			func5(ans);
		}
		else if (ans == "q")
		{
			cout << "退出成功！" << endl;
			break;
		}
		else
		{
			cout << "错误操作指令！请输入正确的操作指令！！！" << endl;
			break;
		}
		cout << "*****************************************************" << endl;

	}
}


//综合 
int main()
{
	welcome();//显示欢迎界面并且提供操作提示
	
	return 0;
}



//
////理想化初始
//int main()
//{
//	FILE* stream1;
//	freopen_s(&stream1, "input_1.txt", "r", stdin);
//	freopen_s(&stream1, "output_1.txt", "w", stdout);
//	int n, m;
//	cin >> n >> m;//n为操作次数 m为初始化元素
//	skipList<int, int> sl(1000000, 10000, 0.5);
//	int* a = new int[m];//数组暂存
//	for (int i = 0; i < m; i++)
//	{
//		cin >> a[i];
//	}
//	sort(a, a + m,cmp);//升序排
//	sl.ideal_initial(a,m);
//	cout << "理想化后的跳表:" << endl;
//	sl.output();
//
//
//
//
//	return 0;
//}

//对比重构的价值
//int main()
//{
//	//FILE* stream1;
//	//freopen_s(&stream1, "input_11.txt", "r", stdin);
//	//freopen_s(&stream1, "output_11.txt", "w", stdout);
//	int n, m;
//	cin >> n >> m;//n为操作次数 m为初始化元素
//	skipList<int, int> sl(1000000, 10000, 0.5);
//	for (int i = 0; i < m; i++)
//	{
//		int temp;
//		cin >> temp;
//		pair<int, int> p = make_pair(temp, temp);
//		sl.insert(p);
//	}
//	cout << "未重构 直接插入的跳表为:" << endl;
//	sl.output();
//
//	sl.reform();
//	cout << "重构的跳表为:" << endl;
//	sl.output();
//
//	//for (int i = 0; i < n - 1; i++)
//	//{
//	//	int op;
//	//	cin >> op;
//	//	int num;
//	//	switch (op)
//	//	{
//	//	case 1:
//	//	{
//	//		cin >> num;
//	//		sl.find(num);
//	//		break;
//	//	}
//	//	case 2:
//	//	{
//	//		cin >> num;
//	//		pair<int, int> p = make_pair(num, num);
//	//		sl.insert(p);
//	//		break;
//	//	}
//	//	case 3:
//	//	{
//	//		cin >> num;
//	//		sl.erase(num);
//	//		break;
//	//	}
//	//	case 4:
//	//	{
//	//		sl.erase_min();
//	//		break;
//	//	}
//	//	case 5:
//	//	{
//	//		sl.erase_max();
//	//		break;
//	//	}
//	//	case 6:
//	//	{
//	//		cout << "所有元素异或和为： ";
//	//		sl.op_xor();
//	//		break;
//	//	}
//	//	default:
//	//		break;
//	//	}
//	//}
//	//sl.reform();
//	//cout << "重构的跳表为:" << endl;
//	//sl.output();
//	//cout << "重构后相同操作：" << endl;
//	//for (int i = 0; i < n - 1; i++)
//	//{
//	//	int op;
//	//	cin >> op;
//	//	int num;
//	//	switch (op)
//	//	{
//	//	case 1:
//	//	{
//	//		cin >> num;
//	//		sl.find(num);
//	//		break;
//	//	}
//	//	case 2:
//	//	{
//	//		cin >> num;
//	//		pair<int, int> p = make_pair(num, num);
//	//		sl.insert(p);
//	//		break;
//	//	}
//	//	case 3:
//	//	{
//	//		cin >> num;
//	//		sl.erase(num);
//	//		break;
//	//	}
//	//	case 4:
//	//	{
//	//		sl.erase_min();
//	//		break;
//	//	}
//	//	case 5:
//	//	{
//	//		sl.erase_max();
//	//		break;
//	//	}
//	//	case 6:
//	//	{
//	//		cout << "所有元素异或和为： ";
//	//		sl.op_xor();
//	//		break;
//	//	}
//	//	default:
//	//		break;
//	//	}
//	//}
//	return 0;
//}

//不交互 输出到文件
//int main()
//{
//	int count = 10;
//	while (count)
//	{
//		input_data(--count);
//		int n, m;
//		cin >> n >> m;//n为操作次数 m为初始化元素
//		skipList<int, int> sl(1000000, 10000, 0.5);
//		for (int i = 0; i < m; i++)
//		{
//			int temp;
//			cin >> temp;
//			pair<int, int> p = make_pair(temp, temp);
//			sl.insert(p);
//		}
//		for (int i = 0; i < n - 1; i++)
//		{
//			int op;
//			cin >> op;
//			int num;
//			switch (op)
//			{
//			case 1:
//			{
//				cin >> num;
//				sl.find(num);
//				break;
//			}
//			case 2:
//			{
//				cin >> num;
//				pair<int, int> p = make_pair(num, num);
//				sl.insert(p);
//				break;
//			}
//			case 3:
//			{
//				cin >> num;
//				sl.erase(num);
//				break;
//			}
//			case 4:
//			{
//				sl.erase_min();
//				break;
//			}
//			case 5:
//			{
//				sl.erase_max();
//				break;
//			}
//			case 6:
//			{
//				cout << "所有元素异或和为： ";
//				sl.op_xor();
//				break;
//			}
//			default:
//				break;
//			}
//		}
//		sl.analyse();
//		
//	}
//	return 0;
//}

