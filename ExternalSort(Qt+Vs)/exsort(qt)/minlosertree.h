#pragma once
#include<iostream>
#include<math.h>
#include<fstream>
#include<cstdio>
#include<vector>
#include<map>
using namespace std;

static long int sizeof_MM;//内存空间能容纳的元素数
static string path;//要外排序的文件路径 例如: F:\vscpp\EXSORT\EXSORT
static string file_name;//排序的文件名称
static long int sizeof_file;//外排序文件的数字个数
static string ff_name;//用来输入输出
static int max_run = 0;//看一共多少个顺串
static int all_temps = 0;//临时文件
static int buffer_size = 100;//合并时输出的
static int page_size;
static int page_num;
static int disk_times;//磁盘访问次数
static int max_n;

struct Player
{//选手
	int element;//元素值 
	int num;//顺串号
	//bool operator<(const Player &p1)
	//{//先看顺串号再看元素
	//	return (num != p1.num) ? (num < p1.num) : (element < p1.element);
	//}
	bool operator<=(const Player& p1)
	{//先看顺串号再看元素
		return (num != p1.num) ? (num < p1.num) : (element < p1.element);
	}
	Player& operator=(const Player& p)
	{
		num = p.num;
		element = p.element;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Player& p) {
		out << p.element;
		return out;
	};
};

class illegalParameterValue
{
public:illegalParameterValue(string s = "value is not legal") :message(s) {};
	  void output() { cout << message; }
private:
	string message;
};

template<class T>
class minLoserTree
{
public:
	minLoserTree(T* ThePlayers = NULL, int n = 0);
	~minLoserTree() { delete[] tree; delete[] edges; }

	void initialize(T* thePlayer,
		int theNumberOfPlayers);
	void play_once(int p, int leftChild, int rightChild);
	int winner(int x, int y) //返回更小的元素下标
	{ //winner 入边 
		return players[x] <= players[y] ? x : y;
	};
	int loser(int x, int y)//返回更大的元素下标
	{//loser 入内部节点
		return players[x] <= players[y] ? y : x;
	};
	void replay(int thePlayer);//重构
	void output();
	void maintain() { tree[0] = edges[1]; };//维护tree[0]
	long long int top() {//返回最小的tree[0]
		return tree[0];
	};
	void make_run(fstream& fin);
	//void make_run1(fstream& fin);
	//void adjust(int pos,int k,int level);//传入位置 r1 2 4  
	//void clear();//清空
	void merge_K(int k, int sta, int level);

	void get_total() {
		totals = 0;
		if (max_run % kk == 0) {
			int temp = max_run / kk; totals += temp;
			while (temp != 1)
			{
				temp /= kk;
				totals += temp;
			}
		}
		else
		{
			int temp = max_run / kk; totals += temp; totals++;
			while (temp != 0)
			{
				temp /= kk;
				totals += temp;
				totals++;
			}
		}
	};
	int kk;				  // K
private:
	T* players;//元素数组
	int* edges;//边上的晋级的元素
	int numberofPlayers;//总共多少参赛者
	int* tree;//专门记录内部节点，tree[0]用来记录最后的输者
	int lowExt;           // lowest-level external nodes
	int offset;           // 2^log(n-1) - 1
	int totals = 0;           //K路合并总共多少 S

};
