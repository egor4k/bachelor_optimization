#include"Stochastic.h"

double Stochastic::set_p(double _p){
    return p=_p;
}
double Stochastic::set_delta(double _delta){
    return delta=_delta;
}
std::vector<double>Stochastic::optimize(Function *fun,Criteria *cr,Area ar,std::vector<double>&x,std::list<std::vector<double>>&tr,const double eps,const double alpha,const int steps){
    unsigned seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::bernoulli_distribution Ber(p);
    std::vector<double>x0(x);
    tr.push_back(x0);
    double fmin(fun->f(x0));
    for(int k=0;k<steps;++k){
        if(Ber(generator)){
            double box[x0.size()][2];
            for(int i=0;i<x0.size();++i){
                box[i][0]=std::max(x0[i]-delta,ar.get_l(i));
                box[i][1]=std::min(x0[i]+delta,ar.get_r(i));
            }
            for(int i=0;i<x0.size();++i){
                std::uniform_real_distribution<double>U(box[i][0],box[i][1]);
                x[i]=U(generator);
            }
            delta*=alpha;
        }else{
            for(int i=0;i<x0.size();++i){
                std::uniform_real_distribution<double>U(ar.get_l(i),ar.get_r(i));
                x[i]=U(generator);
            }
        }
        double fx(fun->f(x));
        if(fx<fmin){
            x0=x;
            fmin=fx;
            tr.push_back(x0);
        }
    }
    k=steps;
    return x0;
}
