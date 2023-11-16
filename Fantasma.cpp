#include "Fantasma.h"
#include <QRandomGenerator>
bool Fantasma::validar = false;
bool Fantasma::estadoMov = false;
int Fantasma::temporizador = 0;
int Fantasma::estado = 0;
int Fantasma::numero = 0;

Fantasma::Fantasma() //Se define el constructor de la clase
{
    estado=0;
    validar=false;
    temporizador = 0;
    estadoMov=false; //Ninguno ha comenzado a moverse

    estadoAnimacion= 0;
    direccion=Direccion::izquierda;
    siguienteDir=Direccion::ninguna;
    azul=false;
    blanco=false;
    moviendose = false;
    inicio = false;
    posX = STARTING_X;
    posY = STARTING_Y;

    CargarImagenes();

    //Cada fantasma tiene un color único
    switch(numero)
    {
    case 0:
        asignarColor("orange");
        break;
    case 1:
        asignarColor("red");
        break;
    case 2:
        asignarColor("blue");
        break;
    }

    ++numero;
}

void Fantasma::CargarImagenes() //Se cargan las imagenes de los fantasmas
{
    derecha1.load(":/rsc/Imagenes_Fantasmas/ghostright1.png");
    derecha2.load(":/rsc/Imagenes_Fantasmas/ghostright2.png");
    arriba1.load(":/rsc/Imagenes_Fantasmas/ghostup1.png");
    arriba2.load(":/rsc/Imagenes_Fantasmas/ghostup2.png");
    abajo1.load(":/rsc/Imagenes_Fantasmas/ghostdown1.png");
    abajo2.load(":/rsc/Imagenes_Fantasmas/ghostdown2.png");
    izquierda1.load(":/rsc/Imagenes_Fantasmas/ghostleft1.png");
    izquierda2.load(":/ghosts/images/ghost_images/ghostleft2.png");
    azul1.load(":/rsc/Imagenes_Fantasmas/ghostscaredblue1.png");
    azul2.load(":/rsc/Imagenes_Fantasmas/ghostscaredblue2.png");
    blanco1.load(":/rsc/Imagenes_Fantasmas/ghostscaredwhite1.png");
    blanco2.load(":/rsc/Imagenes_Fantasmas/ghostscaredwhite2.png");
}

void Fantasma::actualizar()//Para avanzar animaciones
{
    if(estadoAnimacion>2){
        estadoAnimacion=0;
    }
    else{
        estadoAnimacion++;
    }
}

void Fantasma::asignarColor(const QString &col)
{
    if(col=="blue"){
        derecha1.load(":/rsc/Imagenes_Fantasmas/ghostrightblue1.png");
        derecha2.load(":/rsc/Imagenes_Fantasmas/ghostrightblue2.png");
        arriba1.load(":/rsc/Imagenes_Fantasmas/ghostupblue1.png");
        arriba2.load(":/rsc/Imagenes_Fantasmas/ghostupblue2.png");
        abajo1.load(":/rsc/Imagenes_Fantasmas/ghostdownblue1.png");
        abajo2.load(":/rsc/Imagenes_Fantasmas/ghostdownblue2.png");
        izquierda1.load(":/rsc/Imagenes_Fantasmas/ghostleftblue1.png");
        izquierda2.load(":/rsc/Imagenes_Fantasmas/ghostleftblue2.png");
    }
    else if(col=="orange"){
        derecha1.load(":/rsc/Imagenes_Fantasmas/ghostrightorange1.png");
        derecha2.load(":/rsc/Imagenes_Fantasmas/ghostrightorange2.png");
        arriba1.load(":/rsc/Imagenes_Fantasmas/ghostuporange1.png");
        arriba2.load(":/rsc/Imagenes_Fantasmas/ghostuporange2.png");
        abajo1.load(":/rsc/Imagenes_Fantasmas/ghostdownorange1.png");
        abajo2.load(":/rsc/Imagenes_Fantasmas/ghostdownorange2.png");
        izquierda1.load(":/rsc/Imagenes_Fantasmas/ghostleftorange1.png");
        izquierda2.load(":/rsc/Imagenes_Fantasmas/ghostleftorange2.png");
    }
    else if(col=="red"){
        derecha1.load(":/rsc/Imagenes_Fantasmas/ghostrightred1.png");
        derecha2.load(":/rsc/Imagenes_Fantasmas/ghostrightred2.png");
        arriba1.load(":/rsc/Imagenes_Fantasmas/ghostupred1.png");
        arriba2.load(":/rsc/Imagenes_Fantasmas/ghostupred2.png");
        abajo1.load(":/rsc/Imagenes_Fantasmas/ghostdownred1.png");
        abajo2.load(":/rsc/Imagenes_Fantasmas/ghostdownred2.png");
        izquierda1.load(":/rsc/Imagenes_Fantasmas/ghostleftred1.png");
        izquierda2.load(":/rsc/Imagenes_Fantasmas/ghostleftred2.png");
    }
}

void Fantasma::mover()
{
    QPoint p;

    //Se obtienen las posiciones del pacman
    int pac_x = Pacman::GetPacX();
    int pac_y = Pacman::GetPacY();

    if(!moviendose){
        //direccion=static_cast<Direccion>((qrand()%4)+1); //Direcciones aleatorias
        direccion = static_cast<Direccion>(QRandomGenerator::global()->bounded(4) + 1);

    }
    else{
        if((direccion==Direccion::derecha && posY<pac_y) || (direccion==Direccion::izquierda && posY>pac_y)){

            if(direccion==Direccion::izquierda && posY>pac_y){
                siguienteDir=Direccion::arriba;
            }
            else if(direccion==Direccion::derecha &&posY<pac_y){
                siguienteDir=Direccion::abajo;
            }

        }
        else if((direccion==Direccion::abajo && posX<pac_x) || (direccion==Direccion::arriba && posX>pac_x))
        {
            if(direccion==Direccion::arriba && posX>pac_x){
                siguienteDir=Direccion::izquierda;
            }

            else if(direccion==Direccion::abajo && posX<pac_x){
                siguienteDir=Direccion::derecha;
            }
        }
    }
    if(siguienteDir!=direccion){
        switch(siguienteDir){
        case Direccion::izquierda://Si direccion es izquierda
            //Obtener las posiciones del fantasma en 'X' y 'Y'
            p.setX(posX-1);
            p.setY(posY);

            if(mapa::verificarPuntos(p)){
                direccion=siguienteDir;
                siguienteDir=Direccion::ninguna;
            }
            break;

        case Direccion::derecha: //Si la direccion es derecha
            //Obtener las posiciones del fantasma en 'X' y 'Y'
            p.setX(posX+1);
            p.setY(posY);

            if(mapa::verificarPuntos(p)){
                direccion=siguienteDir;
                siguienteDir=Direccion::ninguna;
            }
            break;

        case Direccion::abajo:
            //Obtener las posiciones del fantasma en 'X' y 'Y'
            p.setX(posX);
            p.setY(posY+1);

            if(mapa::verificarPuntos(p)){
                direccion=siguienteDir;
                siguienteDir=Direccion::ninguna;
            }
            break;

        case Direccion::arriba://Si la direccion es hacia arriba
            //Obtener las posiciones del fantasma en 'X' y 'Y'
            p.setX(posX);
            p.setY(posY-1);

            if(mapa::verificarPuntos(p)){
                direccion=siguienteDir;
                siguienteDir=Direccion::ninguna;
            }
            break;
        case Direccion::ninguna:
            break;
        }
    }

    switch(direccion){
    case Direccion::izquierda: //Si la direccion es hacia la izquierda
        p.setX(posX-1); //Se resta a la posicion en 'X' por ir hacia la izquierda
        p.setY(posY);

        if(mapa::verificarPuntos(p)){
            posX-=1;//Se resta a la posicion en 'X' por ir hacia la izquierda
            moviendose=true;
        }
        else{
            moviendose=false;
        }
        break;

    case Direccion::derecha://Si la direccion es a la derecha
        //Obtener las posiciones del fantasma en 'X' y 'Y'
        p.setX(posX+1);//Se suma a la posicion en 'X' por ir hacia la derecha
        p.setY(posY);

        if(mapa::verificarPuntos(p)){
            posX+=1;//Se suma a la posicion en 'X' por ir hacia la derecha
            moviendose=true;
        }
        else{
            moviendose=false;
        }
        break;

    case Direccion::abajo://Si la direccion es hacia abajo
        //Obtener las posiciones del fantasma en 'X' y 'Y'
        p.setX(posX);
        p.setY(posY+1);//Se suma a la posicion en 'Y' por ir hacia abajo

        if(mapa::verificarPuntos(p)){
            posY+=1;//Se suma a la posicion en 'Y' por ir hacia abajo
            moviendose=true;
        }
        else{
            moviendose=false;
        }
        break;

    case Direccion::arriba://Si la direccion es hacia arriba
        //Obtener las posiciones del fantasma en 'X' y 'Y'
        p.setX(posX);
        p.setY(posY-1);//Se resta a la posicion en 'Y' por ir hacia arriba

        if(mapa::verificarPuntos(p)){
            posY-=1;//Se resta a la posicion en 'Y' por ir hacia arriba
            moviendose=true;
        }
        else{
            moviendose=false;
        }
        break;
    case Direccion::ninguna:
        break;
    }

    // Teletransportación cuando se alcanza el límite izquierdo de la línea horizontal media
    if(posX<=0){
        posX=613;
        posY=318;
    }

    // Teletransportación cuando se alcanza el límite derecho de la línea horizontal media
    else if(posX>=614){
        posX=1;
        posY=318;
    }
}

void Fantasma::movDireccionRecta()
{
    int const movimientoHorizontalOffset = 50;

    if(posX == STARTING_X - movimientoHorizontalOffset || posX == STARTING_X + movimientoHorizontalOffset){
        if(direccion==Direccion::derecha){
            //A la izquierda
            direccion=Direccion::izquierda;
        }
        else{
            //A la derecha
            direccion=Direccion::derecha;
        }
    }
    if(direccion==Direccion::derecha){
        posX+=1;//Se incrementa la posicion en 'X' por ir hacia la derecha
    }
    else{
        posX-=1; //Se decrementa la posicion en 'X'
    }
}

void Fantasma::salirInicio(int fantasmaX, int fantasmaY){
    if(fantasmaX>Fantasma::STARTING_X){
        fantasmaX-=1;
    }
    else if(fantasmaX<Fantasma::STARTING_X){
        fantasmaX+=1;
    }
    if(!getInicio()){
        fantasmaY-=1;

        posX = fantasmaX;
        posY = fantasmaY;

        QPoint point(fantasmaX, fantasmaY);

        if(mapa::obtenerVectorRutas().contains(point)){
            inicio = true;
        }
    }
}

//Para delimitar el fantasma
QRectF Fantasma::boundingRect() const
{
    int const ghostRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;
    return QRect(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius);
}

void Fantasma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//Para las animaciones con los sprites
{
    int const ghostRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    if(!azul){
        switch(direccion){
        case Direccion::izquierda://Para direccion hacia la izquierda
            if(estadoAnimacion==0){
                painter->drawPixmap(posX+offsetX, posY+offsetY,ghostRadius, ghostRadius, izquierda1);//Se van dibujando los pixmap de la izquierda
            }
            else{
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, izquierda2);//Se van dibujando los pixmap de la izquierda
            }
            break;
        case Direccion::derecha://Para direccion hacia la izquierda
            if(estadoAnimacion==0){
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, derecha1);//Para direccion hacia la derecha
            }
            else{
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, derecha2);//Para direccion hacia la derecha
            }
            break;
        case Direccion::abajo://Para direccion hacia abajo
            if(estadoAnimacion==0){
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, abajo1);//Para direccion hacia abajo
            }
            else{
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, abajo2);//Para direccion hacia abajo
            }
            break;
        case Direccion::arriba://Para direccion hacia arriba
            if(estadoAnimacion==0){
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, arriba1);//Para direccion hacia arriba
            }
            else{
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, arriba2);//Para direccion hacia arriba
            }
            break;
        case Direccion::ninguna:
            break;
        }
    }
    else{
        if(blanco){
            if(estadoAnimacion==0){
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, blanco1);//Para fantasma en estado blanco
            }
            else{
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, blanco2);//Para fantasma en estado blanco
            }
        }
        else{
            if(estadoAnimacion==0){
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, azul1);//Para fantasma en estado azul
            }
            else{
                painter->drawPixmap(posX+offsetX, posY+offsetY, ghostRadius, ghostRadius, azul2);//Para fantasma en estado azul
            }
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
