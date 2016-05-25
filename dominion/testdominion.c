#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "dominion_helpers.h"


int main (int argc, char** argv) {
    struct gameState G;
    struct gameState *p = &G;
    
    p = newGame();
    
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
    
    //generate rndom number of players between 2 to 4
    int numPlayer = rand()%3 +2;
    printf("The random generated number of players are %d\n", numPlayer);
    
    printf ("Starting game.\n");
    
    initializeGame(numPlayer, k, atoi(argv[1]), p);
    
    int money = 0;
    int turn = 0;
    int currentPlayer;
    i=0;
    int cardPrice = 0;
    int randomCardToBuy = 0;
    int timesToRun;
    int numTryToPlayCard;
    
    int buyCardSuccess;
    int playCardSuccess;
    
    int randomCardToPlay;
    int numberOfHand;
    int cardPlayed = 0;
    
    
    while (!isGameOver(p)) {
        turn++;
        
        currentPlayer = whoseTurn(p);
        printf("It is now %d's turn\n", currentPlayer);
        money = 0;
        //magic number, increase the chance of buying high price card.
        timesToRun = 6;
        numTryToPlayCard=15;
        //Increase the chance of playing an action card.
        
        
        numberOfHand = numHandCards(p);
        //try to find a valid action card to play
        while(numTryToPlayCard> 0){
            randomCardToPlay = rand()%numberOfHand;
            if (randomCardToPlay>6 && randomCardToPlay < 26){
                numTryToPlayCard = 0;
                break;
            }
            numTryToPlayCard--;
        }
        
        //get what card the player is trying to play before play it. Because play the card discard the card
        cardPlayed = handCard(randomCardToPlay, p);
        playCardSuccess = playCard(randomCardToPlay, -1, -1, -1, p);
        //return 0 when success
        if (playCardSuccess == 0){
            printf("Player %d played a %d\n", currentPlayer, cardPlayed);
        }
        
        
        updateCoins(currentPlayer, p, 0);
        
        money =p->coins;
        printf("money is %d\n", money);
        //buy only gold card at the beginning of the game so you will get rich
        if (turn/numPlayer < 20){
            //get a random number from 5 to 26
            //silver to the last card.
            while (timesToRun> 0){
                randomCardToBuy = rand()%2 +5;
                cardPrice = getCost(randomCardToBuy);
                //increase the chance of buying gold
                if (cardPrice > 4 && cardPrice <= money){
                    timesToRun = 0;
                }
                timesToRun--;
            }
            buyCardSuccess = buyCard(randomCardToBuy, p);
            
            if (buyCardSuccess == 0){
                printf("Player %d just bought a %d\n", currentPlayer, randomCardToBuy);
            }

        }
        //if turn is less than 50 don't buy a victory card
        else if ( turn/numPlayer < 50){
            //get a random number from 5 to 26
            //silver to the last card.
            while (timesToRun> 0){
                randomCardToBuy = rand()%22 +5;
                cardPrice = getCost(randomCardToBuy);
                if (cardPrice > 4 && cardPrice <= money){
                    timesToRun = 0;
                }
                timesToRun--;
            }
            buyCardSuccess = buyCard(randomCardToBuy, p);
            if (buyCardSuccess == 0){
                printf("Player %d just bought a %d\n", currentPlayer, randomCardToBuy);
            }
            
        }
        //start buying victory card
        else{
            //get a random number from 1 to 3
            //estate to province.
            while (timesToRun> 0){
                randomCardToBuy = rand()%3 +1;
                cardPrice = getCost(randomCardToBuy);
                //don't buy too many estate.
                if (cardPrice > 2 && cardPrice <= money){
                    timesToRun = 0;
                }
                timesToRun--;
            }
            buyCardSuccess = buyCard(randomCardToBuy, p);
            if (buyCardSuccess == 0){
                printf("Player %d just bought a %d\n", currentPlayer, randomCardToBuy);
            }
        }
        
        
        
        //printf("Player %d's current score is %d\n", currentPlayer, scoreFor(currentPlayer, p));
        endTurn(p);
    } // end of While
    
    printf ("Finished game.\n");
    for (i = 0; i < numPlayer; i++){
        printf("Player %d's current score is %d\n", i, scoreFor(i, p));
    }
    printf("It takes %d turns for %d players to finish the game\n", turn/numPlayer, numPlayer);
    printf("The random generated kingdom cards are ");
    for (i = 0; i < 10; i++){
        printf("%d ", k[i]);
    }
    printf("\n");

    free(p);
    return 0;
}
