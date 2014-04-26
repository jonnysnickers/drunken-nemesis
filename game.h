#ifndef game.h
#define game.h

#include "display.h"

//Function preparing environment for game
void init(State state){

    int i;
    banner(0,75);
    printf("WHEEL OF FORTUNE!\n");

    //Clearing tables and variables
	for(i=0; i<26; i++) state.LETTER_GUESSED[i] = 0;
	for(i=0;i<3;i++) state.SCORES[i] = 0;
	for(i=0;i<3;i++) state.TOTAL_SCORES[i] = 0;
    state.POSITION = 0;
    state.NUM_ROUND = 1;
    state.ROUND_ENDED = 0;

	//Setting rand seed
	srand(time(0));

	//Getting from user number of players and players names
	printf("Enter number of players: ");
	scanf("%d",&state.NUM_PLAYERS);

	for(i=0; i<state.NUM_PLAYERS; i++){
		printf("Enter PLAYER %d name: ", i+1);
		scanf("%s",state.NAMES[i]);
	}

	//Reading list of phrases from file
	FILE *fp;
	fp = fopen("phrases.txt","r");
	while(fscanf(fp, "%s", state.PHRASES[state.NUM_PHRASES++]) != EOF);
	state.NUM_PHRASES--;
	fclose(fp);

	int tmp = rand()%state.NUM_PHRASES;
	for(i=0;i<tmp;i++) state.PHRASE[i] = state.PHRASES[tmp][i];

	int value[] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4};
	for(i=0;i<24;i++)state.VALUE[i] = value[i];
}

#endif
