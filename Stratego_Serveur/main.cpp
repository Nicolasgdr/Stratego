#include <QApplication>
#include "Server.h"
#include "server_view.h"

/**
 * launch the game
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    ServerView sv = ServerView(server);
    sv.show();
    server.add_observer(sv);
    server.start_server();
    return a.exec();
}
