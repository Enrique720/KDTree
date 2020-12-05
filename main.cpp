#include <CGAL/Epick_d.h>
#include <CGAL/point_generators_d.h>
#include <CGAL/Manhattan_distance_iso_box_point.h>
#include <CGAL/K_neighbor_search.h>
#include <CGAL/Search_traits_d.h>
#include <CGAL/Search_traits.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <bits/stdc++.h>
#include "CImg.h"

using namespace std;

typedef CGAL::Epick_d<CGAL::Dimension_tag<100>> Kernel;
typedef Kernel::Point_d Point_d;
typedef Kernel::Iso_box_d Iso_box_d;
typedef Kernel TreeTraits;
typedef CGAL::Manhattan_distance_iso_box_point<TreeTraits> Distance;
typedef CGAL::Orthogonal_k_neighbor_search<TreeTraits, Distance> K_neighbor_search;
typedef K_neighbor_search::Tree Tree;

vector<double> Vectorizar(string filename, int width, int height, int cuts=4)
{
    vector<double> R;
    CImg<double> img(filename.c_str());
    img.resize(width, height);
    CImg<double> img2 = img.haar(false, cuts);
    CImg<double> img3 = img2.crop(0, 0, 16, 16);
    cimg_forXY(img3, x, y) 
    { 
        R.push_back((img(x, y, 0) + img(x, y, 1) +  img(x, y, 2)) / 3);
    }
    return R;
}

int main() {
    const int N = 1000;
    const unsigned int K = 10;

    Tree tree;

    ifstream infile;
    infile.open("data.txt");
    string line, name, emocion;
    map<Point_d*, pair<string,string>> ptrs;
    while (getline(infile, line)) {
        vector<double> coor;
        stringstream ss(line);
        if(getline(ss, line, ' ')){
            name = line;
        }
        if(getline(ss, line, ' ')){
            emocion = line;
        }
        while(getline(ss, line, ' ')){
            coor.push_back(stod(line));
        }
        Point_d* pp = new Point_d(coor.begin(),coor.end());
        ptrs[pp] = {name,emocion};
        tree.insert(*pp);
    }

    ifstream testfile;
    testfile.open("input.txt");
    while (getline(infile, line)) {
        vector<double> coor;
        stringstream ss(line);
        if(getline(ss, line, ' ')){
            name = line;
        }
        if(getline(ss, line, ' ')){
            emocion = line;
        }
        while(getline(ss, line, ' ')){
            coor.push_back(stod(line));
        }
        Point_d qq(coor.begin(),coor.end());
        K_neighbor_search search(tree, qq, 5);
        for(K_neighbor_search::iterator it = search.begin(); it != search.end(); ++it){
            cout << it->first << '\n';
        }
    }

    /*Point_d pp(0.1,0.1,0.1,0.1);

    Distance tr_dist;
    Neighbor_search N1(tree, pp, n); // eps=10.0, nearest=false
    std::cout << "For query rectangle = [0.1, 0.2]^4 " << std::endl
              <<  "the " << K << " approximate furthest neighbors are: " << std::endl;
    for (Neighbor_search::iterator it = N1.begin();it != N1.end();it++) {
        std::cout << " Point " << it->first << " at distance  " << tr_dist.inverse_of_transformed_distance(it->second) << std::endl;
    }*/
    return 0;
}