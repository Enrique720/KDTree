#define cimg_use_png 1
#include "CImg.h"
#include<bits/stdc++.h>


using namespace std;
using namespace cimg_library;

template<class T>
vector<T> vectorizar(CImg<T> &img){
    vector<T> R;
    cimg_forXY(img,x,y){ 
        R.push_back((img(x,y,0) + img(x,y,1) +  img(x,y,2))/3);
    }
    return R;
}

void readImages(string infile, string outfile, int haar){
    fstream input, output;
    input.open(infile, ios::in);
    output.open(outfile, ios::out | ios::trunc);

    string temp;
    while(input >> temp){
        CImg<float> A(temp.c_str());
        A = A.resize(160,160);
        CImg<float> B = A.haar(false,haar);
        CImg<float> C = B.crop(0,0,9,9);    
        vector<float> vc = vectorizar(C);
        output << temp << " ";
        for(auto valor : vc){
            output << valor << " ";
        }
        output << endl;
    }

    input.close();
    output.close();
}

int main(){
    readImages("db.txt","data.txt",4);
}