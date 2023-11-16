#ifndef MAPA_JUEGO_H
#define MAPA_JUEGO_H

#include <QVector>
#include <QPixmap>
#include <array>

class mapa
{

public:

    mapa();

    static bool verificarPuntos(QPoint const& point);
    static QVector<QPoint> const& obtenerVectorRutas() {return Rutas;} //Para los puntos de la ruta

    QPixmap obtenerFondo() const {return fondo;} //Para la imagen del fondo del mapa
    QVector<QPoint> const& obtenerVectorComida() const {return comida;} //Para las posiciones de las bolas de comida
    QVector<QPoint> const& obtenerVectorPoder() const {return poder;}//Para las posiciones de las bolas de poder

private:

    static QVector<QPoint> Rutas;
    QPixmap fondo;
    QVector<QPoint> comida;
    QVector<QPoint> poder;

    void cargarImagen(); //Para cargar la imagen del mapa
    void crearRuta(int startX, int startY, int endX, int endY); //Crear las rutas
    void crearVectorComida();
    void crearVectorPoder();

    QRectF boundingRect() const;
};

#endif // MAPA_JUEGO_H
