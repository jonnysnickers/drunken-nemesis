#ifndef GAME_H
#define GAME_H

#include "display.h"

//Function preparing environment for game
void init(State *state){

    int i;
    //banner(0,75);
    printf("WHEEL OF FORTUNE!\n");

    //Clearing tables and variables
	for(i=0; i<26; i++) state->LETTER_GUESSED[i] = 0;
	for(i=0;i<3;i++) state->SCORES[i] = 0;
	for(i=0;i<3;i++) state->TOTAL_SCORES[i] = 0;
    state->POSITION = 0;

	//Setting rand seed
	srand(time(0));

	//Getting from user number of players and players names
	printf("Enter number of players: ");
	scanf("%d",&state->NUM_PLAYERS);

	for(i=0; i<state->NUM_PLAYERS; i++){
		printf("Enter PLAYER %d name: ", i+1);
		scanf("%s",state->NAMES[i]);
	}

	//Reading list of phrases from file
	FILE *fp;
	fp = fopen("phrases.txt","r");
	while(fscanf(fp, "%s", state->PHRASES[state->NUM_PHRASES++]) != EOF);
	state->NUM_PHRASES--;
	fclose(fp);

	int value[] = {100,150,200,250,-1,250,200,150,100,1000,-2,1000,100,150,200,250,-1,250,200,150,100,2000,-3,2000};
	for(i=0;i<24;i++)state->VALUE[i] = value[i];
}

#endif
