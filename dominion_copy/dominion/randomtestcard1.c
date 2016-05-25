//Random card test for Smithy

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
        
        int pre_numHand = g.handCount[g.whoseTurn];
        myassert(pre_numHand==5, "I should have 5 cards in my hand now");
        cardEffect(13, 0, 0, 0, &g, 0, 0);
        int post_numHand =g.handCount[g.whoseTurn];
        myassert(post_numHand==7, "I should have 7 cards in my hand now");
        //buy a card does not update the coins.
        int i = buyCard(0, &g);
        myassert(i == 0, "I should have enough coins to buy a smithy now");
        post_numHand =g.handCount[g.whoseTurn];
        myassert(post_numHand==7, "I should still have 7 cards in my hand now");
        

    }
    checkasserts();
    
    return 0;
}


