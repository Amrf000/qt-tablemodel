#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemDelegate>
#include "tablemodel.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <numeric>
#include "cyclequeue.h"

struct TableData{
  int data[TableModel::COLUMNCOUNT*TableModel::ROWCOUNT];
  void Rand(){
     for(int j=0;j<TableModel::ROWCOUNT;++j){
        for(int i=0;i<TableModel::COLUMNCOUNT;++i){
            if(i<TableModel::COLUMNCOUNT-2){
                data[j*TableModel::COLUMNCOUNT+i] = qrand() % ((100 + 1) - 0) + 0;
            }else if(i==TableModel::COLUMNCOUNT-2){
               std::accumulate(&data[j*TableModel::COLUMNCOUNT],&data[j*TableModel::COLUMNCOUNT]+18,data[j*TableModel::COLUMNCOUNT+i]);
            }else{

            }

        }
     }

  }
};

extern CycleQueue<TableData> gQueue;

namespace Ui {
class MainWindow;
}

class TorrentViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    inline TorrentViewDelegate(QObject  *mainWindow) : QItemDelegate(mainWindow) {
        m_image = new QImage("E:/dev/qtable/qt-tablemodel/butterfly.png");
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index ) const override
    {
        painter->drawImage(option.rect,*m_image);
    }
private:
    QImage* m_image;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked(bool checked);
    void onTimeOut();

    void on_pushButton_lock_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    TableModel* model;

    TorrentViewDelegate* tDelegate;
    QTimer *timer;
};

#endif // MAINWINDOW_H
