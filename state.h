#ifndef STATE_H
#define STATE_H

/*
 *	Structure containing all information
 *	about current game.
 * */

typedef struct game_state{

    int POSITION;		// position of arrow above the wheel

    int NUM_PLAYERS;		// number of players
    char NAMES[3][50];		// names of players
    int SCORES[3];		// scores during one round
    int TOTAL_SCORES[3];	// sum of rounds scores

    int NUM_PHRASES;		// number of phrases ( constant = 3 )
    char PHRASES[50][1050];	// phrases guessed by players
    char PHRASE[50];		// phrases guessed in current round

    int NUM_ROUND;		// number of rounds
    int ROUND_ENDED;		// the variable that says if round had ended

    int VALUE[24];		// values of wheel fields

    int LETTER_GUESSED[27];	// letter, that was guessed in current round

    int PLAYERCONTINUE;     // counts how many times player can fail when guessing
    int CURRENT_PLAYER;     //current player
} State;

#endif
