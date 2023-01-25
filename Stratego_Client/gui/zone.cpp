#include "zone.h"

Zone::Zone(QWidget * parent, Color color) :
    QWidget(parent), color(color)
{
    grid.setSpacing(0);
    grid.setContentsMargins(0,0,0,0);
}

Zone::Zone(Zone& other) :
    QWidget(other.parentWidget()), color(other.color) {}

void Zone::operator = (Zone rhs)
{
    this->setParent(rhs.parentWidget());
    this->color=rhs.color;
}
