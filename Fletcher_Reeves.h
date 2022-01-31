#pragma once

#include"Optimization.h"

///A class of Fletcger-Reeves optimization method
class Fletcher_Reeves:public Optimization{
    int n=10;///< number of local subintervals
    ///counts local argmin of scalar parameter alpha on interval from l0 to r0 by the direction p from point x, accuracy=eps
    double local_argmin(Function *fun,const std::vector<double>&x,const std::vector<double>&p,double l0,double r0,const double eps);
    ///counts global argmin of scalar parameter alpha on n subintervals by the direction p from point x, accuracy=eps
    double argmin(Function *fun,const std::vector<double>&x,const std::vector<double>&p,const double l0,const double r0,const double eps);
    double possible_alpha(Area ar,const std::vector<double>&x,const std::vector<double>&p,const double alpha);
public:
    ///sets number of local intervals
    int set_n(int _n);
    /// returns point of local minima of function using fletcher-reeves method
    /// *\param fun pointer to function to optimize
    /// *\param cr poinet to stop criteria
    /// *\param x point of start
    /// *\param alpha rigth bound of alpha for counting armin on dyrection p
    /// *\param steps maximal number of steps
    std::vector<double>optimize(Function *fun,Criteria *cr,Area ar,std::vector<double>&x,std::list<std::vector<double>>&tr,const double eps=0.1,const double alpha=1.,const int steps=1000)override;
};
