#include"Area.h"

Area::Area(const std::vector<double>&_l,const std::vector<double>&_r){
    if(_l.size()!=_r.size())
        return;
    l=_l;
    r=_r;
}
double Area::get_l(int i){
    if(!l.size())
        return std::nan("");
    return l.at(i);
}
double Area::get_r(int i){
    if(!r.size())
        return std::nan("");
    return r.at(i);
}
