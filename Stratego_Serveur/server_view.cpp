#include "server_view.h"

ServerView::ServerView(Server& s, QWidget * p) :
        QMainWindow(p),
        server(s),
        tView(new QTableWidget(this))
{
    this->setFixedSize(303,200);
    tView->setMinimumWidth(303);
    tView->setMinimumHeight(200);
    tView->setColumnCount(3);
    tView->verticalHeader()->setVisible(false);
    tView->setHorizontalHeaderItem(0, new QTableWidgetItem("id"));
    tView->setHorizontalHeaderItem(1, new QTableWidgetItem("ip"));
    tView->setHorizontalHeaderItem(2, new QTableWidgetItem("port"));

    setStyle();
}

void ServerView::setStyle(){
    QPixmap pixmap;
    pixmap.load("../Stratego_Client/img/icon.jpg");
    QIcon icon(pixmap);
    this->setWindowIcon(icon);
    this->setWindowTitle("Stratego Serveur");
}

void ServerView::update(){
    tView->setRowCount(server.getNbConnections());
    unsigned row = 0;
    for(auto connection : server.getConnectedClients()){
        if(row == server.getNbConnections()-1){
            tView->setItem(row,0, new QTableWidgetItem(QString::number(connection->getId())));
            tView->setItem(row,1, new QTableWidgetItem(connection->clientAddress().toString()));
            tView->setItem(row,2, new QTableWidgetItem(QString::number(connection->clientPort())));
        }
        row++;
    }
}
