#pragma once
//Ä£Äâ´ÅÅÌºÍÄÚ´æ
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include<fstream>
#include"minlosertree.h"
#include"QString"
using namespace std;



QString exsortt(minLoserTree<Player> &mt, int k,fstream& fin)
{
	mt.make_run(fin);
	if (k == 0)
	{
		k = max_run;
	}

	long int* a = new long int[k + 1];
	for (int i = 1; i <= k; i++) a[i] = INT_MAX;
	minLoserTree<long int> mt1(a, k);

	mt1.kk = k; mt1.get_total();
    mt1.merge_K(k, 1, 0);
    QString sa="exsort succeed\n";
    sa+= "you have maked " + QString::number(max_run)+ " runs\n";
    sa+= "and use " + QString::number(k) + " Merge\n"
                                           "visit disk " + QString::number(disk_times) + " times\n";
    return sa;
}




