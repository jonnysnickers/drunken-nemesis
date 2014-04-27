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
void round(State *state){
    char c[2];
    int tmp,i,counter,temp,playercontinue,fail;
    int act_player = rand()%state->NUM_PLAYERS;

	while(!state->ROUND_ENDED){
        counter = 0;
        playercontinue = 0;
        char guess[50];

		refresh(state, act_player);

		printf("  What do you want to do?\n   1.Guess a consonant.\n   2.Buy vovel.\n   3.Guess word.\n");
        scanf("%d",&tmp);

		switch(tmp){
            case 1:
                spinwheel(state,act_player);

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
            break;
            case 3:
                fail = 0;
                printf("Guess a phrase.\n");
                scanf("%s",guess);
                for(i=0;strlen(guess) == strlen(state->PHRASE) && i<strlen(state->PHRASE);i++)
                    if(state->PHRASE[i] != '_' && state->PHRASE[i] != guess[i])
                            fail = 1;
                if(fail == 0){
                    state->ROUND_ENDED = 1;
                    for(i=0;i<strlen(state->PHRASE);i++)
                        if(state->LETTER_GUESSED[state->PHRASE[i]-'a'] == 0)
                            counter++;
                    state->SCORES[act_player] += counter * 250;
                }
            break;
            default:
            break;
		}
	}
}

void reset( State *state, int i ){
    int j;
    state->NUM_ROUND = i;
    state->ROUND_ENDED = 0;
    for(i=0; i<26; i++) state->LETTER_GUESSED[i] = 0;
	for(i=0;i<3;i++) state->SCORES[i] = 0;

    int tmp = rand()%state->NUM_PHRASES;
	for(i=0;i<strlen(state->PHRASES[tmp]);i++) state->PHRASE[i] = state->PHRASES[tmp][i];
	state->PHRASE[strlen(state->PHRASES[tmp])] = 0;
}

int main(){
    int i;
    State state;
    init(&state);
	for(i = 1; i <= 3; i++){
        reset(&state, i);
        round(&state);
	}

return 0;
}
