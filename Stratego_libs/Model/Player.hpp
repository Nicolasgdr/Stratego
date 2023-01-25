#ifndef PLAYER_HPP
#include"color.h"
#include<vector>
#include<QString>
#define PLAYER_HPP
class Player {
public:

    Player(){color = NONE;}

    Player(QString pseudo,Color color){
        this->pseudo=pseudo;
        this->color=color;
    }

    QString get_pseudo() const{
        return  this->pseudo;
    }

    Color getColor() const{
        return this->color;
    }

private:
    Color color;
    QString pseudo;
};

#endif // PLAYER_HPP
