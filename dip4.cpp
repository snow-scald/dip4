// dip4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include<string>
#include"hxlbmpfile.h"
#include"Arith.h"
#include"WFloat.h"



int main()
{
	HXLBMPFILE bmpfile;
	if(!bmpfile.LoadBMPFile("input.bmp"))
	{
		return 1;
	}

	vector<int> originv;
	vector<int> testv;
	int temp;
	for(int i = 0; i < 1; i++)
	{
		for(int j = 0; j < 128; j++){
			
			temp = int(bmpfile.pDataAt(i)[j]);
			cout << temp << " ";
			originv.push_back(temp);
		}
	}
	cout << endl << endl;

	//WFloat trange(1);
	//string s = dtos(0);
	//cout << s+trange;


	//���� ��ȷ��������1000��128�����ص�һ����б��룬���������������
	printf("Image in!\n");
	arithencode(&bmpfile);
	vector<double>myrange = scrange(&bmpfile);
	vector<double>mylow = sclow(myrange);
	arithdecode(myrange, mylow);
}