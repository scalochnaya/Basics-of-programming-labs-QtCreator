#include "logiclac.h"
#include "ui_logiclac.h"

logiclac::logiclac(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logiclac)
{
    ui->setupUi(this);
    deFunction();
}

logiclac::~logiclac()
{
    delete ui;
}

int n1, n2, res;
QString operation, resstr;

enum sym {
    I = 0,
    Ili = 1,
    LogNe = 2,
    IfTo = 3,
    Equal = 4,
    IsklIli = 5,
    Dec = 6,
    Inc = 7,
    Ne = 8
};

void logiclac::deFunction() //                Функция, выполняющаяся при каком-либо изменении
{
    n1 = ui->logicBox1->currentText().toInt(); n2 = ui->logicBox2->currentText().toInt(); operation = ui->operationBox->currentIndex();
        if (operation == I){
            res = n1 and n2;
        } else if (operation == Ili){
            res = n1 or n2;
        } else if (operation == LogNe){
            res = n1 != n2 ? 1 : 0;
        } else if (operation == IfTo){
            res = n1 == 1 && n2 == 0 ? 0 : 1;
        } else if (operation == Equal){
            res = n1 == n2 ? 1 : 0;
        } else if (operation == IsklIli){
            res = n1 == n2 ? 0 : 1;
        } else if (operation == Dec){
            res = n1 == 1 && n2 == 0 ? 1 : 0;
        } else if (operation == Inc){
            res = n1 == 0 && n2 == 1 ? 1 : 0;
        } else if (operation == Ne){
            res = abs(n1-1);
        }

        if (res == 1){
            QPalette green;
            green.setColor(QPalette::Window, qRgb(0, 255, 0));
            this->setPalette(green);
        } else {
            QPalette red;
            red.setColor(QPalette::Window, qRgb(255, 0, 0));
            this->setPalette(red);
        }

        resstr = QString::number(res);
        ui->resultEdit->setText(resstr);
    }

void logiclac::on_logicBox1_currentIndexChanged(const QString &arg1){deFunction();}
void logiclac::on_operationBox_currentIndexChanged(const QString &arg1){
    deFunction();
    if (operation == Ne){
        ui->logicBox2->hide();
    } else {
        ui->logicBox2->show();
    }
}
void logiclac::on_logicBox2_currentIndexChanged(const QString &arg1){deFunction();}
