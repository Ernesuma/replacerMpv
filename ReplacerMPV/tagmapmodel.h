#ifndef TAGMAPMODEL_H
#define TAGMAPMODEL_H

#include <QDebug>
#include <QAbstractTableModel>
#include <QObject>
#include <QMap>

typedef QString tagMapKey;
typedef QString tagMapValue;
typedef QMap<tagMapKey, tagMapValue> tagMap;

class TagMapModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    // private Member
    tagMap m_map{};
    tagMapKey m_newKey{""};
    tagMapKey m_newValue{""};

public:
    // declare constructors
    TagMapModel(QObject *pParent=0);
    TagMapModel(const tagMap &map, QObject* pParent = 0);

    // empty destructor
    ~TagMapModel(){}

    // implement abstract methods
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    // own methods to add and remove values with custom parameters
    bool insert(const tagMapKey& key, const tagMapValue& value);
    bool removeRows(const QModelIndexList rows);
    bool removeAllRows();

    // getter to access the map as const reference
    const tagMap& getTagMap() const {return m_map;};
};

#endif // TAGMAPMODEL_H
