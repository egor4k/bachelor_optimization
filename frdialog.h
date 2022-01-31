#ifndef FRDIALOG_H
#define FRDIALOG_H

#include <QDialog>
#include<vector>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"
#include"Optimization.h"
#include"Fletcher_Reeves.h"
#include"Stochastic.h"
#include"qcustomplot.h"

namespace Ui {
class FRDialog;
}

class FRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FRDialog(Function*F,Area A,double alpha,int steps,QWidget *parent = nullptr);
    ~FRDialog();

private slots:
    void on_go_clicked();

    void mousePressEvent(QMouseEvent*event);
private:
    Ui::FRDialog *ui;
    Function*F;
    double alpha;
    int steps;
    std::vector<double>l,r;
    double eps;
    int n,st;
    std::vector<double>x0;
};

#endif // FRDIALOG_H
