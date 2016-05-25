//this is the unit test for village

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

  int k[10] = {village,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  initializeGame(2, k, 5, &g);
  //add a village to player 0's hand
  gainCard(0, &g, 2, 0); 
  int i = cardEffect(village, 0, 0, 0, &g, 5, 0);
  myassert(i == 0, "Village should be played successfully");
  int num = g.handCount[0];
  myassert(num == 6, "Player 0 should have 6 cards now");
  int action_num = g.numActions;
  //did not use the play card, so the action should be 3
  myassert(action_num ==3, "PLyaer should have 3 actions now");


  checkasserts();
  return 0;
}
