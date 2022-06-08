#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"hxlbmpfile.h"
#include"Arith.h"
#include"WFloat.h"
using namespace std;

string dtos(double num)
{
	string res{};
	int tint = floor(num);
	double tfloat = num - tint;
	if(tint==0)
	{
		res.insert(res.begin(), '0');
	}
	else{
		while(tint != 0)
		{
			res.insert(res.begin(), char(tint % 10 + '0'));
			tint /= 10;
		}
	}
	res.push_back('.');
	if(tfloat==0)
	{
		res.push_back('0');
	}
	else
	{
		int count = 0;
		while(tfloat != 0 && count < 10)
		{
			tfloat *= 10;
			res.push_back(char(floor(tfloat) + '0'));
			tfloat = tfloat - floor(tfloat);
			count++;
		}
	}	
	return res;
}

Mylongdouble::Mylongdouble(vector<char>tints){
	for(int i = 0; i < tints.size(); i++)
	{
		ints.push_back(int(tints[i]-'0'));
	}
}
Mylongdouble Mylongdouble::operator-(double r){
	if(r==0)
	{
		return *this;
	}
	double tdouble = 0;
	int p = 0;
	Mylongdouble res;
	while(r*10!=floor(r*10))
	{
		r = r * 10;
		if(p < ints.size())
		{
			tdouble = tdouble * 10 + ints[p];
		}
		else
		{
			tdouble = tdouble * 10;
		}
		p++;
	}
	long long ires = long long(tdouble - r);
	while(p!=0)
	{
		p--;
		res.ints.emplace(res.ints.begin(), int(ires % 10));
		ires = ires / 10;
	}
	return res;

}
//Mylongdouble Mylongdouble::operator/(double d){
//	int multi = int(1 / d);
//	int carry = 0;
//	int temp;
//	for(int i = ints.size()-1; i >-1; i--)
//	{
//		temp = (ints[i] * multi + carry);
//		ints[i] = temp%10;
//		carry = temp / 10;
//	}
//	while(ints[ints.size() - 1] == 0)
//	{
//		ints.pop_back();
//	}
//	return *this;
//}

Mylongdouble Mylongdouble::operator/(double d){
	long long upd=0;
	long long intd=long long(d*1000000000);
	Mylongdouble res;
	for(int i = 0; i < 10; i++)
	{
		if(i<ints.size())
		{
			upd = ints[i] + upd * 10;
		}
		else
		{
			upd *= 10;
		}
	}
	for(int i = 10; i < 20; i++)
	{
		res.ints.push_back( int( upd / intd));
		if(i < ints.size())
		{
			upd = (upd % intd)*10 + ints[i];
		}
		else
		{
			upd = (upd % intd) * 10;
		}
	}
	return res;
}


bool Mylongdouble::operator<(double r){
	double tdouble = 0;
	for(int i = 0; i < 10; i++)
	{
		if(i<ints.size())
		{
			tdouble = tdouble * 10 + ints[i];
		}
		else
		{
			tdouble = tdouble * 10;
		}
		r = r * 10;
	}
	return tdouble < r;
}
bool Mylongdouble::operator>(double r){
	double tdouble = 0;
	for(int i = 0; i < 10; i++)
	{
		if(i < ints.size())
		{
			tdouble = tdouble * 10 + ints[i];
		}
		else
		{
			tdouble = tdouble * 10;
		}
		r = r * 10;
	}
	return tdouble > r;
}


vector<double> scrange(HXLBMPFILE *bmp)
{
	vector<double> res(256, 0);
	for(int i = 0; i < bmp->iImageh; i++)
	{
		for(int j = 0; j < bmp->iImagew; j++)
		{
			res[bmp->pDataAt(i)[j]] += 1;
		}
	}
	for(int i = 0; i < 256; i++)
	{
		res[i] = res[i] / (bmp->iImageh * bmp->iImagew);
	}
	return res;
}

vector<double> sclow(vector<double> range){
	vector<double> res(256,0);
	double tempres = 0;
	for(int i = 0; i < 256; i++)
	{
		res[i] = tempres;
		tempres += range[i];
	}
	return res;
}



void arithencode(HXLBMPFILE *bmp){
	int count = 0;
	vector<double>myrange = scrange(bmp);
	vector<double>mylow = sclow(myrange);
	ofstream outdata("outdata.dat", ios::out | ios::binary);
	outdata.write((char *) &(bmp->iImageh), sizeof(int));
	outdata.write((char *) &(bmp->iImagew), sizeof(int));
	//long double tlow = 0;
	//long double thigh = 1;
	//long double trange = 1;
	WFloat tlow(0);
	WFloat thigh (1);
	WFloat trange (1);

	for(int i = 0; i < 1; i++)
	{
		for(int j = 0; j < 512; j++)
		{
			tlow = tlow + trange * dtos(mylow[bmp->pDataAt(i)[j]]);
			thigh = tlow + trange * dtos(myrange[bmp->pDataAt(i)[j]]);
			trange = thigh - tlow;
		}
		tlow = (tlow + thigh) / 2;
	}
	outdata << tlow;
	/*for(int i = 0; i < 1; i++)
	{
		for(int j = 4; j < 8; j++)
		{
			tlow = tlow + trange * mylow[bmp->pDataAt(i)[j]];
			cout << tlow << " ";
			thigh = tlow + trange * myrange[bmp->pDataAt(i)[j]];
			cout << thigh << " ";
			while(floor(tlow*10)==floor(thigh*10))
			{	
				cout << floor(tlow * 10);
				outdata <<char(floor(tlow * 10)+'0');
				count++;
				tlow= 10*tlow- floor(tlow * 10);
				thigh = 10 * thigh - floor(10 * thigh);
			}
			trange = thigh - tlow;
			cout << trange << " "<<endl;
		}
	}*/
	//while(tlow!=0)
	//{
	//	cout << floor(tlow * 10);
	//	outdata << char(floor(tlow * 10)+'0');
	//	count++;
	//	tlow = 10 * tlow - floor(tlow * 10);
	//}
	//cout << " " << count;
	cout << endl;
	outdata.close();
}

void arithdecode(vector<double>myrange, vector<double>mylow){
	HXLBMPFILE output;
	vector<char> inchars;
	ifstream inputdata("outdata.dat", ios::in | ios::binary);
	char tchar;
	inputdata.read((char *) &(output.iImageh), sizeof(int));
	inputdata.read((char *) &(output.iImagew), sizeof(int));
	output.iYRGBnum = 1;
	if(!output.IspImageDataOk())
	{
		return;
	}

	//使用自己完成的高精度浮点数失败
	//while(inputdata >> tchar)
	//{
	//	inchars.push_back(tchar);
	//}
	//Mylongdouble mycode(inchars);
	//for(int i1 = 0; i1 < 1 ; i1++){
	//	for(int i2 = 4; i2 < 8; i2++)
	//	{
	//		for(int j = 0; j < 256; j++)
	//		{
	//			if(mycode > mylow[j] && mycode < mylow[j] + myrange[j]){
	//				output.pDataAt(i1)[i2] = j;
	//				mycode = (mycode - mylow[j]) / myrange[j];//按说应该是小于1的值
	//				cout << j<<" ";
	//				break;
	//			}
	//		}
	//	}
	//}

	//使用long double失败
	//long double mycode;
	//inputdata >> mycode;
	//for(int i1 = 0; i1 < 1; i1++)
	//{
	//	for(int i2 = 0; i2 < 8; i2++)
	//	{
	//		for(int j = 0; j < 256; j++){
	//			if(mycode > mylow[j] && mycode < mylow[j] + myrange[j]){
	//				output.pDataAt(i1)[i2] = j;
	//				mycode = (mycode - mylow[j]) / myrange[j];
	//				cout << j << " ";
	//				break;
	//			}
	//		}
	//	}
	//}

	WFloat mycode;
	inputdata >> mycode;
	cout << endl << endl;
	for(int i1 = 0; i1 < 1; i1++)
	{
		for(int i2 = 0; i2 < 512; i2++)
		{
			for(int j = 0; j < 256; j++){
				if(mycode > dtos(mylow[j]) && mycode < dtos(mylow[j] + myrange[j])){
					output.pDataAt(i1)[i2] = j;
					mycode = (mycode - dtos(mylow[j])) / dtos(myrange[j]);
					cout << j << " ";
					break;
				}
			}
		}
	}


	//output.SaveBMPFile("testout.bmp");
	inputdata.close();
}