#include "tile.h"

tile::tile(QObject *parent,float n_speed, QList<float> n_coords) : QObject(parent)
{
    speed =n_speed;
    coords = n_coords;
    neighbours = new QList<tile*>;
}

float tile::r_speed()
{
    return speed;
}

void tile::c_speed(float new_speed)
{
    speed = new_speed;
}

QList<float> tile::r_coords()
{
    return coords;
}

void tile::c_coords(QList<float> n_coords)
{
    coords = n_coords;
}

QRectF tile::r_qrectf()
{

    qreal x = coords[0];
    qreal y = coords[1];
    qreal w = coords[2]-coords[0];
    qreal h = coords[3]-coords[1];

    return QRectF(x,y,w,h);
}

bool tile::m_contains(QList<float> in_coords)
{
    if( in_coords[0] > coords [0] && in_coords[0] < coords [2] &&  in_coords[1] > coords [1] && in_coords[1] < coords [3])
    {
        return true;
    }
    else
    {
        return false;
    }
}

QList<float> tile::closest(QList<float> in_coords)
{
    QList<float> out_coords = {};
    if(in_coords[0] <coords[0])
    {
        out_coords.append(coords[0]);
    }
    else if(in_coords[0] >coords[2])
    {
        out_coords.append(coords[2]);
    }
    else
    {
        out_coords.append(in_coords[0]);
    }



    if(in_coords[1] <coords[1])
    {
        out_coords.append(coords[1]);
    }
    else if(in_coords[1] >coords[3])
    {
        out_coords.append(coords[3]);
    }
    else
    {
        out_coords.append(in_coords[1]);
    }


    return out_coords;
}

void tile::add_neighbour(tile* in_tile)
{
    neighbours->append(in_tile);
}

QList<tile*>* tile::r_neighour()
{
    return neighbours;
}


