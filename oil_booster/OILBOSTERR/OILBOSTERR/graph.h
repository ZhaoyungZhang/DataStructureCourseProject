#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
#include<climits>
#include<string>
#include<windows.h>
#include<time.h>
#include<sys/timeb.h>
#include<math.h>
using namespace std;

#define ll long long 

//解空间: 某点处放booster 1 或者 不放 0;
/*
3. 如果存在一个点x , x有多条入边e[1]..e[n] , x处的压力`p[x] = max(p[x], p[e[i].from] - e[i].cost) `
即x处的压力为到达x处的压力中的最大值
4. 图中每条边上的任何一点都要能到达 , 一个节点的压力是最大到达压力 , 但
每条边都是一个有效的管道 也要能完整的运输
例如 如果存在一个点x ,  x处的压力>Pmin , 但存在一条边 e , p[e.from] - e.cost < Pmin 这也是不合法的
*/
//复杂度 O（2^n）
//空间 O(最长路径) O(2^n）

ifstream fin;
ofstream fout;

struct btnode {//用于分支定界的子集树 
	btnode* parent;//指向父节点
	int press;//
	int level;//子集树层级
	bool bst_here;//是否放放大器
	int bstnum;//优先级 从根到节点x的路径上的bst个数
	int max_to_cost;
	btnode() {
		parent = NULL;
		press = 0; level = 0; bst_here = false;
		bstnum = 0;

	}
	btnode(int pres, int lev, btnode* par = NULL, int bstn = 0) {
		parent = par;
		press = pres; level = lev;
		bstnum = bstn;
		bst_here = false;
	}

};

class Edge {
public:
	int to;// 终点编号
	int cost;// 长度
	Edge(int to, int cost) : to(to), cost(cost) {}
	~Edge() {}
};

class inEdge {
public:
	int from;// 终点编号
	int cost;// 长度
	inEdge(int from, int cost) : from(from), cost(cost) {}
	~inEdge() {}
};


class Node {
public:
	vector<Edge> edges;//记录所有出边
	int press;
	bool booster;
	int max_to_cost;
	vector<inEdge> inedges;//记录入边 用来更新press
	int toponum;//按拓扑序是第几
	Node() {
		press = 0;
		booster = false;
		edges.clear();
		inedges.clear();
		max_to_cost = 0;
		toponum = 0;
	}
	~Node() {}
};

struct cmp
{
	bool operator () (const btnode* p1, const btnode* p2) {
		return p1->bstnum > p2->bstnum;
	}
};

class DAG {
private:

	int Pmin, Pmax;//
	vector<Node> nodes;// 邻接表
	vector<int> in_deg;
	vector<int> dig;//拓扑序列
	vector<bool> place_bst;//是否要放在这
	priority_queue<btnode*, vector<btnode*>, cmp> pq;//最小堆


public:
	int n, m;//顶点数 边
	DAG() {
		fin >> n >> m >> Pmax;
		Pmin = 0;
		best_ans = INT_MAX;
		nodes.clear();
		in_deg.resize(n + 1, 0);
		dig.resize(n + 1, 0);
		place_bst.resize(n + 1, false);

		//初始化顶点
		for (int i = 0; i <= n; i++)
			nodes.emplace_back(Node());
		//读入边
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			fin >> u >> v >> w;
			nodes[u].edges.emplace_back(v, w);
			//修改入度
			in_deg[v]++;
			nodes[u].max_to_cost = max(nodes[u].max_to_cost, w);
			//更新入边
			nodes[v].inedges.emplace_back(u, w);
		}
		nodes[1].press = Pmax;
		place_bst[1] = true;
	}
	~DAG() {}
	int best_ans;//最优解 数目

	void visualize(int i);//可视化输出
	void visualize2(int i);//可视化输出
	void topsort();//用拓扑排序 来确定先后关系
	void recountpre();
	void output_bst();//输出booster
	void backtracking(int level, int cnt);//回溯解决
	void branch_bound();//分支定界解决

};

void DAG::topsort()
{//确定一个拓扑序列 以便后续
	int cnt = 1;
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (in_deg[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		nodes[u].toponum = cnt;
		dig[cnt++] = u;//排序
		for (auto e : nodes[u].edges) {
			if (--in_deg[e.to] == 0)
				q.push(e.to);
		}
	}
	if (cnt < n) {
		cout << "图中有环路！不符合要求！\n";
		return;
	}
	//for (int i = 1; i <= n; i++) 
		//cout << "top " << i << " " << dig[i] << "\n";
}

// 回溯需要按照拓扑序跑！ dfs
void DAG::backtracking(int level, int cnt)
{//进行回溯决策树里面 左是该节点不放 右子树是放
	//搜索第level层 
	int u = dig[level];//当前点 level也代表了拓扑序

	if (level >= n) {//最底层了
		best_ans = min(cnt, best_ans);
		//记录下最好的情况 不然会被冲了
		//更新放置情况
		for (int i = 1; i <= n; i++) {
			place_bst[i] = false;
			place_bst[i] = nodes[i].booster;
		}
		return;
	}

	if (level == 1) {//第一层 源点肯定放了（不算）只需要判断其他边 如果低了 就在v放
		backtracking(2, 0);
	}
	else {//其他层  如果到v 不行 则在 u放
		int j;
		int flag = 0;
		int temp_pre = -1;//临时变量pre 用来回溯！

		//求press[u]  优化 用入边
		//for (auto& c : nodes[u].inedges) {
		//	int f = c.from;
		//	if (nodes[f].toponum < nodes[u].toponum)
		//	{//必须是拓扑序前面的
		//		temp_pre = max(temp_pre, nodes[u].press - c.cost);
		//	}
		//}
		for (int k = 1; k < level; k++) {//求 前面到 
			for (auto& x : nodes[dig[k]].edges) {
				if (x.to == u)
					//nodes[u].press = max(nodes[u].press, nodes[dig[k]].press - x.cost);
					temp_pre = max(temp_pre, nodes[dig[k]].press - x.cost);
			}
		}

		for (j = 0; j < 2; j++)
		{//进行两种决策
			//剪枝1
			if (temp_pre >= Pmax) {
				backtracking(level + 1, cnt);
				break;
			}
			//剪枝2
			if (temp_pre < Pmin)
			{
				cnt++;
				nodes[u].booster = true;
				//剪枝3
				if (cnt >= best_ans) {
					return;
				}
				backtracking(level + 1, cnt);
			}
			if (j == 0) {//不放 但是需要
				for (auto& v : nodes[u].edges) {//对于所有出边进行判断
					int next_pr = temp_pre - v.cost;
					if (next_pr < Pmin) {
						flag = 1;
						break;
					}
				}
			}
			//决策 put
			if (j == 1 || flag == 1) {//放
				cnt++;
				nodes[u].press = Pmax;
				nodes[u].booster = true;
				//剪枝
				if (cnt >= best_ans)
					return;
				else {
					backtracking(level + 1, cnt);
				}
			}
			//not put
			else if (j == 0) {//对应的 j==0 && flag!=1 
				nodes[u].press = temp_pre;
				nodes[u].booster = false;
				backtracking(level + 1, cnt);
			}
		}
	}
}

//最小耗费 分支定界
void DAG::branch_bound()
{//分支定界 活结点--扩展结点-- 子集空间树
	btnode* enode = new btnode(Pmax, 2);//活结点
	int level = 2;
	while (level <= n - 1)
	{//进行活结点的拓展
		int vert = dig[level];//该层扩展的节点
		int temp_press = -1;
		int flag = 0;

		//求扩展结点的压力
		for (int k = 1; k <= level - 1; k++) {
			for (auto& e : nodes[dig[k]].edges) {
				if (e.to == vert) {
					btnode* p = enode;
					//????
					for (int j = level - 1; j > k; j--)
						p = p->parent;

					temp_press = max(temp_press, p->press - e.cost);
				}
			}
		}
		//限界函数 -最大花费 小必须放
		if (temp_press - nodes[vert].max_to_cost < Pmin) {
			flag = 1;
		}
		//check 到 邻接点是否符合要求
		/*for (auto& e : nodes[vert].edges) {
			if (temp_press < Pmin + e.cost) {
				flag = 1; break;
			}
		}*/
		if (flag == 0) {//两种 放或者放

			btnode* t = new btnode(temp_press, level + 1, enode, enode->bstnum);
			pq.push(t);
			btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
			tt->bst_here = true;
			pq.push(tt);
		}
		else {//必须放
			btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
			tt->bst_here = true;
			pq.push(tt);
		}
		enode = pq.top(); pq.pop();
		level = enode->level;
	}
	best_ans = enode->bstnum;

	btnode* p = enode;
	while (p) {
		place_bst[dig[p->level - 1]] = p->bst_here;
		p = p->parent;
	}

}

void DAG::output_bst()
{
	for (int i = 1; i <= n; i++) {
		if (place_bst[i])
			cout << "node " << i << " \n";
	}
}

void DAG::visualize(int i)
{//可视化
	recountpre();
	//system("cd C:\\Users\\12042\\Desktop\\dagData\\outputimage");
	string name = to_string(i) + ".dot";
	std::ofstream out(name);
	out << "digraph g {\n";
	for (int i = 1; i < nodes.size(); i++) {
		out << i;
		if (place_bst[i])
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=red];\n";
		else
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=white];\n";
	}
	for (auto i = 1; i <= n; ++i) {
		for (auto& edge : nodes[i].edges) {
			out << i << "->" << edge.to << "[label=\"cost=" << edge.cost << "\"];\n";
		}
	}
	out << "}\n";
	out.close();
	string order = "dot -Tjpg " + to_string(i) + ".dot -o solve" + to_string(i) + ".jpg";
	system(order.c_str());
}
void DAG::visualize2(int i)
{//可视化
	recountpre();
	string name = to_string(i) + "-B.dot";
	std::ofstream out(name);
	out << "digraph g {\n";
	for (int i = 1; i < nodes.size(); i++) {
		out << i;
		if (place_bst[i])
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=red];\n";
		else
			out << "[label=\"node" << i << ";pre = " << nodes[i].press << "\",style=filled, fillcolor=white];\n";
	}
	for (auto i = 1; i <= n; ++i) {
		for (auto& edge : nodes[i].edges) {
			out << i << "->" << edge.to << "[label=\"cost=" << edge.cost << "\"];\n";
		}
	}
	out << "}\n";
	out.close();
	//system("C:");
	//system("cd C:\\Users\\12042\\Desktop\\dagData\\outputimage");
	string order = "dot -Tjpg " + to_string(i) + "-B.dot -o solve-B" + to_string(i) + ".jpg";
	system(order.c_str());
}

void DAG::recountpre() {
	for (int i = 2; i <= n; i++) {
		int v = dig[i];
		if (place_bst[v]) {
			nodes[v].press = Pmax;
		}
		else {
			nodes[v].press = 0;
			for (int j = 1; j < i; j++) {
				for (auto& e : nodes[dig[j]].edges) {
					if (e.to == v) {
						nodes[v].press = max(nodes[v].press, nodes[dig[j]].press - e.cost);
					}
				}
			}
		}
	}

}

void check() {
	int flag = 0;
	stringstream ss;
	for (int i = 1; i <= 100; i++) {
		cout << "正在测试数据集: " << i << "\n";
		string opstd = "C:\\Users\\12042\\Desktop\\dagData\\outputSTD\\";
		string myin = "C:\\Users\\12042\\Desktop\\dagData\\output\\";
		opstd += to_string(i) + ".out";
		myin += to_string(i) + ".out";
		ifstream finstd(opstd);
		if (!finstd.is_open()) {
			cout << "文件打开失败\n";
		}
		int ans; finstd >> ans;
		finstd.close();

		ifstream finmy(myin);
		if (!finmy.is_open()) {
			cout << "文件打开失败\n";
		}
		int me; finmy >> me;
		finmy.close();
		if (me != ans) {
			cout << "Wrong Answer\n";
			ss << i << "WA！\n";
			flag = 1;
		}
		else {
			cout << "Accept\n";
		}
	}
	if (!flag) {
		cout << "All Accept!\n";
	}
	else cout << "Wrong Answer\n";
	cout << ss.str();
}


