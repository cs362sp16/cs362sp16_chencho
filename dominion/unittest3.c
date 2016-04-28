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
  int card = handCard(3, &g);
  //printf("%d\n", card);
  myassert( (card == 1 || card ==4), "hand card should be either a copper or a estate");
  card = handCard(0, &g);
  myassert( (card == 1 || card ==4), "hand card should be either a copper or a estate");
  card = handCard(1, &g);
  myassert( (card == 1 || card ==4), "hand card should be either a copper or a estate");
  if (failed == 0){
     printf("test completed successfully\n");
  }

  return 0;
}
