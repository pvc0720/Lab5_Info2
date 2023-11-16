#include "BolaComida.h"

Bola_Comida::Bola_Comida(int x, int y, int ancho, int altura) //Se define el constructor de la bola de comida
{
    this->x=x;
    this->y=y;
    this->ancho = ancho;
    this->alto = altura;
}

QRectF Bola_Comida::boundingRect() const //Se delimita el rectangulo donde estara el personaje
{
    return QRect(x, y, ancho, alto);
}

void Bola_Comida::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::blue));//Color de las bolas
    painter->drawEllipse(x, y, ancho, alto);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
