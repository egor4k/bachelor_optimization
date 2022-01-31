#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_next_clicked()
{
    switch(ui->function->currentIndex()){
        case 0:F=new x2y4;break;
        default:F=new Rosenbrock;break;
    }
    alpha=ui->alpha->value();
    steps=ui->max_steps->value();
    std::vector<double>l(2),r(2);
    l[0]=ui->xl->value();
    l[1]=ui->yl->value();
    r[0]=ui->xr->value();
    r[1]=ui->yr->value();
    Area A(l,r);
    if(!ui->method->currentIndex()){
        FRDialog D(F,A,alpha,steps);
        D.exec();
    }else{
        StDialog D(F,A,alpha,steps);
        D.exec();
    }
}
