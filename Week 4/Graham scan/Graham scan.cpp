#include <iostream>
#include <vector>
#include <fstream>
#include "vecta.h"

using namespace std;
using namespace vecta;

vec2d<double> P; //cursed global variable.

int compareAngles(vec2d<double> pt1, vec2d<double> pt2){
	double area = (pt1 - P) ^ (pt2 - P);

	if (area == 0) {
		if (len(pt1) >= len(pt2)) {
			return -1;
		}
		else {
			return 1;
		}
	}

	if (area < 0) {
		return 1;
	}

	return -1;
}

int findMinElem(vector<vec2d<double>>& arr) {
	int currMin = 0;

	for (size_t i = 1; i < arr.size(); i++) {
		if (arr[currMin].y > arr[i].y||(arr[currMin].y == arr[i].y && arr[currMin].x > arr[i].x)) {
			currMin = i;
		}
	}

	return currMin;
}

void bubbleSort(vector<vec2d<double>>& arr) {
	for (size_t i = 1; i < arr.size() - 1; i++) {
		for (size_t j = 1; j < arr.size()-1; j++) {
			if (compareAngles(arr[j], arr[j + 1]) == 1) swap(arr[j], arr[j + 1]);
		}
	}
}

int sortColinear(vector<vec2d<double>>& arr) {
	size_t maxIter = arr.size();

	for (size_t i = 1; i < maxIter-1; i++) {
		if (((arr[i] - P) ^ (arr[i + 1] - P)) == 0) {
			vec2d<double> temp = arr[i + 1];
			arr.erase(arr.begin()+i+1);
			arr.push_back(temp);
			i--;
			maxIter--;
		}
	}

	return maxIter;
}

int main()
{
	vector<vec2d<double>> arr;
	ifstream file("test2.txt");
	size_t len;

	file >> len;


	vec2d<double> inpt;
	for (size_t i = 0; i < len; i++) {
		file >> inpt.x;
		file >> inpt.y;

		arr.push_back(inpt);
	}

	size_t res = findMinElem(arr);
	
	swap(arr[0], arr[res]);
	P = arr[0];
	bubbleSort(arr);
	size_t newSize = sortColinear(arr);

	if (newSize < 3) return 0;

	size_t currHull = 4;

	while (currHull <= newSize) {
		for (size_t i = 0; i < currHull - 2; i++) {
			if (((arr[i + 1] - arr[i]) ^ (arr[i + 2] - arr[i])) < 0) {
				vec2d<double> temp = arr[i + 1];
				arr.erase(arr.begin() + i + 1);
				arr.push_back(temp);
				i=0;
				newSize--;
				currHull--;
			}
		}
		currHull++;
	}


	if (((arr[currHull-1] - arr[currHull - 2]) ^ (arr[0] - arr[currHull - 2])) < 0) {
		vec2d<double> temp = arr[currHull - 1];
		arr.erase(arr.begin() + currHull - 1);
		arr.push_back(temp);
		newSize--;
		currHull--;
	}

	ofstream ofile("input.txt", ios::trunc);
	ofile << "unit 1" << endl;
	ofile << "polygon" << endl;
	for (size_t i = 0; i < currHull; i++) {
		ofile << arr[i].x << " " << arr[i].y << endl;
	}
	ofile << "points" << endl;
	for (size_t i = 0; i < len; i++) {
		ofile << arr[i].x << " " << arr[i].y << endl;
	}
	ofile.close();

}

