#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<cstdio>
#include<vector>
#include"minlosertree.h"

using namespace std;


//缓冲区 
struct Page {
	long int* arr;
	int position; //当前顺串扫描的位置 
	Page() {
		position = 0;
	}
	Page(int page_size) {
		position = 0;
		arr = new long int[page_size + 1];
	}
};



template<class T>
minLoserTree<T>::minLoserTree(T* ThePlayers, int n)
{
	initialize(ThePlayers, n);
}

template<class T>
void minLoserTree<T>::initialize(T* thePlayer, int theNumberOfPlayers)
{
	int n = theNumberOfPlayers;
	if (n < 2)
		throw illegalParameterValue("必须至少有两个元素！");

    //delete[] players;

	players = thePlayer;
	numberofPlayers = n;
    //delete[]tree; delete[]edges;
	tree = new int[n];//树结构重置 0为最小的节点 n个节点
	edges = new int[n];//一共n-1个边 0不用 1 - n-1

	//计算 s = 2^log (n-1),S是最底层的最左端的内部节点
	//int s = 2*log2(n - 1);
	int s;
	for (s = 1; 2 * s <= n - 1; s += s);

	lowExt = 2 * (n - s);//n-s是最底层外部节点个数
	offset = 2 * s - 1;

	int i;
	// 外层节点比赛
	for (i = 2; i <= lowExt; i += 2)
		play_once((offset + i) / 2, i - 1, i);

	//处理剩下的节点
	if (n % 2 == 1)
	{//n为奇数
		play_once(n / 2, edges[n - 1], lowExt + 1);
		//处理完 外部 都是每次+=2  奇数第一次+1+2
		i = lowExt + 3;
	}
	else i = lowExt + 2;

	//
	for (; i <= n; i += 2)
	{
		play_once((i - lowExt + n - 1) / 2, i - 1, i);
	}

	maintain();
	//cout << tree[0] << endl;
};

template<class T>
void minLoserTree<T>::play_once(int p, int leftChild, int rightChild)
{
	//get now
	tree[p] = loser(leftChild, rightChild);//树节点里面放大的
	edges[p] = winner(leftChild, rightChild);

	//循环递归实现其他比赛
	while (p % 2 == 1 && p > 1)
	{
		tree[p / 2] = loser(edges[p - 1], edges[p]);
		edges[p / 2] = winner(edges[p - 1], edges[p]);
		p = p / 2;//往上走 找父母
	}
}

template<class T>
void minLoserTree<T>::replay(int thePlayer)
{//从改变的开始 到根 重比  只输入位置
	int n = numberofPlayers;
	if (thePlayer <= 0 || thePlayer > numberofPlayers)
		throw illegalParameterValue("错误的序号!");

	int matchNode,    //要进行比赛的节点
		leftChild,
		rightChild;

	if (thePlayer <= lowExt)
	{//在最外层节点开始进行比赛
		matchNode = (offset + thePlayer) / 2;
		leftChild = 2 * matchNode - offset;
		rightChild = leftChild + 1;//相邻比赛
	}
	else
	{//不是最外面一层外部节点，更上一层
		matchNode = (thePlayer - lowExt + n - 1) / 2;
		if (2 * matchNode == n - 1)
		{//处理的是 改变的节点为单着的那个节点的情况
			leftChild = edges[2 * matchNode];//左孩子为树节点
			rightChild = thePlayer;//右孩子就是自己
		}
		else
		{//处理一般情况
			leftChild = 2 * matchNode - n + 1 + lowExt;
			rightChild = leftChild + 1;
		}
	}

	tree[matchNode] = loser(leftChild, rightChild);
	edges[matchNode] = winner(leftChild, rightChild);

	//处理特殊的单数
	if (matchNode == n - 1 && n % 2 == 1)
	{//如果是奇数个元素并且下一次要和那个单着的比
		matchNode /= 2;//父节点
		tree[matchNode] = loser(edges[n - 1], lowExt + 1);
		edges[matchNode] = winner(edges[n - 1], lowExt + 1);
	}

	//比其他的
	matchNode /= 2;
	for (; matchNode >= 1; matchNode /= 2)
	{
		tree[matchNode] = loser(edges[2 * matchNode], edges[2 * matchNode + 1]);
		edges[matchNode] = winner(edges[2 * matchNode], edges[2 * matchNode + 1]);
	}

	maintain();

}

template<class T>
void minLoserTree<T>::output()
{
	cout << "numbers of players = " << numberofPlayers << " lowExt(最外部元素) = "
		<< lowExt << " offset = " << offset << endl;
	cout << "树以及相邻的边结构为： \n";
	for (int i = 1; i < numberofPlayers; i++)
	{
		cout << "Tree[" << i << "] = " << players[tree[i]] << " ";
		cout << "Edge[" << i << "] =" << players[edges[i]] << endl;
	}
	cout << "Tree[0] = " << players[tree[0]] << endl;
}

template<class T>
void minLoserTree<T>::make_run(fstream& fin)
{//使用minloser 生成顺串

	//关于make_run磁盘访问数
	//应该是:每次读入最大输入buffer个 1次  然后内排序生成顺串 输出时每次要访问一次
	// 	   输出优化？ 缓冲区存 顺串号+数字 最后输出到对应文件
	//		但是带来问题： 无法确定输入输出缓冲区大小 
	//这里计算方法 以 全部为输入缓冲区 每次输出访问一次disk 计算。
	disk_times += (sizeof_file / sizeof_MM) + 1;


	if (!fin.is_open()) {
		cout << "打不开文件！" << endl;
		return;
	}

	//内存大小可自己设定
	//sizeof_MM = 3;

	//有多少个输出顺串 取决于多少个 顺串号num
	cout << "正在生成顺串......\n";
	int pos = top();//替换的位置
	while (players[pos].num != INT_MAX)
	{//还有未排序的
		pos = top();//替换的位置
		if (players[pos].num > max_run && players[pos].num != INT_MAX) max_run = players[pos].num;
		Player p;//用来替换的
		string output_file = ff_name + "_R" + to_string(players[pos].num) + ".txt";
		ofstream fout(output_file, ios::app);
		disk_times++;//输出
		fout << players[pos].element << " ";//输出
		fout.close();//随手关闭
		//读入下一个
		long int temp;
		if (fin >> temp)
		{//不是文件末尾	
			if (!fin.eof())
			{
				p.element = temp;
				//disk_times++;
				if (p.element < players[pos].element) {
					p.num = players[pos].num + 1;
				}
				else p.num = players[pos].num;
			}
			else {//读完了
				fin.close();
				p.element = INT_MAX;
				p.num = INT_MAX;
			}

		}
		else {//读完了
			fin.close();
			p.element = INT_MAX;
			p.num = INT_MAX;
		}
		players[pos] = p;//替换
		replay(pos);
		pos = top();//替换的位置
	}
	all_temps = max_run;
	cout << max_run << " 个顺串生成成功！！！\n";

	for (int i = 1; i <= max_run; i++)
	{
		string s = ff_name + "_r" + to_string(i) + ".txt";
		ofstream fo(s, ios::app);
		fo << INT_MAX;
	}
}

//K路归并
template<class T>
void minLoserTree<T>::merge_K(int k, int sta, int level)
{//注意 不能用Player结构输入  归并不比较run num   每次进行一次的归并
 //每次归并输出只有一个 每层多个    
	int file_num = all_temps + 1 - sta;
	int end_level = all_temps;
	int times;//计算每层归并次数
	int next_sta = sta;

	if (file_num <= 1) {
		cout << "合并完成！" << endl;
		return;
	}
	

	if (file_num % k != 0) times = (file_num / k) + 1;
	else times = file_num / k;

	if (times == 0)
		times = 1;

	while (times--)
	{//每层多次合并

		int now_k = min(end_level - next_sta + 1, k);//处理后面不是正好的情况
		next_sta += now_k;
		map<int, string> name;//读入的名字
		ifstream* fins = new ifstream[now_k + 1];

		page_num = now_k + 1;
		page_size = sizeof_MM / page_num;
		Page* inBuffer = new Page[now_k + 1];
		vector<long> outBuffer(page_size, 0);

		int outpoint = 0;//输出指针
		for (int i = 0; i <= now_k; i++)
		{
			inBuffer[i] = Page(page_size);
		}

		
		if (level == 0) {//读入run 
			for (int i = sta; i < sta + now_k; i++)
			{
				string s = ff_name + "_R" + to_string(i) + ".txt";
				name[i] = s;
				fins[i - sta + 1].open(s);
			}
		}
		else
		{//读入S
			for (int i = sta; i < sta + now_k; i++)
			{
				name[i] = ff_name + "_S" + to_string(i) + ".txt";
				fins[i - sta + 1].open(name[i]);
			}
		}

		//外存读入inBuffer
		for (int i = 1; i <= now_k; i++)
		{
			int cnt = 0;
			while (cnt < page_size && !fins[i].eof())
			{
				fins[i] >> inBuffer[i].arr[cnt++];
			}
			inBuffer[i].position = 0;
			disk_times++;//读一次 读满
		}

		T* ps = new T[now_k + 1];
		ps[0] = INT_MAX;
		for (int i = 1; i <= now_k; i++)
		{
			ps[i] = inBuffer[i].arr[0];
			inBuffer[i].position++;
		}



		//for (int i = sta; i < sta + now_k; i++)
		//{//先输入各run第一个建树
		//	long int temp;
		//	if (!fins[i - sta + 1].is_open()) {
		//		cout << "顺串 "<<i-sta+1<<" 打开失败！" << endl;
		//		return;
		//	}
		//	//先读满
		//	//int num = 0;
		//	//while (num < page_size && !fins[i - sta + 1].eof()) {
		//	//	fins[i - sta + 1] >> in_buffer[i - sta + 1][num];
		//	//	num++;
		//	//}
		//	//in_pointers[i - sta + 1] = 0;

		//	//	//读取外部节点 
		//	//for (int j = 1; j <= now_k; j++) {
		//	//	players[j] = in_buffer[j][0];
		//	//	in_pointers[j]++;
		//	//}


		//	if (fins[i - sta + 1] >> temp)
		//	{
		//		if (fins[i - sta + 1].eof())
		//		{
		//			fins[i - sta + 1].close();
		//			ps[i - sta + 1] = INT_MAX;
		//			continue;
		//		}
		//		ps[i - sta + 1] = temp;
		//	}
		//	else
		//	{
		//		ps[i - sta + 1] = INT_MAX;
		//	}
		//}

		string output_file = ff_name + "_S" + to_string(++all_temps) + ".txt";
		if (all_temps - max_run == totals) {
			output_file = ff_name + "_sorted.txt";//最后一次输出
		}
		ofstream fout(output_file, ios::app);

		//初始化之前要判断 如果就一个元素 输出就行了
		//if (now_k == 1)
		//{
		//	fout << ps[1];
		//	long int temp;
		//	while (fins[1] >> temp)
		//	{
		//		//改了
		//		if (fins[1].eof()||temp==INT_MAX)
		//		{
		//			fins[1].close();
		//			break;
		//		}
		//		fout << temp;
		//		disk_times += 2;
		//	}
		//	//处理下一次循环
		//	for (int i = sta; i < sta + now_k; i++)
		//	{
		//		fins[i - sta + 1].close();
		//	}
		//	fout.close();
		//	sta = next_sta;
		//	continue;
		//}

		//每次都得初始化
		initialize(ps, now_k);

		int pos = top();//替换的位置
		while (players[pos] != INT_MAX)
		{
			pos = top();//替换的位置
			outBuffer[outpoint++] = players[pos];
			//T p;//用来替换的
			
			//fout << players[pos] << " ";//输出
			
			//输出缓冲区已满，将数据块写入外存 
			if (outpoint == page_size) {
				for (outpoint = 0; outpoint < page_size; outpoint++) {
					fout << outBuffer[outpoint] << " ";
				}
				outpoint = 0;
				disk_times++;//一次性输出一堆
			}
			//disk_times++;

			//输入缓冲区已空，从外存读入数据块 
			if (inBuffer[pos].position >= page_size) {
				int cnt = 0;
				while (cnt < page_size && !fins[pos].eof()) {
					fins[pos] >> inBuffer[pos].arr[cnt++];
				}
				inBuffer[pos].position = 0;
				players[pos] = inBuffer[pos].arr[inBuffer[pos].position];
				inBuffer[pos].position++;
				disk_times++;
			}
			//继续读取缓冲区 
			else {
				players[pos] = inBuffer[pos].arr[inBuffer[pos].position];
				inBuffer[pos].position++;
			}


			////读入下一个
			//if (fins[pos] >> p)
			//{//不是文件末尾	
			//	disk_times++;
			//	if (fins[pos].eof())
			//	{
			//		fins[pos].close();
			//		p = INT_MAX;
			//		break;
			//	}
			//}
			//else {//读完了
			//	fins[pos].close();
			//	p = INT_MAX;
			//}



			//players[pos] = p;//替换
			replay(pos);
			pos = top();//替换的位置
		}

		for (int indx = 0; indx < outpoint; indx++) {
			fout << outBuffer[indx] << " ";
		}
		disk_times++;//处理剩余的
		if (all_temps - max_run != totals) {
			fout << INT_MAX;
		}
		

		for (int i = sta; i < sta + now_k; i++)
		{
			fins[i - sta + 1].close();
		}
		fout.close();
		sta = next_sta;
	}
	if (next_sta > max_run)
		merge_K(k, next_sta, 1);//标志 不读入run了
	else
		merge_K(k, next_sta, 0);

}
