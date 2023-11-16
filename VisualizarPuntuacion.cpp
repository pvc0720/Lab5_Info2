#include "VisualizarPuntuacion.h"
#include <QPainter>

VisualizarPuntuacion::VisualizarPuntuacion()//Se define el constructor de la clase
{
    ancho=600;
    altura=200;
    x=0;
    y=680;

    puntuacion=0;
}

void VisualizarPuntuacion::SetPuntuacion(int puntaje)
{
    puntuacion=puntaje;
}

QRectF VisualizarPuntuacion::boundingRect() const //Se delimita el rectangulo donde estara el item
{
    return QRect(x, y, ancho, altura);
}

void VisualizarPuntuacion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font = painter->font();
    font.setPointSize (30);

    painter->setPen(QPen(Qt::white));
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter, "Puntuacion: " + QString::number(puntuacion));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
