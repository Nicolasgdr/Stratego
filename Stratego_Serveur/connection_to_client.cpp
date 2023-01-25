#include "connection_to_client.h"
#include "Server.h"

ConnectionToClient::ConnectionToClient(qintptr socket_descriptor,QObject*parent):
        QObject(parent),
        socket_descriptor_(socket_descriptor),
        server(nullptr),
        inGame(false),
        gameId(-1)
{
    this->socket= new QTcpSocket();
    if(!this->socket->setSocketDescriptor(this->socket_descriptor_))
    {
        qDebug()<<"Error";
        emit error(socket->error());
        return;
    }
    qDebug()<<"Client connected..."<<"connecting slot...\n";
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_in()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(log_out()),Qt::DirectConnection);
    connect(this,SIGNAL(send_data(QByteArray)),this,SLOT(sendToClient(QByteArray)),Qt::DirectConnection);
}

void ConnectionToClient::read_in(){
    qDebug() << "---------------------------\n"<<"Data received...\n";
    buffer.clear();
    buffer = QByteArray(socket->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    qDebug()<<doc;
    server->handleMessageFromClient(buffer,this);
}


void ConnectionToClient::log_out(){
    socket->deleteLater();
    qDebug()<<"LOG_OUT";
    server->disconnectClient(this);
    server->notify_observers();
}

bool ConnectionToClient::isInGame() const{
    return inGame;
}

void ConnectionToClient::setInGame(bool inGame){
    this->inGame = inGame;
}

void ConnectionToClient::setServer(Server* s){
    server = s;
}

void ConnectionToClient::setId(unsigned id){
    this->id = id;
}

void ConnectionToClient::setStat(int stat){
    this->stat = stat;
}

int ConnectionToClient::getStat(){
    return stat;
}

void ConnectionToClient::setGameId(unsigned id){
    gameId = id;
}

void ConnectionToClient::setPlayerColor(Color col){
    player_color = col;
}

void ConnectionToClient::setPlayerPseudo(QString pseudo){
    player_pseudo = pseudo;
}

QHostAddress ConnectionToClient::clientAddress() const{
    return socket->peerAddress();
}

quint16 ConnectionToClient::clientPort() const{
    return socket->peerPort();
}

unsigned ConnectionToClient::getId() const{
    return id;
}

int ConnectionToClient::getGameId() const{
    return gameId;
}

const Color& ConnectionToClient::getColor() const{
    return player_color;
}

const QString& ConnectionToClient::getPlayerPseudo() const{
    return player_pseudo;
}

void ConnectionToClient::sendToClient(QByteArray data){
    if(socket->state() == QAbstractSocket::ConnectedState){
        qDebug()<<"============================";
        QDataStream stream(socket);
        stream.startTransaction();
        stream << data;
        qDebug()<<socket->bytesToWrite();
        stream.commitTransaction();
        qDebug()<<"Data send to "<<clientPort();
        qDebug()<<"============================";
    }
}
