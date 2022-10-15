#include "calcwidget.h"
#include "ui_calcwidget.h"
#include "QtMath"
#include "qmath.h"

calcwidget::calcwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calcwidget)
{
    ui->setupUi(this);
}

calcwidget::~calcwidget()
{
    delete ui;
}

QString oper = " ", resstr, qls;
long double num1, num2, res;
bool ok1, ok2; //                                  Обозначение переменных

//                                                             Блок считывания операции

void calcwidget::on_plusR_clicked()
{
    oper = "+";
    ui->num1Label->setText(QString :: fromUtf8("Слагаемое 1"));
    ui->num2Label->setText(QString :: fromUtf8("Слагаемое 2"));
    ui->resultLabel->setText(QString :: fromUtf8("Сумма"));
    ui->num2Edit->show();
    ui->num2Label->show();
}
void calcwidget::on_minusR_clicked()
{
    oper = "-";
    ui->num1Label->setText(QString :: fromUtf8("Вычитаемое"));
    ui->num2Label->setText(QString :: fromUtf8("Вычитатель"));
    ui->resultLabel->setText(QString :: fromUtf8("Разность"));
    ui->num2Edit->show();
    ui->num2Label->show();
}
void calcwidget::on_multiplicationR_clicked()
{
    oper = "*";
    ui->num1Label->setText(QString :: fromUtf8("Множитель 1"));
    ui->num2Label->setText(QString :: fromUtf8("Множитель 2"));
    ui->resultLabel->setText(QString :: fromUtf8("Произведение"));
    ui->num2Edit->show();
    ui->num2Label->show();
}
void calcwidget::on_divisionR_clicked()
{
    oper = "/";
    ui->num1Label->setText(QString :: fromUtf8("Делимое"));
    ui->num2Label->setText(QString :: fromUtf8("Делитель"));
    ui->resultLabel->setText(QString :: fromUtf8("Частное"));
    ui->num2Edit->show();
    ui->num2Label->show();
}
void calcwidget::on_sqrtR_clicked()
{
    oper = "sqrt";
    ui->num1Label->setText(QString :: fromUtf8("Число"));
    ui->resultLabel->setText(QString :: fromUtf8("Корень"));
    ui->num2Edit->hide();
    ui->num2Label->hide();
}
void calcwidget::on_sinR_clicked()
{
    oper = "sin";
    ui->num1Label->setText(QString :: fromUtf8("Градусы"));
    ui->resultLabel->setText(QString :: fromUtf8("Синус"));
    ui->num2Edit->hide();
    ui->num2Label->hide();
}

void calcwidget::on_cosR_clicked()
{
    oper = "cos";
    ui->num1Label->setText(QString :: fromUtf8("Градусы"));
    ui->resultLabel->setText(QString :: fromUtf8("Косинус"));
    ui->num2Edit->hide();
    ui->num2Label->hide();
}

//                                                                 Нажатие на кнопку
void calcwidget::on_doButton_clicked()
{
    QPalette errorPalette, normalPalette;
    errorPalette.setColor(QPalette::Base, Qt::red);
    normalPalette.setColor(QPalette::Base, Qt::white);

    num1 = ui->num1Edit->text().toDouble(&ok1);
    num2 = ui->num2Edit->text().toDouble(&ok2);

    ui->num1Edit->setPalette(ok1 ? normalPalette : errorPalette);
    ui->num2Edit->setPalette(ok2 ? normalPalette : errorPalette);

    ui->resultEdit->clear();

    if (oper == " "){
        ui->errorEdit->setText(QString::fromUtf8("Операция не выбрана"));
        ui->resultEdit->clear();
    } else{
        ui->resultEdit->clear();

        if(!ok1 && !ok2){
            ui->errorEdit->setText(QString::fromUtf8("Оба операнда не числа"));
        } else if(!ok1 && ok2){
            ui->errorEdit->setText(QString::fromUtf8("1й операнд не число"));
        } else{
            ui->errorEdit->clear();

            if(oper == "sqrt" or oper == "sin" or oper == "cos"){
                if (oper == "sqrt"){
                    if (num1 >= 0){
                        res = sqrtl(num1);
                    }else{
                        ui->num1Edit->setPalette(errorPalette);
                        ui->errorEdit->setText(QString::fromUtf8("Корня отриц. числа не существует"));
                    }
                } else if (oper == "sin"){
                    long double x = fmodl(num1, 360);
                    double y = (long double) x;
                    res = sin(qDegreesToRadians(y));
                } else if (oper == "cos") {
                    long double x = fmodl(num1, 360);
                    double y = (long double) x;
                    res = cos(qDegreesToRadians(y));
                }
            } else {
                if(ok1 && !ok2){
                    ui->errorEdit->setText(QString::fromUtf8("2й операнд не число"));
                    ui->num2Edit->setPalette(errorPalette);
                } else {
                    if(oper == "+"){
                        res = num1 + num2;
                    } else  if(oper == "-"){
                        res = num1 - num2;
                    } else if(oper == "*"){
                        res = num1 * num2;
                    } else if(oper == "/"){
                        if (num2 == 0){
                            ui->num2Edit->setPalette(errorPalette);
                            ui->errorEdit->setText(QString::fromUtf8("Делить на 0 нельзя"));
                        } else{
                            res = num1 / num2;
                        }
                    }
                }
            }
            resstr = QString :: number(res, 'f', 10);
            ui->resultEdit->setText(resstr);

            qls = ui->resultEdit->text();
            if (qls == "inf" || qls == "nan"){
                ui->resultEdit->setText(QString::fromUtf8("Бесконечность"));
            }
        }
    }
}

