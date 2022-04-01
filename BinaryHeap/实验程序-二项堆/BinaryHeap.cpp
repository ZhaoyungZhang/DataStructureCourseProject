#include"BinaryHeap.h"
#include<bits/stdc++.h>
using namespace std;


/*  返回关键字最小的节点
         O(logn)       */
template <typename K, typename V, typename Compare>
BinaryHeapNode<K,V>* BinaryHeap<K, V, Compare>::Find_Min()
{//最小的一定在根表上 扫描
	if (Root == NULL) {
		if(putflag)
			cout << "empty\n";
		else fout<< "empty\n";
		return NULL;
	}
	bnode* minPtr = NULL;
	bnode* scan = Root;
	K min_k = INT_MAX;
	while (scan != NULL) {
		if (compare(scan->key, min_k)) {
			min_k = scan->key;
			minPtr = scan;
		}
		scan = scan->sibiling;
	}
	return minPtr;
}


/*    合并两个二项堆
		 O(logn)       */
template <typename K, typename V, typename Compare>
void BinaryHeap<K,V,Compare>::Union(Bheap& Heap)
{//进行堆合并
	//先合并根表
	//判断非空
	/*if (Heap.Root == NULL) {
		return;
	} 
	if (Root == NULL) {
		Root = Heap.Root;
		Heap.Root = NULL;
		return;
	}*/

	Merge_Root(Heap);
	if (Root == NULL) {
		cout << "根表连接失败！\n";
		return;
	}
	//扫描指针
	bnode* prex = NULL;
	bnode* cur = Root;
	bnode* next = Root->sibiling;

	while (next != NULL) {//遍历每个二项树的根
		if ((cur->degree != next->degree) || (next->sibiling != NULL
			&& next->sibiling->degree == cur->degree)) {
			//当前树和下一棵树度不等， 或者三个连续的二项树度相等。
			//都是要指针迁移
			prex = cur; cur = next;
		}
		else if (compare(cur->key, next->key)) {
			//如果两棵树的度相等 且cur的根key 小
			cur->sibiling = next->sibiling;
			treeLink(next, cur);//next 作为 cur左孩子
		}
		else {//next key小 cur 作为next 的左孩子
			if (prex == NULL) Root = next;
			else
				prex->sibiling = cur->sibiling;
			treeLink(cur, next);
			cur = next;
		}
		next = cur->sibiling;
	}
}


/*    合并根表 度数非递减
		 O(logn)       
	                   */
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Merge_Root(Bheap& Heap)
{
	if (Heap.Root == NULL) {
		return;
	}
	if (Root == NULL) {
		Root = Heap.Root;
		Heap.Root = NULL;
		return;
	}
	//使用两个指针扫描
	bnode* pa = Root, *pb = Heap.Root, *tail = NULL;
	Root = NULL; Heap.Root = NULL;
	while (pa != NULL && pb != NULL) {
		//不断链接 until有一堆为空
		if (pa->degree <= pb->degree) {
			lineAtTail(tail, pa);//尾端插入
			pa = pa->sibiling;
		}
		else {
			lineAtTail(tail, pb);
			pb = pb->sibiling;
		}
	}
	//看那个还有剩下的
	if (pa != NULL) {
		tail->sibiling = pa;
	}
	else if (pb != NULL) {
		tail->sibiling = pb;
	}
	else {//都没剩下
		tail->sibiling = NULL;
	}

}


/*    插入一个新元素
		 O(logn)
					   */
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::insert(pair<K, V> x)
{
	/*if (check_exist(x)) {
		cout<< "该元素已经存在,禁止插入！\n";
		return;
	}*/
	size++;
	bnode* cur = new bnode(x);
	if (Root == NULL) Root = cur;
	else {
		Bheap H(cur, compare);
		Union(H);
	}
}


/*   从堆中删除最小/大 KEY元素，并且返回删除元素的指针
		 O(logn)
		返回pair指针			   */
template <typename K, typename V, typename Compare>
pair<K,V>* BinaryHeap<K, V, Compare>::Extract_Min()
{
	if (Root == NULL) {
		if(putflag)
			cout << "empty\n";
		else fout<< "empty\n";

		return NULL;
	}
	bnode* minptr = NULL, * pre = NULL, * cur = Root;
	K mink = Root->key;//初始 根即最值
	while (cur->sibiling != NULL) {//跟表上找最值
		if (compare(cur->sibiling->key, mink)) {
			mink = cur->sibiling->key;
			pre = cur;
		}
		cur = cur->sibiling;
	}
	if (pre == NULL) {//只有一个元素 或者根为所求
		minptr = Root;
		Root = Root->sibiling;
	}
	else {//否则 
		minptr = pre->sibiling;
		pre->sibiling = minptr->sibiling;
	}
	Bheap h(minptr->LeftChild, compare);//最小值 除去根的 堆
	h.reverse();
	Union(h);//再合并回去
	pair<K, V> rv = pair<K, V>(minptr->key, minptr->data);
	delete minptr;
	size--;
	return &rv;
}


/*对被删除的部分进行逆置 方便合并
		 O(logn)
						*/
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::reverse() {
	bnode* cur = Root,*rcur;
	Root = NULL;
	while (cur != NULL) {
		cur->parent = NULL;//第一层
		rcur = cur;
		cur = cur->sibiling;
		if (Root == NULL) {
			Root = rcur;
			rcur->sibiling = NULL;
		}
		else {
			rcur->sibiling = Root;
			Root = rcur;
		}
	}
}


/*    元素X关键字赋予新值(减小)
		 O(logn)
	                    */
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Decrease_Key(K oldkey, K newk)
{//赋值后 还需 调整本二项树

	if (!compare(newk, oldkey)) {
		if (putflag == 1)
			cout << "new key is greater! Refuse!\n";
		else fout << "new key is greater! Refuse!\n";
		return;
	}

	bnode* x = Find(Root,oldkey);
	if (x == NULL) {
		if(putflag == 1)
			cout << "not exist can't decrease!\n";
		else fout << "not exist can't decrease!\n";
		return;
	}
	
	x->key = newk;
	//只需要交换值就行了
	bnode* z = x->parent, * y = x;
	while (z != NULL && z->key > y->key) {
		swap(z->key, y->key);
		y = z;
		z = y->parent;
	}

	//bnode* par = x->parent, * xs = x->sibiling;
	//调整
	//while (par != NULL && compare(x->key, par->key)) {
	//	//从下向上
	//	//向上了 需要调整右兄弟
	//	x->sibiling = par->sibiling;
	//	par->sibiling = xs;
	//	//如果 X is 某层链中间
	//	bnode* x_pre=find_pre(x), *par_pre=find_pre(par);
	//	if (x_pre != NULL) {
	//		x_pre->sibiling = par;
	//	}
	//	if (par_pre != NULL) {
	//		par_pre->sibiling = x;
	//	}
	//	if (par->parent != NULL && par->parent->LeftChild == par) {
	//		par->parent->LeftChild = x;//如果 X换上去是最左孩子
	//	}
	//	//修改X 孩子
	//	bnode* x_child = x->LeftChild;
	//	if (x->parent->LeftChild == x) {//x是左孩子
	//		x->LeftChild = par;
	//	}
	//	else {
	//		x->LeftChild = par->LeftChild;
	//		par->LeftChild->parent = x;
	//	}
	//	x->parent = par->parent;
	//	par->parent = x;
	//	//修改par 孩子
	//	par->LeftChild = x_child;
	//	if (x_child != NULL) {
	//		x_child->parent = par;
	//	}
	//	swap(x->degree, par->degree);//交换度数
	//	par = x->parent;
	//}

}


/*    删除关键字为Key的节点
		 O(logn)+O(n)
						*/
template <typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Delete(K KEY)
{
	bnode* x = Find(Root,KEY);
	if (x == NULL) {
		if(putflag == 1)
			cout << "not exist! can't delete！\n";
		else 
			fout << "not exist! can't delete！\n";
		return ;
	}

	Decrease_Key(x->key, INT_MIN);
	Extract_Min();
	
}

template<typename K, typename V, typename Compare>
BinaryHeapNode<K, V>* BinaryHeap<K, V, Compare>::Find(bnode* t, K KEY)
{
	bnode* cur = t, * x = NULL;
	while (cur != NULL) {
		if (cur->key == KEY)
			return cur;
		else {
			x = Find(cur->LeftChild, KEY);
			if (x != NULL) {//递归找
				return x;
			}
			cur = cur->sibiling;
		}
	}
	return NULL;//没找到
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::Post(bnode* x)
{//后序遍历
	bnode* cur = x;
	while (cur != NULL) {
		Post(cur->LeftChild);
		cout << "key is " << cur->key << "\ndata is " << cur->data
			<< "\ndegree is " << cur->degree << "\n";
		cur = cur->sibiling;
	}
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::preTravel(bnode* x)
{//前序遍历
	bnode* cur = x;
	if (cur != NULL) {
		cout << "key is " << cur->key << "\ndata is " << cur->data
			<< "\ndegree is " << cur->degree << "\n";
		if (cur->LeftChild != NULL) {
			for (bnode* t = cur->LeftChild; t != NULL; t = t->sibiling) {
				preTravel(t);
			}
		}
	}
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::preT()
{
	for (bnode* t = Root; t != NULL; t = t->sibiling) {
		preTravel(t);
	}
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::levelTravel()
{//层次遍历
	queue< bnode* > q; q.push(Root);
	while (!q.empty()) {
		bnode* cur = q.front(); q.pop();
		bnode* t = cur;
		while (t->sibiling !=NULL)
		{
			q.push(t->sibiling);
			t = t->sibiling;
		}
		if (cur->LeftChild != NULL) q.push(cur->LeftChild);

		cout << "key is " << cur->key << "\ndata is " << cur->data
			<< "\ndegree is " << cur->degree << "\n";

	}
}

template<typename K, typename V, typename Compare>
bool BinaryHeap<K, V, Compare>::check_exist(pair<K,V> p)
{
	queue< bnode* > q; q.push(Root);
	while (!q.empty()) {
		bnode* cur = q.front(); q.pop();
		if (cur->key == p.first) {
			return true;
		}

		bnode* t = cur;
		while (t->sibiling != NULL)
		{
			q.push(t->sibiling);
			t = t->sibiling;
		}
		if (cur->LeftChild != NULL) q.push(cur->LeftChild);

	}
	return false;
}

template<typename K, typename V, typename Compare>
void BinaryHeap<K, V, Compare>::visualize(string filename) {
	//dot作图 先声明节点 然后指定颜色
	int i = -1;
	fstream fo(filename+".dot", ios::out);
	fo << "digraph g{" << "\n";
	bnode* r = Root;
	string str;
	if (r != NULL) {
		str += "{rank=\"same\";" + to_string(r->key) + ';';
	}
	while (r != NULL) {
		queue<bnode* > q;
		q.push(r);
		while (q.size()) {
			string ss= "{rank=\"same\";";
			bnode* e = q.front(); q.pop();
			bnode* child = e->LeftChild;
			while (child != NULL) {
				fo << e->key << "->" << child->key<< "[color = blue]";
				q.push(child);
				if (child->sibiling != NULL) {
					fo << ";\n";
				}
				else fo << "[weight=10][color=blue]; \n";
				ss += to_string(child->key) + ";";
				child = child->sibiling;
			}
			ss += "};\n";
			fo << ss << endl;
		}
		bnode* temp = r;
		r = r->sibiling;
		if (r != NULL) {
			fo << temp->key << "->" << r->key << "[color=blue];" << '\n' << endl;
			str += to_string(r->key) + ";";
		}
	}
	str += "};\n";
	fo << str << endl;
	if (i != -1)
		fo << i << "[label=\" dest: " << i << "\",style=filled, fillcolor=green]" << endl;
	fo << "}" << endl;
	string sss = "dot -Tjpg " + filename + ".dot -o " + filename + ".jpg";
	system(sss.c_str());
}
