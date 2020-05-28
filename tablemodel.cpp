#include "tablemodel.h"

TableModel::TableModel(int *rowsInfo,int len,QObject * parent /* = 0*/)
    : QAbstractTableModel(parent)//,m_isLocked(true)
{
    memcpy(this->rowsInfo, rowsInfo,len*sizeof(int));
}

int TableModel::columnCount(const QModelIndex & /*parent = QModelIndex()*/) const
{
    return COLUMNCOUNT;
}


int TableModel::rowCount(const QModelIndex & /* parent = QModelIndex()*/) const
{
    return ROWCOUNT;
}


QVariant TableModel::data(const QModelIndex & index, int role) const
{
    if (!IndexIsValid(index))
        return QVariant();


    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return rowsInfo[index.row()*COLUMNCOUNT+index.column()];

    return QVariant();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    // If you are displaying headers, will want to add more code here
    if (orientation == Qt::Horizontal)
        return QString("%1").arg(section+1);
    else
        return QString("%1").arg(section+1);
}


Qt::ItemFlags TableModel::flags(const QModelIndex & index) const
{
    if (!IndexIsValid(index))
        return Qt::ItemIsEnabled;

    //if (rowsInfo[index.row()]->CanBeChanged(index.column()))
    //    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
//    if(m_isLocked){
//        return QAbstractTableModel::flags(index) & ~Qt::ItemIsSelectable;
//    }

    return QAbstractTableModel::flags(index);

    /* Optional setting. Makes it so cannot select indexes that can't be changed (need to remove above return as well)
    // If you don't know what this does, look at http://stackoverflow.com/questions/3920307/how-can-i-remove-a-flag-in-c
    return QAbstractTableModel::flags(index) & ~Qt::ItemIsSelectable;
    */
}

bool TableModel::setData(const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole*/)
{
    if (index.column() < COLUMNCOUNT && IndexIsValid(index) && role == Qt::EditRole) {
        rowsInfo[index.row()*COLUMNCOUNT+index.column()]= value.toInt();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool TableModel::setData(int* rowsInfo,const int& len,const QModelIndex & leftTop,const QModelIndex & rightBottom){
    memcpy(this->rowsInfo, rowsInfo,len*sizeof(int));
    emit dataChanged(leftTop, rightBottom);
    return true;
}

//void TableModel::setLock(bool isLocked){
//    m_isLocked = isLocked;
//}

bool TableModel::IndexIsValid(const QModelIndex & index) const
{
    return index.isValid() && index.row() < rowCount();
}

