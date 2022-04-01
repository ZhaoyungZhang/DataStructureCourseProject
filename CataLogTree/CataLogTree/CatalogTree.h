#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
using namespace std;
typedef long long ll;

//使用带父结点指针的儿子兄弟树


struct Node
{
	Node* parent;//每个节点都要记录父节点
	Node* LeftChild;//只记录第一个孩子
	Node* sibiling;//平级向后连
	int file_type;//0文件 1目录
	string file_name;//文件或者目录名字
	ll fnum;//子文件数目
	ll file_size;//该文件大小
	
	//针对目录文件来说的
	ll all_mx;//目录配额 和 后代配额
	ll son_used;//所有的孩子占的大小

	char power;//权限

	Node(int type, string fname, ll size = 0) {
		file_type = type; file_size = size;
		fnum = 0;
		parent = NULL; LeftChild = NULL;
		sibiling = NULL;
		file_name = fname;
		all_mx = 0;
		son_used = 0;
		power = 'p';//r是管理员权限
	}
	~Node() {  }
	bool pre_add_size(ll size) {//预分配 文件
		if (all_mx && son_used + size > all_mx)
			return false;
		return true;
	}
	void add_size(ll size) {//预分配成功才进入这个
		son_used += size;
	}
	void get_size() {
		if (file_type == 0) {
			cout <<"文件大小: "<<file_size<<"\n";//文件
		}
		else
		{
			cout << "目录配额大小: " << all_mx << " 使用了 " << son_used << "\n";
		}
		
	}
	bool set_size(ll all) {//分配一个配额 只对目录有用
		if (all < son_used) return false;

		return true;
	}

};

class CatalogTree
{
private:
	Node* root;
	Node* CurNode;//当前位置
	char my_power;
public:
	CatalogTree();
	~CatalogTree() { delete root; };

	string outname;
	string inname;
	ifstream ffin;
	ofstream ffout;
	int put_flag;//输出在cmd 还是 file
	
	//基础
	void dir();//列出当前目录下的所有子目录和文件项
	void cd();//累出当前目录的绝对路径
	void cd_recur(Node* now);
	void cd_back();//当前目录变为当前目录的父目录。
	void cdstr(string& str);//当前目录变为STR所表示路径的目录
	void mkdir(string& str);//在当前目录下创建一个子目录str，如果存在则不进行任何操作
	void mkfile(string& str);//在当前目录下创建一个文件，若存在不进行。
	void delet(string& str);//删除当前目录下名字为STR的目录或者文件，如果不存在，不进行操作
	void deletenode(Node* now);
	void save(string& str);//将从根节点开始的目录树结构保存到文件中
	void save_recur(ofstream& fout, Node* now, int depth);//递归保存
	void load(string& str);//从文件STR中读取之前保存的目录树结构，并且根据其重新建立当前的目录树
	void load_recur(ifstream& fin, int depth);
	void read_data(int num);
	
	//size
	void mkfile_size(string& str, ll size);//make file with 大小限制  str相对路径
	void setdir_size(ll all_mx);//给当前 原有的 目录文件设置配额
	void remove_size(string& str);//删除文件或者目录
	
	//其他
	void cd_root();//回到root
	void mkdir_p(string& str);//自行创建多层目录
	void put_size() { CurNode->get_size(); }//获取当前目录的配额

   //权限
	void _r() { my_power = 'r'; }
	void _p() { my_power = 'p'; }
	void mkdir_r(string& str);//创建带权限的目录
	void mkfile_r(string& str);//创建带权限的文件
	void delet_r(string& str);
	
	
    //拓展文件操作
	//剪切
	void mv_a2b(string &a,string &b);//从a移动到b
	//复制
	void cp_a2b(string& a, string& b);//把当前目录下的a 复制到b下 b下不能有重名的
	void cp_r(Node *t);//递归拷贝节点
};

