#ifndef STDIALOG_H
#define STDIALOG_H

#include <QDialog>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"
#include"Optimization.h"
#include"Fletcher_Reeves.h"
#include"Stochastic.h"
#include"qcustomplot.h"

namespace Ui {
class StDialog;
}

class StDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StDialog(Function*_F,Area _A,double _alpha,int _steps,QWidget *parent = nullptr);
    ~StDialog();

private slots:
    void on_pushButton_clicked();

    void mousePressEvent(QMouseEvent*event);
private:
    Ui::StDialog *ui;
    Function*F;
    double alpha;
    int steps;
    std::vector<double>l,r,x0;
    double p,delta;
};

#endif // STDIALOG_H
