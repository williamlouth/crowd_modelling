#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QTime::currentTime().msec());
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);




    grass* grass_1 = new grass(20,{0,0,100,250});
    grass* grass_2 = new grass(20,{0,250,100,350});
    grass* grass_3 = new grass(20,{100,250,500,350});

    map_1 = new m_map();
    map_1->add_tile(grass_1);
    map_1->add_tile(grass_2);
    map_1->add_tile(grass_3);

    grass_1->add_neighbour(grass_2);
    grass_2->add_neighbour(grass_1);
    grass_2->add_neighbour(grass_3);
    grass_3->add_neighbour(grass_2);



    pers_l = new QList<person*>();

//    make_pers({25,10});
//    make_pers({50,10});
//    make_pers({75,10});

    for(int j = 5;j<150; j+=50)
    {
        for(int i = 25;i<100; i+=25)
        {
            make_pers({i,j});
        }
    }


    do_draw(map_1,pers_l);


//    qDebug() << map_1;
//    qDebug() << map_1->t_list[0];



    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(m_tick()));
    timer->start(100);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::do_draw(m_map* in_map, QList<person*>* in_pers_l)
{
    QBrush greenBrush(Qt::green);
    QBrush yellowBrush(Qt::yellow);

    QPen outpen(Qt::black);

    for(int i=0; i<in_map->t_list.size();i++)
    {
        rect = scene->addRect(in_map->t_list[i]->r_qrectf(),outpen,greenBrush);
    }

    for(int i=0; i<in_pers_l->count();i++)
    {
        circ = scene->addEllipse(in_pers_l[0][i]->r_qrectf(),outpen,yellowBrush);
    }

}

void MainWindow::make_pers(QList<float> n_coords, QList<float> in_destination)
{

    person* bob_2 = new person(this,n_coords,in_destination);

    for(int i=0; i<pers_l->count();i++)
    {
        connect((*pers_l)[i],SIGNAL(find_pos()),bob_2,SLOT(recieve_sig()));
        connect(bob_2,SIGNAL(find_pos()),(*pers_l)[i],SLOT(recieve_sig()));

        connect((*pers_l)[i],SIGNAL(send_pos(QList<float>)),bob_2,SLOT(r_coords_slot(QList<float>)));
        connect(bob_2,SIGNAL(send_pos(QList<float>)),(*pers_l)[i],SLOT(r_coords_slot(QList<float>)));

    }


    connect(bob_2,SIGNAL(get_map()),this,SLOT(recieve_sig()));
    connect(this,SIGNAL(send_map(m_map*)),bob_2,SLOT(r_map_slot(m_map*)));
    pers_l->append(bob_2);


    return;


}

void MainWindow::m_tick()
{

    for(int i=0; i<pers_l->count();i++)
    {
        (*pers_l)[i]->do_move();
    }


    do_draw(map_1,pers_l);



}

void MainWindow::recieve_sig()
{
    emit send_map(map_1);
}




