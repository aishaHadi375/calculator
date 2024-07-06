#include "calculator.h"
#include "ui_calculator.h"
#include<QDebug>

double calcval=0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
    ui->Display->setText("0");
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++){
        QString butname= "button"+ QString::number(i);
        numButtons[i]=calculator::findChild<QPushButton *>(butname);
        connect(numButtons[i], SIGNAL(released()), this, SLOT (numpressed()));
    }
    connect(ui->add, SIGNAL(released()), this, SLOT (mathbuttonpressed()));
    connect(ui->subtract, SIGNAL(released()), this, SLOT (mathbuttonpressed()));
    connect(ui->multiply, SIGNAL(released()), this, SLOT (mathbuttonpressed()));
    connect(ui->divide, SIGNAL(released()), this, SLOT (mathbuttonpressed()));
    connect(ui->equals, SIGNAL(released()), this, SLOT (equalbuttonpressed()));
    connect(ui->changesign, SIGNAL(released()), this, SLOT (changesignbuttonpressed()));
    connect(ui->percentage, SIGNAL(released()), this, SLOT(percentbuttonpressed())); // Connect percent button
    connect(ui->clear, SIGNAL(released()), this, SLOT(clearbuttonpressed()));
    connect(ui->decimal, SIGNAL(released()), this, SLOT(decimalbuttonpressed()));
}

calculator::~calculator()
{
    delete ui;
}
void calculator::numpressed(){
QPushButton *button =(QPushButton *)sender();
QString butval= button->text();
QString displayval =ui->Display->text();
if((displayval.toDouble()==0) && (displayval.length() == 1)){
    ui->Display->setText(butval);
}
else{
    QString newval = displayval + butval;
    double dbnewval= newval.toDouble();
    ui->Display->setText(QString::number(dbnewval, 'g', 16));
}
}
void calculator:: mathbuttonpressed(){
    divTrigger=false;
    mulTrigger=false;
    addTrigger=false;
    subTrigger=false;
    QString displayval =ui->Display->text();
   calcval= displayval.toDouble();
   QPushButton *button=(QPushButton *)sender();
   QString butval = button->text();
   if(QString::compare(butval, "/", Qt::CaseInsensitive)==0){
       divTrigger=true;
   }
   else if(QString::compare(butval, "*", Qt::CaseInsensitive)==0){
       mulTrigger=true;
   }
   else if(QString::compare(butval, "+", Qt::CaseInsensitive)==0){
       addTrigger=true;
   }
   else{
       subTrigger=true;
   }
     ui->Display->setText("");
}
void calculator:: equalbuttonpressed(){
    double solution= 0.0;
    QString displayval = ui->Display->text();
    double dbdisplayval=displayval.toDouble();
    if(addTrigger|| subTrigger|| mulTrigger||divTrigger){
        if(addTrigger){
            solution=calcval + dbdisplayval;
        }
        else if(subTrigger){
            solution=calcval - dbdisplayval;
        }
        else if(mulTrigger){
            solution=calcval * dbdisplayval;
        }
        else{
                solution=calcval / dbdisplayval;
        }
    }
    ui->Display->setText(QString::number(solution));
}
void calculator::changesignbuttonpressed(){
    QString displayval =ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayval)){
        double dbdisplayval = displayval.toDouble();
        double dbdisplayvalsign = -1* dbdisplayval;
        ui->Display->setText(QString::number(dbdisplayvalsign));
    }
}
void calculator::percentbuttonpressed() {
    QString displayval = ui->Display->text();
    double dbdisplayval = displayval.toDouble();
    double percentval = dbdisplayval / 100.0;
    ui->Display->setText(QString::number(percentval, 'g', 16));
}

void calculator::clearbuttonpressed() {
    calcval = 0.0;
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    ui->Display->setText("0");
}
void calculator::decimalbuttonpressed() {
    QString displayval = ui->Display->text();
    if (!displayval.contains('.')) {
        ui->Display->setText(displayval + ".");
    }
}











