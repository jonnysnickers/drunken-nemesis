#include "game.h"


void spinwheel(State *state,int act_player){
    int tmp = rand()%50 + 5;
    int i;
    for(i = 0;i<tmp;i++){
        state->POSITION = (state->POSITION+1)%24;
        refresh(state,act_player);
        Sleep(40);
    }
}



//Each call of this function simulates one round of game
void next_round(State *state){
    char c[2];
    int tmp,i,counter;
    int act_player = rand()%state->NUM_PLAYERS;

	while(!state->ROUND_ENDED){
        counter = 0;
		refresh(state, act_player);

		printf("  What do you want to do?\n   1.Guess a consonant.\n   2.Buy vovel.\n   3.Guess word.\n");
        scanf("%d",&tmp);

		switch(tmp){
            case 1:
                printf("Press SPACE to spinn the wheel.\n");
                getch();
                spinwheel(state,act_player);

                //obsluga wyjatkow
                if(state->VALUE[state->POSITION] < 0){
                    printf("zjebales\n");
                }
                else{
                    printf("Guess a consonant.\n");
                    scanf("%s",c);
                    for(i=0;i<strlen(state->PHRASE);i++){
                        if(state->PHRASE[i] == c[0]){
                            state->LETTER_GUESSED[c[0] - 'a'] = 1;
                            counter++;
                        }
                    }
                    state->SCORES[act_player] += counter*state->VALUE[state->POSITION];
                }
                act_player = (act_player + 1)%state->NUM_PLAYERS;

            break;
            case 2:

            break;
            case 3:

            break;
            default:
            break;
		}
	}
}

int main(){
    int i;
    State state;
	init(&state);
	next_round(&state);

return 0;
}
