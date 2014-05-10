#include "game.h"
/**
*   The main.
**/

int main(){
    int i;
    State state;

    banner(0,75);
    init(&state);

	for(i = 1; i <= 3; i++){
            prepare_next_round(&state);
            round(&state);
	}

	write_result(&state);

return 0;
}
