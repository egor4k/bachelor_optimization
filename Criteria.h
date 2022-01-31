#pragma once

#include<vector>
#include<numeric>
#include<cmath>
#include"Function.h"

/// A class of stop criteria
class Criteria{
public:
    virtual bool stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps)=0;///< returns 1 if you should continue and 0 if you should stop
    virtual~Criteria(){}///< empty destructor
};

/// A class of stop criteria by the value of gradient norm
class Gradient:public Criteria{
public:
    bool stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps)override;
};

/// A class of stop criteria by the value of arguments
class Argument:public Criteria{
public:
    bool stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps)override;
};

/// A class of stop criteria by the value of function
class Value:public Criteria{
public:
    bool stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps)override;
};

/// A class of stop criteria by the quantity of steps
class Steps:public Criteria{
    bool stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps)override;
};
