#include "widget.h"
#include "ui_widget.h"

GraphicView::GraphicView(QWidget *parent)
    : QWidget(parent)
    , board(Board(this)), blue_deck(Deck(this, BLUE)), red_deck(Deck(this, RED))
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    board.setMaximumSize(600,600);
    board.setMinimumSize(600,600);
    hbox.addWidget(&board);
    hbox.addLayout(&decks_layout);
    hbox.setSpacing(0);
    hbox.setContentsMargins(0,0,0,0);

    blue_deck.setMaximumSize(480,270);
    blue_deck.setMinimumSize(480,270);
    decks_layout.addWidget(&blue_deck);

    red_deck.setMaximumSize(480,270);
    red_deck.setMinimumSize(480,270);
    decks_layout.addWidget(&red_deck);
    decks_layout.setSpacing(0);
    decks_layout.setContentsMargins(0,0,0,0);

}

GraphicView::~GraphicView()
{
    delete ui;
}

void GraphicView::setFirst(const char * text)
{

   board.setFirst(text);
}


