#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctime"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<int> allIter;
QVector<int> algIter;

void MainWindow::on_pushButton_clicked()

{
      for(int i = 0; i<ui->aligning_spinBox->value(); i++){
      int AlgorythmIterations = 0;
      int WholeIterations = 0;

      int SIZE = ui->vertex_spinBox->value();
      int EDGE = ui->edges_spinBox->value();
      int a[SIZE][SIZE];

      int d[SIZE]; // минимальное расстояние
      int v[SIZE]; // посещенные вершины
      int temp;
      int minindex, min;

      // Инициализация матрицы связей
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                   a[i][j] = 0;
            }
        }
       srand(time(NULL));
       int rand_1, rand_2, rand_3;
       for(int i = 0; i<EDGE; i++){
             do {
                    rand_1 = rand()%SIZE;
                    rand_2 = rand()%SIZE;
                } while (rand_1 == rand_2);

                rand_3 = rand()%100+1;

                a[rand_1][rand_2] = rand_3;
                a[rand_2][rand_1] = rand_3;

       }

      for (int i = 0; i<SIZE; i++)
      {
        d[i] = 2147483647;
        v[i] = 1;
      }
      d[0] = 0;
      // Шаг алгоритма
      do {
        AlgorythmIterations++;
        minindex = 2147483647;
        min = 2147483647;
        for (int i = 0; i<SIZE; i++)
        { // Если вершину ещё не обошли и вес меньше min
          WholeIterations++;
          if ((v[i] == 1) && (d[i]<min))
          { // Переприсваиваем значения
            min = d[i];
            minindex = i;
          }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 2147483647)
        {
          for (int i = 0; i<SIZE; i++)
          {
            WholeIterations++;
            if (a[minindex][i] > 0)
            {
              temp = min + a[minindex][i];
              if (temp < d[i])
                d[i] = temp;
            }
          }
          v[minindex] = 0;
        }
      } while (minindex < 2147483647);

      allIter.push_back(WholeIterations);
      algIter.push_back(AlgorythmIterations);
      }

      int AllIterAverage = 0;
      int AlgIterAverage = 0;

      for(int i = 0;i<allIter.size();i++){
        AllIterAverage += allIter.at(i);
      }

      AllIterAverage = AllIterAverage/ allIter.size();

      for(int i = 0;i<algIter.size();i++){
        AlgIterAverage += algIter.at(i);
      }

      AlgIterAverage = AlgIterAverage/ algIter.size();

      QString str;
      str += "Al. Iterations = " + QString::number(AlgIterAverage)+"\n";
      str += "Whole Iterations = " + QString::number(AllIterAverage) + "\n";

      ui->textBrowser->setText(str);
}
