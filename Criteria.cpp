#include"Criteria.h"

bool  Gradient::stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps){
    std::vector<double>g(fun->gradient(x));
    return (std::inner_product(g.begin(),g.end(),g.begin(),0.)>eps);
}


bool Argument::stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps){
    std::vector<double>y(x.size());
    for(int i=0;i<y.size();++i)
        y[i]=x[i]-x0[i];
    return(std::inner_product(y.begin(),y.end(),y.begin(),0.)>eps);
}

bool Value::stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps){
    return(abs((fun->f(x)-fun->f(x0))/fun->f(x))>eps);
}

bool Steps::stop(Function*fun,const std::vector<double>&x0,const std::vector<double>&x,const double eps){
    return true;
}
