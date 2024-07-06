#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private:
    Ui::calculator *ui;
    double calcval;
        bool divTrigger;
        bool mulTrigger;
        bool addTrigger;
        bool subTrigger;

private slots:
    void numpressed();
    void mathbuttonpressed();
    void equalbuttonpressed();
    void changesignbuttonpressed();
    void clearbuttonpressed();
    void percentbuttonpressed();
    void decimalbuttonpressed();
};


#endif // CALCULATOR_H
