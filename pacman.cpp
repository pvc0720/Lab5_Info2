#include "pacman.h"

int Pacman::posX{};
int Pacman::posY{};

Pacman::Pacman() //Se define el constructor
{
    cargarImagenes();

    estadoAnimacion = 0;
    factorAnimacion = 6;

    direccion=Direccion::izquierda; //La direccion predefinida al empezar el juego
    siguienteDir=Direccion::ninguna;
    posX=POSX;
    posY=POSY;
}

void Pacman::Reiniciar()
{
    estadoAnimacion = 0;
    factorAnimacion = 6;

    direccion=Direccion::izquierda;//La direccion predefinida al empezar el juego
    siguienteDir=Direccion::ninguna;
    posX=POSX;
    posY=POSY;
}

void Pacman::AdvanzarAnimacion() //Para avanzar la animacion
{
    if(estadoAnimacion>8*factorAnimacion-2){
        estadoAnimacion=0;
    }
    else{
        estadoAnimacion++;
    }
}

void Pacman::cargarImagenes()
{
    //Para movimientos a la derecha
    derecha1.load(":/rsc/Imagenes_Pacman/pacclose.png");
    derecha2.load(":/rsc/Imagenes_Pacman/pacopen1.png");
    derecha3.load(":/rsc/Imagenes_Pacman/pacopen2.png");
    derecha4.load(":/rsc/Imagenes_Pacman/pacopen3.png");

    //Para movimiento hacia arriba
    arriba1.load(":/rsc/Imagenes_Pacman/paccloseu.png");
    arriba2.load(":/rsc/Imagenes_Pacman/pacopen1u.png");
    arriba3.load(":/rsc/Imagenes_Pacman/pacopen2u.png");
    arriba4.load(":/rsc/Imagenes_Pacman/pacopen3u.png");

    //Para movimientos hacia abajo
    abajo1.load(":/rsc/Imagenes_Pacman/pacclosed.png");
    abajo2.load(":/rsc/Imagenes_Pacman/pacopen1d.png");
    abajo3.load(":/rsc/Imagenes_Pacman/pacopen2d.png");
    abajo4.load(":/rsc/Imagenes_Pacman/pacopen3d.png");

    //Para movimientos a la izquierda
    izquierda1.load(":/rsc/Imagenes_Pacman/pacclosel.png");
    izquierda2.load(":/rsc/Imagenes_Pacman/pacopen1l.png");
    izquierda3.load(":/rsc/Imagenes_Pacman/pacopen2l.png");
    izquierda4.load(":/rsc/Imagenes_Pacman/pacopen3l.png");
}

void Pacman::SetSiguienteDireccion(Direccion direccion) //Para establece la siguiente direccion del pacman
{
    siguienteDir=direccion;
}

void Pacman::Mover()
{
    // Punto de ruta que se prueba para validez
    QPoint point;

    if(siguienteDir!=direccion){
        switch(siguienteDir){
            case Direccion::izquierda: //Direccion izquierda
                //Se establecen las coordenadas 'x' y 'y' del pacman
                point.setX(posX-1);
                point.setY(posY);

                if(mapa::verificarPuntos(point)){
                    direccion=siguienteDir;
                    siguienteDir=Direccion::ninguna;
                }
                break;

            case Direccion::arriba: //Direccion hacia arriba
                //Se establecen las coordenadas 'x' y 'y' del pacman
                point.setX(posX);
                point.setY(posY-1);
                if(mapa::verificarPuntos(point)){
                    direccion=siguienteDir;
                    siguienteDir=Direccion::ninguna;
                }
                break;

            case Direccion::abajo: //Direccion hacia abajo
                //Se establecen las coordenadas 'x' y 'y' del pacman
                point.setX(posX);
                point.setY(posY+1);
                if(mapa::verificarPuntos(point)){
                    direccion=siguienteDir;
                    siguienteDir=Direccion::ninguna;
                }
                break;

            case Direccion::derecha: //Direccion hacia la derecha
                //Se establecen las coordenadas 'x' y 'y' del pacman
                point.setX(posX+1);
                point.setY(posY);
                if(mapa::verificarPuntos(point)){
                    direccion=siguienteDir;
                    siguienteDir=Direccion::ninguna;
                }
                break;
            case Direccion::ninguna: //Si no hay ninguna direccion
                break;
        }
    }

    switch(direccion){
        case Direccion::izquierda: //Para direccion izquierda
            //Se establecen las coordenadas 'x' y 'y' del pacman
            point.setX(posX-1);
            point.setY(posY);

            if(mapa::verificarPuntos(point)){
                posX = posX - 1; //Se resta a 'X' por ir hacia la izquierda
            }
            break;

        case Direccion::arriba://Para direccion hacia arriba
            //Se establecen las coordenadas 'x' y 'y' del pacman
            point.setX(posX);
            point.setY(posY-1);

            if(mapa::verificarPuntos(point)){
                posY= posY - 1;  //Se resta a 'Y' por ir hacia arriba
            }
            break;

        case Direccion::abajo: //Para direccion hacia abajo
            //Se establecen las coordenadas 'x' y 'y' del pacman
            point.setX(posX);
            point.setY(posY+1);

            if(mapa::verificarPuntos(point)){
                posY= posY + 1; //Se suma a la posicion en 'Y' por ir hacia abajo
            }
            break;

        case Direccion::derecha: //Direccion hacia la derecha
            //Se establecen las coordenadas 'x' y 'y' del pacman
            point.setX(posX+1);
            point.setY(posY);

            if(mapa::verificarPuntos(point)){
                posX = posX + 1; //Se suma a la direccion en 'X' por ir hacia la derecha
            }
            break;

        case Direccion::ninguna: //Si no se mueve para ningun lado
            break;
    }
    // Teletransportación cuando se alcanza el límite izquierdo de la línea horizontal media
    if(posX<=0){
        posX=613;
    }
    //Teletransportación cuando se alcanza el límite derecho de la línea horizontal media
    if(posX>=614){
        posX=1;
    }
}

//Para delimitar el pacman
QRectF Pacman::boundingRect() const
{
    int const pacmanRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    return QRect(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius);
}

void Pacman::paint(QPainter *pintar, const QStyleOptionGraphicsItem *, QWidget *) //Para las animaciones con los sprites
{
    int const pacmanRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    switch(direccion){
    case Direccion::izquierda: //Para direccion izquierda
        if(estadoAnimacion<2*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, izquierda1); //Se van dibujando los pixmap de la izquierda
        }
        else if(estadoAnimacion<4*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, izquierda2);//Se van dibujando los pixmap de la izquierda
        }
        else if(estadoAnimacion<6*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, izquierda3);//Se van dibujando los pixmap de la izquierda
        }
        else if(estadoAnimacion<8*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, izquierda4);//Se van dibujando los pixmap de la izquierda
        }
        break;

    case Direccion::derecha: //Para direccion derecha
        if(estadoAnimacion<2*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, derecha1);//Se van dibujando los pixmap de la derecha
        }
        else if(estadoAnimacion<4*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, derecha2);//Se van dibujando los pixmap de la derecha
        }
        else if(estadoAnimacion<6*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, derecha3);//Se van dibujando los pixmap de la derecha
        }
        else if(estadoAnimacion<8*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, derecha4);//Se van dibujando los pixmap de la derecha
        }
        break;

    case Direccion::abajo: //Para la direccion hacia abajo
        if(estadoAnimacion<2*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, abajo1);//Se van dibujando los pixmap de abajo
        }
        else if(estadoAnimacion<4*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, abajo2);//Se van dibujando los pixmap de abajo
        }
        else if(estadoAnimacion<6*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, abajo3);//Se van dibujando los pixmap de abajo
        }
        else if(estadoAnimacion<8*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, abajo4);//Se van dibujando los pixmap de abajo
        }
        break;

    case Direccion::arriba://Direccion hacia arriba
        if(estadoAnimacion<2*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, arriba1);//Se van dibujando los pixmap de arriba
        }
        else if(estadoAnimacion<4*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, arriba2);//Se van dibujando los pixmap de arriba
        }
        else if(estadoAnimacion<6*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, arriba3);//Se van dibujando los pixmap de arriba
        }
        else if(estadoAnimacion<8*factorAnimacion){
            pintar->drawPixmap(posX+offsetX, posY+offsetY, pacmanRadius, pacmanRadius, arriba4);//Se van dibujando los pixmap de arriba
        }
        break;

    case Direccion::ninguna:
        break;
    }
}
