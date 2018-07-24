#ifndef GRASS_H
#define GRASS_H

#include <QObject>
#include "tile.h"

class grass : public tile
{
public:
    grass(float n_speed = 2, QList<float> n_coords = {0.,0.,1.,1.});
};

#endif // GRASS_H
