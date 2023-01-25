#ifndef SERVER_VIEW_H
#define SERVER_VIEW_H

#include <iostream>
#include <QHostAddress>
#include <QMainWindow>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include "Server.h"
#include "../Stratego_libs/Model/observ.h"

using std::cout;
/**
 * @brief The ServerConsole class contains all the necessary
 * methods to view in console the stratego server side.
 */
class ServerView : public QMainWindow, public Observer{

    Server& server;

    QTableWidget * tView;
    /**
     * @brief Sets the style of the widget.
     */
    void setStyle();

public:
    /**
     * @brief Constructs a serverView.
     * @param s the server
     * @param parent
     */
    ServerView(Server& s, QWidget * parent = nullptr);

    void update() override;
};

#endif // SERVER_VIEW_H
