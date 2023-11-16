#include "game_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow ventana;
    ventana.show();

    return QApplication::exec();
}
