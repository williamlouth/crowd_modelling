#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QRectF>

class tile : public QObject
{
    Q_OBJECT
public:
    explicit tile(QObject *parent = nullptr, float n_speed = 1.0, QList<float> n_coords={0,0,1,1});
    float r_speed();
    void c_speed(float new_speed);
    QList<float> r_coords();
    void c_coords(QList<float> n_coords);
    QRectF r_qrectf();

    bool m_contains(QList<float> in_coords);
    QList<float> closest(QList<float> in_coords);

    void add_neighbour(tile* in_tile);
    QList<tile*>* r_neighour();

protected:
    QList<float> coords;
    float speed;

signals:

public slots:

private:
    QList<tile*>* neighbours;
};

#endif // TILE_H
