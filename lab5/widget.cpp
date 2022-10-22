#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QLineEdit>

QPalette wPalette, rPalette, oPalette, yPalette, gPalette;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->errorLabel->hide();

    wPalette.setColor(QPalette::Base, Qt::white);
    rPalette.setColor(QPalette::Base, Qt::red);
    oPalette.setColor(QPalette::Base, qRgb(253, 106, 2));
    yPalette.setColor(QPalette::Base, Qt::yellow);
    gPalette.setColor(QPalette::Base, Qt::green);
}

Widget::~Widget()
{
    delete ui;
}

int res, pow, agil, luck, intel, gen, w, h, xp, mp, att, def, err1 = 0, err2 = 0, err3 = 0, err4 = 0, ost;
QString resstr, oststr;


void Widget::on_createButton_clicked() //                                                        НАЖАТИЕ НА КНОПКУ
{
    w = ui->image->width();
    h = ui->image->height();

    ui->resEdit->setPalette(wPalette);

    ui->errorLabel->hide();
    ui->ostLabel->show();

    QString name = ui->nameEdit->text();
    if (gen == 2){
        ui->hiLabel->setText("Привет, г-жа " + name);
    } else if (gen == 1) {
        ui->hiLabel->setText("Привет, г-н " + name);
    } else {
        ui->hiLabel->setText("Определитесь с Вашим полом, пожалуйста");
    }
    pow = ui->powEdit->text().toInt();
    agil = ui->agilEdit->text().toInt();
    intel = ui->intelEdit->text().toInt();
    luck = ui->luckEdit->text().toInt();
    res = pow + agil + intel + luck;
    ost = 15 - res;
    oststr = QString::number(ost);
    if(res <= 15){
        resstr = QString::number(res);
        ui->resEdit->setText(resstr);
        ui->resEdit->setPalette(wPalette);
        //                                                                                  БЛОК С КАРТИНКАМИ И СТАТАМИ
        xp = (10*pow + 5*agil + 5*luck + 5*intel)/10;
        ui->xpEdit->setText(QString::number(xp));
        mp = (0*pow + 10*agil + 0*luck + 5*intel)/10;
        ui->mpEdit->setText(QString::number(mp));
        att = (10*pow + 5*agil + 0*luck + 10*intel)/10;
        ui->attEdit->setText(QString::number(att));
        def = (5*pow + 10*agil + 5*luck + 5*intel)/10;
        ui->defEdit->setText(QString::number(def));

            if (att >= 12){
                QPixmap doge(":/img/img/doge.png");
                ui->image->setPixmap(doge.scaled(w, h, Qt::KeepAspectRatio));
                ui->classBox->setCurrentIndex(2);
            } else if (gen == 1){
                if (att >= 10){
                    QPixmap geralt(":/img/img/geralt.png");
                    ui->image->setPixmap(geralt.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(2);
                } else if (att >= 9){
                    QPixmap rook(":/img/img/2603808.png");
                    ui->image->setPixmap(rook.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(1);
                } else if (att >= 7){
                    QPixmap friman(":/img/img/gordon.png");
                    ui->image->setPixmap(friman.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(2);
                } else if (att >= 6) {
                    QPixmap bishop(":/img/img/istockphoto-533191783-1024x1024.png");
                    ui->image->setPixmap(bishop.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(1);
                } else if (att >= 5) {
                    QPixmap knight(":/img/img/1423912022_520150214-smeshnye-demotivatory.png");
                    ui->image->setPixmap(knight.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(1);
                } else if (att >= 4) {
                    QPixmap james(":/img/img/james.png");
                    ui->image->setPixmap(james.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(2);
                } else if (att >= 3 ){
                    QPixmap king(":/img/img/570673.69460a55.5000x5000o.f3e0fff92cfc.png");
                    ui->image->setPixmap(king.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(1);
                } else if (att < 3){
                    QPixmap peshak(":/img/img/4EPXvmP0_vU.png");
                    ui->image->setPixmap(peshak.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(1);
                }
            } else if (gen == 2){
                if (xp >= 10){
                    QPixmap ferz(":/img/img/48-484147_queen-1-queen-chess-png.png");
                    ui->image->setPixmap(ferz.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(1);
                } else if (xp >= 8) {
                    QPixmap boss(":/img/img/boss.png");
                    ui->image->setPixmap(boss.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(2);
                } else if (xp >= 6){
                    QPixmap lara(":/img/img/lara.png");
                    ui->image->setPixmap(lara.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(2);
                } else{
                    QPixmap alyx(":/img/img/alyx.png");
                    ui->image->setPixmap(alyx.scaled(w, h, Qt::KeepAspectRatio));
                    ui->classBox->setCurrentIndex(2);
                }
            }

    } else {
        ui->errorLabel->show();
        ui->ostLabel->hide();
        ui->image->clear();
        ui->resEdit->clear();
        ui->resEdit->setPalette(rPalette);
        ui->classBox->setCurrentIndex(0);
    }

    if (err1 > 0 || err2 > 0 || err3 > 0 || err4 > 0){ //                                    ЕСЛИ НЕПРАВИЛЬНО УКАЗАНЫ ДАННЫЕ
        ui->image->clear();
        ui->resEdit->clear();
        ui->xpEdit->clear();
        ui->mpEdit->clear();
        ui->attEdit->clear();
        ui->defEdit->clear();
        ui->ostLabel->hide();
    } else {
        ui->ostLabel->setText("(осталось " + oststr + " очков(-а))");
    }


    QString luckstr = ui->luckEdit->text();
    QString intelstr = ui->intelEdit->text();
    QString powstr = ui->powEdit->text();
    QString agilstr = ui->agilEdit->text();

    if (luckstr == nullptr || intelstr == nullptr || agilstr == nullptr || powstr == nullptr){
        if (luckstr == nullptr)
            ui->luckEdit->setText("no");
        if (intelstr == nullptr)
            ui->intelEdit->setText("no");
        if (agilstr == nullptr)
            ui->agilEdit->setText("no");
        if (powstr == nullptr)
            ui->powEdit->setText("no");
        ui->mpEdit->clear();
        ui->xpEdit->clear();
        ui->attEdit->clear();
        ui->defEdit->clear();
        ui->ostLabel->hide();
    }
    if (luckstr == "no" || intelstr == "no" || agilstr == "no" || powstr == "no"){
        ui->resEdit->setPalette(rPalette);
        ui->classBox->setCurrentIndex(0);
    }


}

void Widget::pal(QLineEdit *edit, int &x, int &err){
    bool ok;
    x = edit->text().toInt(&ok);

    if (x <= 10 && x >= 0 && ok){
        if (x >= 0 && x <= 3){
            edit->setPalette(oPalette);
        } else if (x > 3 && x <= 7){
            edit->setPalette(yPalette);
        } else {
            edit->setPalette(gPalette);
        }
        err = 0;
    } else {
        edit->setPalette(rPalette);
        err++;
    }
}

void Widget::on_powEdit_textChanged(const QString &arg1) //                                        МЕНЕЕ 10 НА КАЖДЫЙ БЛОК
{
   pal(ui->powEdit, pow, err1);
}
void Widget::on_agilEdit_textChanged(const QString &arg1)
{
    pal(ui->agilEdit, agil, err2);
}
void Widget::on_intelEdit_textChanged(const QString &arg1)
{
    pal(ui->intelEdit, intel, err3);
}
void Widget::on_luckEdit_textChanged(const QString &arg1)
{
    pal(ui->luckEdit, luck, err4);
}

void Widget::on_mButton_clicked(){gen = 1;}//                                                              ПОЛ
void Widget::on_wButton_clicked(){gen = 2;}
