#include "person.h"

person::person(QObject *parent,QList<float> n_coords, QList<float> in_destination) : QObject(parent)
{

    coords = n_coords;
    velocity ={0,1};
//    waypoints = in_waypoints;
//    waypoints = ;
//    m_target = {50,200};

    destination = in_destination;
    destination = {450,300};

    markers = {{50,300},{500,300}};
    m_target = markers[0];
    speed =2;
    dist_to_goal = 10;
    fat = 10.0;
    warn_size = 20;

    pushy = qrand() % 100;
    pushy = pushy/100.0;

    old_distances = {0};



}

QList<float> person::r_coords()
{
    return coords;
}

QRectF person::r_qrectf()
{
    qreal x = coords[0];
    qreal y = coords[1];
    float fat = 5;

    return QRectF(x-fat,y-fat,2*fat,2*fat);
}

void person::n_coords(QList<float> n_coords)
{
    coords = n_coords;
}

void person::do_move()
{
    make_markers();


    distances = {};
    check_ways();
    calc_velocity();
    collisions();

    for(int i=0; i<other_coords.count();i++)
    {
        distances.append(qSqrt(pow(other_coords[i][0] - (coords[0] + velocity[0]),2) + pow(other_coords[i][1] - (coords[1] + velocity[1]),2)));
    }

    double d_min = *std::min_element(distances.begin(), distances.end());
    double od_min = *std::min_element(old_distances.begin(), old_distances.end());


    for(int i=0; i<distances.count();i++)
    {
        if (distances[i] < warn_size)
        {
            if (d_min > od_min)
            {
                velocity[0] *= pushy;
                velocity[1] *= pushy;
            }

        }

        if (distances[i] < fat)
        {
            velocity[0] = 0;
            velocity[1] = 0;
        }
   }


    coords[0] += velocity[0];
    coords[1] += velocity[1];
    old_distances = distances;
}

void person::recieve_sig()
{
    emit send_pos(coords);
}



void person::r_coords_slot(QList<float> in_coords)
{
    other_coords.append(in_coords);
    return;
}

void person::r_map_slot(m_map* out_map)
{
    map_1 = out_map;
    return;
}

void person::calc_velocity()
{
    float vx = m_target[0] -coords[0];
    float vy = m_target[1] -coords[1];
    float s = qSqrt(pow(vx,2) + pow(vy,2));
    if(s >= speed)
    {
        velocity = {speed*vx/s,speed*vy/s};
    }
    else if(s == 0)
    {
        velocity = {0,0};
    }
    else
    {
        velocity = {vx,vy};
    }
}

void person::check_ways()
{
    float dist = qSqrt(pow(m_target[0] -coords[0],2) + pow(m_target[1] -coords[1],2));
    if( dist <= dist_to_goal && markers.size() >1)
    {
        markers.removeFirst();
        m_target = markers[0];
    }
}

void person::collisions()
{
    other_coords = {};
    emit find_pos();
    return;
}

void person::make_markers()
{
    emit get_map();
    markers = {destination};

    for (int i = 0; i < map_1->t_list.size();i++)
    {
        if (map_1->t_list[i]->m_contains(destination) && !map_1->t_list[i]->m_contains(coords))
        {
            markers.prepend(map_1->t_list[i]->closest(coords));
            QList<tile*>* neighbour = map_1->t_list[i]->r_neighour();
            for (int j = 0; j < neighbour->size(); j++)
            {
                if(neighbour[0][0]->m_contains(coords))
                {
                    qDebug() << "hi";
                }
            }
        }
    }

    A_star();


    if (! markers.isEmpty())
    {
        m_target = markers[0];
    }
    else
    {
        m_target = coords;
    }

}

void person::A_star()
{

}


