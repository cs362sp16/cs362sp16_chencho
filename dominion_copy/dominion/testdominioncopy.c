#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState *p = &G;
    
    srand(time(0));
    
    if (argc < 2){
        printf("Please enter a seed number\n");
        exit(0);
    }
    //randomly generate 10 kingdom cards.
    int k[10];
    int i;

    for (i = 0; i < 10; i ++){
        int kcard;
        int checkDuplicate = 0;
        do{
            checkDuplicate = 0;
            //kingdom cards are between 7 to 26
            kcard = rand()%20 + 7;
            int j;
            for (j = 0; j < i; j++){
                if (kcard == k[j]){
                    kcard = rand()%20 + 7;
                    checkDuplicate = 1;
                }
            }
        }while (checkDuplicate == 1);
        
        
        k[i] = kcard;
    }
    printf("The random generated cards are ");
    for (i = 0; i < 10; i++){
        printf("%d ", k[i]);
    }
    printf("\n");
    
    //generate rndom number of players between 2 to 4
    int numPlayer = rand()%3 +2;
    printf("The random generated number of players are %d", numPlayer);

  printf ("Starting game.\n");
  
  initializeGame(numPlayer, k, atoi(argv[1]), p);
  
  int money = 0;
  int smithyPos = -1;
  int adventurerPos = -1;
  i=0;

  int numSmithies = 0;
  int numAdventurers = 0;

  while (!isGameOver(p)) {
    money = 0;
    smithyPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(p); i++) {
      if (handCard(i, p) == copper)
    money++;
      else if (handCard(i, p) == silver)
    money += 2;
      else if (handCard(i, p) == gold)
    money += 3;
      else if (handCard(i, p) == smithy)
    smithyPos = i;
      else if (handCard(i, p) == adventurer)
    adventurerPos = i;
    }

    if (whoseTurn(p) == 0) {
      if (smithyPos != -1) {
        printf("0: smithy played from position %d\n", smithyPos); 
	playCard(smithyPos, -1, -1, -1, p); 
	printf("smithy played.\n");
	money = 0;
	i=0;
	while(i<numHandCards(p)){
	  if (handCard(i, p) == copper){
	    playCard(i, -1, -1, -1, p);
	    money++;
	  }
	  else if (handCard(i, p) == silver){
	    playCard(i, -1, -1, -1, p);
	    money += 2;
	  }
	  else if (handCard(i, p) == gold){
	    playCard(i, -1, -1, -1, p);
	    money += 3;
	  }
	  i++;
	}
      }

      if (money >= 8) {
        printf("0: bought province\n"); 
        buyCard(province, p);
      }
      else if (money >= 6) {
        printf("0: bought gold\n"); 
        buyCard(gold, p);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
        printf("0: bought smithy\n"); 
        buyCard(smithy, p);
        numSmithies++;
      }
      else if (money >= 3) {
        printf("0: bought silver\n"); 
        buyCard(silver, p);
      }

      printf("0: end turn\n");
      endTurn(p);
    }
    else {
      if (adventurerPos != -1) {
        printf("1: adventurer played from position %d\n", adventurerPos);
	playCard(adventurerPos, -1, -1, -1, p); 
	money = 0;
	i=0;
	while(i<numHandCards(p)){
	  if (handCard(i, p) == copper){
	    playCard(i, -1, -1, -1, p);
	    money++;         
	  }
	  else if (handCard(i, p) == silver){
	    playCard(i, -1, -1, -1, p);
	    money += 2;
	  }
	  else if (handCard(i, p) == gold){
	    playCard(i, -1, -1, -1, p);
	    money += 3;
	  }
	  i++;
	}
      }

      if (money >= 8) {
        printf("1: bought province\n");
        buyCard(province, p);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
        printf("1: bought adventurer\n");
	buyCard(adventurer, p);
	numAdventurers++;
      }else if (money >= 6){
        printf("1: bought gold\n");
	    buyCard(gold, p);
        }
      else if (money >= 3){
        printf("1: bought silver\n");
	    buyCard(silver, p);
      }
      printf("1: endTurn\n");
      
      endTurn(p);      
    }

      printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, p), scoreFor(1, p));
	    
  } // end of While

  printf ("Finished game.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, p), scoreFor(1, p));

  return 0;
}
