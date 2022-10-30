#include "widget.h"
#include "ui_widget.h"
#include "qmath.h"
#include <QMessageBox>

QPalette redPalette, whitePalette; // Обозначение палитр (красный, белый)

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    redPalette.setColor(QPalette::Base, Qt::red); // Установка цвета на палитру
    whitePalette.setColor(QPalette::Base, Qt::white);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::warnColor(QLineEdit *le, bool ok){ // Изменение цвета лайнэдита при введенном некорректном значении
    if (!ok){
        le->setPalette(redPalette);
    } else {
        le->setPalette(whitePalette);
    }

}

double storona( double x1,   double y1,   double x2,   double y2){ // Функция по рассчету стороны треугольника
    x1 = sqrt((abs(x1-x2))*(abs(x1-x2)) + (abs(y1-y2)*abs(y1-y2)));
    return x1; // Функция возвращает длину стороны треугольника
}

void Widget::on_countButton_clicked() // Нажатие на кнопку
{
    double ax, ay, bx, by, cx, cy; // Обозначение переменных точек A, B, C в формате (x, y)
    double perimetr, ploshad; //  Обозначение переменных площади, периметра
    double ab, ac, bc; // Обозначение сторон треугольника
    bool ok1, ok2, ok3, ok4, ok5, ok6; // Обозначение булиевых переменных для проверки значений на корректность

    ax = ui->axEdit->text().toDouble(&ok1); // Считываем значения с лайнэдитов, переводим в тд double; проверяем на корректность
    ay = ui->ayEdit->text().toDouble(&ok2);
    bx = ui->bxEdit->text().toDouble(&ok3);
    by = ui->byEdit->text().toDouble(&ok4);
    cx = ui->cxEdit->text().toDouble(&ok5);
    cy = ui->cyEdit->text().toDouble(&ok6);

    if (!ok1 || !ok2 || !ok3 || !ok4 || !ok5 || !ok6){ // Окошко с ошибкой, некорректное значение
        QMessageBox::warning(this, "Внимание", "Введено некорректное значение");
        warnColor(ui->axEdit, ok1);
        warnColor(ui->ayEdit, ok2);
        warnColor(ui->bxEdit, ok3);
        warnColor(ui->byEdit, ok4);
        warnColor(ui->cxEdit, ok5);
        warnColor(ui->cyEdit, ok6);
        return ;
    }

    ab = storona(ax, ay, bx, by); // Вызов функции (считаем стороны треугольника)
    ac = storona(ax, ay, cx, cy);
    bc = storona(bx, by, cx, cy);

    perimetr = ab + ac + bc; // Периметр
    ploshad = sqrt(perimetr/2 * (perimetr/2 - ab) * (perimetr/2 - ac) * (perimetr/2 - bc)); // Площадь по формуле Герона

    ui->perEdit->setText(QString::number(perimetr)); // Вывод результата в лайнэдиты (периметр, площадь)
    ui->ploEdit->setText(QString::number(ploshad));
}
