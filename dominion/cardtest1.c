//Card test for feast

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

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,council_room,ambassador,
	       outpost,baron,tribute};

  initializeGame(2, k, 5, &g);
  int i = cardEffect(feast, smithy, 0, 0, &g, 0, 0);
  myassert(i == 0, "I should be able to play feast and buy a smithy");

  i = cardEffect(feast, adventurer, 0, 0, &g, 0, 0);
  myassert(i != 0, "I should not be able to play feast and buy an adventurer because it is too expensive");
  i = cardEffect(feast, mine, 0, 0, &g, 0, 0);
  myassert(i != 0, "I should not be able to play feast and buy an mine because it does not exist");
  checkasserts();
  return 0;
}

