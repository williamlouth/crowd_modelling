#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QRectF>
#include <QtMath>
#include <QDebug>
#include <QTime>

#include "tile.h"
#include "m_map.h"

class person : public QObject
{
    Q_OBJECT
public:
    explicit person(QObject *parent = nullptr, QList<float> n_coords = {0,0}, QList<float> in_destination = {50,200});
    QList<float> r_coords();
    QRectF r_qrectf();
    void n_coords(QList<float> n_coords = {0,0});

    void do_move();

protected:


signals:
    void find_pos();
    void send_pos(QList<float> o_coords);
    void get_map();

public slots:
    void recieve_sig();
    void r_coords_slot(QList<float> in_coords);
    void r_map_slot(m_map* out_map);

private:
    QList<float> velocity;
    QList<float> coords;
    QList<float> m_target;

    QList<tile> waypoints;

    QList<QList<float>> markers;

    QList<float> destination;


    QList<QList<float>> other_coords;
    QList<float> distances;
    QList<float> old_distances;
    m_map* map_1;

    float speed;
    float dist_to_goal;
    float fat;
    float warn_size;
    float pushy;

    void calc_velocity();
    void check_ways();
    void collisions();
    void make_markers();

    void A_star();

};

#endif // PERSON_H
