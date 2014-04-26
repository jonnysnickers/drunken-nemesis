#ifndef state.h
#define state.h

typedef struct game_state{

    int POSITION;

    int NUM_PLAYERS;
    char NAMES[3][50];
    int SCORES[3];
    int TOTAL_SCORES[3];

    int NUM_PHRASES;
    char PHRASES[50][50];
    char PHRASE[50];

    int NUM_ROUND;
    int ROUND_ENDED;

    int VALUE[24];

    int LETTER_GUESSED[27];
}State

#endif