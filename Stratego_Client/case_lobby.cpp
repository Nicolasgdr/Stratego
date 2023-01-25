#include "case_lobby.h"
#include <Qimage>

#include <QPainter>

CaseLobby::CaseLobby(const QString &creator, int gameId, Color color, QListWidget *parent = nullptr)
    : QListWidgetItem(parent), creator(creator), gameId(gameId), color(color)
{
    QFont font("Calibri", 10, QFont::Bold);
    this->setFont(font);
    this->setSizeHint(QSize(100,50));
    this->setForeground(QColor(255, 255, 255));
    this->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    this->setText("Creator : " + creator + " - Game ID : " +QString::number(gameId));
    QBrush textColor(Qt::black);
    this->setForeground(textColor);
    QImage imageSide;
    switch (color)
    {
    case RED:        
        imageSide = QImage("../Stratego_Client/img/red_side.jpg");
        break;
    case BLUE:
        imageSide = QImage("../Stratego_Client/img/blue_side.jpg");
        break;
    default:
        ;
    }
    QBrush brush(imageSide);
    this->setBackground(brush);
}

const QString& CaseLobby::getCreator()const{
    return creator;
}

const int& CaseLobby::getGameId()const{
    return gameId;
}

const Color& CaseLobby::getColor()const{
    return color;
}
