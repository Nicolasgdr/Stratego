#ifndef CASE_LOBBY_H
#define CASE_LOBBY_H

#endif // CASE_LOBBY_H

#include <QListWidgetItem>
#include <QListWidget>

#include "../Stratego_libs/Model/color.h"
#include "qevent.h"

/**
 * @brief The CaseLobby class represents a created game waiting for a second player.
 * It displays the color the second player will have, the pseudo of the creator of the
 * game and the gameID.
 */
class CaseLobby : public QListWidgetItem{

    QString creator;
    int gameId;
    Color color;

public:
    /**
     * @brief Creates a new caseLobby.
     * @param creator The pseudo of the creator.
     * @param gameId The game ID.
     * @param color The color remaining.
     * @param parent The parent widget of the caseLabby.
     */
    CaseLobby(const QString &creator, int gameId, Color color, QListWidget *parent);

    /**
     * @brief Gets the pseudo of creator of the game
     * @return The pseudo of the creator of the game.
     */
    const QString& getCreator()const;

    /**
    * @brief Gets the ID of the game
    * @return the ID of the game
    */
    const int& getGameId()const;

    /**
     * @brief Gets the color remaining in the game.
     * @return The color remaining in the game.
     */
    const Color& getColor()const;
};
