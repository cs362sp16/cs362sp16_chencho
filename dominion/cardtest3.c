//This is the unit test for gardens

#include "dominion.h"
#include "dominion_helpers.h"
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
  //gain a garden to hand for player 0
  gainCard(2, &g, 2, 0);
  //trying to play garden
  int i = cardEffect(gardens, 0, 0, 0, &g, 5, 0);
  int num = g.handCount[0];
  myassert( i == -1, "I should not be able to play garden card");
  myassert(num == 6, "There should still be 6 cards in my hand");

  checkasserts();
  return 0;
}
