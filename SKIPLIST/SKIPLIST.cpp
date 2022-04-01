#include<iostream>
#include<sstream>
#include<cstdio>
#include<math.h>
#include"SKIPLIST.h"
#include<algorithm>
using namespace std;

static double find_nums=0;
static double find_times = 0;

static double insert_nums=0;
static double insert_times = 0;

static double erase_nums=0;
static double erase_times = 0;
//find search insert erase 最大复杂度O(maxlevel+n)
//					平均复杂度O(log2 n)
//
//erase min O（1）
//erase max O (n)
//xor		O(n)
//重构条件：进行插入或者删除或者查找时 count次数>n
//重构复杂度：

template<class K, class E>
skipList<K, E>::skipList(K largekey, int maxPairs, float prob)
{//构造函数 关键字小于largekey 且数对个数size最多为maxpairs 0<prob<1
	cutoff = prob * RAND_MAX;
	maxlevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;//初始化级数
	dSize = 0;
	tailKey = largekey;

	//生成头,tail结点,last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxlevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E> * [maxlevel + 1];
	//链表为空时，任意级链表中的头节点都指向尾节点
	for (int i = 0; i <= maxlevel; i++)
	{
		headerNode->next[i] = tailNode;
	}
}

template<class K, class E>
pair< K, E>* skipList<K, E>::find(K& theKey)
{//返回匹配的数对的指针
//如果没有匹配的数对，返回NULL
	find_times++;
	if (theKey >= tailKey)
		return NULL;//无匹配数对
	//位置beforeNode是关键字为theKey的节点之前的最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	int count = 0;
	for (int i = levels; i >= 0; i--)
	{//跟踪i级指针
		while (beforeNode->next[i]->element.first < theKey)
		{
			count++;
			beforeNode = beforeNode->next[i];
		}
	}
	//检查下一个节点的关键字是否是theKey

	if (beforeNode->next[0]->element.first == theKey)
	{
		
		count++;
		cout << "find "<< theKey<<" 进行了 " << count << "次元素比较";
		cout << "  结果为: YES\n";
		check(count);
		find_nums += count;
		return &beforeNode->next[0]->element;
	}
	cout << "find " << theKey << " 进行了 " << count << "次元素比较";
	cout << "  结果为: NO\n";
	check(count);
	find_nums += count;
	return NULL;//无匹配的
}

template<class K, class E>
int skipList<K, E>::level() const
{//返回一个表示链表级的随机数，这个数不大于maxlevel
	int lev = 0;
	while (rand() <= cutoff)
	{
		lev++;
	}
	return (lev <= maxlevel) ? lev : maxlevel;
}
template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(K& theKey,int &count)
{//搜索关键字theKey，把每一集链表中要查看的最后一个节点存储在数组last中
//返回包含关键字thekey的节点
	//位置beforenode是关键字thekey的节点之前的最后一个节点

	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		count++;
		while (beforeNode->next[i]->element.first < theKey)
		{
			count++;
			beforeNode = beforeNode->next[i];
		}
		last[i] = beforeNode;//最后一级链表i的节点
	}
	//cout << "erase 进行了 " << count++ << "次元素比较" << endl;
	return beforeNode->next[0];
}

template<class K, class E >
void skipList<K, E>::insert(pair< K, E>& thePair)
{//把数对pair插入字典 覆盖关键字相同 存在的数对
	insert_times++;
	if (thePair.first >= tailKey)
	{
		ostringstream s;
		s << "Key = " << thePair.first << "Must be <" << tailKey;
		throw illegalValue(s.str());
	}
	int count = 0;
	//查看关键字为thekey的数对是否已经存在
	skipNode<K, E>* theNode = search(thePair.first,count);
	if (theNode->element.first == thePair.first)
	{//存在 更新
		int theLevel = level(); //新节点的级
		//使级theLevel 为 <=levels+1
		if (theLevel > levels)
		{
			theLevel = ++levels;
			last[theLevel] = headerNode;
		}

		//在节点Node后插入新节点
		skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
		for (int i = 0; i <= theLevel; i++)
		{//插入i级链表
			newNode->next[i] = last[i]->next[i];
			last[i]->next[i] = newNode;
		}
		dSize++;
		cout << "insert " << thePair.first << " 进行了 " << count << "次元素比较" << endl;
		check(count);
		insert_nums += count;
		return;
	}

	//不存在 则确定新节点所在的级链表
	int theLevel = level(); //新节点的级
	//使级theLevel 为 <=levels+1
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	//在节点Node后插入新节点
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{//插入i级链表
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;
	cout << "insert "<<thePair.first<<" 进行了 " << count << "次元素比较" << endl;
	insert_nums += count;
	check(count);
	return;
}

template<class K, class E >
void skipList<K, E>::erase(K& theKey)
{//删除
	erase_times++;
	int count = 1;
	if (theKey >= tailKey)
		return;

	//查看是否有匹配的
	skipNode<K, E>* theNode = search(theKey,count);
	count++;
	if (theNode->element.first != theKey)//不存在
	{
		cout << "erase " << theKey << " 失败，跳表中无该元素！！！" << endl;
		erase_nums+=count;
		check(count);
		return;
	}
		
	//删除
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
	{
		//count = count + 2;
		last[i]->next[i] = theNode->next[i];
	}

	//更新链表级
	while (levels > 0 && headerNode->next[levels] == tailNode)
	{
		//count++;
		levels--;
	}
	erase_nums += count;
	cout << "erase "<<theKey<<" 进行了 " << count << "次元素比较" << endl;
	delete theNode;
	dSize--;
	check(count);
	
}

template<class K, class E>
void skipList<K, E>::output()
{
	skipNode<K, E>* theNode = headerNode->next[0];
	while (theNode != tailNode)
	{
		cout <<"元素值 : "<<theNode->element.second << " ";
		cout << "链表级 : "<<theNode->lsize << endl;
		theNode = theNode->next[0];
	}
	cout << endl;
}

template<class K, class E>
void skipList<K, E>::erase_min()
{
	if (headerNode->next[0] == tailNode)
	{
		cout << "Nothing in skipList" << endl;
		return;
	}
	int minLevel = levels;
	while (headerNode->next[minLevel] != headerNode->next[0])
		minLevel--;
	skipNode< K, E>* minNode = headerNode->next[0];
	cout<<"ERASE MIN "<< minNode->element.second << " SUCCESS!!!"<<endl;
	for (int i = minLevel; i >= 0; i--)
	{
		headerNode->next[i] = minNode->next[i];
	}

	delete minNode;
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;
	dSize--;
}

template<class K, class E>
void skipList<K, E>::erase_max()
{
	int count = 0;
	if (headerNode->next[0] == tailNode)
		return;
	skipNode< K, E>* lastNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (lastNode->next[i] != tailNode)
		{
			count++;
			lastNode = lastNode->next[i];
		}
	}
	//cout << lastNode->element.first << endl;
	K theKey = lastNode->element.first;
	cout << "ERASE MAX " << theKey << " SUCCESS!!!" <<  " 进行了 " << count << " 次元素比较 " << endl;
	//erase(beforeNode->element.first);
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
		{
			beforeNode = beforeNode->next[i];
		}
		last[i] = beforeNode;//最后一级链表i的节点
	}
	skipNode<K, E>* theNode = beforeNode->next[0];
	//删除
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
	{
		last[i]->next[i] = theNode->next[i];
	}

	//更新链表级
	while (levels > 0 && headerNode->next[levels] == tailNode)
	{
		//count++;
		levels--;
	}
	delete theNode;
	dSize--;
}

template<class K, class E>
void skipList<K, E>::op_xor()
{//输出所有元素的异或和
	skipNode<K, E>* scanNode = headerNode->next[0];
	K val = 0;
	while (scanNode != tailNode)
	{
		val ^= scanNode->element.second;
		scanNode = scanNode->next[0];
	}
	cout << val << endl;
	//ss<<val<<endl;
}

template<class K, class E>
void skipList<K, E>::reform()
{//当find 扫描个数 > 
	//重构  O（n*seta(levels）)
	//计算每个应该的level
	int* rank = new int[dSize];
	for (int i = 0; i < dSize; i++)
	{
		rank[i] = 0;
	}
	get_level(rank, levels, 0, dSize); // rank放着每个元素的级
	
	skipNode< K, E>* ScanNode = headerNode->next[0];//扫描
	
	for (int i = 0; i <=maxlevel; i++)
	{//默认修改一下 last 后面每次 一个都更新
		last[i] = headerNode;
		last[i]->next[i] = tailNode;
	}

	for (int i = 0; i < dSize; i++)
	{//依次进行next重构 符合自己该有的级别

		if (rank[i] <= levels) //处理可能存在的断级问题
			levels = rank[i];
		
		//保存一下 下一个节点 后面将当前节点的next重构
		ScanNode->lsize = rank[i];
		skipNode<K, E>* NextNode = ScanNode->next[0];//要连接的
		ScanNode->next = new skipNode<K, E> * [rank[i] + 1];
		
		for (int j = 0; j <= rank[i]; j++)
		{//插入i级链表
			ScanNode->next[j] = last[j]->next[j];
			last[j]->next[j] = ScanNode;
			last[j]= ScanNode;
		}
		ScanNode = NextNode;
	}
	cout << "重构完成！"<<endl;

}

template<class K, class E>
void skipList<K, E>::ideal_initial(int *a,int m)
{//复杂度O(LOGN)//排序 + O(logn)//rank + o(n)//初始化
	//初始化M个 所以级数是 log2(m) +1 
	//链表0---i级 i级数对个数是 n/2^i
	//按照链表级来构造
	int level = log2(m);//向下取整
	int *b = new int[m];//每个里面放级别
	for (int i = 0; i < m; i++) b[i] = 0;
	get_level(b, level,0,m-1); // b放着每个元素的级
	
	for (int i = 0; i < m; i++)
	{
		if (b[i]+1 > levels)
		{
			levels = b[i]+1;
			last[b[i]] = headerNode;
		}
		pair<K, E> thePair(make_pair(a[i], a[i]));
		skipNode<K, E>* newNode = new skipNode<K, E>(thePair,b[i]+1);
		for (int j = 0; j <= b[i]; j++)
		{//插入i级链表
			newNode->next[j] = last[j]->next[j];
			last[j]->next[j] = newNode;
		}
	}
}

template<class K, class E>
void skipList<K, E>::get_level(int *b, int level, int low, int high)
{

	if (level <= 0) return;
	int mid = (low + high) / 2;
	if (mid == 0) return;
	if (b[mid] != 0) return;
	b[mid] = level;
	get_level(b, level - 1, mid, high);
	get_level(b, level - 1, low, mid);
}

template<class K, class E>
void skipList<K, E>::check(int count)
{
	if(need_reform==1)
	if (count >= (maxlevel + dSize + log2(dSize)) / 2)   // (maxlevel + dSize +log2(dSize))/2)
	{//进行重构
		cout << "*****************************************************" << endl;
		cout << "比较次数过多 进行重构整理" << endl;
		reform();
		cout << "*****************************************************" << endl;
	}
	else
	{
		return;
	}
	return;
}

template<class K, class E>
void skipList<K, E>::analyse()
{
	if (find_times != 0) {
		cout << "Total find nums: " << find_nums << endl;
		cout << "Averge find times: " << find_nums / find_times << endl;
	}
	else
	{
		cout << "Total find nums: " << find_nums << endl;
		cout << "Averge find times: " << 0 << endl;
	}
	if (insert_times != 0) {
		cout << "Total insert nums: " << insert_nums << endl;
		cout << "Averge insert times: " << insert_nums / insert_times << endl;
	}
	else
	{
		cout << "Total insert nums: " << insert_nums << endl;
		cout << "Averge insert times: " << 0 << endl;
	}
	if (erase_times != 0)
	{
		cout << "Total erase nums: " << erase_nums << endl;
		cout << "Averge erase times: " << erase_nums / erase_times << endl;
	}
	else
	{
		cout << "Total erase nums: " << erase_nums << endl;
		cout << "Averge erase times: " <<  0 << endl;
	}
	find_nums = 0;
	find_times = 0;
	insert_nums = 0;
	insert_times = 0;
	erase_nums = 0;
	erase_times = 0;
}



