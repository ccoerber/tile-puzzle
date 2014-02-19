#ifndef TILE_H
#define TILE_H

enum Token{
    TOK_BAR_A = 1 << 0,
    TOK_BAR_B = 1 << 1,
    TOK_TREE_A = 1 << 2,
    TOK_TREE_B = 1 << 3,
    TOK_GG_A = 1 << 4,
    TOK_GG_B = 1 << 5,
    TOK_PG_A = 1 << 6,
    TOK_PG_B = 1 << 7,
};

/*
 * This class represents one of the puzzles tiles.  A tile has a token on each of
 * its four sides.  The tokens are stored in an array.  Index 0 is the top token,
 * index 1 is the right token, etc., as follows.
 *
 * -------
 * |  0  |
 * |3   1|
 * |  2  |
 * -------
 *
 * A tile can also be rotated (clockwise).  A rotated tile stores its tokens in the same indexes
 * of the array, but when queried, will return the token at the index which represents
 * which side of the tile the token exists.  For example, if the tile has been rotated twice,
 * calling tokenAt(1) - the token on the right side of the tile - will actually return the token
 * at index 3 of the array.
 *
 */

class Tile{
public:
    Tile(int id, Token tok1, Token tok2, Token tok3, Token tok4);
    ~Tile(){}

    void rotate();

    // returns the token at the specified position, taking the rotation into account.
    // position 0: top
    // position 1: right
    // position 2: bottom
    // position 3: left
    Token tokenAt(int pos) const;

    int getId() const { return _id; }
    void dump() const;

private:
    Token _tokens[4];
    int _rotation;
    int _id;
};

#endif // TILE_H
