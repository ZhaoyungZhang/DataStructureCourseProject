#pragma once
#include<iostream>
#include<sstream>
#include<cstdio>
//允许重复
using namespace std;
class illegalValue
{
public:
	illegalValue(string m = "the value is illegal !") :message(m) {}
	void output() { cerr << message; }
private:
	string message;
};

template <class K, class E>
struct skipNode
{
	typedef pair<K, E> pairType;

	pairType element;
	skipNode<K, E>** next;//指针数组
	int lsize;//链表级
	skipNode(pairType& thePair, int size)
		:element(thePair) {
		lsize = size-1;
		next = new skipNode<K, E> * [size];
	}
};

template<class K, class E>
class skipList
{
public:
	bool empty()const { return dSize == 0; }//o(1)
	int size() const { return dSize; }
	skipList(K largekey, int maxPairs = 10000, float prob = 0.5);
	pair< K, E>* find(K& thekey);
	int level() const;
	skipNode<K, E>* search(K& theKey,int &count);//search复杂度 O(log2 n)
	void insert(pair< K, E>& thePair);//插入复杂度 先search O(logn)+ 改指针 +O(thelevel)
	void erase(K& theKey);//删除 先search O(logn)+ 改指针 +O(levels)
	void output();
	void erase_min();//O(minlevel)
	void erase_max();//o(log n)+erase 
	void op_xor();
	void reform();//重构
	//初始化为严格跳表
	void ideal_initial(int *a,int m);
	void get_level(int *b, int level, int low, int high);
	void check(int count);
	//void display();//对跳表进行简单地可视化表现
	void analyse();//进行分析
	int need_reform = 1;//默认需要重构
private:
	float cutoff;//用来确定层数
	int levels; //当前最大的非空链表
	int dSize; //字典的数对个数
	int maxlevel;//允许的最大链表层数
	K tailKey; //最大关键字
	skipNode<K, E>* headerNode; //头结点指针
	skipNode<K, E>* tailNode;//为节点指针
	skipNode<K, E>** last;//指针 数组  每个数组项为一个指针 last[i] 指向 i层最后一个节点
	//last[i] 表示i层最后节点
	
};

