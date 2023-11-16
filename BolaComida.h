#ifndef BOLACOMIDA_H
#define BOLACOMIDA_H

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "Mapa_Juego.h"

class Bola_Comida : public QGraphicsItem
{
public:
    Bola_Comida(int x , int y, int ancho, int altura); //constructor

protected:
    int ancho;
    int alto;
    int x;
    int y;

    //Para los limites externos del personaje en la escena.
    QRectF boundingRect() const override;
    void paint(QPainter *pintar, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif // BOLACOMIDA_H
