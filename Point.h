//
// Created by suro on 2020-11-28.
//

#ifndef KDTREE_POINT_H
#define KDTREE_POINT_H

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double vec[100];
    string name;
    string emocion;
    Point() {
        for(int i=0; i<100; i++) {
            vec[i] = 0;
        }
    }
    Point (vector<double> coor) {
        for(int i=0; i<100; i++) {
            vec[i] = coor[i];
        }
    }
    bool operator==(const Point& p) const{
        for(int i=0; i<100; i++) {
            if(vec[i] != p.vec[i]) return false;
        }
        return true;
    }
    bool  operator!=(const Point& p) const { return ! (*this == p); }
}; //end of class

struct Construct_coord_iterator {
    typedef  const double* result_type;
    const double* operator()(const Point& p) const
    { return static_cast<const double*>(p.vec); }
    const double* operator()(const Point& p, int)  const
    { return static_cast<const double*>(p.vec+3); }
};


#endif //KDTREE_POINT_H
