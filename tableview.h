#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView:public QTableView
{
    Q_OBJECT

public:
    TableView(QWidget *parent = 0);
     ~TableView();
    void setLock(bool lock);
protected slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    bool isLocked;
};

#endif // TABLEVIEW_H
