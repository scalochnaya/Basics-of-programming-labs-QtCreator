#ifndef LOGICLAC_H
#define LOGICLAC_H

#include <QWidget>

namespace Ui {
class logiclac;
}

class logiclac : public QWidget
{
    Q_OBJECT

public:
    explicit logiclac(QWidget *parent = nullptr);
    ~logiclac();

private slots:

    void deFunction();

    void on_logicBox1_currentIndexChanged(const QString &arg1);

    void on_operationBox_currentIndexChanged(const QString &arg1);

    void on_logicBox2_currentIndexChanged(const QString &arg1);

private:
    Ui::logiclac *ui;
};

#endif // LOGICLAC_H
