#ifndef ACTION_SEND_H
#define ACTION_SEND_H

enum Action_send
{
    CONNECTION_TO_SERVER,  //c->s
    CREATE_GAME, //c->s
    REFRESH_LOBBY,  //s->c
    LAUNCH_GAME, //c->s
    SEND_DATA,  //s->c
    PLACE_PAWN, //c->s
    MOVE_PAWN, //c->s
    TO_NEXT_PLAYER, //c->s
    GAME_IS_OVER,  //s->c
    ERROR,  //s->c
    PLACE_ALL_PAWN,
    DELETE_GAME,  //c->s
    PRIVATE_GAME,  //s->c
    //sent while client is closing the pop up of the end game or while closing the pause pop up
    RETURNING_TO_LOBBY,  //c->s
    OPPONENT_LEAVED,  //s->c
    PAUSE,  //c->s
    GAME_PAUSE,  //s->c
    RELOAD_GAME  //c->s
};

#endif // ACTION_SEND_H

