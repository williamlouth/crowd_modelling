#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include "person.h"
#include "m_map.h"
#include "grass.h"
#include "wall.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    QList<person*>* pers_l;

    m_map* map_1;

    int* m_int;

signals:
    void send_map(m_map* out_map);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *circ;


    void do_draw(m_map* in_map,QList<person*>* in_pers_l);
    void make_pers(QList<float> n_coords = {0,0}, QList<float> destination = {0,0});

public slots:
    void m_tick();
    void recieve_sig();

};

#endif // MAINWINDOW_H
