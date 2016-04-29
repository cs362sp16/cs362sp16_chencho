//This is the unittest for Smithy

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
  //add a smithy to player 0
  gainCard(0, &g, 2, 0);
  int i = cardEffect(smithy, 0, 0 ,0, &g, 5, 0);
  myassert(i == 0, "Smithy should be successful");
  int num = g.handCount[0];
  //printf("%d\n", num);
  myassert(num == 8, "There should be 8 cards for player 0 now");
  
  
  gainCard(0, &g, 2, 0);
  i = cardEffect(smithy, 0, 0 ,0, &g, 8, 0);
  num = g.handCount[0];
  myassert(i == 0, "Smithy should be successful");
  myassert(num == 10, "There should be 10 cards for player 0 now because there will be no more card from the deck");
  
  gainCard(0, &g, 2, 0);
  i = cardEffect(smithy, 0, 0 ,0, &g, 10, 0);
  num = g.handCount[0];
  myassert(i == 0, "Smithy should be successful");
  myassert(num == 10, "There should be 10 cards for player 0 now because there will be no more card from the deck");
  checkasserts();
  return 0;
}
