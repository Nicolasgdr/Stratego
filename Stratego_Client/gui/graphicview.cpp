#include "graphicview.h"
#include "ui_widget.h"
#include "Client.h"
#include <QDir>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>

GraphicView::GraphicView(bool solo, QWidget *parent, Client* cli)
    : QWidget(parent), cli(cli), board(Board(this))
    , blue_deck(Deck(this, BLUE)), red_deck(Deck(this, RED)), soloGame(solo)
    , buffer(Buffer()), ui(new Ui::Widget)
{
    ui->setupUi(this);

    initlayouts();
    initBoard();
    initDecks();
    initPlayer();
    initConnections();
    qDebug()<<QDir::currentPath();
    this->setStyleSheet(".QWidget {"
                        " background-image:url('../Stratego_Client/img/background.jpg');"
                        " background-repeat: no-repeat;"
                        "}");
    connect(this,SIGNAL(taskFinished()),this,SLOT(deleteLater()));
}

GraphicView::~GraphicView()
{
    delete ui;
}

void GraphicView::setGame(game_info game){
    this->game = game;
    blue_deck.setGame(game);
    red_deck.setGame(game);
    update();
}

void GraphicView::update()
{    
    GameState state = game.state;
    switch(state)
    {
    case (NOT_STARTED) : ; break;
    case (PLACEMENT) :
        placement();
        player.setDisabled(true);
        break;
    case(PLAYER_TURN) :
        player.setDisabled(true);
        if(game.currentPlayerColor==game.playerColor){
            player.setText("Play your turn");
        } else {
            player.setText("Other player's turn");
        }
        board.update(game.board);;
        red_deck.update(NEXT_PLAYER, game.currentPlayerColor);
        blue_deck.update(NEXT_PLAYER, game.currentPlayerColor);
        break;
    case(NEXT_PLAYER) :
        if(game.currentPlayerColor==game.playerColor){
            player.setDisabled(false);
            player.setText("To next player >>");
        }
        board.update(game.board);
        break;
    case(END_GAME) :
        break;
    }
}

void GraphicView::showGame(){
    this->show();
}

void GraphicView::showError(QString msg){
    QMessageBox box;
    box.setWindowTitle("Error");
    box.setText(msg);
    box.exec();
}

void GraphicView::showEndGame(QString msg){
    QStringList list = msg.split(" ");
    QMessageBox box;
    box.setWindowTitle("Winner");
    box.setText(msg);
    if(list[1] == "blue") box.setStyleSheet("background-color: #6699ff;");
    else box.setStyleSheet("background-color: #ff6666;");
    box.exec();
    cli->returning_to_lobby();
}

void GraphicView::showMessage(int nb){
    QString msg = "Game id : "+ QString::number(nb);
    QMessageBox box;
    box.setWindowTitle("Message");
    box.setText(msg);
    box.exec();
    cli->returning_to_lobby();
}

void GraphicView::initlayouts()
{
    hbox.addWidget(&board);
    hbox.addLayout(&decks_layout);
    decks_layout.addWidget(&blue_deck);
    decks_layout.addLayout(&buttons_layout);
    QHBoxLayout* hbox_layout = new QHBoxLayout;
    hbox_layout->addWidget(&player);
    if(soloGame){
        initPause();
        hbox_layout->addWidget(&pause);
    }
    buttons_layout.addLayout(hbox_layout, Qt::AlignCenter);
    buttons_layout.setSpacing(0);
    decks_layout.addWidget(&red_deck);

    hbox.setSpacing(0);
    hbox.setContentsMargins(25,25,25,25);

    decks_layout.setSpacing(0);
    decks_layout.setContentsMargins(25,25,25,25);
}

void GraphicView::initBoard()
{
    board.setMaximumSize(650,650);
    board.setMinimumSize(650,650);
}

void GraphicView::initDecks()
{
    blue_deck.setMaximumSize(480,290);
    blue_deck.setMinimumSize(480,290);

    red_deck.setMaximumSize(480,290);
    red_deck.setMinimumSize(480,290);
}

void GraphicView::initPlayer()
{
    player.setText("Welcome");
    player.setFixedWidth(200);
    player.setDisabled(false);
}

void GraphicView::initPause(){
    pause.setText(QString::fromUtf8("\u23F8"));
    pause.setFixedSize(QSize(25, 25));
    pause.setStyleSheet("QPushButton { font-size: 18px; }");
}

void GraphicView::initConnections()
{
    QObject::connect(&board, SIGNAL(pos_selected(int,int)), this, SLOT(give_info(int,int)));
    QObject::connect(&blue_deck, SIGNAL(rank_selected(Rank)), this, SLOT(give_info(Rank)));
    QObject::connect(&red_deck, SIGNAL(rank_selected(Rank)), this, SLOT(give_info(Rank)));
    QObject::connect(&player, SIGNAL(clicked()), this, SLOT(next_player()));
    if(soloGame)
        QObject::connect(&pause,SIGNAL(clicked()), this, SLOT(do_pause()));
}

void GraphicView::placement()
{
    Color color = game.playerColor;
    board.update(game.board);
    red_deck.update(PLACEMENT, color);
    blue_deck.update(PLACEMENT, color);
}

void GraphicView::give_info(Rank rank)
{
    if(game.state==PLACEMENT)
        buffer.set_rank(rank);
}

void GraphicView::give_info(int row, int col)
{
    // place a piece
    if(game.state==PLACEMENT && buffer.has_rank())
    {
        cli->place_pawn(row,col,buffer.get_rank(),game.playerColor);
    }
    // move a piece
    else if(game.state==PLAYER_TURN && buffer.has_pos())
    {
        array<int,2> old_pos=buffer.empty_pos();
        if(old_pos[0]==row && old_pos[1]==col)
            buffer.set_pos(row, col);
        else
            cli->move_pawn(old_pos[0], old_pos[1], row, col, game.playerColor);
    }
    // store the piece to move
    else if(game.state==PLAYER_TURN)
    {
        buffer.set_pos(row,col);
    }
}

void GraphicView::next_player()
{
    if(game.currentPlayerColor == game.playerColor){
        cli->to_next_player();
        if(game.state==END_GAME) update();
    }
}

void GraphicView::do_pause(){
    cli->pause();
}
