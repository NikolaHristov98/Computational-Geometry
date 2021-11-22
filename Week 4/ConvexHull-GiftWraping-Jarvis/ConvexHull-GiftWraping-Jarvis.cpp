#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "vecta.h"

using namespace std;
using namespace vecta;

int main()
{
    size_t size;
    ifstream inpt("test2.txt", ios::in);

    inpt >> size;

    vector < vec2d<double>> arrPts;


    for (size_t i = 0; i < size; i++) {
        double x, y;
        inpt >> x >> y;

        arrPts.push_back(vec2d<double>(x, y));
    }
    
    //Взимаме най лявата точка, ако има повече от една взимаме най-долната
    size_t currPos = 0;

    for (size_t i = 1; i < size; i++) {
        if (arrPts[currPos].x > arrPts[i].x||(arrPts[currPos].x==arrPts[i].x&&arrPts[currPos].y>arrPts[i].y)) {
            currPos = i;
        }
    }

    size_t pos = 0;
    swap(arrPts[pos], arrPts[currPos]);
    pos++;
    
   while(1) {
        currPos = pos;

        for (size_t i = pos + 1; i < arrPts.size(); i++) {
            if (((arrPts[currPos] - arrPts[pos - 1]) ^ (arrPts[i] - arrPts[currPos])) < 0 || (((arrPts[currPos] - arrPts[pos - 1]) ^ (arrPts[i] - arrPts[currPos])) == 0 && (((arrPts[currPos] - arrPts[pos - 1]) ^ (arrPts[currPos] - arrPts[pos - 1])) < ((arrPts[i] - arrPts[currPos]) ^ (arrPts[i] - arrPts[currPos]))))) {
                currPos = i;
            }
        }

        if (((arrPts[currPos] - arrPts[pos - 1]) ^ (arrPts[0] - arrPts[currPos])) < 0) {
            break;
        }
       
        swap(arrPts[pos], arrPts[currPos]);
        pos++;
    }


   ofstream ofile("input.txt", ios::trunc);
   ofile << "unit 10" << endl;
   ofile << "polygon" << endl;
   for (size_t i = 0; i < pos; i++) {
       ofile << arrPts[i].x << " " << arrPts[i].y << endl;
   }
   ofile << "points" << endl;
   for (size_t i = 0; i < size; i++) {
       ofile << arrPts[i].x << " " << arrPts[i].y << endl;
   }
   ofile.close();
    

}
