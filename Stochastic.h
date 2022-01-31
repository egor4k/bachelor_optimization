#pragma once

#include"Optimization.h"

///A class of stochastic optimization
class Stochastic:public Optimization{
    double p,delta;
public:
    /// sets parameter p
    double set_p(double _p);
    /// sets parameter delta
    double set_delta(double _delta);
    ///returns point of local minima of function using stochastic method
    /// *\param fun pointer to function to optimize
    /// *\param cr poinet to stop criteria
    /// *\param ar area of finding local minima
    /// *\param x point of start
    /// *\param alpha parameter of decreasing delta
    /// *\param steps maximal number of steps

    std::vector<double>optimize(Function *fun,Criteria *cr,Area ar,std::vector<double>&x,std::list<std::vector<double>>&tr,const double eps=0.1,const double alpha=1.,const int steps=1000);
};
