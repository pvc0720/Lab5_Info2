#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsItem>
#include <QPainter>
#include "Direcciones.h"
#include "Mapa_Juego.h"
#include "pacman.h"

class Fantasma : public QGraphicsItem
{

public:
    Fantasma();

    //Posiciones iniciales de los Fantasmas
    static int const STARTING_X = 307;
    static int const STARTING_Y = 318;

    static int getEstado(){return estado;}
    static void setEstado(int Estado){estado=Estado;}
    static void incrementarEstado(){++estado;}

    static bool getFantasma(){return validar;}
    static void setFantasma(bool Fan){validar = Fan;}

    static bool getEstadoMov(){return estadoMov;}
    static void setEstadoMov(bool inicioMov){estadoMov = inicioMov;}

    static int  getTemporizador(){return temporizador;}
    static void incrementarTemp(){++temporizador;}

    bool getAzul() const {return azul;}
    void setAzul(bool opcion) {azul=opcion;}

    void setBlanco(bool opcion) {blanco=opcion;}
    bool getInicio() const {return inicio;}

    int GetFantasmaX() const {return posX;}
    int GetFantasmaY() const {return posY;}

    void actualizar();
    void mover();
    void salirInicio(int fantasmaX, int fantasmaY);
    void movDireccionRecta();

private:

    static int numero;
    static int estado;
    static bool validar;
    static bool estadoMov;
    static int temporizador;

    unsigned short int estadoAnimacion;
    unsigned short int posX;
    unsigned short int posY;

    QPixmap dibujos;
    QPixmap Azul;
    QPixmap Blanco;
    QPixmap izquierda1, izquierda2;
    QPixmap arriba1, arriba2;
    QPixmap abajo1, abajo2;
    QPixmap derecha1, derecha2;
    QPixmap azul1, azul2;
    QPixmap blanco1, blanco2;

    bool azul;
    bool blanco;
    bool moviendose;
    bool inicio;

    Direccion direccion;
    Direccion siguienteDir;

    void CargarImagenes();
    void asignarColor(const QString& col);

    //Para los limites externos del personaje en la escena.
    QRectF boundingRect() const override;
    void paint(QPainter *pintar, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


#endif // FANTASMA_H
