#pragma once
#include<cmath>
#include<fstream>
#include <iostream>
#include<vector>
#include"hxlbmpfile.h"
#include"WFloat.h"
using namespace std;

string dtos(double num);
vector<double> scrange(HXLBMPFILE *);
vector<double> sclow(vector<double>);
void arithencode(HXLBMPFILE *);
void arithdecode(vector<double>, vector<double>, vector<int> &);

/*class Mylongdouble{
private:
	vector<int> ints;
public:
	Mylongdouble(vector<char>tints = {});
	Mylongdouble operator-(double r);
	Mylongdouble operator/(double d);
	bool operator<(double r);
	bool operator>(double r);
};*/



