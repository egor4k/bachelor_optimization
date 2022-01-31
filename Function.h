#pragma once

#include<vector>

///An abstract class of function
class Function{
public:
    ///returns value of function in point x
    virtual double f(const std::vector<double>&x){}
    ///returns gradient of function in point x
    virtual std::vector<double>gradient(const std::vector<double>&x){}
    ///returns dimension of function
    virtual int dim()=0;
    virtual~Function(){}
};

///A class of function f(x,y)=x^2+y^4
class x2y4:public Function{
public:
    ///returns f(x[0], x[1])=x[0]^2+x[1]^4
    double f(const std::vector<double>&x)override;
    ///returns vector g=(2*x[0], 4*x[1]^3)
    std::vector<double>gradient(const std::vector<double>&x)override;
    ///retuns 2
    int dim()override;
};

///A class of Rosenbrock function f(x,y)=(x-1)^2+(y-x^2)^2
class Rosenbrock:public Function{
public:
    ///returns f(x[0], x[1])=(x[0]-1)^2+(x[1]-x[0]^2)^2;
    double f(const std::vector<double>&x)override;
    ///returns vector g=( 2(x[0]-1)-4x[0]*(x[1]-x[0]*x[0]), 2*(x[1]-x[0]*x[0])
    std::vector<double>gradient(const std::vector<double>&x)override;
    ///retuns 2
    int dim()override;
};

///A class of Boot function f(x,y)=(x+2y-7)^2+(2x+y-5)^2
class Boot:public Function{
public:
    ///returns f(x[0], x[1])=(x[0]+2*x[1]-7)^2+(2*x[0]+x[1]-5)^2;
    double f(const std::vector<double>&x)override;
    ///returns vector g=(2*(x[0]+2*x[1]-7)+4*(2*x[0]+x[1]-5), 4*(x[0]+2*x[1]-7)+2*(2*x[0]+x[1]-5))
    std::vector<double>gradient(const std::vector<double>&x)override;
    ///retuns 2
    int dim()override;
};

///A class of 3 dimensional function f(x,y)=(x-1)^2+(y-5)^2+(z-2)^2
class Dim_3:public Function{
public:
    ///returns f(x[0], x[1], x[2])=(x[0]-1)^2+(x[1]-5)^2+(x[2]-2)^2;
    double f(const std::vector<double>&x)override;
    ///returns vector g=(2(x[0]-1), 2*(x[1]-5), 2*(x[2]-2))
    std::vector<double>gradient(const std::vector<double>&x)override;
    ///retuns 3
    int dim()override;
};

///A class of function with two global minimas f(x,y)=(x^2-1)^2+(y^2-4)^2
class Extr_2:public Function{
public:
    ///returns f(x[0], x[1])=(x[0]*x[0]-1)^2+(x[1]*x[1]-4)^2;
    double f(const std::vector<double>&x)override;
    ///returns vector g=( 4*x[0]*(x[0]*x[0]-1), 4*x[1]*(x[1]*x[1]-4))
    std::vector<double>gradient(const std::vector<double>&x)override;
    ///retuns 2
    int dim()override;
};
