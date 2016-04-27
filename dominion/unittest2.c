//This is a unit test for fullDEckCOunt function

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

  int count = fullDeckCount(1, copper, &g);

  myassert(count == 7, "there should be 7 copper");
  
  count = fullDeckCount(1, estate, &g);
  myassert(count == 3, "there should be 3 esatete");

  count = fullDeckCount(1, curse, &g);
  myassert(count ==0,  "there should be no curse");

  if (failed == 0){
     printf("test completed successfully!");
  }
  printf("%d\n", count);

  return 0;
}


  
  
