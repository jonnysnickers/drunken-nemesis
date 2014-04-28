#ifndef GAME_H
#define GAME_H

#include "display.h"

/**
*   This function prepares environment for game i.e.
*   set values for all fields from struct "state".
**/
void init(State *state){

    int i;
    printf("WHEEL OF FORTUNE!\n");

    //Clearing tables and variables
	for(i=0; i<26; i++) state->LETTER_GUESSED[i] = 0;
	for(i=0;i<3;i++) state->SCORES[i] = 0;
	for(i=0;i<3;i++) state->TOTAL_SCORES[i] = 0;
    state->POSITION = 0;
    state->NUM_ROUND = 0;
    state->NUM_PHRASES = 0;
    state->ROUND_ENDED = 0;

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

    //Setting values of points in each field of wheel. -1 is bancrupt, -2 free rund and -3 loose turn.
	int value[] = {100,150,200,250,-1,250,200,150,100,1000,-2,1000,100,150,200,250,-1,250,200,150,100,2000,-3,2000};
	for(i=0;i<24;i++)state->VALUE[i] = value[i];
}

/**
*   This function is responsible for preparing state for next round i.e.
*   Incrementing number of round, setting ROUND_ENDED to 0,
*   Clearing guessed letters and choosing phrase foe next round.
**/
void reset(State *state){
    int i;
    state->NUM_ROUND++;
    state->ROUND_ENDED = 0;
    for(i=0; i<26; i++) state->LETTER_GUESSED[i] = 0;
	for(i=0; i<3; i++) state->SCORES[i] = 0;

    int tmp = rand()%state->NUM_PHRASES;
	for(i=0;i<strlen(state->PHRASES[tmp]);i++) state->PHRASE[i] = state->PHRASES[tmp][i];
	state->PHRASE[strlen(state->PHRASES[tmp])] = 0;
}

/**
*   This functin simulate spinning of wheel and change value of POSITION in state
**/
void spinwheel(State *state, int act_player){
    int tmp = rand()%50 + 5;
    int i;
    for(i = 0; i < tmp; i++){
        state->POSITION = (state->POSITION+1)%24;
        refresh(state,act_player);
        Sleep(40);
    }
}

#endif
