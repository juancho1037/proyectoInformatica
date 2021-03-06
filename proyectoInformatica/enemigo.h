#ifndef ENEMIGO_H
#define ENEMIGO_H
//#define DEBUG_ENEMIGO

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <proyectil.h>
#include <random>
#include <QTimer>
#include <movimientos.h>
#include <QMediaPlayer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include "animaciones.h"
#include "personaje.h"
#include "bonusrocket.h"
#include "bonuslife.h"

class enemigo : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
private:
    bool direction; // true Derecha // false izquierda
    //qreal last_position;
    QTimer *timer;
    QPixmap *pixmap_zombie;
    QMediaPlayer *sonido;
    qreal columnas, alto, ancho, *last_position;
    long int velocidad;
    short int amplitud, limite;
    unsigned short int temporal;
    bool habilidad;
    unsigned short int cambio;

    // metodos privados

    void cambiarAnimacion(); // encargado el movimiento del sprite // refresco
    void asignarCaracteristicas(); // asignar aleatoriamente pixmap y posicion.


public:
    enemigo(qreal *lastPosition);

    ~enemigo();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );


private slots:
    void moverEnemigo();

};

#endif // ENEMIGO_H
