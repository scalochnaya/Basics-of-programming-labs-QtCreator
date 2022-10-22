#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class Widget;
extern QPalette nPalette, ePalette;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_createButton_clicked();

    void on_powEdit_textChanged(const QString &arg1);

    void on_agilEdit_textChanged(const QString &arg1);

    void on_intelEdit_textChanged(const QString &arg1);

    void on_luckEdit_textChanged(const QString &arg1);

    void on_mButton_clicked();

    void on_wButton_clicked();

private:
    Ui::Widget *ui;
    void pal(QLineEdit*, int&, int&);

};

#endif // WIDGET_H
