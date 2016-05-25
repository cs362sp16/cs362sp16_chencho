//This unit test it to test numHandCards(struct gameState *state) function

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

  int num = numHandCards(&g);
  //printf("%d\n", num);
  myassert(num == 5, "At the beginning of the game player has 5 cards in their hand.");

  g.handCount[0]++;
  num = numHandCards(&g);
  myassert(num ==6, "The cards of the player should be 6 now.");

  g.handCount[0] = 15;
  num = numHandCards(&g);
  myassert(num == 15, "THe cards of the player should be 15 now.");

  if (failed == 0){
     printf("Test complete successfully\n");
     }
  return 0;
}
