#include"Function.h"

double x2y4::f(const std::vector<double>&x){
        return x[0]*x[0]+x[1]*x[1]*x[1]*x[1];
    }

std::vector<double>x2y4::gradient(const std::vector<double>&x){
        std::vector<double>g(x.size());
        g[0]=2*x[0];
        g[1]=4*x[1]*x[1]*x[1];
        return g;
    }

int x2y4::dim(){
        return 2;
    }

double Rosenbrock::f(const std::vector<double>&x){
        return (x[0]-1)*(x[0]-1)+(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0]);
    }

std::vector<double>Rosenbrock::gradient(const std::vector<double>&x){
        std::vector<double>g(x.size());
        g[0]=2*(x[0]-1)-4*x[0]*(x[1]-x[0]*x[0]);
        g[1]=2*(x[1]-x[0]*x[0]);
        return g;
    }

int Rosenbrock::dim(){
    return 2;
}

double Boot::f(const std::vector<double>&x){
        return (x[0]+2*x[1]-7)*(x[0]+2*x[1]-7)+(2*x[0]+x[1]-5)*(2*x[0]+x[1]-5);
    }

std::vector<double>Boot::gradient(const std::vector<double>&x){
        std::vector<double>g(x.size());
        g[0]=2*(x[0]+2*x[1]-7)+4*(2*x[0]+x[1]-5);
        g[1]=4*(x[0]+2*x[1]-7)+2*(2*x[0]+x[1]-5);
        return g;
    }

int Boot::dim(){
        return 2;
    }


double Dim_3::f(const std::vector<double>&x){
        return (x[0]-1)*(x[0]-1)+(x[1]-5)*(x[1]-5)+(x[2]-2)*(x[2]-2);
    }

std::vector<double>Dim_3::gradient(const std::vector<double>&x){
        std::vector<double>g(x.size());
        g[0]=2*(x[0]-1);
        g[1]=2*(x[1]-5);
        g[2]=2*(x[2]-2);
        return g;
    }

int Dim_3::dim(){
        return 3;
    }


double Extr_2::f(const std::vector<double>&x){
        return (x[0]*x[0]-1)*(x[0]*x[0]-1)+(x[1]*x[1]-4)*(x[1]*x[1]-4);
    }

std::vector<double>Extr_2::gradient(const std::vector<double>&x){
        std::vector<double>g(x.size());
        g[0]=4*x[0]*(x[0]*x[0]-1);
        g[1]=4*x[1]*(x[1]*x[1]-4);
        return g;
    }

int Extr_2::dim(){
        return 2;
    }
