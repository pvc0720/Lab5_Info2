#include "Mapa_Juego.h"

QVector<QPoint> mapa::Rutas;

mapa::mapa()
{
    cargarImagen();

    //Lineas Horizontales
    //LINEA 1
    crearRuta(35, 35, 274, 35);
    crearRuta(340, 35, 579, 35);

    //LINEA 2
    crearRuta(35, 121, 579, 121);

    //LINEA 3
    crearRuta(35, 187, 144, 187);
    crearRuta(209, 187, 274, 187);
    crearRuta(340, 187, 406, 187);
    crearRuta(470, 187, 579, 187);

    //LINEA 4
    crearRuta(209, 252, 406, 252);

    //LINEA 5 - LINEA MEDIA
    crearRuta(0, 318, 209, 318);
    crearRuta(406, 318, 614, 318);

    //LINEA 6
    crearRuta(209, 384,406, 384);

    //LINEA 7
    crearRuta(35, 449, 274, 449);
    crearRuta(340, 449, 579, 449);

    //LINEA 8
    crearRuta(35, 514, 79, 514);
    crearRuta(144, 514, 470, 514);
    crearRuta(536, 514, 579, 514);

    //LINEA 9
    crearRuta(35, 580, 144, 580);
    crearRuta(209, 580, 274, 580);
    crearRuta(340, 580, 406, 580);
    crearRuta(470, 580, 579, 580);

    //LINEA 10
    crearRuta(35, 645, 579, 645);

    //LINEAS VERTICALES
    //LINEA 1
    crearRuta(35, 35, 35, 187);
    crearRuta(35, 449, 35, 514);
    crearRuta(35, 580, 35, 645);

    //LINEA 2
    crearRuta(79, 514, 79, 580);

    //LINEA 3
    crearRuta(144, 35, 144, 580);

    //LINEA 4
    crearRuta(209, 121, 209, 187);
    crearRuta(209, 252, 209, 449);
    crearRuta(209, 514, 209, 580);

    //LINEA 5
    crearRuta(274, 35, 274, 121);
    crearRuta(274, 187, 274, 252);
    crearRuta(274, 449, 274, 514);
    crearRuta(274, 580, 274, 645);

    //LINEA 6
    crearRuta(340, 35, 340, 121);
    crearRuta(340, 187, 340, 252);
    crearRuta(340, 449, 340, 514);
    crearRuta(340, 580, 340, 645);

    //LINEA 7
    crearRuta(406, 121, 406, 187);
    crearRuta(406, 252, 406, 449);
    crearRuta(406, 514, 406, 580);

    //LINEA 8
    crearRuta(470, 35, 470, 580);

    //LINEA 9
    crearRuta(536, 514, 536, 580);

    //LINEA 10
    crearRuta(579, 35, 579, 187);
    crearRuta(579, 449, 579, 514);
    crearRuta(579, 580, 579, 645);

    crearVectorPoder();
    crearVectorComida();
}

void mapa::cargarImagen()
{
    fondo.load(":/rsc/map.png");
}

void mapa::crearRuta(int startX, int startY, int endX, int endY) //solo líneas izquierda-derecha y arriba-abajo
{
    QPoint p;

    if (startX == endX){ //condición de línea vertical
        if (startY < endY){ //linea vertical de startY a endY
            for (int y=startY; y<=endY; y++){
                p.setX(startX);
                p.setY(y);

                if (! Rutas.contains(p)){
                    Rutas.push_front(p);
                }
            }
        }
        else if(startY==endY){ //punto único
            p.setX(startX);
            p.setY(startY);
            if (! Rutas.contains(p)){
                Rutas.push_front(p);
            }
        }
    }

    if (startY == endY){ //condicion de linea horizontal

        if (startX < endX){ //linea horizontal de startX a endX

            for (int x=startX; x<=endX; x++){
                p.setX(x);
                p.setY(startY);
                if (! Rutas.contains(p)){
                    Rutas.push_front(p);
                }
            }
        }
        else{ //punto unico
            p.setX(startX);
            p.setY(startY);
            if (! Rutas.contains(p)){
                Rutas.push_front(p);
            }
        }
    }
}

//Comprueba si el punto dado es accesible para Pacman (está presente en el vector m_PacmanPaths)
bool mapa::verificarPuntos(QPoint const& point)
{
    for(auto item : Rutas){
        if(item == point){
             return true;
        }
    }
    return false;
}

void mapa::crearVectorComida()
{
    int const contador = 10;
    // Coordenadas (x, y) donde se colocarán las bolas de comida
    std::array< int, contador > CoorVerticales={35,79,144,209,274,340,406,470,536,579};
    std::array< int, contador > CoorHorizontales={35,121,187,252,318,384,449,514,580,645};

    for(int i : CoorVerticales){
        for(int j : CoorHorizontales){
            QPoint PuntoComida(i,j);

            // Comprobar si el punto está en la ruta
            if(mapa::obtenerVectorRutas().contains(PuntoComida)){
                //Saltar puntos donde están las bolas de poder
                if((PuntoComida.x()==35 && PuntoComida.y()==75)  ||
                   (PuntoComida.x()==579 && PuntoComida.y()==75) ||
                   (PuntoComida.x()==35 && PuntoComida.y()==514) ||
                   (PuntoComida.x()==579 && PuntoComida.y()==514))
                {
                    continue;
                }
                //Se comprueba si el punto ya está en el vector
                if(comida.contains(PuntoComida)){
                    continue;
                }
                comida.push_back(QPoint(i,j));
            }
        }
    }
}

void mapa::crearVectorPoder()
{
    QPoint BolaPoderPosicion1 = QPoint(35,75);
    QPoint BolaPoderPosicion2 = QPoint(579,75);
    QPoint BolaPoderPosicion3 = QPoint(35,514);
    QPoint BolaPoderPosicion4 = QPoint(579,514);

    poder.push_back(BolaPoderPosicion1);
    poder.push_back(BolaPoderPosicion2);
    poder.push_back(BolaPoderPosicion3);
    poder.push_back(BolaPoderPosicion4);
}

QRectF mapa::boundingRect() const
{
    return QRect(0,0,614,740);
}
