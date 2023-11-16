#ifndef VISUALIZARPUNTUACION_H
#define VISUALIZARPUNTUACION_H

#include <QGraphicsItem>

class VisualizarPuntuacion : public QGraphicsItem
{

public:

    VisualizarPuntuacion();//Constructor de la clase
    void SetPuntuacion(int puntaje);
    void IncrementarPuntuacion(int puntaje){puntuacion+=puntaje;}
    int GetPuntuacion() {return puntuacion;}

private:

    int x;
    int y;
    int ancho;
    int altura;
    int puntuacion;

    //Se delimita el espacio que ocupara el item
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif //VISUALIZARPUNTUACION_H
