#ifndef CONNECTION_TO_CLIENT_H
#define CONNECTION_TO_CLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QJsonDocument>
#include "../Stratego_libs/Model/color.h"

//forward declaration
class Server;

/**
 * @brief An instance of this class is created by the server when a client connects. It
 * accepts messages coming from the client and is responsible for sending data
 * to the client since the socket is private to this class.
 */
class ConnectionToClient :  public QObject
{
    Q_OBJECT
    /**
     * @brief Sockets are used in the operating system as channels of communication
     * between two processes.
     */
    QTcpSocket * socket;
    /**
     * @brief The socket descriptor
     */
    qintptr socket_descriptor_;
    /**
     * @brief The server instance that handle this thread.
     */
    Server * server;
    /**
     * @brief Reads the data from the client.
     */
    QByteArray buffer;
    /**
     * @brief The colour of the player when creating/joining a lobby.
     */
    Color player_color;
    /**
     * @brief The pseudonym of the player. It is unique.
     */
    QString player_pseudo;
    /**
     * @brief The id of the thread.
     */
    unsigned id;
    /**
     * @brief Shows whether the client is in a game or not.
     * If it is it will not send refresh lobby messages to the
     * other side socket.
     */
    bool inGame;
    /**
     * @brief The id of the game if the client has joined a lobby.
     */
    int gameId;
    /**
     * @brief The number of wins against other players.
     */
    int stat;

public:
    /**
    * @brief Create a thread to handle an incomming connection.
    * @param socket_descriptor the socket's descriptor
    * @param parent the parent
    */
    ConnectionToClient(qintptr socket_descriptor, QObject* parent=0);
    /**
     * @brief Sets the server field.
     * @param s the server's address to point to.
     */
    void setServer(Server* s);
    /**
     * @brief Sets the id of the thread.
     *
     * It is used by the server when it creates the thread.
     *
     * @param id the id to set to.
     */
    void setId(unsigned id);
    /**
     * @brief Sets the stat field.
     * @param stat the number of wins
     */
    void setStat(int stat);
    /**
     * @brief Gets the number of wins of a client.
     * @return the number of wins
     */
    int getStat();
    /**
     * @brief Indicates whether a client is in a game or not.
     * @return true if the client is in game, false otherwise.
     */
    bool isInGame() const;
    /**
     * @brief Sets the inGame field.
     * @param inGame true if in game, false if not in game
     */
    void setInGame(bool inGame);
    /**
     * @brief Sets the gameId field.
     * @param id the id to set to
     */
    void setGameId(unsigned id);
    /**
     * @brief Sets the color of the player that is connected.
     * This method is called when a player has created or joined a game.
     * @param col the color to set
     */
    void setPlayerColor(Color col);
    /**
     * @brief Sets the player's pseudonym after he entered it.
     * @param pseudo the pseudonym to set
     */
    void setPlayerPseudo(QString pseudo);
    /**
     * @brief Gets the client's address when the socket is in connected state.
     * @return A QHostAddrees of the client or null if the socket isn't in connected state.
     */
    QHostAddress clientAddress() const;
    /**
     * @brief Gets the client's port when the socket is in connected state.
     * @return The port of the client or 0 if the socket isn't in connected state.
     */
    quint16 clientPort() const;
    /**
     * @brief Gets the id of the ConnectionToClient.
     */
    unsigned getId() const;
    /**
     * @brief Gets the game id.
     * @return the id of the game
     */
    int getGameId() const;
    /**
     * @brief Gets the color of the player that created or joined a game.
     * @return the color
     */
    const Color& getColor() const;
    /**
     * @brief Gets the player pseudonym.
     * @return the pseudonym of the client
     */
    const QString& getPlayerPseudo() const;

    inline void notify(QByteArray data){emit send_data(data);}
    /**
     * @brief operator ==
     * @param rhs
     * @return
     */
    inline bool operator==(ConnectionToClient&rhs){return rhs.socket_descriptor_==this->socket_descriptor_;}

private slots:

    /**
     * @brief Sends data to the client's socket.
     * Does nothing if the socket's isn't in connected state.
     * @param data the data to send from a QJsonDocument.
     */
    void sendToClient(QByteArray data);
    /**
     * @brief Reads data received by the client side socket.
     */
    void read_in();
    /**
    * @brief Logs out the connection to client.
    */
    void log_out();

signals:
    void error(QTcpSocket::SocketError error);

    void send_data(QByteArray);

};

#endif // CONNECTION_TO_CLIENT_H
