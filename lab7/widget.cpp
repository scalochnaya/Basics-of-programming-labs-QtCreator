#include "widget.h"
#include "ui_widget.h"
#include <QtMath>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_spinBox_valueChanged(int arg1) // добавление в таблицу кол-во строк согласно значению спинбокса
{
    ui->tableWidget->setRowCount(arg1);
}

bool Widget::cross(int x1, int x2, int y1, int y2, int x3, int x4, int y3, int y4) // проверка на пересечение с хабра
{
    double Ua, Ub, numerator_a, numerator_b, denominator;
    denominator=(y4-y3)*(x1-x2)-(x4-x3)*(y1-y2);

    if (denominator == 0)
    {
        if ( (x1*y2-x2*y1)*(x4-x3) - (x3*y4-x4*y3)*(x2-x1) == 0 && (x1*y2-x2*y1)*(y4-y3) - (x3*y4-x4*y3)*(y2-y1) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        numerator_a=(x4-x2)*(y4-y3)-(x4-x3)*(y4-y2);
        numerator_b=(x1-x2)*(y4-y2)-(x4-x2)*(y1-y2);
        Ua=numerator_a/denominator;
        Ub=numerator_b/denominator;
        return Ua >=0 && Ua <=1 && Ub >=0 && Ub <=1 ? true : false;
    }
}

int array[200][2]; // Обозначение двумерного глобального массива

bool Widget::fromTableToArray(int size) // Добавление значений таблицы в массив
{
    bool allOk = true; // Проверка на корректность значений в каждой ячейке, флаг

    for (int r = 0; r < size; r++) // Цикл по строкам
    {
        for(int c = 0; c < 2; c++) // Цикл по х, у
        {
            bool ok = false;
            QTableWidgetItem *cell = ui->tableWidget->item(r, c);
            if (cell != nullptr)
            {
                int d = cell->text().toInt(&ok);
                if (ok)
                {
                    array[r][c] = d;
                }
            }
            else
            {
                cell = new QTableWidgetItem;
                ui->tableWidget->setItem(r, c, cell);
            }
            cell->setBackground(ok ? Qt::white : Qt::red);

            allOk = allOk && ok;
            }
        }

        return allOk;
}

void Widget::on_pushButton_clicked() // Кнопка, которая задействует проверку на пересечение и расчет периметра / площади
{
    int size = ui->tableWidget->rowCount();
    if(fromTableToArray(size))
    {
        array[size][0] = array[0][0];
        array[size][1] = array[0][1];


        for (int c = 2; c < size - 1; c++)
        {
            bool flag = cross(array[0][0], array[1][0], array[0][1], array[1][1], array[c][0], array[c+1][0], array[c][1], array[c+1][1]); // Проверка на пересечение по  функции
                if (flag == true)
                {
                    ui->lineEdit->setText("ЕСТЬ ПЕРЕСЕЧЕНИЕ");
                    QMessageBox::warning(this, "ВНИМАНИЕ!", "Найдено пересечение"); // Ошибка в новом окне
                    ui->perEdit->clear();
                    ui->ploEdit->clear();
                    return;
                }
        }


        for (int r = 1; r < size - 2; r++)
        {
            for (int c = r+2; c < size; c++)
            {
                bool flag = cross(array[r][0], array[r+1][0], array[r][1], array[r+1][1], array[c][0], array[c+1][0], array[c][1], array[c+1][1]); // Снова проверка на пересечение
                if (flag == true)
                {
                    ui->lineEdit->setText("ЕСТЬ ПЕРЕСЕЧЕНИЕ");
                    QMessageBox::warning(this, "ВНИМАНИЕ!", "Найдено пересечение"); // Ошибка в новом окне
                    ui->perEdit->clear();
                    ui->ploEdit->clear();
                    return;
                }
            }
        }


        ui->lineEdit->clear();

        double ploshad = 0;

        for (int i = 0; i < size; i++)
        {
            ploshad += array[i][0] * array[i+1][1]; // Сложение и ывчитание к площади по принципу "площадь под графиком"
            ploshad -= array[i][1] * array[i+1][0];
        }
        if (ploshad != 0)
        {
            double perimetr = 0;
            for (int i = 0; i < size; i++)
            {
                perimetr += sqrt(qPow((array[i+1][0] - array[i][0]), 2) + qPow((array[i+1][1] - array[i][1]), 2)); // Подсчет и сложение сторон, Т Пифагора
            }
            ui->perEdit->setText(QString::number(perimetr)); // Вывод результата в эдиты периметра и площади
            ui->ploEdit->setText(QString::number(abs((ploshad)/2)));
        }
        else                                         // Если площадь нулевая
        {
            ui->perEdit->clear();
            ui->ploEdit->clear();
            ui->lineEdit->setText("ТАКОГО ТРЕУГОЛЬНИКА НЕ СУЩЕСТВУЕТ"); // Ошибка в новом окне
            QMessageBox::warning(this, "ВНИМАНИЕ!", "Такого треугольника не существует");
            return;
        }
    }
}
