//THis is the unit test for endTurn function
//
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    int i;
    srand(time(0));
    int seed = rand()%400 + 1;
    printf("%d\n", seed);
    //allow 2 to 4 players
    int numPlayer = rand()%3 +2;
    //initialize the game with more players
    initializeGame(numPlayer, k, seed, &g);
    for (i = 0; i < numPlayer; i++){
       currentPlayer = whoseTurn(&g);
       myassert(currentPlayer ==i, "It should be player %d's turn");
       myassert(g.coins > 1, "The player should have more than 1 coin");
       myassert(g.coins < 6, "THe player should have less than 6 coins");
       endTurn(&g);
    }

    if (failed == 0){
       printf("all tests complete successfully\n");
    }
    return 0;
}
