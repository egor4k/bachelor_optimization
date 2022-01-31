#include"Fletcher_Reeves.h"
#include<iostream>

double Fletcher_Reeves::local_argmin(Function *fun,const std::vector<double>&x,const std::vector<double>&p,double l0,double r0,const double eps){
    const double Phi((1+sqrt(5))/2);
    double l(l0+(r0-l0)*(2-Phi)),r(r0-(r0-l0)*(2-Phi));
    std::vector<double>xl(x.size()),xr(x.size());
    for(int i=0;i<x.size();++i){
        xl[i]=x[i]+l*p[i];
        xr[i]=x[i]+r*p[i];
    }
    double fl(fun->f(xl)),fr(fun->f(xr));
    while(r0-l0>eps){
        if(fl<fr){
            r0=r;
            r=l;
            xr=xl;
            fr=fl;
            l=l0+(r0-l0)*(2-Phi);
            for(int i=0;i<xl.size();++i)
                xl[i]=x[i]+l*p[i];
            fl=fun->f(xl);
        }
        else{
            l0=l;
            l=r;
            xl=xr;
            fr=fl;
            r=r0-(r0-l0)*(2-Phi);
            for(int i=0;i<xr.size();++i)
                xr[i]=x[i]+r*p[i];
            fr=fun->f(xr);
        }
    }
    return(l0+r0)/2;
}
double Fletcher_Reeves::argmin(Function *fun,const std::vector<double>&x,const std::vector<double>&p,const double l0,const double r0,const double eps){
    if(n==1)
        return local_argmin(fun,x,p,l0,r0,eps);
    std::vector<double>b(n+1);
    const double s=(r0-l0)/n;
    b[0]=l0;
    for(int i=1;i<b.size();++i)
        b[i]=b[i-1]+s;
    double amin(local_argmin(fun,x,p,b[0],b[1],eps));
    std::vector<double>y(fun->dim());
    for(int i=0;i<y.size();++i)
        y[i]=x[i]+amin*p[i];
    double fmin(fun->f(y));
    for(int i=0;i<n-1;++i){
        double a(local_argmin(fun,x,p,b[i],b[i+1],eps));
        for(int j=0;j<y.size();++j)
            y[j]=x[j]+a*p[j];
        if(fun->f(y)<fmin){
            fmin=fun->f(y);
            amin=a;
        }
    }
    return amin;
}
int Fletcher_Reeves::set_n(int _n){
    return n=_n;
}
double Fletcher_Reeves::possible_alpha(Area ar,const std::vector<double>&x,const std::vector<double>&p,const double alpha){
    double p_alpha(alpha);
    for(int i=0;i<x.size();++i){
        if(x[i]+p_alpha*p[i]<ar.get_l(i))
            p_alpha=(ar.get_l(i)-x[i])/p[i];
        if(x[i]+p_alpha*p[i]>ar.get_r(i))
            p_alpha=(ar.get_r(i)-x[i])/p[i];
    }
    return p_alpha;
}
std::vector<double>Fletcher_Reeves::optimize(Function *fun,Criteria *cr,Area ar,std::vector<double>&x,std::list<std::vector<double>>&tr,const double eps,const double alpha,const int steps){
    std::vector<double>g(fun->gradient(x)),P(g.size()),x0(x.size());
    double sq_norm_g(std::inner_product(g.begin(),g.end(),g.begin(),0.));
    for(int i=0;i<P.size();++i)
        P[i]=-g[i];
    //std::cout<<x0[0]<<x0[1]<<std::endl;
    do{
        x0=x;
        tr.push_back(x0);
        double sq_norm_g0(sq_norm_g);
        double p_alpha(possible_alpha(ar,x,P,alpha));
        double a(argmin(fun,x0,P,0,p_alpha,eps));
        for(int i=0;i<x.size();++i)
            x[i]=x0[i]+a*P[i];
        g=fun->gradient(x);
        sq_norm_g=std::inner_product(g.begin(),g.end(),g.begin(),0.);
        if(sq_norm_g<DBL_EPSILON)
            return x;
        double beta(sq_norm_g/sq_norm_g0);
        for(int i=0;i<P.size();++i)
            P[i]=-g[i]+beta*P[i];
        ++k;
    }while((cr->stop(fun,x0,x,eps))&&(k<steps));
    return x;
}
