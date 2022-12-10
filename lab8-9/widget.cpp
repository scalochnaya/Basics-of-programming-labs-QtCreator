#include "widget.h"
#include "ui_widget.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QElapsedTimer>

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

int globalArray[200]; // Объявление глобального массива, который будет вбирать в себя значения из таблицы


void Widget::on_spinBox_valueChanged(int value) // Соответствие кол-ва столбцов со значением в спинбоксе
{
    ui->tableWidget->setRowCount(value);
}





//------------------------------------------------------------БЛОК ФУНКЦИЙ--------------------------------------------

bool Widget::fillArrayFromTable(int *array, int size){ // Функция заполнения массива из значений в таблице
    bool allOk = true;

    for (int r = 0; r < size; r++){
        bool ok = false;
        QTableWidgetItem *cell = ui->tableWidget->item(r, 0);
        if (cell != nullptr){
            int d = cell->text().toInt(&ok);
            if (ok){
                array[r] = d;
            }
        }
        else {
            cell = new QTableWidgetItem;
            ui->tableWidget->setItem(r, 0, cell);
        }
        cell->setBackground(ok ? Qt::white : Qt::red);
        allOk = allOk && ok;
    }

    return allOk;
}

void Widget::fillTableFromArray(int *array, int size){ // Функция заполнения таблицы из массива
    for (int j = 0; j < size; j++){
        QTableWidgetItem *cell = new QTableWidgetItem();
        cell = ui->tableWidget->item(j, 0);
        cell->setText(QString::number(array[j]));
        ui->tableWidget->setItem(j, 0, cell);
    }
}

void Widget::randNumsIntoTable(int size){ // Заполнение массива рандомными числами (функция)

    for (int j = 0; j < size; j++){
        ui->tableWidget->setItem(j, 0, new QTableWidgetItem("0"));
        QTableWidgetItem *cell = new QTableWidgetItem();
        cell = ui->tableWidget->item(j, 0);
        cell->setText(QString::number(qrand()));
        ui->tableWidget->setItem(j, 0, cell);
    }
}

//                                                         СОРТИРОВКИ, ФУНКЦИИ

bool is_sorted(int * array, int size) // Проверка, отсортирован ли массив
{
    for (int i = 1; i < size; ++i)
    {
         if (array[i] < array[i-1])
         {
              return false;
         }
    }
    return true;
}

void Widget::bubbleSort(int *array,int size) // Сортировка пузырьком
{
    if (!is_sorted(array, size)){
        int tmp, k;
        while(size > 1) {
            k = 0;
            for (int i=1; i< size; ++i) {
                if(array[i] < array[i-1]) {
                    tmp = array[i-1];
                    array[i-1] = array[i];
                    array[i] = tmp;
                    k = i;
                }
            }
            size = k;
        }
    }
}

void Widget::hairbrushSort(int *array,int size) // Сортировка расческой
{
    if (!is_sorted(array, size)){
        int tmp, k;
        int s = size;
        long long cnt = 0;
        while(size > 1) {
            s /= 1.247f;
            if (s < 1) s = 1;
            k = 0;
            for (int i=0; i+s < size; ++i) {
                if(array[i] > array[i+s]) {
                    tmp = array[i];
                    array[i] = array[i+s];
                    array[i+s] = tmp;
                    k = i;
                }
                ++cnt;
            }
            if (s == 1)
                size = k + 1;
        }
    }
}


void PeremeshivanieMassiva(int *array, int size) { // (Обезьянья сортировка) Перетасовка элементов в случайном порядке
  for (int i = 0; i < size; ++i)
    std::swap(array[i], array[rand() % size]);
}

void Widget::bogosort(int  *array, int size) // Обезьянья сортировка (основная функция)
{
    while (! is_sorted(array, size))
    {
         PeremeshivanieMassiva(array, size);
    }
}

void Widget::gnomeSort(int *array, int size) // Гномья сортировка
{
    if (!is_sorted(array, size)){
        int i = 1;

        while (i < size) {
            if (i == 0) {
                i = 1;
            }
            if (array[i-1] <= array[i]) {
                ++i;
            } else {
                int tmp = array[i];
                array[i] = array[i-1];
                array[i-1] = tmp;
                --i;
            }
        }
    }
}

void Widget::quickSort(int* array, int size) // Быстрая сортировка
{
    if (!is_sorted(array, size)){
        int sizeD = size;
        int pivot = 0;
        int ind = sizeD/2;
        int i, j = 0, k = 0;
        if(sizeD > 1){
            int* L = new int[sizeD];
            int* R = new int[sizeD];
            pivot = array[ind];
            for(i=0; i<sizeD; i++){
                if(i != ind){
                    if(array[i] < pivot){
                        L[j] = array[i];
                        j++;
                    }
                    else{
                        R[k] = array[i];
                        k++;
                    }
                }
            }
            quickSort(L,j);
            quickSort(R,k);
            for(int cnt=0; cnt<sizeD; cnt++){
                if(cnt<j){
                    array[cnt] = L[cnt];;
                }
                else if(cnt==j){
                    array[cnt] = pivot;
                }
                else{
                    array[cnt] = R[cnt - (j+1)];
                }
           }
       }
    }
}

void Widget::trueBubbleSort(int * array, int size){ // Честный пузырек
    if (!is_sorted(array, size)){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (array[j] > array[j + 1]) {
                    int b = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = b;
                }
            }
        }
    }
}





//----------------------------------------------ВЗАИМОДЕЙСТВИЕ С ВИДЖЕТОМ-----------------------------------------------


//                                    БЛОК ВЫЗОВА СОРТИРОВОК

void Widget::on_fastSortButton_clicked() // При нажатии на соответствующую кнопку вызывает функцию быстрой сортировки
{
    QElapsedTimer timer;
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        timer.start();
        quickSort(globalArray, n);
        long long time = timer.nsecsElapsed();

        fillTableFromArray(globalArray, n);
        QMessageBox::information(this, "Таблица отсортирована!", "Затраченное время: " + QString::number(time) + " нс.");
        return ;
    }

}

void Widget::on_hairbrushSortButton_clicked() // При нажатии на соответствующую кнопку вызывает функцию сортировки расческой
{
    QElapsedTimer timer;
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        timer.start();
        hairbrushSort(globalArray, n);
        long long time = timer.nsecsElapsed();

        fillTableFromArray(globalArray, n);
        QMessageBox::information(this, "Таблица отсортирована!", "Затраченное время: " + QString::number(time) + " нс.");
        return ;
    }
}

void Widget::on_bubbleSortButton_clicked() // При нажатии на соответствующую кнопку вызывает функцию сортировки пузырьком
{
    QElapsedTimer timer;
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        timer.start();
        bubbleSort(globalArray, n);
        long long time = timer.nsecsElapsed();

        fillTableFromArray(globalArray, n);
        QMessageBox::information(this, "Таблица отсортирована!", "Затраченное время: " + QString::number(time) + " нс.");
        return ;
    }
}

void Widget::on_monkeSortButton_clicked() // При нажатии на соответствующую кнопку вызывает функцию обезьяньей сортировки
{
    QElapsedTimer timer;
    int n = ui->tableWidget->rowCount();

    if (n >= 10){
        QMessageBox::warning(this, "Внимание!", "Использовать обезьянью сортировку для этого не очень практично");
        return ;
    }
    else {
        if (fillArrayFromTable(globalArray, n)){
            timer.start();
            bogosort(globalArray, n);
            long long time = timer.nsecsElapsed();

            fillTableFromArray(globalArray, n);
            QMessageBox::information(this, "Таблица отсортирована!", "Затраченное время: " + QString::number(time) + " нс.");
            return ;
        }
    }
}

void Widget::on_gnomeSortButton_clicked() // При нажатии на соответствующую кнопку вызывает функцию гномьей сортировки
{
    QElapsedTimer timer;
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        timer.start();
        gnomeSort(globalArray, n);
        long long time = timer.nsecsElapsed();

        fillTableFromArray(globalArray, n);
        QMessageBox::information(this, "Таблица отсортирована!", "Затраченное время: " + QString::number(time) + " нс.");
        return ;
    }
}

void Widget::on_trueBubbleButton_clicked()  // При нажатии на соответствующую кнопку вызывает функцию честной сортировки пузырьком
{
    QElapsedTimer timer;
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        timer.start();
        trueBubbleSort(globalArray, n);
        long long time = timer.nsecsElapsed();

        fillTableFromArray(globalArray, n);
        QMessageBox::information(this, "Таблица отсортирована!", "Затраченное время: " + QString::number(time) + " нс.");
        return ;
    }
}


//                                    БЛОК РАСЧЕТА МАКС/МИН/СР ЗНАЧЕНИЙ

void Widget::on_maxButton_clicked() // При нажатии на кнопку max выводит наибольшее значение из ячееек таблицы
{
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        bubbleSort(globalArray, n);

        ui->countEdit->setText(QString::number(globalArray[n - 1]));
    } else {
        QMessageBox::critical(this, "Внимание!", "Значение(я) таблицы заполнены неправильно");
        return ;
    }
}

void Widget::on_minButton_clicked() // При нажатии на кнопку min выводит наименьшее значение из ячееек таблицы
{
    int n = ui->tableWidget->rowCount();

    if (fillArrayFromTable(globalArray, n)){
        bubbleSort(globalArray, n);

        ui->countEdit->setText(QString::number(globalArray[0]));
    } else {
        QMessageBox::critical(this, "Внимание!", "Значение(я) таблицы заполнены неправильно");
        return ;
    }
}

void Widget::on_srzButton_clicked() // При нажатии на кнопку ср.знач выводит среднее значение из ячееек таблицы
{
    int n = ui->tableWidget->rowCount();
    int srz = 0;

    if (fillArrayFromTable(globalArray, n)){
        bubbleSort(globalArray, n);

        for (int j = 0; j < n; j++){
            srz += globalArray[j];
        }
        ui->countEdit->setText(QString::number(srz / n));
    } else {
        QMessageBox::critical(this, "Внимание!", "Значение(я) таблицы заполнены неправильно");
        return ;
    }
}


//                                    БЛОК ГЕНЕРАЦИИ РАНДОМНЫХ ЗНАЧЕНИЙ В ТАБЛИЦЕ

void Widget::on_randomButton_clicked()
{
    int n = ui->tableWidget->rowCount();

    randNumsIntoTable(n); // Вызов функции, генерирующей рандомные значения в ячейках

}

//                                    БЛОК ПОИСКА

void Widget::on_findButton_clicked()
{
    int n = ui->tableWidget->rowCount();
    int findThisNum = ui->findEdit->text().toInt();
    int counter = 0;
    int* arrayOfNums = new int[n];
    QString nums;

    if (fillArrayFromTable(globalArray, n)){
        if (!is_sorted(globalArray, n)){
            // Линейный поиск
            bool flag = false;
            for (int i = 0; i < n; i++){
                if (globalArray[i] == findThisNum){
                    arrayOfNums[counter] = i;
                    counter++;
                    flag = true;
                }
            }
            if (!flag){
                QMessageBox::critical(this, "Внимание!", "Число не было найдено");
                return ;
            } else {
                for (int j = 0; j < counter; j++){
                    nums += " " + QString::number(arrayOfNums[j]);
                    if (j == counter - 1)
                        QMessageBox::information(this, "Число найдено", "Количество вхождений - " + QString::number(counter) + ", индексы ячеек -" + nums + "\nБыл использован линейный поиск");
                }
            }
        } else {
            // Бинарный поиск
            int left1 = 0, left2 = 0;
            int right1 = n, right2 = n;
            int mid1, mid2;
            int l = 0, r = 0;
            bool flag = false;

            while ((left1 <= right1)) {
                mid1 = (left1 + right1) / 2;

                if (globalArray[mid1] == findThisNum){
                    r = mid1;
                    left1 = mid1 + 1;
                    flag = true;
                    continue;
                }
                if (globalArray[mid1] > findThisNum){
                    right1 = mid1 - 1;
                }
                else {
                    left1 = mid1 + 1;
                }
            }
            while ((left2 <= right2)) {
                mid2 = (left2 + right2) / 2;

                if (globalArray[mid2] == findThisNum){
                    l = mid2;
                    right2 = mid2 - 1;
                    flag = true;
                    continue;
                }
                if (globalArray[mid2] > findThisNum){
                    right2 = mid2 - 1;
                }
                else {
                    left2 = mid2 + 1;
                }
            }

            if (r - l >= 0 && flag == true){
                for (int j = 0; j < r - l + 1; j++){
                    nums += " " + QString::number(l+j);
                    if (j == r - l)
                        QMessageBox::information(this, "Число найдено", "Количество вхождений - " + QString::number(r - l + 1) + ", индексы ячеек -" + nums + "\nБыл использован бинарный поиск");                }
            } else {
                QMessageBox::critical(this, "Внимание!", "Число не было найдено");
            }

        }
    } else {
        QMessageBox::critical(this, "Внимание!", "Значение(я) таблицы заполнены неправильно");
        return ;
    }
    delete [] arrayOfNums;
}

