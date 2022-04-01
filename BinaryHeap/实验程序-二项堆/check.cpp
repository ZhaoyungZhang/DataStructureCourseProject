#include<bits/stdc++.h>
#include<windows.h>
#define LL long long
#define MAXN 101000
using namespace std;
int main()
{
    int cnt = 100;
    int flag = 1;
	for(int i=1;i<=100;i++)
	{
        string a="F:\\vscpp\\BinaryHeap\\BinaryHeap\\outputSTD\\outputstd" 
            + to_string(i) + ".txt";

        string b= "F:\\vscpp\\BinaryHeap\\BinaryHeap\\outputSTD\\outputstd" 
            + to_string(i) + ".txt";
		string order="fc "+a+" "+b;
		if(system(order.c_str()))
		{
			puts("Wrong Answer!\n");
            flag = 0;
			break;
		}
        else{ cout<<"accept\n";
	    }
    }
    fir:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
	FOREGROUND_GREEN);
    if(flag) cout<<"ALL ACCEPT!\n";
    else cout<<"Wrong Answer!\n";
	return 0;
}


