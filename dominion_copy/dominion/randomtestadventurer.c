//Random card test for Adventurer

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
        int i = cardEffect(7,1,1,1,&g,0,0);
        
        myassert(i == 0, "I should always be able to play adventurer");
        myassert(g.handCount[g.whoseTurn]==7, "The player should have 7 cards in hand after playing adventure");
        
        updateCoins(g.whoseTurn, &g, 0);
        int postCoin = g.coins;
        myassert(preCoin < postCoin+1, "The player should have at least 2 more coin after playing adventure");
        
        initializeGame(numPlayer, k, atoi(argv[1]), &g);
        i = buyCard(0, &g);
        myassert(i == 0, "I should have enough coins to buy a smithy now");
        //play one more treasure
        i = cardEffect(7,1,1,1,&g,0,0);
        myassert(i == 0, "I should always be able to play adventurer");
        i = cardEffect(7,1,1,1,&g,0,0);
        myassert(i == 0, "I should always be able to play adventurer");

    }
    checkasserts();
    
    return 0;
}


