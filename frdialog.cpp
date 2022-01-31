#include "frdialog.h"
#include "ui_frdialog.h"
#include<iostream>

FRDialog::FRDialog(Function*_F,Area _A,double _alpha,int _steps,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FRDialog),alpha(_alpha),steps(_steps)
{
    F=_F;
    l.resize(2);
    r.resize(2);
    x0.resize(2);
    l[0]=_A.get_l(0);
    l[1]=_A.get_l(1);
    r[0]=_A.get_r(0);
    r[1]=_A.get_r(1);
    x0[0]=(l[0]+r[0])/2;
    x0[1]=(l[1]+r[1])/2;
    ui->setupUi(this);

    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));
    ui->plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(l[0],r[0]);
    ui->plot->yAxis->setRange(l[1],r[1]);

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->plot->xAxis, ui->plot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(l[0],r[0]), QCPRange(l[1],r[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //colorMap->data()->setRange(QCPRange(-10,10), QCPRange(-10,10)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        std::vector<double>point(2);
        point[0]=x;
        point[1]=y;
        z = F->f(point); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->plot);
    ui->plot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Value of function");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot);
    ui->plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->plot->rescaleAxes();
}

FRDialog::~FRDialog()
{
    delete ui;
}

void FRDialog::on_go_clicked()
{
    eps=ui->epsilon->value();
    n=ui->subint->value();
    st=ui->stop->currentIndex();
    Area A(l,r);
    Criteria*C;
    switch(st){
        case 0:C=new Steps;break;
        case 1:C=new Value;break;
        case 2:C=new Gradient;break;
        default:C=new Argument;break;
    }
    if((x0[0]<l[0])||(x0[1]<l[1])||(x0[0]>r[0])||(x0[1]>r[1]))
        return;
    std::list<std::vector<double>>tr;
    Optimization*opt=new Fletcher_Reeves;
    std::vector<double>xp(opt->optimize(F,C,A,x0,tr,eps,alpha,steps));
    double fx(F->f(xp));
    int k(opt->get_k());
    ui->x->setText(QString::number(xp[0]));
    ui->y->setText(QString::number(xp[1]));
    ui->f->setText(QString::number(fx));
    ui->k->setText(QString::number(k));

    ui->plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(l[0],r[0]);
    ui->plot->yAxis->setRange(l[1],r[1]);

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->plot->xAxis, ui->plot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(l[0],r[0]), QCPRange(l[1],r[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //colorMap->data()->setRange(QCPRange(-10,10), QCPRange(-10,10)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        std::vector<double>point(2);
        point[0]=x;
        point[1]=y;
        z = F->f(point); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->plot);
    ui->plot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Value of function");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot);
    ui->plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    QCPCurve*tr_curve=new QCPCurve(ui->plot->xAxis,ui->plot->yAxis);
    tr_curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    tr_curve->setPen(QPen(Qt::black));
    //std::list<std::vector<double>>::iterator it;
//    tr_curve->addData(1,x0[0],x0[1]);
//    tr_curve->addData(2,0.,0.);
    int i(0);
    for(std::list<std::vector<double>>::iterator it=tr.begin();it!=tr.end();++it)
        tr_curve->addData(i++,(*it)[0],(*it)[1]);
    ui->plot->rescaleAxes();
    ui->plot->replot();
//    ui->plot->addGraph();
//    ui->plot->graph(0)->setPen(QPen(Qt::black));
//    QVector<double>X,Y;
//    std::vector<std::vector<double>>::iterator it;
//    for(it=tr.begin();it!=tr.end();++it){
//        X.push_back((*it)[0]);
//        Y.push_back((*it)[1]);
//    }
//    ui->plot->graph(0)->setData(X,Y);
}

void FRDialog::mousePressEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    x0[0]=ui->plot->xAxis->pixelToCoord(event->x());
    x0[1]=ui->plot->yAxis->pixelToCoord(event->y());
    eps=ui->epsilon->value();
    n=ui->subint->value();
    st=ui->stop->currentIndex();
    Area A(l,r);
    Criteria*C;
    switch(st){
        case 0:C=new Steps;break;
        case 1:C=new Value;break;
        case 2:C=new Gradient;break;
        default:C=new Argument;break;
    }
    if((x0[0]<l[0])||(x0[1]<l[1])||(x0[0]>r[0])||(x0[1]>r[1]))
        return;
    std::list<std::vector<double>>tr;
    Optimization*opt=new Fletcher_Reeves;
    std::vector<double>xp(opt->optimize(F,C,A,x0,tr,eps,alpha,steps));
    double fx(F->f(xp));
    int k(opt->get_k());
    ui->x->setText(QString::number(xp[0]));
    ui->y->setText(QString::number(xp[1]));
    ui->f->setText(QString::number(fx));
    ui->k->setText(QString::number(k));

    ui->plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(l[0],r[0]);
    ui->plot->yAxis->setRange(l[1],r[1]);

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->plot->xAxis, ui->plot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(l[0],r[0]), QCPRange(l[1],r[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //colorMap->data()->setRange(QCPRange(-10,10), QCPRange(-10,10)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        std::vector<double>point(2);
        point[0]=x;
        point[1]=y;
        z = F->f(point); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->plot);
    ui->plot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Value of function");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot);
    ui->plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    QCPCurve*tr_curve=new QCPCurve(ui->plot->xAxis,ui->plot->yAxis);
    tr_curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    tr_curve->setPen(QPen(Qt::black));
    //std::list<std::vector<double>>::iterator it;
//    tr_curve->addData(1,x0[0],x0[1]);
//    tr_curve->addData(2,0.,0.);
    int i(0);
    for(std::list<std::vector<double>>::iterator it=tr.begin();it!=tr.end();++it)
        tr_curve->addData(i++,(*it)[0],(*it)[1]);
    ui->plot->rescaleAxes();
    ui->plot->replot();
}
