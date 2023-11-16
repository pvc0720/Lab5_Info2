#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsItem>
#include "Direcciones.h"
#include "Mapa_Juego.h"

class Pacman : public QGraphicsItem
{
public:

    static int GetPacX() {return posX;}
    static int GetPacY() {return posY;}

    Pacman();
    void Reiniciar();
    void AdvanzarAnimacion();
    void SetSiguienteDireccion(Direccion direccion);
    Direccion GetSiguienteDirecccion() const {return siguienteDir;}
    void Mover();

private:

    //Posiciones iniciales del Pacman
    static int const POSX = 320;
    static int const POSY = 514;
    static int posX;
    static int posY;

    QPixmap dibujo;
    QPixmap izquierda1, izquierda2, izquierda3, izquierda4;
    QPixmap arriba1, arriba2, arriba3, arriba4;
    QPixmap abajo1, abajo2, abajo3, abajo4;
    QPixmap derecha1, derecha2, derecha3, derecha4;

    int estadoAnimacion;
    int factorAnimacion;

    Direccion direccion;
    Direccion siguienteDir;

    void cargarImagenes();

    //Para los limites externos del personaje en la escena.
    QRectF boundingRect() const override;
    void paint(QPainter *pintar, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PACMAN_H
