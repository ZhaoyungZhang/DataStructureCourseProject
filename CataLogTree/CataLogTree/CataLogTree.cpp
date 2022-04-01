#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"CatalogTree.h"
using namespace std;
typedef long long ll;
const ll MAXN = 1e8;

vector<string> split(const string& str, char c)
{
	vector<string> res;//存分割玩的string数组
	string temp;
	for (auto i : str)
	{
		if (i == c) res.push_back(temp), temp.clear();
		else temp += i;
	}
	if (!temp.empty()) res.push_back(temp);
	return res;
}

CatalogTree::CatalogTree()
{//构造方法
	delete root;
	root = new Node(1, "/");//根目录 是/
	CurNode = root;
	put_flag = 1;//1默认为输出在文件 0输出在cmd
	my_power = 'p';//person
}

//dir 需要按照字典序输出  先输出所有文件  再文件夹
void CatalogTree::dir()
{//列出当前目录下的所有子目录与文件项
//从左到右扫 输出换行 文件后面加* 目录不加
//dir命令的输出顺序按照字典序排列，先输出所有文件再输出所有文件夹名。
	map<string, int> file_mp;
	map<string, int> dir_mp;
	Node* now = CurNode->LeftChild;
	for (; now != NULL; now = now->sibiling) {
		if (now->file_type == 0) {//文件
			string s = now->file_name + "*\n";
			file_mp[s] = 0;
		}
		else if (now->file_type == 1) {//目录
			string s = now->file_name + "\n";
			dir_mp[s] = 1;
		}
	}
	//输出:
	for (auto s : file_mp) {
		if(put_flag)
			ffout << s.first;
		else 
			cout << s.first;
	}
	for (auto s : dir_mp) {
		if (put_flag)
			ffout << s.first;
		else
			cout << s.first;
	}
}

void CatalogTree::cd_recur(Node* now) {//递归 因为必须先回到根再输出
	if (now == root) {
		if (put_flag)
			ffout << "/";
		else
			cout << "/";
		return;
	}
	else {//递归到根
		cd_recur(now->parent);
		if (now->parent == root) {
			if (put_flag)
				ffout << now->file_name;
			else
				cout << now->file_name;
		}
		else
			if (put_flag)
				ffout << "/" << now->file_name;
			else
				cout << "/" << now->file_name;
	}
}

void CatalogTree::cd_back()
{//回到父亲目录
	if (CurNode == root) {
		//cout << "已经是根目录!\n";
		return;
	}
	CurNode = CurNode->parent;
	return;
}

void CatalogTree::cdstr(string& str)
{//STR可能是绝对路径 也可能是 相对路径  要改变CurNode
	Node* now;
	if (str[0] == '/') {//绝对路径
		Node* t = root;
		vector<string> res = split(str, '/');
		int flag;
		for (int i = 0; i < res.size(); i++) {
			string s = res[i];
			if (s != "") {
				flag = 0;
				for (now = t->LeftChild; now != NULL; now = now->sibiling) {
					if (now->file_name == s && now->file_type == 1)
					{//找到了该目录
						t = now;//改变CUR
						flag = 1;
						break;
					}
				}
				if (!flag) {
					//有一次没找到
					if(put_flag)
						ffout << "路径错误！未找到！\n";
					else
						cout << "路径错误！未找到！\n";

					
					return;
				}
			}
		}
		//引入copy 为了防止有错误路径 
		//可以将Cur停留在最后存在的正确目录上
		CurNode = t;
	}
	else {//相对路径
		vector<string> res = split(str, '/');
		Node* copy_cur = CurNode;
		int flag;
		for (int i = 0; i < res.size(); i++) {
			string s = res[i];
			flag = 0;
			if (s != "") {
				for (now = copy_cur->LeftChild; now != NULL; now = now->sibiling) {
					if (now->file_name == s && now->file_type == 1)
					{//找到了该目录
						copy_cur = now;//改变CUR
						flag = 1;
						break;
					}
				}
				if (!flag) {
					//没找到 有一层没有 就不行
					if (put_flag)
						ffout << "相对路径错误！未找到！\n";
					else
						cout<< "相对路径错误！未找到！\n";
					return;
				}
			}
		}
		CurNode = copy_cur;

	}
}

void CatalogTree::cd()
{//列出当前目录的绝对路径
	cd_recur(CurNode);
	if (put_flag)
		ffout << "\n";
	else cout << "\n";
}

void CatalogTree::mkdir(string& str)
{//创建一个目录
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//在兄弟链表上搜索
		if (now->file_name == str && now->file_type == 1)
		{//重名了
			if(put_flag)
				ffout << "该目录已经存在！\n";
			else
				cout<< "该目录已经存在！\n";
			return;
		}
	}
	now = new Node(1, str, MAXN);
	now->parent = CurNode;
	now->file_size = 0;//目录文件无大小
	now->all_mx = MAXN;
	now->son_used = 0;
	now->sibiling = CurNode->LeftChild;//连上
	CurNode->LeftChild = now;
}

void CatalogTree::mkfile(string& str)
{//在当前目录下 创建一个文件  传入的是文件名
	Node* now = CurNode->LeftChild;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//在兄弟链表上搜索
		if (now->file_name == str && now->file_type == 0)
		{//重名了
			if(put_flag)
				ffout << "该文件已经存在！\n";
			else
				cout<< "该文件已经存在！\n";
			return;
		}
	}
	now = new Node(0, str, 0);
	now->parent = CurNode;
	now->file_size = 0;
	now->sibiling = CurNode->LeftChild;//连上
	CurNode->LeftChild = now;
	//处理父节点们的size
	for (auto t = CurNode; t != NULL; t = t->parent) {
		t->fnum++;
	}
}

void CatalogTree::delet(string& str)
{//删除当前目录下名字为str的目录或者文件
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		if (now->file_name == str) {
			if (now->power == 'r'&&my_power!='r') {
				cout << "权限不够！\n";
				return;
			}
			deletenode(now);
			return;
		}
	}
	//没找到
	ffout << "can't find file or dir\n";
	return;
}

void CatalogTree::deletenode(Node* t)
{//进行具体的删除
	if (t->power == 'r' && my_power != 'r') {
		cout << "权限不够！\n";
		return;
	}


	if (t->file_type == 0) {//如果要删除文件
		Node* now = t->parent->LeftChild;//定位到左孩子
		if (t == now) {//如果删除的是左孩子，必须要改父节点指针
			t->parent->LeftChild = now->sibiling;
			delete t;
			return;
		}

		for (auto now = t->parent->LeftChild; now != NULL; now = now->sibiling) {
			if (t == now->sibiling) {
				now->sibiling = t->sibiling;
				delete t;
				return;
			}
		}

	}
	else {//删除的是目录 
		if (t->LeftChild != NULL) {//dir中有file 递归删除
			while (t->LeftChild != NULL)
			{
				for (auto now = t->LeftChild; now != NULL; now = now->sibiling) {
					if (now->sibiling == NULL) {
						deletenode(now);
						break;
					}
				}
			}
			deletenode(t);
		}
		else {
			if (t->LeftChild == root) return;
			if (t->parent->LeftChild == t) t->parent->LeftChild = t->sibiling;
			else {
				for (auto now = t->parent->LeftChild; now != NULL; now = now->sibiling) {
					if (t == now->sibiling) {
						now->sibiling = t->sibiling;
						return;
					}
				}
			}
			delete t;
		}
	}
}

void CatalogTree::save(string& str)
{//还需要保存 CURNODE！！
	//str = str + ".txt";
	ofstream fout(str);
	if (!fout.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}
	else {//把目录树 存入文件
		save_recur(fout, root, 0);
		//最后插一个END 结束标志 
		fout << "END\n";
		fout << "CUR:";
		fout.close();
		string oname = outname;
		ffout.close();
		ffout.open(str, ios::app);
		cd();
		ffout.close();
		ffout.open(oname, ios::app);
		cout << "save success";
	}
}

void CatalogTree::save_recur(ofstream& fout, Node* now, int depth)
{//前面几个 |  就几级目录  前序
	if (now != NULL) {
		//标志是哪一级文件
		for (int i = 0; i <= depth; i++) {
			fout << "|";
		}
		if (now->file_type == 0) {//文件
			fout << now->file_name << "\n";
		}
		else if (now->file_type == 1) {//目录
			fout << "-" << now->file_name << "\n";
		}
		if (now->file_type == 1) {//目录文件如果有子文件的话
			for (auto t = now->LeftChild; t != NULL; t = t->sibiling) {
				save_recur(fout, t, depth + 1);
			}
		}
	}
}

//几个 | 代表第几级 如果有- 说明是目录 没有说明是文件
int judge_depth(string& str) {
	int cnt = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '|') cnt++;
		else break;
	}
	return cnt;
}

void CatalogTree::load(string& str)
{//从文件读入 把目录树建立起来
	//目录就继续 向下
	//str += ".txt";
	ifstream fin(str);
	string s;
	if (!fin.is_open()) {
		cout << "文件打开失败! 无法加载 ! \n";
		fin.close();
		return;
	}
	else {
		getline(fin, s);//读第一行 为根的
		delete root;
		root = new Node(0, "/");
		CurNode = root;//CurNode 回到根目录下
		load_recur(fin, 1);

		getline(fin, s);
		string str = s.substr(4);
		cdstr(str);//改curnode
		fin.close();
		if(put_flag)
			ffout << "load success !\n";
		else cout << "load success !\n";
		return;
	}
}

void CatalogTree::load_recur(ifstream& fin, int depth)
{//递归加载 
	string s; getline(fin, s);
	if (s != "END") {//没读到末尾

		int deep = judge_depth(s);
		//deal with CurNode
		for (int i = deep; i < depth; i++) {//当前行
			cd_back();//然后回到原来的目录下
		}

		if (s[deep] == '-') {//目录
			//目录名字
			string str = s.substr(deep + 1);
			mkdir(str);
			//之后进入该目录 然后进行递归
			cdstr(str);
			load_recur(fin, deep + 1);
		}
		else {//文件
			string str = s.substr(deep);
			mkfile(str);
			load_recur(fin, deep);
		}

	}
}

void CatalogTree::read_data(int num)
{
	inname = "in" + to_string(num) + ".txt";
	outname = "out" + to_string(num) + ".txt";

	ffin.open(inname);
	ffout.open(outname, ios::app);
}

void CatalogTree::mkfile_size(string& str, ll size)
{//带配额的文件 必须从根开始判断 因为如果 后面满足了 前面也不一定满足
	Node* now = CurNode->LeftChild;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//在兄弟链表上搜索
		if (now->file_name == str && now->file_type == 0)
		{//重名了
			if (put_flag)
				ffout << "该文件已经存在！\n";
			else
				cout << "该文件已经存在！\n";
			return;
		}
	}


	if (CurNode->son_used+size > CurNode->all_mx) {
		cout << "不符合配额要求! 配额太大!\n";
		return;
	}
	else {
		now = new Node(0, str, size);
		now->parent = CurNode;
		now->sibiling = CurNode->LeftChild;//连上
		CurNode->son_used += size;
		now->file_size = size;
		CurNode->LeftChild = now;
	}
	
	//处理父节点们的fnum
	for (auto t = CurNode; t != NULL; t = t->parent) {
		t->fnum++;
	}
}

void CatalogTree::setdir_size(ll all_mx)
{//只修改 目录的配额 一层层进 然后看 每个
	if (CurNode->file_type != 1) {
		cout << "只能对目录文件设置配额!\n";
		return;
	}
	if (CurNode->parent->son_used + all_mx > CurNode->all_mx) {
		cout << "分配配额太小n";
		return;
	}
	if (CurNode->son_used > all_mx) {
		cout << "分配配额太小n";
		return;
	}
	CurNode->all_mx = all_mx;
	cout << "分配成功！\n";
	return;
}

void CatalogTree::remove_size(string& str)
{

}

void CatalogTree::cd_root()
{
	CurNode = root;
}

void CatalogTree::mkdir_r(string& str)
{
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//在兄弟链表上搜索
		if (now->file_name == str && now->file_type == 1)
		{//重名了
			if (put_flag)
				ffout << "该目录已经存在！\n";
			else
				cout << "该目录已经存在！\n";
			return;
		}
	}
	now = new Node(1, str);
	now->parent = CurNode;
	now->file_size = 0;//目录文件无大小
	now->power = 'r';
	now->sibiling = CurNode->LeftChild;//连上
	CurNode->LeftChild = now;
}

void CatalogTree::mkdir_p(string& str)
{//生成多级目录 必须传入绝对路径 这条路径上 如果存在就直接进入 不存在就新建
	vector<string> res = split(str, '/');
	int flag;
	Node* now;
	Node* t = root;
	for (int i = 0; i < res.size(); i++) {
		string s = res[i];
		if (s != "") {
			flag = 0;
			for (now = t->LeftChild; now != NULL; now = now->sibiling) {
				if (now->file_name == s && now->file_type == 1)
				{//找到了该目录
					flag = 1;
					t = now;//改变CUR
					break;
				}
			}
			if (!flag) {
				//没找到 就新建
				CurNode = t;
				mkdir(s);
				t = CurNode->LeftChild;
			}
		}
	}

	CurNode = t;
	cout << "mkdir-p success\n";
}

void CatalogTree::mkfile_r(string& str)
{
	Node* now = CurNode->LeftChild;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		//在兄弟链表上搜索
		if (now->file_name == str && now->file_type == 0)
		{//重名了
			if (put_flag)
				ffout << "该文件已经存在！\n";
			else
				cout << "该文件已经存在！\n";
			return;
		}
	}
	now = new Node(0, str, 1);
	now->parent = CurNode;
	now->sibiling = CurNode->LeftChild;//连上
	now->power = 'r';
	CurNode->LeftChild = now;
	//处理父节点们的nums
	for (auto t = CurNode; t != NULL; t = t->parent) {
		t->fnum++;
	}
}

void CatalogTree::delet_r(string& str)
{
	my_power = 'r';
	delet(str);
	my_power = 'p';
}

void CatalogTree::mv_a2b(string& a, string& b)
{//将当前目录下 a 无论文件或者目录 转移到 b 路径下  不能是根目录
	//找到a 然后保存一下指针 找到b直接连指针就行了
	if (a == "/") {
		cout << "不能移动根目录\n";
		return;
	}
	Node* now;

	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		if (now->file_name == a) {
			if (now->power == 'r' && my_power != 'r') {
				cout << "权限不够！\n";
				return;
			}
			//找到该文件了
			if (now == now->parent->LeftChild) {
				now->parent->LeftChild = now->sibiling;
			}
			vector<string> sons=split(b,'/');
			for (auto s : sons) {
				if (s == now->file_name) {
					cout << "不能将父目录移动到子目录中!\n";
					return;
				}
			}
			cdstr(b);//修改CurNode
			now->sibiling = CurNode->LeftChild;
			CurNode->LeftChild = now;
			now->parent = CurNode;
			//插入该文件或者目录
			cout << "move success!\n";
			return;
		}
	}
	//没找到
	ffout << "can't find file or dir\n";
	return;
}

void CatalogTree::cp_a2b(string& a, string& b)
{//复制 先找到a 文件或者目录 之后复制 复制需要递归复制
//之后 把cd b 看有没有重名的 没有 就直接 插入就行了
	if (a == "/") {
		cout << "不能复制根目录\n";
		return;
	}
	Node* now;
	for (now = CurNode->LeftChild; now != NULL; now = now->sibiling) {
		if (now->file_name == a) {
			if (now->power == 'r' && my_power != 'r') {
				cout << "权限不够！\n";
				return;
			}
			//找到该文件了
			//复制该节点
			Node* t = CurNode;//记录原来的curNode
			//CurNode 用来插入
			Node* scanNode = now;//用来扫now那边
			cdstr(b);//修改CurNode
			//check 没有a
			for (auto checknode = CurNode->LeftChild; 
				checknode != NULL; 
				checknode = checknode->sibiling) {
				if (checknode->file_name == a && checknode->file_type == now->file_type) {
					cout << "目录：" << b << " 下，已经存在 " << a << " 不可以复制！\n";
					return;
				}
			}
			cp_r(now);
			cdstr(b);//修改CurNode
			
			//插入该文件或者目录
			cout << "copy success!\n";
			return;
		}
	}
	//没找到
	ffout << "can't find file or dir\n";
	return;
}

void CatalogTree::cp_r(Node* t)
{//t是要复制的节点 scanode是用来扫描要复制的节点的子节点
	if (t->power == 'r' && my_power != 'r') {
		cout << "权限不够！\n";
		return;
	}

	if (t->file_type == 0) {//如果文件
		mkfile(t->file_name);
	}
	else {//复制的是目录 
		mkdir(t->file_name);
		cdstr(t->file_name);

		for (auto now = t->LeftChild; now != NULL; now = now->sibiling) {
			if (now->file_type == 1) {//目录
				cp_r(now);
				break;
			}
			else
			{
				mkfile(now->file_name);
			}
		}
		
		cd_back();
	}
}





