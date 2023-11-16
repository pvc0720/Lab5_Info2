#include "BolaPoder.h"

BolaPoder::BolaPoder(int x, int y, int ancho, int altura)
    : Bola_Comida(x,y,ancho,altura)
{

}

QRectF BolaPoder::boundingRect() const //Se delimita el rectangulo donde estara el personaje
{
    return QRect(x, y, ancho, alto);
}

void BolaPoder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::cyan));//Color de las bolas
    painter->drawEllipse(x, y, ancho, alto);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
