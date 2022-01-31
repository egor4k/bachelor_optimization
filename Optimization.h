#pragma once

#include<cfloat>
#include<chrono>
#include<random>
#include<vector>
#include<list>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"

///An abstract class of optimizations methods
class Optimization{
protected:
    int k=0;///< number of iterations after counting minima
public:
    ///counts point of minima
    virtual std::vector<double>optimize(Function *fun,Criteria *cr,Area ar,std::vector<double>&x,std::list<std::vector<double>>&tr,const double eps=0.1,const double alpha=1.,const int steps=1000){}
    ///returns number of iterations after counting minima
    int get_k(){
        return k;
    }
    ///empty destructor
    virtual~Optimization(){}
};
