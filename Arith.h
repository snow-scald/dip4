#pragma once
#include<cmath>
#include<fstream>
#include <iostream>
#include<vector>
#include"hxlbmpfile.h"
#include"WFloat.h"
using namespace std;

string dtos(double num);


class Mylongdouble{
private:
	vector<int> ints;
public:
	Mylongdouble(vector<char>tints = {});
	Mylongdouble operator-(double r);
	Mylongdouble operator/(double d);
	bool operator<(double r);
	bool operator>(double r);
};

vector<double> scrange(HXLBMPFILE *bmp);
vector<double> sclow(vector<double> range);
void arithencode(HXLBMPFILE *bmp);
void arithdecode(vector<double>myrange, vector<double>mylow);

