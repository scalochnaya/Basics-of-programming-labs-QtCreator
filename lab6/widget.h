#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>

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
    void on_countButton_clicked();

    void warnColor(QLineEdit *le, bool ok);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
