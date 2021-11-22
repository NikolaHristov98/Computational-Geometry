#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include "vecta.h"

using namespace std;
using namespace vecta;

struct bounds {
	size_t hull1, hull2;
};

vector<vec2d<double>> readPoly(string path) {
	ifstream file(path);
	size_t s;
	file >> s;

	vector<vec2d<double>> res;

	for (size_t i = 0; i < s; i++) {
		vec2d<double> currvec;
		file >> currvec.x >> currvec.y;
		res.push_back(currvec);
	}

	return res;
}

void revqueue(queue<size_t>& q) {
	stack<size_t> t;
	while (q.size()) {
		t.push(q.front());
		q.pop();
	}
	while (t.size()) {
		q.push(t.top());
		t.pop();
	}
}

size_t findLeftmost(vector<vec2d<double>>& hull, size_t shull) {
	size_t currIndex = 0;

	for (size_t i = 1; i < shull; i++) {
		if (hull[i].x < hull[currIndex].x) {
			currIndex = i;
		}
	}

	return currIndex;
}

size_t findRightmost(vector<vec2d<double>>& hull, size_t shull) {
	size_t currIndex = 0;

	for (size_t i = 1; i < shull; i++) {
		if (hull[i].x > hull[currIndex].x) {
			currIndex = i;
		}
	}

	return currIndex;
}

queue<size_t> generateQueue(size_t from, size_t max, bool reverse = false) {
	int inc = 1;
	if (reverse) inc = -1;

	queue<size_t> result;
	result.push(from);

	for (size_t i = from + inc; true; i += inc) {
		if (i == -1) i = max - 1;
		if (i == max) i = 0;
		if (i == from)break;
		result.push(i);

	}

	return result;
}

bool arePositiveOriented(vector<vec2d<double>>& hull, size_t elem, size_t max, vec2d<double> pothhull) {
	if (elem + 1 >= max) {
		if (((hull[0] - hull[elem]) ^ (pothhull - hull[elem])) > 0) return true;
	}
	else {
		if (((hull[elem + 1] - hull[elem]) ^ (pothhull - hull[elem])) > 0) return true;
	}

	return false;
}

vector<vec2d<double>> joinHull(vector<vec2d<double>>& hull1, vector<vec2d<double>>& hull2, size_t shull1, size_t shull2) {
	bounds upper, lower;

	upper.hull1 = findRightmost(hull1, shull1);
	upper.hull2 = findLeftmost(hull2, shull2);
	lower = upper;

	queue<size_t> indhull1 = generateQueue(upper.hull1, shull1, !arePositiveOriented(hull1, upper.hull1, shull1, hull2[upper.hull2]));
	queue<size_t> indhull2 = generateQueue(upper.hull2, shull2, arePositiveOriented(hull2, upper.hull2, shull2, hull1[upper.hull1]));

	queue<size_t> tempindhull1 = indhull1, tempindhull2 = indhull2;

	size_t temp1 = tempindhull1.front(), temp2 = tempindhull2.front();
	tempindhull1.pop();
	tempindhull2.pop();

	while (1) {
		if (((hull1[tempindhull1.front()] - hull1[temp1]) ^ (hull2[temp2] - hull1[temp1])) > 0) {
			tempindhull1.push(temp1);
			temp1 = tempindhull1.front();
			tempindhull1.pop();
			continue;
		}
		if (((hull2[tempindhull2.front()] - hull2[temp2]) ^ (hull1[temp1] - hull2[temp2])) < 0) {
			tempindhull2.push(temp2);
			temp2 = tempindhull2.front();
			tempindhull2.pop();
			continue;
		}
		break;
	}

	upper.hull1 = temp1;
	upper.hull2 = temp2;

	tempindhull1 = indhull1, tempindhull2 = indhull2;
	revqueue(tempindhull1);
	revqueue(tempindhull2);

	temp1 = tempindhull1.front(), temp2 = tempindhull2.front();
	tempindhull1.pop();
	tempindhull2.pop();

	while (1) {
		if (((hull1[tempindhull1.front()] - hull1[temp1]) ^ (hull2[temp2] - hull1[temp1])) < 0) {
			tempindhull1.push(temp1);
			temp1 = tempindhull1.front();
			tempindhull1.pop();
			continue;
		}
		if (((hull2[tempindhull2.front()] - hull2[temp2]) ^ (hull1[temp1] - hull2[temp2])) > 0) {
			tempindhull2.push(temp2);
			temp2 = tempindhull2.front();
			tempindhull2.pop();
			continue;
		}
		break;
	}

	lower.hull1 = temp1;
	lower.hull2 = temp2;

	vector<vec2d<double>> newHull;

	revqueue(indhull2);

	while (indhull1.front() != lower.hull1) {
		temp1 = indhull1.front();
		indhull1.push(temp1);
		indhull1.pop();
	}

	while (indhull2.front() != upper.hull2) {
		temp2 = indhull2.front();
		indhull2.push(temp2);
		indhull2.pop();
	}

	while (indhull1.front() != upper.hull1){
		newHull.push_back(hull1[indhull1.front()]);
		indhull1.pop();
	} 
	newHull.push_back(hull1[indhull1.front()]);
	indhull1.pop();

	while (indhull2.front() != lower.hull2){
		newHull.push_back(hull2[indhull2.front()]);
		indhull2.pop();
	} 
	newHull.push_back(hull2[indhull2.front()]);
	indhull2.pop();

	size_t hsize = newHull.size();

	while (indhull2.size()) {
		newHull.push_back(hull2[indhull2.front()]);
		indhull2.pop();
	}

	while (indhull1.size()) {
		newHull.push_back(hull1[indhull1.front()]);
		indhull1.pop();
	}

	return newHull;
}

int main()
{
	auto firstpoly = readPoly("firstpoly.txt"), secondpoly = readPoly("secondpoly.txt");

	joinHull(firstpoly, secondpoly, firstpoly.size(), secondpoly.size());


}
