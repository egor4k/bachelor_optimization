#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"
#include"Optimization.h"
#include"Fletcher_Reeves.h"
#include"Stochastic.h"
#include"frdialog.h"
#include"stdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_next_clicked();

private:
    Ui::MainWindow *ui;
    Function*F;
    double alpha;
    int steps;

};
#endif // MAINWINDOW_H
