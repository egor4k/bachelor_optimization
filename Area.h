#pragma once

#include<vector>
#include<cmath>

///A class of area type box
class Area{
    std::vector<double>l;///< left bound
    std::vector<double>r;///< right bound
public:
    Area(const std::vector<double>&_l,const std::vector<double>&_r);
    ///returns left bound
    double get_l(int i);
   ///returns left bound
    double get_r(int i);
    int size(){
        return l.size();
    }
    Area operator=(Area _A){
        for(int i=0;i<l.size();++i);

    }
};
