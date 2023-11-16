#ifndef FINALIZACIONJUEGO_H
#define FINALIZACIONJUEGO_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class FinalizacionJuego : public QGraphicsItem
{

public:

    FinalizacionJuego();//Constructor de la clase
    void SetPuntuacion(int puntaje);
    void SetGanarJuego(bool ganar);
    void SetPerderjuego(bool perder);

private:

    bool ganarJuego;
    bool perderJuego;
    bool jugando;
    int puntuacion;
    int ancho;
    int alto;

    QRectF boundingRect() const override;
    void paint(QPainter *pintar, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // FINALIZACIONJUEGO_H
