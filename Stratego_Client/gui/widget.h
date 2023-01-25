#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "board.h"
#include "deck.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class GraphicView : public QWidget
{
    Board board;
    Deck blue_deck;
    Deck red_deck;
    QHBoxLayout hbox=QHBoxLayout(this);
    QVBoxLayout decks_layout;

public:
    GraphicView(QWidget *parent = nullptr);
    ~GraphicView();

    void setFirst(const char * text);

private:
    Ui::Widget *ui;
};
#endif // GRAPHICVIEW_H
