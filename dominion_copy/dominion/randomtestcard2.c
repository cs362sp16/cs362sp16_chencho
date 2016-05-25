//Random card test for Garden

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int main(int argc, char **argv) {
    struct gameState g;
    if (argc < 2){
        printf("Please enter a seed number\n");
        exit(0);
    }
    
    int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,council_room,ambassador, outpost,baron,tribute};
    
    srand(time(0));
    int i;
    //randomly run the test 2000 times.
    for (i = 0; i < 2000; i++){
        //generate rndom number of players between 2 to 4
        int numPlayer = rand()%3 +2;
        
        initializeGame(numPlayer, k, atoi(argv[1]), &g);
        /*
         * Not effective input
         for (n = 0; n < 2000; n++){
         for (i = 0; i < sizeof(struct gameState); i++){
         ((char*)&g)[i]=floor(rand()*256);
         }
         }
         */
        updateCoins(g.whoseTurn, &g, 0);
        int preCoin = g.coins;
        
        //gain a garden to hand for player 0
        gainCard(2, &g, 2, 0);
        //trying to play garden
        int i = cardEffect(gardens, 0, 0, 0, &g, 5, 0);
        int num = g.handCount[0];
        myassert( i == -1, "I should not be able to play garden card");
        myassert(num == 6, "There should still be 6 cards in my hand");
        
        updateCoins(g.whoseTurn, &g, 0);
        int postCoin = g.coins;
        myassert(preCoin == postCoin, "The player should have at least 2 more coin after playing adventure");
        
    }
    checkasserts();
    
    return 0;
}


