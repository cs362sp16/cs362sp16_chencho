#include "dominion.h"
#include <stdio.h>

int failed = 0;

int myassert(int b,char* msg) {
  if (b == 0) {
    printf("FAILED ASSERTION: %s\n",msg);
    failed = 1;
  }
    return 0;
}

void checkasserts() {
  if (!failed) {
    printf ("TEST SUCCESSFULLY COMPLETED.\n");
  }
}  

int main() {
    struct gameState g;
    
    int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};
    
    initializeGame(2, k, 5, &g);

    int currentPlayer = whoseTurn(&g);
    myassert(currentPlayer == 0, "It should be player 0's turn");
    myassert(g.coins > 1, "The player should have more than 1 coin");
    endTurn(&g);
    currentPlayer = whoseTurn(&g);
    myassert(currentPlayer == 1, "It should be player 1's turn");
    myassert(g.coins > 1, "The player should have more than 1 coin");
    endTurn(&g);
    currentPlayer = whoseTurn(&g);
    myassert(currentPlayer ==0, "It should be player 0's turn");
    myassert(g.coins > 1, "The player should have more than 1 coin");

    int numPlayer = 4;
    int i;
    //initialize the game with more players
    initializeGame(numPlayer, k, 10, &g);
    for (i = 0; i < numPlayer; i++){
       currentPlayer = whoseTurn(&g);
       myassert(currentPlayer ==i, "It should be player %d's turn");
       myassert(g.coins > 1, "The player should have more than 1 coin");
       endTurn(&g);
    }


    if (failed == 0){
       printf("all tests complete successfully\n");
    }
    return 0;
}
