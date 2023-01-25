#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game = Game();
    GraphicView view = GraphicView(game);
    game.add_observer(view);

    MainWindow window = MainWindow(game, view);

    window.show();
    return a.exec();
}
