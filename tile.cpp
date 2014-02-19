#include "tile.h"
#include <stdio.h>

Tile::Tile(int id, Token tok1, Token tok2, Token tok3, Token tok4) :
    _id(id),
    _rotation(0)
{
    _tokens[0] = tok1;
    _tokens[1] = tok2;
    _tokens[2] = tok3;
    _tokens[3] = tok4;
}

void Tile::rotate()
{
    _rotation = (_rotation + 1)%4;
}

// returns the token at the specified position, taking the rotation into account.
// position 0: top
// position 1: right
// position 2: bottom
// position 3: left
Token Tile::tokenAt(int pos) const
{
	// take the rotation of the tile into account
	int i = (pos + _rotation) % 4;
	return _tokens[i];
}

void Tile::dump() const
{
    printf("----------\n");
    printf("|        |\n");
    printf("|    %d   |\n", _id);
    printf("|        |\n");
    printf("----------\n");
}
