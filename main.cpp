#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include "tile.h"

using namespace std;

std::queue<Tile*> allTiles;
std::stack<Tile*> solvedStack;

// Takes two tile objects, compares tokens of tile1 at pos1 with tile2 at pos2. Rotates
// tile2 all the way around until match is found
bool matchTiles(Tile* tile1, Tile* tile2, int pos1, int pos2);

// Dumps an ascii representation of the current state of the solved puzzle
void dumpTiles();

// Returns a string representation the token enum that is passed in
const char* tokToStr(Token);

// Run some tests to ensure algorithm is working
void runTests();

int main()
{
    allTiles.push(new Tile(1, TOK_PG_B, TOK_BAR_A, TOK_GG_A, TOK_TREE_A));
    allTiles.push(new Tile(2, TOK_TREE_B, TOK_BAR_B, TOK_GG_B, TOK_PG_B));
    allTiles.push(new Tile(3, TOK_GG_B, TOK_PG_A, TOK_GG_A, TOK_BAR_A));
    allTiles.push(new Tile(4, TOK_BAR_A, TOK_GG_B, TOK_PG_A, TOK_TREE_A));

    solvedStack.push(allTiles.front());
    allTiles.pop();

    int max_iterations = 10;
    int iterations = 0;
    int lastIdMatched = -1;

    while (allTiles.size() > 0 && iterations < max_iterations) {

    	Tile* tile = solvedStack.top();
    	Tile* candidate = allTiles.front();
    	allTiles.pop();

    	if (matchTiles(tile, candidate, 1, 3)) {
    		solvedStack.push(candidate);
    		printf("Match found\n");
    	}
    	else {
    		allTiles.push(candidate);
    		printf("Match not found\n");
    	}

    	iterations++;
    }

    return 0;
}

// Takes two tile objects, compares tokens of tile1 at pos1 with tile2 at pos2. Rotates
// tile2 all the way around until match is found
bool matchTiles(Tile* tile1, Tile* tile2, int pos1, int pos2) {

	printf("matchTiles(tile1: %d, tile2: %d, pos1: %d, pos2: %d)\n", tile1->getId(), tile2->getId(), pos1, pos2);

    int tries = 4;
    while (tries > 0){
        if (tile1->tokenAt(pos1) == tile2->tokenAt(pos2)) {
              return true;
        }
        else {
            tries--;
            tile2->rotate();
        }
    }

    return false;
}

// Dumps an ascii representation of the current state of the solved puzzle
void dumpTiles()
{
    // TODO
}

// Returns a string representation the token enum that is passed in
const char* tokToStr(Token tok)
{
    switch(tok){
    case TOK_BAR_A: return "BT";
    case TOK_BAR_B: return "BB";
    case TOK_GG_A:  return "GT";
    case TOK_GG_B:  return "GB";
    case TOK_PG_A:  return "PT";
    case TOK_PG_B:  return "PB";
    case TOK_TREE_A:    return "TT";
    case TOK_TREE_B:    return "TB";
    }

    return "";
}

// Run some tests to ensure algorithm is working
void runTests()
{
	printf("runTests()");

	Tile* t1 = new Tile(1, TOK_BAR_A, TOK_BAR_B, TOK_GG_A, TOK_GG_B);
	Tile* t2 = new Tile(1, TOK_BAR_A, TOK_BAR_B, TOK_GG_A, TOK_GG_B);

	bool val = matchTiles(t1, t2, 1, 2);

	if (!val) printf("matchTile failed");

}
