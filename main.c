#include "game.h"

/*
void spinwheel(){
    int tmp = rand()%50 + 5;
    int i;
    for(i = 0;i<tmp;i++){
        POSITION = (POSITION+1)%24;
        system("cls");
        refresh();
        Sleep(40);
    }
}
*/

/*
//Each call of this function simulates one round of game
void next_round(int num){
	ROUND_ENDED = 0;
	while(!ROUND_ENDED){
		refresh(num, rand()%NUM_PLAYERS);

	}
}
*/
int main(){
    int i;
    State state;
	init(&state);
	printf("%d %d %d\n%s\n",state.NUM_PHRASES,state.NUM_PLAYERS,state.NUM_ROUND,state.PHRASE);
	//refresh(state,1);

return 0;
}
