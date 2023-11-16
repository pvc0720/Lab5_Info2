#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

#include "Mapa_Juego.h"
#include "pacman.h"
#include "BolaPoder.h"
#include "BolaComida.h"
#include "Fantasma.h"
#include "FinalizacionJuego.h"
#include "VisualizarPuntuacion.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:

    explicit GameWindow(QWidget* parent = nullptr);
    ~GameWindow() override;


private slots:

    void Actualizar();
    void FantasmaActualizar();

private:

    Ui::GameWindow *pantalla;
    QGraphicsScene escena;

    mapa  plantilla;
    Pacman jugador;
    Fantasma fantasma1;
    Fantasma fantasma2;
    Fantasma fantasma3;
    Fantasma fantasma4;
    FinalizacionJuego finalizacion;
    VisualizarPuntuacion puntaje;

    QTimer tiempo;
    QTimer tiempoEnemigos;

    int comida{0};

    QGraphicsPixmapItem* pixItem{nullptr};

    std::vector<std::unique_ptr<Bola_Comida>> bolasComida;
    std::vector<std::unique_ptr<BolaPoder>> bolasPoder;

    enum class EstadoJuego
    {
        Telon,
        Inicio,
        Parar
    };

    EstadoJuego estado;

    void IniciarCampoDeJuego();
    void PrepararJuego();
    void AgregarBolas();
    void AgregarItemsGraficos();
    void AgregarPoderes();
    void AgregarComida();

    void IniciarJuego();
    void Limpieza();//Para quitar todos los articulos al finalizar el juego

    void ColisionPoder();
    void ColisionComida();
    void ColisionFantasma();
    void FinJuego(bool win);
    void EsconderItems();

    void keyPressEvent(QKeyEvent *event) override;

};

#endif // DIALOG_H
