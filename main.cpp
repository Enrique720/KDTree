#include <bits/stdc++.h>

using namespace std;

#include "CImg/CImg.h"

using namespace cimg_library;
using namespace std;

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



int main(){
    
        

}