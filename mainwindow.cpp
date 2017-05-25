#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctime"
#include "cstdlib"

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

QVector<__int64> allIter;
QVector<__int64> algIter;
QString str_cache;

const __int32 INF = 2147483647;

__int32 **a;
__int32 *d; // минимальное расстояние
__int32 *v;

unsigned int start;
unsigned int TIME = 0;
unsigned int finish;
void MainWindow::on_pushButton_clicked()

{

      for(__int32 i = 0; i<ui->aligning_spinBox->value(); i++){

      __int64 AlgorythmIterations = 0;
      __int64 WholeIterations = 0;

      __int32 SIZE = ui->vertex_spinBox->value();
      __int32 EDGE = ui->edges_spinBox->value();
      a = new __int32*[SIZE];

        for(__int32 i = 0; i<SIZE; i++){
            a[i] = new __int32[SIZE];
         }
         d = new __int32[SIZE]; // минимальное расстояние
         v = new __int32[SIZE]; // посещенные вершины


      __int32 temp;
      __int32 minindex, min;

      // Инициализация матрицы связей
        for(__int32 i = 0; i<SIZE; i++){
            for(__int32 j = 0; j<SIZE; j++){
                   a[i][j] = 0;
            }
        }
       srand(time(NULL));
       __int32 rand_1, rand_2, rand_3;
       for(int i = 0; i<EDGE; i++){
             do {
                    rand_1 = rand()%SIZE;
                    rand_2 = rand()%SIZE;
                } while (rand_1 == rand_2 || a[rand_1][rand_2] != 0);

                rand_3 = rand()%100+1;

                a[rand_1][rand_2] = rand_3;
                a[rand_2][rand_1] = rand_3;

       }
      start = clock();
      for (__int32 i = 0; i<SIZE; i++)
      {
        d[i] = INF;
        v[i] = 1;
      }
      d[0] = 0;
      // Шаг алгоритма
      do {
        AlgorythmIterations++;
        minindex = INF;
        min = INF;
        for (__int32 i = 0; i<SIZE; i++)
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
        if (minindex != INF)
        {
          for (__int32 i = 0; i<SIZE; i++)
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
      } while (minindex < INF);

      allIter.push_back(WholeIterations);
      algIter.push_back(AlgorythmIterations);

      for(__int32 i = 0; i<SIZE; i++){
          delete a[i];
       }
      delete a;
      delete v;
      delete d;
      finish = clock();
      TIME += (finish - start);
//      start = 0;
//      finish = 0;

      }

      TIME = (finish - start)/ui->aligning_spinBox->value();

      __int64 AllIterAverage = 0;
      __int64 AlgIterAverage = 0;

      for(__int32 i = 0;i<allIter.size();i++){
        AllIterAverage += allIter.at(i);
      }

      AllIterAverage = AllIterAverage/ allIter.size();

      for(__int32 i = 0;i<algIter.size();i++){
        AlgIterAverage += algIter.at(i);
      }

      AlgIterAverage = AlgIterAverage/ algIter.size();

      QString str;
      str += "Al. Iterations = " + QString::number(AlgIterAverage)+"\n";
      str += "Whole Iterations = " + QString::number(AllIterAverage) + "\n";
      str += "Time = " + QString::number(TIME)+" ms " + "\n";

      str_cache+= str;

      //allIter.size()*32;

      allIter.clear();
      algIter.clear();

      ui->textBrowser->setText(str_cache);

}
