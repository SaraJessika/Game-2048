#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QFont>
#include <QMouseEvent>
#include <QMessageBox>
#include "time.h" //хранить текущее время системы

//2 Лаба, 4 семестр
//2048
//Сарычева Алена
//2 курс МО

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionClassic_field, SIGNAL(triggered(bool)), this, SLOT(itemSlot())); //Классическое поле
    connect(ui->actionHard_Field, SIGNAL(triggered(bool)), this, SLOT(itemSlot())); // Сложное поле
    connect(ui->actionHardcore_Field, SIGNAL(triggered(bool)), this, SLOT(itemSlot())); //Очень сложное поле
    setFixedSize(POLESIIIZE, POLESIIIZE+ui->menubar->height()); //фиксируем поле(прибавляем меню)

    connect(timer, SIGNAL(timeout()), this, SLOT(update())); //таймер в update
    srand(time(0)); //запускает генератор рандомных чисел
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (GAME)
        {
            if (event-> key() == Qt::Key_Left)
            {
                for (int j = 0; j < max_kletka; j++)
                {
                    int i=1;
                    while ( i < max_kletka) //столбец
                    {
                        if (Pole[i][j]!=0 && ((Pole[i][j] == Pole[i-1][j]) || Pole[i-1][j] == 0))
                        {
                            Pole[i-1][j] = Pole[i][j]+Pole[i-1][j];
                            Pole[i][j] = 0;
                            if (i>1)
                                i--;
                        }
                        else i++;
                    }
                };
                RanChis();
                repaint();
            }
            if (event-> key() == Qt::Key_Right)
            {
                for (int j = 0; j < max_kletka; j++)
                {
                    int i=max_kletka-2;
                    while ( i > -1) //столбец
                    {
                        if (Pole[i][j]!=0 && ((Pole[i][j] == Pole[i+1][j]) || Pole[i+1][j] == 0))
                        {
                            Pole[i+1][j] = Pole[i][j]+Pole[i+1][j];
                            Pole[i][j] = 0;
                            if (i < max_kletka-2)
                                i++;
                        }
                        else i--;
                    }
                };
                RanChis();
                repaint();
            }
            if (event-> key() == Qt::Key_Up)
            {
                for (int i = 0; i < max_kletka; i++)
                {
                    int j=1;
                    while ( j < max_kletka) //строка
                    {
                        if (Pole[i][j]!=0 && ((Pole[i][j] == Pole[i][j-1]) || Pole[i][j-1] == 0))
                        {
                            Pole[i][j-1] = Pole[i][j]+Pole[i][j-1];
                            Pole[i][j] = 0;
                            if (j>1)
                                j--;
                        }
                        else j++;
                    }
                };
                RanChis();
                repaint();
            }
            if (event-> key() == Qt::Key_Down)
            {
                for (int i = 0; i < max_kletka; i++)
                {
                    int j=max_kletka-2;
                    while ( j > -1) //строка
                    {
                        if (Pole[i][j]!=0 && ((Pole[i][j] == Pole[i][j+1]) || Pole[i][j+1] == 0))
                        {
                            Pole[i][j+1] = Pole[i][j]+Pole[i][j+1];
                            Pole[i][j] = 0;
                            if (j < max_kletka-2)
                                j++;
                        }
                        else j--;
                    }
                };
                RanChis();
                repaint();
            }
        }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPoint start(0,20); //нач.точка
    painter.translate(start); //начинаем рисовать
    QFont sizeText = QFont(QString(),POLESIIIZE/8,POLESIIIZE/8,true); //задаем параметры текста
    painter.setFont(sizeText);    //применяем

    if (!GAME)
    {
    painter.setBrush(QBrush(QColor(110, 127, 181))); //раскрашиваю клетки
    QRect Global_Rect(0,0,POLESIIIZE,POLESIIIZE);
    painter.drawRect(Global_Rect); //задаю куб
    painter.drawText(QRect(Global_Rect), Qt::AlignCenter, QString("2048")); //закрепляем в центре
    }

    else
    {
        painter.setFont(QFont("",12)); //рисую в центре клетки
        painter.setBrush(QBrush(QColor(181, 110, 110))); //раскрашиваю клетки
        for (int i = 0; i < max_kletka; i++) //строки
        {
            for (int j = 0; j < max_kletka; j++) //столбцы
            {
                QRect MyRect(i*size_kletka,j*size_kletka,size_kletka,size_kletka); //хранит информацию о точке, и ее парамерах
                painter.drawRect(MyRect); //рисую квадрат

                QString kl1=QString("%1").arg(Pole[i][j]);//1 элемент = n
                if (Pole[i][j])
                    painter.drawText(MyRect,Qt::AlignCenter, kl1); //рисую числа
            }
        }
        painter.drawText(QPoint(0, (max_kletka+1)*size_kletka), QString("Score: ")+QString().setNum(Score()));//рисуем счет
        painter.drawText(QPoint(0, (max_kletka+2)*size_kletka), time_count());//рисуем время
    }
}

void MainWindow::itemSlot()
{
    QAction *obj = (QAction*)sender(); //оператор явного преобразования типа (QAction*), тк obj объект QObject

    if (obj == ui->actionClassic_field) //классическая игра 4х4
    {
        GAME = true;
        max_kletka = 4;
        POLESIIIZE = max_kletka*size_kletka;
    }

    if (obj == ui->actionHard_Field) //сложная игра 6х6
    {
        GAME = true;;
        max_kletka = 6;
        POLESIIIZE = max_kletka*size_kletka;
    }

    if (obj == ui->actionHardcore_Field) //очень сложная 9х9
    {
        GAME = true;;
        max_kletka = 9;
        POLESIIIZE = max_kletka*size_kletka;
    }

    setFixedSize(POLESIIIZE, POLESIIIZE+2*size_kletka+ui->menubar->height()); //фиксируем поле(прибавляем меню)

    for (int i = 0; i < max_kletka; i++)
        for (int j = 0; j < max_kletka; j++)
            Pole[i][j] = 0;          //обнуляю поле

    RanChis(); //рандомлю число
    RanChis(); //рандомлю число

    Timesss.start();
    repaint();
}

int MainWindow::Score() //подсчет рекорда
{
    int tmp = 0;
    for (int i = 0; i < max_kletka; i++)
        for ( int j = 0; j < max_kletka; j++)
               if (tmp < Pole[i][j])
                   tmp = Pole[i][j];
    return tmp;
}

void MainWindow::RanChis() //функция рандома
{
      int tmpX, tmpY;
      do
      {
          tmpX = rand()%max_kletka, tmpY = rand()%max_kletka; //рандомлю координаты
      }
      while ((Pole[tmpX][tmpY]!=0));
      //здесь две пары хорошие

      int num = rand()%100; //рандомлю с вероятностью 90:10

      if (num < 91)
          Pole[tmpX][tmpY] = 2;
      else Pole[tmpX][tmpY] = 4;
}

QString MainWindow::time_count() //считаем время
{
    if((int(Timesss.elapsed())/60000>=10)&&(int(Timesss.elapsed())/1000>=10))
            return "Time: "+QString().setNum(int(Timesss.elapsed())/60000)+":"+QString().setNum(int(Timesss.elapsed())/1000);
                else
                    if((int(Timesss.elapsed())/60000<10)&&(int(Timesss.elapsed())/1000>=10))
                        return "Time: 0"+QString().setNum(int(Timesss.elapsed())/60000)+":"+QString().setNum(int(Timesss.elapsed())/1000);
                else
                    if((int(Timesss.elapsed())/60000>10)&&(int(Timesss.elapsed())/1000<10))
                       return "Time: "+QString().setNum(int(Timesss.elapsed())/60000)+":0"+QString().setNum(int(Timesss.elapsed())/1000);
                else
                        return "Time: 0"+QString().setNum(int(Timesss.elapsed())/60000)+":0"+QString().setNum(int(Timesss.elapsed())/1000);
}

void MainWindow::update()
{

    if (GAME == false) //конец игры
    {
        QMessageBox :: information(this, "EXIT", "GAME OVER");
        qApp->exit();
    }
}
