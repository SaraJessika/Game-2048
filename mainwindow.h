#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QImage>
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void update();
    void itemSlot();

private:
    Ui::MainWindow *ui;

    QTimer *timer = new QTimer(); //таймер
    bool GAME = false; //играет
    int size_kletka = 50; //размер клетки
    int max_kletka = 9; //максимальное колличество клеток
    int POLESIIIZE = max_kletka*size_kletka; //размер поля
    int Score();

    int Pole [9][9] = {0}; //обнуляем(очищаем) массив

    void RanChis(); //рандом чисел
    QElapsedTimer Timesss;
    QString time_count();
};
#endif // MAINWINDOW_H
