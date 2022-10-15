#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>

namespace Ui {
class calcwidget;
}

class calcwidget : public QWidget
{
    Q_OBJECT

public:
    explicit calcwidget(QWidget *parent = nullptr);
    ~calcwidget();

private slots:
    void on_plusR_clicked();

    void on_minusR_clicked();

    void on_multiplicationR_clicked();

    void on_divisionR_clicked();

    void on_sqrtR_clicked();

    void on_doButton_clicked();

    void on_sinR_clicked();

    void on_cosR_clicked();

private:
    Ui::calcwidget *ui;
};

#endif // CALCWIDGET_H
