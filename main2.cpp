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

    int nPts; // actual number of data points
    ANNpointArray dataPts; // data points
    
    int dimension = 100;

    map<ANNpoint, pair<string,string>> ptrs;
    int i=0;
    vector<ANNpoint> coor;
    while (getline(infile, line)) {
        i++;
        int j = 0;
        ANNpoint pp;
        pp = annAllocPt(dimension);
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
        ptrs[pp] = {name,emocion};
    }
    dataPts = annAllocPts(i, dimension);
    for(int k = 0; k < i ; k++){
        dataPts[k] = coor[k];
    }
    /*for(int k = 0; k < i ; k++){
        for(int p = 0; p < dimension; p++){
            cout << dataPts[k][p] << " ";
        }
        cout << endl;
    }*/

    ANNkd_tree* kdTree;
    kdTree = new ANNkd_tree(dataPts,i,dimension);
    ANNpoint queryPt;
    queryPt = annAllocPt(dimension);
    ifstream testfile;
    testfile.open("input.txt");

    while (getline(testfile, line)) {
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
        cout << "%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
        for (int i = 0; i < k; i++) { 
            dists[i] = sqrt(dists[i]); 
            cout << i << " " << nnIdx[i] << " " << dists[i] << "\n";
            cout << "first: " <<ptrs[dataPts[nnIdx[i]]].first << " second: ";
            cout << ptrs[dataPts[nnIdx[i]]].second << endl; 
            cout << "-------------------------" << endl;
        }
    }
}
