#include "FinalizacionJuego.h"

FinalizacionJuego::FinalizacionJuego() //Se define el constructor de la clase
{
    ancho = 600;
    alto = 200;
    setX(614/2-ancho/2);
    setY(714/2-alto/2);

    ganarJuego=false;
    perderJuego=false;

    puntuacion=0;
    jugando=false;
}

void FinalizacionJuego::SetPuntuacion(int puntaje)
{
    puntuacion = puntaje;
}

void FinalizacionJuego::SetGanarJuego(bool ganar)
{
    ganarJuego = ganar;
}

void FinalizacionJuego::SetPerderjuego(bool perder)
{
    perderJuego = perder;
}

//Para delimitar el espacio del text
QRectF FinalizacionJuego::boundingRect() const
{
    return QRect(x(), y(), ancho, alto);
}

void FinalizacionJuego::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penVerde(Qt::green);
    QPen penAzul(Qt::blue);
    painter->setPen(penVerde);
    QFont font = painter->font();
    font.setPointSize (30);
    painter->setFont(font);

    if(!jugando)
    {
        if(ganarJuego) //Si se gana en el juego
        {
            painter->setPen(penAzul);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"Ganaste");
            painter->drawText(boundingRect(),Qt::AlignCenter, "Puntuacion Final : "+QString::number(puntuacion));
           }
        else if(perderJuego)//Si se pierde el juego
        {
            painter->setPen(penVerde);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"Game Over");
            painter->setPen(penAzul);
            painter->drawText(boundingRect(),Qt::AlignCenter, "Puntuacion Final : "+QString::number(puntuacion));
        }    
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
