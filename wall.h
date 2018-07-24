#ifndef WALL_H
#define WALL_H

#include <QObject>
#include "tile.h"

class wall : public tile
{
public:
    wall(float n_speed = 0, QList<float> n_coords= {0,0,1,1});
};

#endif // WALL_H
