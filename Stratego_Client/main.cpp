#include <iostream>
#include <QApplication>
#include "Client.h"

using namespace std;

/**
 * @brief The main of the Stratego application
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client controller = Client();
    controller.start();
    controller.show();
    return a.exec();
}
