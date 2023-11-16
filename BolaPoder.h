#ifndef BOLAPODER_H
#define BOLAPODER_H

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>
#include "BolaComida.h"

class BolaPoder: public Bola_Comida
{

public:
    BolaPoder(int x, int y, int ancho, int altura);//Constructor

private:

    //Para delimitar espacio que ocupa el personaje
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // BOLAPODER_H

