#include "tile.h"

Tile::Tile(QWidget * parent) : QPushButton(parent) {}

Tile::Tile(Tile& other) : QPushButton(other.parentWidget()){}

void Tile::operator = (Tile rhs){ setParent(rhs.parentWidget()); }
