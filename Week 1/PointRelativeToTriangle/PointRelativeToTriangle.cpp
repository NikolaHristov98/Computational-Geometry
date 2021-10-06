/*
Задача: По подадени 4 точки A, B, C, P, да се провери къде лежи точката P спрямо триъгълника ABC като се използват
насочените лица на ABP, BCP, CAP.

Вход:

*/
#include <iostream>
#include <fstream>
#include "vecta.h"
using namespace std;
using namespace vecta;

int getSign(double x) {
	if (x > 0)return 1;
	if (x < 0)return -1;
	return 0;
}


int main()
{
	//Tests 
	//0 0 2 0 1 1 0 0 - съвпада с А
	//0 0 2 0 1 1 2 0 - съвпада с B
	//0 0 2 0 1 1 1 1 - съвпада с C
	//0 0 2 0 1 1 1 0.5 - вътре в ABC
	//0 0 2 0 1 1 0 0.5 - изъвн в ABC
	//0 0 2 0 1 1 0.5 0.5 - върху CA
	//0 0 2 0 1 1 1 0 - върху AB
	//0 0 2 0 1 1 1.5 0.5 - върху BC

	double inptX, inptY;

	cout << "Xa = ";
	cin >> inptX;
	cout << "Ya = ";
	cin >> inptY;

	vec2d<> A(inptX, inptY);

	cout << "Xb = ";
	cin >> inptX;
	cout << "Yb = ";
	cin >> inptY;

	vec2d<> B(inptX, inptY);

	cout << "Xc = ";
	cin >> inptX;
	cout << "Yc = ";
	cin >> inptY;

	vec2d<> C(inptX, inptY);

	cout << "Xp = ";
	cin >> inptX;
	cout << "Yp = ";
	cin >> inptY;

	vec2d<> P(inptX, inptY);

	double ABP = (B - A) ^ (P - B);
	double BCP = (C - B) ^ (P - C);
	double CAP = (A - C) ^ (P - A);

	int sABP = getSign(ABP), sBCP = getSign(BCP), sCAP = getSign(CAP);

	//Ако две от лицата са 0 то съвпада с връх
	if (sABP == 0 && sABP == sBCP) {
		cout << "B" << endl;
		return 0;
	}

	if (sABP == 0 && sABP == sCAP) {
		cout << "A" << endl;
		return 0;
	}

	if (sBCP == 0 && sBCP == sCAP) {
		cout << "C" << endl;
		return 0;
	}

	//Ако само едно от лицата е нула
	if (sABP == 0) {
		if (sBCP == sCAP) cout << "AB" << endl;
		else cout << "-ABC" << endl;
		return 0;
	}

	if (sBCP == 0) {
		if (sABP == sCAP) cout << "BC" << endl;
		else cout << "-ABC" << endl;
		return 0;
	}

	if (sCAP == 0) {
		if (sABP == sBCP) cout << "CA" << endl;
		else cout << "-ABC" << endl;
		return 0;
	}

	if (sABP == sBCP && sBCP == sCAP) cout << "ABC";
	else cout<<"-ABC"<<endl;

	ofstream ofile("input.txt", ios::trunc);
	ofile << "unit 50" << endl;
	ofile << "polygon" << endl;
	ofile << A.x << " " << A.y << endl;
	ofile << B.x << " " << B.y << endl;
	ofile << C.x << " " << C.y << endl;
	ofile << "points" << endl;
	ofile << P.x << " " << P.y << endl;
	ofile.close();


	return 0;
}

