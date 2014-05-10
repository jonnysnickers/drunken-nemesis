#ifndef GAME_H
#define GAME_H

#include "display.h"
#include "state.h"

void tolowercase( char * s ){
    int i;
    for( i = 0; i < strlen(s); i++ ){
        if( s[i] >= 'A' && s[i] <= 'Z' ){
            s[i] -= ('A' - 'a');
        }
    }
}

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
	//
    printf("Do you want to enter your own phrases (Y/N)?\n");
    char a[100];
    scanf("%s", a);
    if( a[0] == 'Y' || a[0] == 'y' ){
        state->NUM_PHRASES = 3;
        printf("Enter three strings: (separete words with \'_\')\n");
        int i,j;
        for( i = 0; i < 3; i++){
            printf("Enter phrase: ");
            scanf( "%s", a );
            tolowercase(a);
            strcpy( state->PHRASES[i], a );
        }
        for(i =0; i< 3; i++){
            printf("%s\n",state->PHRASES[i]);
        }
        getch();
    }
    else{	//Reading list of phrases from file
        FILE *fp;
        fp = fopen("phrases.txt","r");
        while(fscanf(fp, "%s", state->PHRASES[state->NUM_PHRASES++]) != EOF);
        state->NUM_PHRASES--;
        fclose(fp);
    }
	//Setting values of points in each field of wheel. -1 is bancrupt, -2 free rund and -3 loose turn.
	int value[] = {100,150,200,250,-1,250,200,150,100,1000,-2,1000,100,150,200,250,-1,250,200,150,100,2000,-3,2000};
	for(i=0;i<24;i++)state->VALUE[i] = value[i];
}

/**
 *   This function is responsible for preparing state for next round i.e.
 *   Incrementing number of round, setting ROUND_ENDED to 0,
 *   Clearing guessed letters and choosing phrase for next round.
 *   Chosen phrase is replaced with last phrase in table, number of
 *   phrases is decremented.
 **/
void prepare_next_round(State *state){
	int i;
    state->NUM_ROUND++;
	state->ROUND_ENDED = 0;
	for(i=0; i<26; i++) state->LETTER_GUESSED[i] = 0;
	for(i=0; i<3; i++) state->SCORES[i] = 0;

	int tmp = rand()%state->NUM_PHRASES;
	for(i=0;i<strlen(state->PHRASES[tmp]);i++) state->PHRASE[i] = state->PHRASES[tmp][i];
    state->PHRASE[strlen(state->PHRASES[tmp])] = 0;

	for(i=0;i<strlen(state->PHRASES[tmp]);i++) state->PHRASES[tmp][i] = state->PHRASES[state->NUM_PHRASES][i];
	state->NUM_PHRASES--;
}

/**
 *   This functin simulate spinning of wheel and changes value of POSITION in state.
 **/
void spinwheel(State *state ){
	int tmp = rand()%50 + 5;
	int i;
	for(i = 0; i < tmp; i++){
		state->POSITION = (state->POSITION+1)%24;
		refresh(state);
		Sleep(40);
	}
}


/**
 *   This functin is called when player wants to guess a pharase.
 **/
void guess_a_phrase( State * state ){
	int fail = 0, i,counter = 0;
	char guess[100];
    printf("Guess a phrase.\n");
    scanf("%s",guess);
    tolowercase(guess);
    if( strlen(guess) == strlen(state->PHRASE) ){
        for(i=0;i<strlen(state->PHRASE);i++){
            if( state->PHRASE[i] == '_' ){
                continue;
            }
            if( state->PHRASE[i] != guess[i] ){
                fail = 1;
                state->PLAYERCONTINUE--;
                break;
            }
        }
    }
    else {
        fail = 1;
        state->PLAYERCONTINUE--;
    }
	if(fail == 0){
		state->ROUND_ENDED = 1;
		for(i=0;i<strlen(state->PHRASE);i++){
			if(state->LETTER_GUESSED[state->PHRASE[i]-'a'] == 0){
				counter++;
			}
		}
		state->SCORES[state->CURRENT_PLAYER] += counter * 500;
	}
}

/**
 *   This functin is called when player wants to guess a consonant.
 **/
void case1( State * state ){
    spinwheel(state);
    //Here we handle the case of bancrupt, free and lose
    int temp = state->VALUE[state->POSITION];
    // BANKRUPT
    if(temp == -1){
        state->SCORES[state->CURRENT_PLAYER] = 0;
        state->PLAYERCONTINUE = 0;
        printf("You loose all moeny and turn, press SPACE to continue.\n");
        getch();
        return;
    }
    // FREE ROUND
    else if(temp == -2){
        state->PLAYERCONTINUE++;
        printf("You get a free round!\nPress SPACE to continue.\n");
        getch();
        return;
    }
    // LOSE ROUND
    else if(temp == -3){
        state->PLAYERCONTINUE = 0;
        printf("You loose turn, press SPACE to continue.\n");
        getch();
        return;
    }

    printf("Guess a consonant.\n");
    char c[10];
    scanf("%s",c);
    tolowercase(c);
    int i;
    int counter = 0;
    if(state->LETTER_GUESSED[c[0] - 'a'] == 0 && (c[0] != 'a' && c[0] != 'e' && c[0] != 'i' && c[0] != 'o' && c[0] != 'u')){
        for(i=0;i<strlen(state->PHRASE);i++){
            if(state->PHRASE[i] == c[0]){
            state->LETTER_GUESSED[c[0] - 'a'] = 1;
            counter++;
            }
        }
    }
    else{
        state->PLAYERCONTINUE--;
        return;
    }
    if( counter == 0 ){
        state->PLAYERCONTINUE--;
        return;
    }
    state->SCORES[state->CURRENT_PLAYER] += counter*state->VALUE[state->POSITION];
    refresh( state );
    printf("Do you want to guess a phrase(Y/N)?\n");
    char answer[10];
    scanf("%s",answer);
    if( answer[0] == 'Y' || answer[0] == 'y' ){
        guess_a_phrase( state );
    }
}

/**
 *   This functin is called when player wants to buy a vowel.
 **/
void case2( State * state ){
    if(state->SCORES[state->CURRENT_PLAYER] >= 250){
        state->SCORES[state->CURRENT_PLAYER] -= 250;
        printf("Guess a vowel.\n");
        char c[10];
        int i;
        scanf("%s",c);
        tolowercase(c);
        int is_vowel_in_phrase = 0;
        if((c[0] == 'a' || c[0] == 'e' || c[0] == 'i' || c[0] == 'o' || c[0] == 'u')){
            for(i=0;i<strlen(state->PHRASE);i++){
                if(state->PHRASE[i] == c[0]){
                   is_vowel_in_phrase = 1;
                   state->LETTER_GUESSED[c[0] - 'a'] = 1;
               }
            }
            if( is_vowel_in_phrase == 0 ){
                state->PLAYERCONTINUE--;
            }
        }
        else {
            state->PLAYERCONTINUE--;
        }
    }
    else {
        state->SCORES[state->CURRENT_PLAYER] = 0;
        state->PLAYERCONTINUE--;
    }
}

/**
 *   This functin is one round of the game.
 **/
void round(State *state){
	char c[2];
    int tmp,i,temp;
	state->CURRENT_PLAYER = rand()%state->NUM_PLAYERS;
	state->PLAYERCONTINUE = 1;

		//Main loop
    while(!state->ROUND_ENDED){

        refresh(state);

        printf("  What do you want to do?\n   1.Guess a consonant.\n   2.Buy vowel (costs 250).\n");
        scanf("%d",&tmp);

        //Switch that handle the decision of player
        switch(tmp){
            case 1:
                   case1( state );
            break;
            case 2:
                   case2( state );
            break;
            //Penalty for typig in something different than 1,2.
            default:
                printf("Penalty Bankrupt, press SPACE to continue\n");
                state->SCORES[state->CURRENT_PLAYER] = 0;
                state->PLAYERCONTINUE = 0;
                getch();
                fflush(stdin);
            break;
        }
        if(state->PLAYERCONTINUE == 0){
            state->CURRENT_PLAYER = (state->CURRENT_PLAYER + 1)%state->NUM_PLAYERS;
            state->PLAYERCONTINUE = 1;
        }
    }
    int h;
    for(h=0;h<state->NUM_PLAYERS;h++)
        state->TOTAL_SCORES[h] += state->SCORES[h];
}

#endif
