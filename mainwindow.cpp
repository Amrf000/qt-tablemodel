#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int numbers[TableModel::COLUMNCOUNT*TableModel::ROWCOUNT]={0};
    model = new TableModel(numbers,sizeof(numbers)/sizeof(numbers[0]));
    ui->tableView->setModel(model);
    tDelegate = new TorrentViewDelegate(this);
    ui->tableView->setItemDelegateForColumn(TableModel::COLUMNCOUNT-1, tDelegate);
    ui->tableView->setColumnWidth(TableModel::COLUMNCOUNT-1,22);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

}

MainWindow::~MainWindow()
{
    delete model;
    delete tDelegate;
    timer->stop();
    delete timer;
    delete ui;
}

void MainWindow::onTimeOut()
{
     static TableData t;
     if(gQueue.isEmpty()){
         return;
     }
     gQueue.pop(t);
     model->setData(&t.data[0],TableModel::COLUMNCOUNT*TableModel::ROWCOUNT,model->index(0,0),model->index(TableModel::ROWCOUNT-1,TableModel::COLUMNCOUNT-1));
}

void MainWindow::on_pushButton_start_clicked(bool checked)
{
    if(checked){
        if(gQueue.isEmpty()){
            TableData t;//TODO: remove it
            for(int i=0;i<50;++i){
                t.Rand();
                gQueue.push(t);
            }
        }
        timer->start(20);
    }else{
        timer->stop();
    }
}

void MainWindow::on_pushButton_lock_clicked(bool checked)
{
    //static bool oldState;
    //static int flag = 0;
    if(checked){
         ui->tableView->setLock(false);
         ui->pushButton_lock->setText("锁定范围");
         //if(flag>0){
         //     ui->tableView->blockSignals(oldState);
         //}
         //flag = 1;
    }else{
        //oldState  = ui->tableView->blockSignals(true);
        ui->tableView->setLock(true);
        ui->pushButton_lock->setText("解除锁定");
    }
}
