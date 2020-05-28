#include "tableview.h"

TableView::TableView(QWidget *parent/* = 0*/):QTableView(parent),isLocked(true)
{
}

TableView::~TableView()
{
}

void TableView::setLock(bool lock)
{
    isLocked = lock;
}

void TableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if(isLocked){
//        QModelIndexList indexes = deselected.indexes();
//        QModelIndex first = selected.first();
//        QModelIndex last = selected.last();
       bool oldstate =  this->blockSignals(true);
       bool oldstate1 =  this->selectionModel()->blockSignals(true);
       this->selectionModel()->select(selected, QItemSelectionModel::Deselect);
       this->selectionModel()->select(deselected, QItemSelectionModel::Select);
       this->blockSignals(oldstate);
       this->selectionModel()->blockSignals(oldstate1);
    }
    viewport()->update();
}
