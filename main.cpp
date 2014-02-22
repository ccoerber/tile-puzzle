#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <queue>
#include "tile.h"

using namespace std;

std::queue<Tile*> allTiles;
std::vector<Tile*> solvedStack;

// Takes two tile objects, compares tokens of tile1 at pos1 with tile2 at pos2. Rotates
// tile2 all the way around until match is found
bool matchTiles(Tile* tile1, Tile* tile2, int pos1, int pos2);
bool matchTiles(Tile* tile1, Tile* tile2, Tile* tile3, int pos1, int pos2, int pos3, int pos4);
bool matchTokens(Token tok1, Token tok2);

// Dumps an ascii representation of the current state of the solved puzzle
void dumpSolutionList(bool solution = false);

// Returns a string representation the token enum that is passed in
const char* tokToStr(Token);

// Run some tests to ensure algorithm is working
void runTests();

void findNextMatch(int tileNumber);

int main()
{

    allTiles.push(new Tile(1, TOK_PG_B, TOK_BAR_A, TOK_GG_A, TOK_TREE_A));
    allTiles.push(new Tile(2, TOK_TREE_B, TOK_BAR_B, TOK_GG_B, TOK_PG_B));
    allTiles.push(new Tile(3, TOK_GG_B, TOK_PG_A, TOK_GG_A, TOK_BAR_A));
    allTiles.push(new Tile(4, TOK_BAR_A, TOK_GG_B, TOK_PG_A, TOK_TREE_A));
    allTiles.push(new Tile(5, TOK_BAR_B, TOK_GG_B, TOK_PG_B, TOK_TREE_A));
    allTiles.push(new Tile(6, TOK_TREE_B, TOK_PG_B, TOK_TREE_A, TOK_BAR_B));
    allTiles.push(new Tile(7, TOK_BAR_A, TOK_GG_A, TOK_PG_B, TOK_TREE_A));
    allTiles.push(new Tile(8, TOK_BAR_A, TOK_GG_B, TOK_TREE_A, TOK_PG_B));
    allTiles.push(new Tile(9, TOK_TREE_B, TOK_BAR_A, TOK_GG_B, TOK_PG_A));

    for (int i = 0; i < (int)allTiles.size(); ++i) {

    	Tile* firstTile = allTiles.front();
    	allTiles.pop();

    	solvedStack.push_back(firstTile);

    	for (int j = 0; j < 4; ++j) {

    		findNextMatch(1);
    		firstTile->rotate();
    	}


    	allTiles.push(solvedStack.back());
    	solvedStack.pop_back();
    }

    //dumpTiles();
    return 0;
}

void findNextMatch(int tileNumber)
{
	//printf("findNextMatch(tileNumber: %d)\n", tileNumber);

	// compare most recent solved tile with next available candidate tile

	Tile* tile = solvedStack.back();

	for (int i = 0; i < (int)allTiles.size(); ++i) {

		// grab the next candidate tile
		Tile* candidate = allTiles.front();
		allTiles.pop();

		// check for match between latest solved tile and candidate
		bool match = false;
		if (tileNumber == 1 || tileNumber == 2) {

			match = matchTiles(tile, candidate, 1, 3);
		}
		else if (tileNumber == 3 || tileNumber == 6) {

			match = matchTiles(solvedStack.at(tileNumber - 3), candidate, 2, 0);
		}
		else if (tileNumber == 4 || tileNumber == 5 || tileNumber == 7 || tileNumber == 8) {

			match = matchTiles(tile, candidate, solvedStack.at(tileNumber - 3), 1, 3, 2, 0);
		}

		// a match was found
    	if (match) {

    		// put the matching tile on the solved stack
    		solvedStack.push_back(candidate);

    		if (allTiles.empty()){
    			dumpSolutionList(true);
    		}
    		else {
    			dumpSolutionList();
    			findNextMatch(tileNumber + 1);
    		}

    		allTiles.push(solvedStack.back());
    		solvedStack.pop_back();
    	}
    	else {
    		allTiles.push(candidate);
    	}
	}

}

// Takes two tile objects, compares tokens of tile1 at pos1 with tile2 at pos2. Rotates
// tile2 all the way around until match is found
bool matchTiles(Tile* tile1, Tile* tile2, int pos1, int pos2)
{
	//printf("matchTiles(tile1: %d, tile2: %d, pos1: %d, pos2: %d)\n", tile1->getId(), tile2->getId(), pos1, pos2);

    int tries = 4;
    while (tries > 0){
        if (matchTokens(tile1->tokenAt(pos1), tile2->tokenAt(pos2))) {
              return true;
        }
        else {
            tries--;
            tile2->rotate();
        }
    }

    return false;
}

bool matchTiles(Tile* tile1, Tile* tile2, Tile* tile3, int pos1, int pos2, int pos3, int pos4)
{
    int tries = 4;
    while (tries > 0){
        if (matchTokens(tile1->tokenAt(pos1), tile2->tokenAt(pos2)) && matchTokens(tile3->tokenAt(pos3), tile2->tokenAt(pos4))) {
              return true;
        }
        else {
            tries--;
            tile2->rotate();
        }
    }

    return false;
}

bool matchTokens(Token tok1, Token tok2)
{
	if (tok1 == TOK_BAR_A && tok2 == TOK_BAR_B) 		return true;
	else if(tok1 == TOK_BAR_B && tok2 == TOK_BAR_A) 	return true;
	else if(tok1 == TOK_GG_A && tok2 == TOK_GG_B) 		return true;
	else if(tok1 == TOK_GG_B && tok2 == TOK_GG_A) 		return true;
	else if(tok1 == TOK_PG_A && tok2 == TOK_PG_B) 		return true;
	else if(tok1 == TOK_PG_B && tok2 == TOK_PG_A) 		return true;
	else if(tok1 == TOK_TREE_A && tok2 == TOK_TREE_B) 	return true;
	else if(tok1 == TOK_TREE_B && tok2 == TOK_TREE_A) 	return true;
	else return false;

}

// Dumps an ascii representation of the current state of the solved puzzle.  If solution
// is set to TRUE, the solvedStack contains all tiles so mark as a solution to the puzzle.
void dumpSolutionList(bool solution)
{
	if (solution) printf("SOLUTION: ");

	for (int i = 0; i < (int)solvedStack.size(); ++i) {
		printf("%d(%d) ", solvedStack.at(i)->getId(), solvedStack.at(i)->getRotation());
	}
	printf("\n");
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
