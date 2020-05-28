#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
public:
    enum {
      COLUMNCOUNT = 20,
      ROWCOUNT = 40
    };
    TableModel(int *rowsInfo,int len,QObject * parent = 0);
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;


    // Make it editable
    Qt::ItemFlags flags(const QModelIndex & index) const override;
    bool setData(const QModelIndex & index, const QVariant & value,
        int role = Qt::EditRole) override;
    bool setData(int* rowsInfo,const int& len,const QModelIndex & leftTop,const QModelIndex & rightBottom);
    void setLock(bool isLocked);
private:
    bool IndexIsValid(const QModelIndex & index) const;

    // Will be stored with rowsInfo[row] being responsible for the displayed at the given row.
    int rowsInfo[COLUMNCOUNT*ROWCOUNT];
    bool m_isLocked;
};


#endif // TABLEMODEL_H
