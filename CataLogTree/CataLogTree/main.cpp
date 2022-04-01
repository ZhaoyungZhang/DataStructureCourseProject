#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"CatalogTree.h"

using namespace std;
typedef long long ll;
//使用带父结点指针的儿子兄弟树


void op1(int num,int put_f) {
	string s;
	CatalogTree ct;
	ct.put_flag = put_f;
	ct.read_data(num);
	while (getline(ct.ffin, s)) {
		if (s == "dir") {
			ct.dir();
		}
		else if (s == "cd") {
			ct.cd();
		}
		else if (s == "cd ..") {//cd..
			ct.cd_back();
		}
		else if (s[0] == 'c' && s[1] == 'd' && s[3] != '.') {
			string str = s.substr(3);
			ct.cdstr(str);
		}
		else if (s.substr(0, 5) == "mkdir") {
			string str = s.substr(6);
			ct.mkdir(str);
		}
		else if (s.substr(0, 6) == "mkfile") {
			string str = s.substr(7);
			ct.mkfile(str);
		}
		else if (s.substr(0, 6) == "delete") {
			string str = s.substr(7);
			ct.delet(str);
		}
		else if (s.substr(0, 4) == "save") {
			string str = s.substr(5);
			ct.save(str);
		}
		else if (s.substr(0, 4) == "load") {
			string str = s.substr(5);
			ct.load(str);
		}
		else if (s == "quit") {
			cout << "程序已退出\n";
			break;
		}
		else {
			cout << "wrong ops!\n";
		}
	}
}
void op2() {
	string s;
	CatalogTree ct;
	ct.put_flag = 0;
	cout << "***********************************************************\n";
	cout << "dir         \t\t\t\t列出当前目录下所有目录项\n";
	cout << "cd          \t\t\t\t列出当前路径\n";
	cout << "cd str		 \t\t\t\t当前目录变为str所表示路径的目录\n";
	cout << "cd ..		 \t\t\t\t当前目录变为当前目录的父目录\n";
	cout << "cd ~		 \t\t\t\t回到根目录\n";
	cout << "mkdir str	 \t\t\t\t在当前目录下创建一个名为str的目录\n";
	cout << "mkfile str	 \t\t\t\t在当前目录下创建一个名为str的文件\n";
	cout << "delete str	 \t\t\t\t删除当前目录下名为str的目录或文件\n";
	cout << "save str	 \t\t\t\t保存虚拟目录到str文件中\n";
	cout << "load str	 \t\t\t\t载入str文件中的虚拟目录\n\n";

	cout << "-r			 \t\t\t\t系统权限变为root权限\n";
	cout << "-p			 \t\t\t\t系统权限变为'p'权限\n";
	cout << "mkdir-r str \t\t\t\t当前目录下创建一个名为str目录，权限为r\n";
	cout << "mkfile-r str\t\t\t\t当前目录下创建一个名为str目录，权限为r\n";
	cout << "delete-r str\t\t\t\t以root权限,删除当前目录下名为str的目录或文件\n\n";
	
	cout << "mkdir-m str \t\t\t\t根据输入的str绝对路径，生成多级目录\n\n";
	
	cout << "mv a b	     \t\t\t\t把当前路径下的a剪切到绝对路径b下\n";
	cout << "cp a b		 \t\t\t\t把当前路径下的a复制到绝对路径b下\n\n";

	cout << "mkfile-s str size\t\t\t在当前下创建大小为size,名为str的文件\n";
	cout << "Q size		 \t\t\t\t给当前路径的目录设置配额为size\n";
	cout << "remove str	 \t\t\t\t删除绝对路径str最后一个文件以及目录\n";
	cout << "show		 \t\t\t\t展示当前目录的配额大小以及使用情况或文件的大小\n\n";

	cout << "quit		 \t\t\t\t退出\n";
	cout << "***********************************************************\n";
	getline(cin, s);
	while (getline(cin, s)) {
		if (s == "dir") {
			ct.dir();
		}
		else if (s == "-r") {
			ct._r();
		}
		else if (s == "-p") {
			ct._p();
		}
		else if (s == "cd") {
			ct.cd();
		}
		else if (s == "cd ~") {
			ct.cd_root();
		}
		else if (s == "cd ..") {//cd..
			ct.cd_back();
		}
		else if (s[0]=='Q') {
			ll size = stoi(s.substr(2));
			ct.setdir_size(size);
		}
		else if (s == "show") {
			ct.put_size();
		}
		else if (s[0] == 'c' && s[1] == 'p') {
			string stra, strb;
			int pos = 3;
			for (int i = 3; i < s.size(); i++) {
				if (s[i] != ' ') {
					stra += s[i];
				}
				else break;
			}
			strb = s.substr(pos + 2);
			ct.cp_a2b(stra, strb);
		}
		else if (s[0] == 'm' && s[1] == 'v') {
			string stra, strb;
			int pos = 3;
			for (int i = 3; i < s.size(); i++) {
				if (s[i] != ' ') {
					stra += s[i];
				}
				else break;
			}
			strb = s.substr(pos+2);
			ct.mv_a2b(stra, strb);
		}
		else if (s[0] == 'c' && s[1] == 'd' && s[3] != '.') {
			string str = s.substr(3);
			ct.cdstr(str);
		}
		else if (s.substr(0, 5) == "mkdir") {
			if (s[5] == '-'&&s[6]=='s') {
				string str = s.substr(8);
				ct.mkdir_r(str);
			}
			else if (s[5] == '-' && s[6] == 'm') {
				string str = s.substr(8);
				ct.mkdir_p(str);
			}
			else {
				string str = s.substr(6);
				ct.mkdir(str);
			}
		}
		else if (s.substr(0, 6) == "mkfile") {
			if (s[6] == '-'&& s[7]!='s') {
				string str = s.substr(9);
				ct.mkfile_r(str);
				continue;
			}
			else if (s[6] == '-' && s[7] == 's') {// mkfile-s a 100
				string stra, strb;
				int pos = 0;
				for (int i = 9; i < s.size(); i++) {
					if (s[i] != ' ') {
						stra += s[i];
					}
					else {
						pos = i;
						break;
					}
				}
				strb = s.substr(pos + 1);
				int num = stoi(strb);
				ct.mkfile_size(stra, num);
				continue;
			}
			string str = s.substr(7);
			ct.mkfile(str);
		}
		else if (s.substr(0, 6) == "delete") {
			if (s[6] == '-') {
				string str = s.substr(9);
				ct.delet_r(str);
				continue;
			}
			string str = s.substr(7);
			ct.delet(str);
		}
		else if (s.substr(0, 4) == "save") {
			string str = s.substr(5);
			ct.save(str);
		}
		else if (s.substr(0, 4) == "load") {
			string str = s.substr(5);
			ct.load(str);
		}
		else if (s == "quit") {
			cout << "程序已退出\n";
			break;
		}
		else {
			cout << "wrong ops!\n";
		}
	}
}
void op3(string inname) {
	string s;
	CatalogTree ct;
	ct.put_flag=0 ;
	ct.inname=inname;
	while (getline(ct.ffin, s)) {
		if (s == "dir") {
			ct.dir();
		}
		else if (s == "cd") {
			ct.cd();
		}
		else if (s == "cd ..") {//cd..
			ct.cd_back();
		}
		else if (s[0] == 'c' && s[1] == 'd' && s[3] != '.') {
			string str = s.substr(3);
			ct.cdstr(str);
		}
		else if (s.substr(0, 5) == "mkdir") {
			string str = s.substr(6);
			ct.mkdir(str);
		}
		else if (s.substr(0, 6) == "mkfile") {
			string str = s.substr(7);
			ct.mkfile(str);
		}
		else if (s.substr(0, 6) == "delete") {
			string str = s.substr(7);
			ct.delet(str);
		}
		else if (s.substr(0, 4) == "save") {
			string str = s.substr(5);
			ct.save(str);
		}
		else if (s.substr(0, 4) == "load") {
			string str = s.substr(5);
			ct.load(str);
		}
		else if (s == "quit") {
			cout << "程序已退出\n";
			break;
		}
		else {
			cout << "wrong ops!\n";
		}
	}
}

void welcome() {
	while (1)
	{
		cout << "*********************************\n";
		cout << "虚拟文件系统\n";
		cout << "选择数据输入方式\n";
		cout << "DATA1 输入十个样例数据集\n";
		cout << "DATA2 手动输入数据\n";
		cout << "DATA3 输入指定路径的文件\n";
		cout << "*********************************\n";
		string da; cin >> da;

		if (da == "DATA1") {
			cout << "输出在CMD还是文件？\nCMD : 0\nFILE :1\n";
			int ans; cin >> ans;
			for (int i = 0; i <= 9; i++)
			{
				op1(i, ans);
			}
		}
		else if (da == "DATA2") {
			op2();
		}
		else if (da == "DATA3") {
			cout << "请输入路径。\n";
			string inname; cin >> inname;
			op3(inname);
		}
		else {
			cout << "错误的输入！请重新输入！";
		}
	}
}


int main() {
	welcome();
	return 0;
}

