
//#include "ann_1.1.2/include/ANN/ANN.h"
//#include "ann_1.1.2/src/ANN.cpp"
//#include "ann_1.1.2/src/kd_tree.cpp"

#include <ANN/ANN.h>
#include "CImg.h"
#include <bits/stdc++.h>
using namespace cimg_library;
using namespace std;



// g++ main2.cpp Iann/include -Lann/lib -lANN -L/usr/X11R6/lib -lm -lpthread -lX11
// -Iann/include -Lann/lib -lANN
vector<double> Vectorizar(string filename, int width, int height, int cuts=4)
{
    vector<double> R;
    CImg<double> img(filename.c_str());
    img.resize(width, height);
    CImg<double> img2 = img.haar(false, cuts);
    CImg<double> img3 = img2.crop(0, 0, 16, 16);
    cimg_forXY(img3, x, y){
        R.push_back((img(x, y, 0) + img(x, y, 1) +  img(x, y, 2)) / 3);
    }
    return R;
}


int main() {
const int N = 1000;
    const unsigned int K = 10;

    ifstream infile;
    infile.open("data.txt");
    string line, name, emocion;
    //ANNkd_tree::ANNkd_tree tree;

    int nPts; // actual number of data points
    ANNpointArray dataPts; // data points
    
    int dimension = 100;
    //dataPts = annAllocPts(maxPts, dimension);

    map<ANNpoint, pair<string,string>> ptrs;
    int i=0;
    vector<ANNpoint> coor;
    while (getline(infile, line)) {
        i++;
        int j = 0;
        ANNpoint pp;
        annAllocPt(dimension);

        stringstream ss(line);
        if(getline(ss, line, ' ')){
            name = line;
        }
        if(getline(ss, line, ' ')){
            emocion = line;
        }
        while(getline(ss, line, ' ')){
            pp[j++] = stod(line);
            coor.push_back(pp);
            //coor.push_back(stod(line));
        }
        //Point_d* pp = new Point_d(coor.begin(),coor.end());
        ptrs[pp] = {name,emocion};
        //tree.insert(*pp);
    }
    dataPts = annAllocPts(i, dimension);

    for(int k = 0; k < i ; k++){
        dataPts[k] = coor[k];
    }
    auto kdTree = new ANNkd_tree(dataPts,nPts,dimension);
    ANNpoint queryPt = annAllocPt(dimension);
    ifstream testfile;
    testfile.open("input.txt");
    while (getline(infile, line)) {
        //vector<double> coor;
        stringstream ss(line);
        if(getline(ss, line, ' ')){
            name = line;
        }
        if(getline(ss, line, ' ')){
            emocion = line;
        }
        int j = 0;
        while(getline(ss, line, ' ')){
            queryPt[j++] = stod(line);
            //coor.push_back(stod(line));
        }
        ANNidxArray nnIdx; // near neighbor indices
        ANNdistArray dists; // near neighbor distances
        int k=5;
        nnIdx = new ANNidx[k]; // allocate near neigh indices
        dists = new ANNdist[k];
        kdTree->annkSearch(queryPt,k,nnIdx,dists);
        for (int i = 0; i < k; i++) { 
            dists[i] = sqrt(dists[i]); 
            cout << i << " " << nnIdx[i] << " " << dists[i] << "\n";
        }
    }
}
