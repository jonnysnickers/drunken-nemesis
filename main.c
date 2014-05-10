#include "game.h"
/**
*   Each call of this function simulates one round of game
**/
void round(State *state){
    char c[2];
    int tmp,i,counter,temp,playercontinue,fail;
    int act_player = rand()%state->NUM_PLAYERS;

    //Main loop
	while(!state->ROUND_ENDED){
        counter = 0;
        playercontinue = 0;
        char guess[50];

		refresh(state, act_player);

		printf("  What do you want to do?\n   1.Guess a consonant.\n   2.Buy vovel.\n   3.Guess word.\n");
        scanf("%d",&tmp);

        //Switch that handle the decision of player
		switch(tmp){
            case 1:
                spinwheel(state,act_player);
                //Here we handle the case of bancrupt, free and lose
                temp = state->VALUE[state->POSITION];
                if(temp < 0){
                    if(temp == -1){
                        state->SCORES[act_player] = 0;
                        playercontinue = 0;
                        printf("You loose all moeny and turn, press SPACE to continue.\n");
                        getch();
                    }
                    else if(temp == -2){
                        playercontinue = 1;
                        printf("You can guess any letter without any consequences.\n");
                        scanf("%s",c);
                        for(i=0;i<strlen(state->PHRASE);i++)
                            if(state->PHRASE[i] == c[0])
                                state->LETTER_GUESSED[c[0] - 'a'] = 1;
                    }
                    else if(temp == -3){
                        playercontinue = 0;
                        printf("You loose turn, press SPACE to continue.\n");
                        getch();
                    }
                }
                else{
                    printf("Guess a consonant.\n");
                    scanf("%s",c);
                    if(state->LETTER_GUESSED[c[0] - 'a'] == 0 && (c[0] != 'a' && c[0] != 'e' && c[0] != 'i' && c[0] != 'o' && c[0] != 'u'))
                        for(i=0;i<strlen(state->PHRASE);i++){
                            if(state->PHRASE[i] == c[0]){
                                state->LETTER_GUESSED[c[0] - 'a'] = 1;
                                counter++;
                                playercontinue = 1;
                            }
                        }
                    state->SCORES[act_player] += counter*state->VALUE[state->POSITION];
                }
                if(playercontinue == 0)act_player = (act_player + 1)%state->NUM_PLAYERS;

            break;
            case 2:
                if(state->SCORES[act_player] >= 250){
                    state->SCORES[act_player] -= 250;
                    printf("Guess a vovel.\n");
                    scanf("%s",c);
                    if((c[0] == 'a' || c[0] == 'e' || c[0] == 'i' || c[0] == 'o' || c[0] == 'u'))
                        for(i=0;i<strlen(state->PHRASE);i++)
                            if(state->PHRASE[i] == c[0])
                                state->LETTER_GUESSED[c[0] - 'a'] = 1;
                }
		else {
		    if( state->SCORES[act_player] > 100 ){
		        state->SCORES[act_player] -= 100;
		    }
		    else{
			state->SCORES[act_player] = 0;
		    }
		}
            break;
            case 3:
                fail = -1;
                printf("Guess a phrase.\n");
                scanf("%s",guess);
                for(i=0;strlen(guess) == strlen(state->PHRASE) && i<strlen(state->PHRASE);i++)
                    if(state->PHRASE[i] != '_' && state->PHRASE[i] != guess[i])
                            fail = 1;
                    else if( (i == strlen(state->PHRASE) - 1) && fail == -1 )
                        fail = 0;
                if(fail == 0){
                    state->ROUND_ENDED = 1;
                    for(i=0;i<strlen(state->PHRASE);i++)
                        if(state->LETTER_GUESSED[state->PHRASE[i]-'a'] == 0)
                            counter++;
                    state->SCORES[act_player] += counter * 500;
                }
                act_player = (act_player + 1)%state->NUM_PLAYERS;
            break;
            //Penalty for typig in something different than 1,2,3.
            default:
                printf("Penalty Bancrout, press SPACE to continue\n");
                state->SCORES[act_player] = 0;
                act_player = (act_player + 1)%state->NUM_PLAYERS;
                getch();
                fflush(stdin);
            break;
		}
	}
	int h;
	for(h=0;h<state->NUM_PLAYERS;h++)
        state->TOTAL_SCORES[h] += state->SCORES[h];
}

int main(){
    int i;
    State state;

    banner(0,75);
    init(&state);

	for(i = 1; i <= 3; i++){
        reset(&state);
        round(&state);
	}

	write_result(&state);

return 0;
}
