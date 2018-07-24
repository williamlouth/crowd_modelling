#include "m_map.h"

m_map::m_map(QObject *parent) : QObject(parent)
{

}

void m_map::add_tile(tile* new_tile)
{
    t_list.append(new_tile);
}

