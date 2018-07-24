#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "tile.h"

class m_map : public QObject
{
    Q_OBJECT
public:
    explicit m_map(QObject *parent = nullptr);

    void add_tile(tile* new_tile);
    QList<tile*> t_list;

protected:

signals:

public slots:
};

#endif // MAP_H
