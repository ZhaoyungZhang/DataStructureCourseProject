#pragma once
#include<bits/stdc++.h>
using namespace std;

//允许重复值，如果多个重复的数据的话，就只对第一个进行操作。
//二项堆节点 兄弟父亲链表 组织结构
template < typename K, typename V>
struct BinaryHeapNode
{
	BinaryHeapNode* parent;
	BinaryHeapNode* LeftChild;
	BinaryHeapNode* sibiling;
	int degree;
	K key;//值
	V data;//堆应该是个维护字典的结构

	//默认构造
	BinaryHeapNode() {
		parent = LeftChild = sibiling = NULL;
		degree = 0; key = data = INT_MIN; //毕竟是要排序
	}
	BinaryHeapNode(pair<K,V> p) {
		parent = LeftChild = sibiling = NULL;
		degree = 0; key = p.first; data = p.second;//毕竟是要排序
	}
	//copy 构造
	BinaryHeapNode(BinaryHeapNode& bhn) {
		parent = bhn.parent;
		LeftChild = bhn.LeftChild;
		sibiling = bhn.sibiling;
		degree = bhn.degree;
		key = bhn.key;
		data = bhn.data;
	}
	//构造
	BinaryHeapNode(BinaryHeapNode* p, BinaryHeapNode* lc,
		BinaryHeapNode* sib, int deg, K k,V d) {
		parent = p;
		LeftChild = lc;
		sibiling = sib;
		degree = deg;
		key = k;
		data = d;
	}
	//重载等号
	BinaryHeapNode& operator=(BinaryHeapNode& bhn) {
		if (&bhn == this) {//排除
			return *this;
		}
		delete this->parent;
		delete this->LeftChild;
		delete this->sibiling;
		this->parent = bhn.parent;
		this->LeftChild = bhn.LeftChild;
		this->sibiling = bhn.sibiling;
		this->degree = bhn.degree;
		this->key = bhn.key;
		this->key = bhn.data;
		return *this;
	}
	//重载<号
	bool operator<(const BinaryHeapNode& bhn) {
		return this->key < bhn.key;
	}

}; 




//适配！！！  还定义了比较方法 可以最大堆！
template <typename K, typename V, typename Compare = less<K> >
class BinaryHeap 
{
public:
	//简化 一个是Bnode 一个是Bheap
	typedef BinaryHeapNode<K, V>	bnode;
	typedef BinaryHeap			Bheap;
	ofstream fout;
	ifstream fin;
	string inname;
	string outname;
	int putflag;
private:
	bnode* Root;//根节点，最小值节点
	Compare compare;//键比较器，默认小于，为最小堆!
	int heap_degree;
	int size;
	

public:
	BinaryHeap(bnode* h, Compare c = Compare()) 
		:Root(h), compare(c), heap_degree(0),size(0), putflag(1) {}
	BinaryHeap(Compare c = Compare())
		:Root(nullptr), compare(c), heap_degree(0), size(0), putflag(1) {}
	BinaryHeap(string inn, string outn, Compare c = Compare())
	{
		Root = nullptr; compare = c; heap_degree = 0; size = 0;
		outname = outn;
		inname = inn;
		fout.open(outname);
		fin.open(inname);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "文件打开失败!\n";
			return;
		}
	}
	void Make_Heap(Compare c = Compare()) {
		Root = NULL; compare = c;
		heap_degree = 0; size = 0;
	}//初始化一个空堆

	void setcompare(Compare c) {
		compare = c;
	}
	void lineAtTail(bnode *&tail,bnode *cur) {//尾端插入 
		if (Root == NULL) {
			Root = cur;
			tail = cur;
		}
		else {
			tail->sibiling = cur;
			tail = tail->sibiling;
		}
	}
	void treeLink(bnode* l, bnode* r)
	{//进行两颗等度数的二项树链接
		l->parent = r;
		l->sibiling = r->LeftChild;
		r->LeftChild = l;
		r->degree ++;
	}
	bnode* find_pre(bnode* cur) {//插找某节点的 左兄弟
		bnode* pre = NULL;
		if (cur->parent == NULL) 
			pre = Root;
		else if (cur->parent->LeftChild == cur) {//无前驱
			return pre;
		}
		else pre = cur->parent->LeftChild;
		while (pre->sibiling != cur) {
			pre = pre->sibiling;
		}
		return pre;
	}
	bool check_exist(pair<K, V> p);

	BinaryHeapNode<K,V>* Find_Min();//返回一个指向最小关键字元素的指针
	BinaryHeapNode<K, V>* Find(bnode* t,K KEY);//找到关键字K的指针

	void Union(Bheap& Heap);//与堆H合并，合并的结果保存在当前堆中,H变为空
	void Merge_Root(Bheap& Heap);//合并根表

	void reverse();//逆置 用于删除

	void insert(pair<K,V> x);//插入元素X
	void push(pair<K, V> x) { insert(x); }


	pair<K, V>* Extract_Min();//从堆中删除最小关键字元素，并返回指向删除元素的指针
	void pop() {
		Extract_Min();
	}
	void top() {
		Find_Min();
	}

	void Decrease_Key(K oldkey, K newk);//将元素X的关键字赋予新值K
	
	void Delete(K KEY);//从堆中删除元素X

	void Post(bnode* x);//后序遍历
	void preTravel(bnode* x);//前序遍历
	void preT();//前序遍历
	void levelTravel();//层次遍历

	void outputPost() { Post(Root); }
	void outputpre() { preT(); };
	
	void visualize(string filename);

	//优先队列里面 应该只用到insert Extract MIN FINDmin FIND Delete  Decrease_Key
};
