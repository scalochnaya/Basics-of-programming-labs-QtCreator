#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    bool fromTableToArray(int size);

    bool cross(int x1, int x2, int y1, int y2, int x3, int x4, int y3, int y4);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
