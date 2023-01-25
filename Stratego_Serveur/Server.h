#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <iostream>
#include <tuple>
#include <memory>
#include <QString>
#include "connection_to_client.h"
#include "../Stratego_libs/Model/observ.h"
#include "../Stratego_libs/Model/game.h"

static constexpr unsigned nbPort = 2022;

/**
 * @brief Represents a Stratego server.
 *
 * It handles the clients connections, the games, the lobbies informations, ...
 * It also updates its data base. It is coded in a multi-client architecture so
 * each connection is handled by a ConnectionToClient.
 */
class Server : public QTcpServer, public Observable
{
    Q_OBJECT
    /**
     * @brief Stocks the client connections.
     */
    std::vector<ConnectionToClient*> connections;
    /**
     * @brief Handles a game between two client connections.
     */
    std::vector<std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>> gameHandler;
    /**
     * @brief A container that contains information about a lobby.
     * It contains the game id, the id of the creator and the not chosen color.
     * A lobby is a game that was created by a player and that waits for a second player
     * to join it.
     */
    std::vector<std::tuple<int, QString, Color>> lobbiesInfo;
    /**
     * @brief A client id that is used to indentify a new ConnectionToClient thread.
     * It is incremented when there is a incomming connection.
     */
    unsigned clientId;
    /**
     * @brief A game id that is used to indentify a new game instance.
     * It is incremented every time a new game is created.
     */
    unsigned gameId;
    /**
    * @brief db is database on server.
    */
    QSqlDatabase db;
    /**
     * @brief Generates a random int between 0 and 2 both included.
     * @return a random int between 0 and 2
     */
    int genRandomInt();
    /**
     * @brief Sends a CONNECTION_ESTABLISHED or REFESH_LOBBY message to all connected clients.
     */
    void refreshLobbies() const;
    /**
     * @brief Removes a lobby identified by its id.
     * @param id the id of the lobby to remove
     */
    bool removeLobby(int id);
    /**
     * @brief Sends data to clients that are playing a game.
     * @param tuple contains the game and the associated clients that are playing
     */
    void sendData(const std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>& tuple) const;
    /**
     * @brief Gets the tuple from gameHandler field through a connection to client.
     * @param cli the connection to client that is joining, playing a game.
     * @return the index of the tuple from gameHandler field
     */
    int getIndexTuple(ConnectionToClient* cli) const;
    /**
     * @brief Removes a tuple where its game has ended from the gameHandler field.
     * @param index the index of the tuple to remove
     */
    void removeTuple(int index);
    /**
     * @brief Handles the reloading of a game.
     * @param cli the client who wants to reload a game
     * @return true if the reloading is a success, false otherwise
     */
    bool gameReloader(ConnectionToClient* cli, QByteArray data);
    /**
     * @brief Checks if the disconnected client was in game or not.
     * @param idx the index to check
     * @return true if the client was in a game, false otherwise
     */
    bool wasInGame(int idx,ConnectionToClient * ctc);
    /**
     * @brief Checks whether the user pseudonym exists or not in the db. If not the function
     * add the user to the user table.
     * @param pseudo the player pseudonym
     */
    void checkDbUser(QString pseudo);
    /**
     * @brief Checks whether the given name has a game in pause with the given gameId.
     * @param gId the id of the game that is in pause
     * @param name the name of the client
     */
    bool checkPauseDb(int gId, QString name);
    /**
     * @brief Removes a pause line fromd the pause table.
     * @param name the name of the client
     * @param gId the id of the game
     */
    void removePauseFromDb(QString name, int gId);
    /**
     * @brief Adds a game to HISTORY table when it has finished.
     * @param tuple the tuple that contains informations about the finished game.
     */
    void addGameToHistoryDb(const std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>& tuple);
    /**
     * @brief Adds a line into the PAUSE table.
     * If the player is playing against a bot, he can make a pause.
     * @param name the name of the player that is making a pause
     * @param gameId the id of the game
     */
    void addPauseToDb(QString name, int gameId);
    /**
     * @brief Refreshes the win statistic of a client if he has won.
     * If the first player has won then the function refreshes the tuple of the client
     * in the STAT table. It does the same actions if the second player wins.
     * @param tuple the tuple that contains the informations to check
     */
    void refreshStat(const std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>& tuple);
    /**
     * @brief Checks whether the client has a lobby. If he has, then the function delete the lobby
     * if this one is public. Then it deletes the created tuple in the gameHandler field.
     * @param idx the index of the tuple to check
     * @return true if the lobby was public, false otherwise
     */
    bool checkLobby(int idx);
public:
    /**
    * @brief server
    * @param parent
    */
    explicit  Server(QObject*parent=0);

    ~Server();
    /**
    * @brief start_server launch the server
    *  the server need a port and QhostAdress
    *  if the server start we have a message server connected
    */
    void start_server();
    /**
     * @brief Gets the clients' connections.
     * @return A vector of connected clients.
     */
    const std::vector<ConnectionToClient*> getConnectedClients() const;
    /**
     * @brief Gets the number of client connections.
     * @return The number of connected clients.
     */
    unsigned getNbConnections() const;
    /**
     * @brief Handles messages sent by a client.
     * @param msg the message to interpret.
     * @param data the data to handle
     * @param cli the client connection to the client that sent the message.
     */
    void handleMessageFromClient(QByteArray data, ConnectionToClient * cli);
    /**
     * @brief Disconnects a given client.
     *
     * This method is used in ConnectionToClient class and it is used when
     * the ConnectionToClient thread has stopped.
     *
     * @param ctc the connection to client to disconnect.
     */
    void disconnectClient(ConnectionToClient * ctc);

    void add_observer(Observer& observer) override;

    void remove_observer(Observer& observer) override;

    void notify_observers() override;

protected:
    /**
    * @brief Creates a new thread when there is an available connection.
    *
    * @param handle the socket's descriptor.
    */
    void  incomingConnection(qintptr handle) override;


};
#endif // SERVER_H
