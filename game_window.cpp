#include "game_window.h"
#include "ui_game_window.h"

GameWindow::GameWindow(QWidget *parent) : QDialog(parent), pantalla(new Ui::GameWindow)
{
    pantalla->setupUi(this);
    setFocus(Qt::ActiveWindowFocusReason);
    estado= EstadoJuego::Telon;
    IniciarCampoDeJuego();
    PrepararJuego();
    IniciarJuego();
}

void GameWindow::IniciarCampoDeJuego()
{
    escena.setParent(this);
    pantalla->graphicsView->setScene(&escena);
    pantalla->graphicsView->setRenderHint(QPainter::Antialiasing);
    escena.setSceneRect(0,0,614,740); //delimitar escena
    pantalla->graphicsView->setStyleSheet("background-color:black");//Para color del graphicsView
    pantalla->graphicsView->setSceneRect(escena.sceneRect());
}

void GameWindow::PrepararJuego()
{
    AgregarItemsGraficos();
    AgregarBolas();
}

void GameWindow::AgregarBolas()
{
    // Obtener las posiciones generadas de Bola_Comida y BolaPoder del objeto GameMap
    QVector<QPoint> const PosicionPoder = plantilla.obtenerVectorPoder();
    QVector<QPoint> const PosicionComida = plantilla.obtenerVectorComida();

    comida=PosicionComida.size();

    int const RadioPoder = 15; //Radio de la bola

    //Para las Bolas de poder
    for(auto item : PosicionPoder){
        bolasPoder.push_back(std::make_unique<BolaPoder>(item.x(),
                                                         item.y(),
                                                         RadioPoder,
                                                         RadioPoder));
    }
    int const RadioComida= 7;//Radio de la bola

    //Para las bolas de comida
    for(auto item : PosicionComida){
        bolasComida.push_back(std::make_unique<Bola_Comida>(item.x(),
                                                            item.y(),
                                                            RadioComida,
                                                            RadioComida));
    }
    //Se agregan a la escena
    AgregarPoderes();
    AgregarComida();
}

void GameWindow::AgregarPoderes()
{
    for(auto& item: bolasPoder){
        escena.addItem(item.get());
    }
}

void GameWindow::AgregarComida()
{
    for(auto& item : bolasComida){
        escena.addItem(item.get());
    }
}

GameWindow::~GameWindow()
{
    delete pantalla;
}

void GameWindow::AgregarItemsGraficos()
{
    //Agregar imagen de mapa de fondo
    pixItem = escena.addPixmap(plantilla.obtenerFondo());

    //Se agrega el pacman a la escena
    escena.addItem(&jugador);

    //Se agregan fantasmas a la escena
    escena.addItem(&fantasma1);
    escena.addItem(&fantasma2);
    escena.addItem(&fantasma3);
    escena.addItem(&fantasma4);

    //Para la puntuacion
    escena.addItem(&finalizacion);
    escena.addItem(&puntaje);
}

void GameWindow::IniciarJuego()
{
    //Para que los fantasmas inicien su movimiento en la escena
    connect(&tiempo, &QTimer::timeout, this, &GameWindow::Actualizar);
    connect(&tiempoEnemigos, &QTimer::timeout, this, &GameWindow::FantasmaActualizar);

    tiempo.start(10);
    tiempoEnemigos.start(12);

    estado = EstadoJuego::Inicio;
    setFocus();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Direccion nextDirection = jugador.GetSiguienteDirecccion();

    switch(event->key())
    {
    case Qt::Key_A:
        nextDirection = Direccion::izquierda;
        break;

    case Qt::Key_D:
        nextDirection = Direccion::derecha;
        break;

    case Qt::Key_S:
        nextDirection = Direccion::abajo;
        break;

    case Qt::Key_W:
        nextDirection = Direccion::arriba;
        break;

    default:
        break;
    }
    jugador.SetSiguienteDireccion(nextDirection);
}

void GameWindow::FantasmaActualizar()
{
    //Se establecen las posiciones de los fantasmas
    int fantasma1X = fantasma1.GetFantasmaX();
    int fantasma1Y = fantasma1.GetFantasmaY();
    int fantasma2X = fantasma2.GetFantasmaX();
    int fantasma2Y = fantasma2.GetFantasmaY();
    int fantasma3X = fantasma3.GetFantasmaX();
    int fantasma3Y = fantasma3.GetFantasmaY();
    int fantasma4X = fantasma4.GetFantasmaX();
    int fantasma4Y = fantasma4.GetFantasmaY();

    if(Fantasma::getEstadoMov()){
        fantasma1.mover();
        fantasma2.mover();
        fantasma3.mover();
        fantasma4.mover();
    }
    else{
        if(!fantasma1.getInicio()){
            fantasma1.movDireccionRecta();
        }
        else{
            fantasma1.mover();
        }
        if(!fantasma2.getInicio()){
            fantasma2.movDireccionRecta();
        }
        else{
            fantasma2.mover();
        }
        if(!fantasma3.getInicio()){
            fantasma3.movDireccionRecta();
        }
        else{
            fantasma3.mover();
        }
        if(!fantasma4.getInicio()){
            fantasma4.movDireccionRecta();
        }
        else{
            fantasma4.mover();
        }

        //Sustituto del temporizador implementado para cada fantasma para diferenciar su hora de inicio
        if(fantasma1.GetFantasmaX()==300 ||
           fantasma2.GetFantasmaX()==300 ||
           fantasma3.GetFantasmaX()==300 ||
           fantasma4.GetFantasmaX()==300)
        {
            Fantasma::incrementarTemp();
        }

        //Iniciar Fantasma 1
        if(Fantasma::getTemporizador()>=3){
            fantasma1.salirInicio(fantasma1X, fantasma1Y);
        }

        //Iniciar Fantasma 2
        if(Fantasma::getTemporizador()>=6){
            fantasma2.salirInicio(fantasma2X, fantasma2Y);
        }

        //Iniciar Fantasma 3
        if(Fantasma::getTemporizador()>=9){
            fantasma3.salirInicio(fantasma3X, fantasma3Y);
        }

        //Iniciar Fantasma 4
        if(Fantasma::getTemporizador()>=12){
            fantasma4.salirInicio(fantasma4X, fantasma4Y);
        }
        //Todos los fantasmas se mueven libremente
        if(fantasma1.getInicio()&&
           fantasma2.getInicio()&&
           fantasma3.getInicio()&&
           fantasma4.getInicio())
        {
            Fantasma::setEstadoMov(true);
        }
    }
}

void GameWindow::Actualizar()
{
    //Cambia la posición de pacman
    jugador.Mover();

    ColisionPoder();
    ColisionFantasma();
    ColisionComida();

    if(comida==0){
        tiempo.stop();
        tiempoEnemigos.stop();
        FinJuego(true);
    }

    if(Fantasma::getFantasma()){
        Fantasma::incrementarEstado();

        if(Fantasma::getEstado()==1){
            tiempoEnemigos.setInterval(50);
        }

        if(Fantasma::getEstado()==750){
            fantasma1.setBlanco(true);
            fantasma2.setBlanco(true);
            fantasma3.setBlanco(true);
            fantasma4.setBlanco(true);
        }

        if(Fantasma::getEstado()==1000){
            Fantasma::setFantasma(false);

            fantasma1.setAzul(false);
            fantasma2.setAzul(false);
            fantasma3.setAzul(false);
            fantasma4.setAzul(false);

            fantasma1.setBlanco(false);
            fantasma2.setBlanco(false);
            fantasma3.setBlanco(false);
            fantasma4.setBlanco(false);

            Fantasma::setEstado(0);
            tiempoEnemigos.setInterval(4);
        }
    }

    jugador.AdvanzarAnimacion();
    fantasma1.actualizar();
    fantasma2.actualizar();
    fantasma3.actualizar();
    fantasma4.actualizar();

    escena.update(escena.sceneRect());
}
void GameWindow::Limpieza()//Para quitar todos los articulos al finalizar el juego
{
    bolasComida.clear();
    bolasPoder.clear();
}

void GameWindow::ColisionPoder()
{
    auto iter = std::begin(bolasPoder);

    for (auto& item : bolasPoder){
        if(jugador.collidesWithItem(item.get())) //Si hay colision
        {
            bolasPoder.erase(iter); //Se elimina la bola

            //El estado de los fantasmas cambia cuando ocurre una colision
            Fantasma::setEstado(0);

            fantasma1.setAzul(true);
            fantasma2.setAzul(true);
            fantasma3.setAzul(true);
            fantasma4.setAzul(true);

            Fantasma::setFantasma(true);
            puntaje.IncrementarPuntuacion(100);//Se incrementa la puntuacion
            return;
        }
        ++iter;
    }
}

void GameWindow::ColisionFantasma()
{
    //Si colisiona con cualquiera de los 4 fantasmas pierde el juego
    if(jugador.collidesWithItem(&fantasma1) ||
       jugador.collidesWithItem(&fantasma2) ||
       jugador.collidesWithItem(&fantasma3) ||
       jugador.collidesWithItem(&fantasma4))
    {
            tiempo.stop();
            tiempoEnemigos.stop();
            FinJuego(false);
    }
}

void GameWindow::ColisionComida()
{
    auto iter = std::begin(bolasComida);

    for (auto& item : bolasComida){
        if(jugador.collidesWithItem(item.get())){
            bolasComida.erase(iter); //Se elimina la bola de comida
            puntaje.IncrementarPuntuacion(1);
            comida--;
            return;
        }
        ++iter;
    }
}

void GameWindow::FinJuego(bool win)
{
    Limpieza();
    EsconderItems();
    finalizacion.show();
    finalizacion.SetPuntuacion(puntaje.GetPuntuacion());

    if(win){
        finalizacion.SetGanarJuego(true);
    }
    else{
        finalizacion.SetPerderjuego(true);
    }
    escena.update();
    estado = EstadoJuego::Parar;
}

void GameWindow::EsconderItems()
{
    pixItem->hide();
    puntaje.hide();

    jugador.hide();

    fantasma1.hide();
    fantasma2.hide();
    fantasma3.hide();
    fantasma4.hide();
}

