#ifndef DISPLAY_H
#define DISPLAY_H

#include<stdio.h>
#include<string.h>
#include<time.h>
#include "state.h"

#include<windows.h>
#define CLEAR "cls"




/** START OF BANNER **/
/**
*   This part of code is responsible for the
*   display of banner at the beggining of the game.
**/
char A[10][1024] ={
            "                                                                                                      _       _  _                    _                ___       ___             _                                                                                                                             ",
            "                                                                                                     ( )  _  ( )( )                  (_ )            /'___)    /'___)           ( )_                                                                                                                           ",
            "                                                                                                     | | ( ) | || |__     __     __   | |       _   | (__     | (__   _    _ __ | ,_) _   _   ___     __                                                                                                       ",
            "                                                                                                     | | | | | ||  _ `\\ /'__`\\ /'__`\\ | |     /'_`\\ | ,__)    | ,__)/'_`\\ ( '__)| |  ( ) ( )/' _ `\\ /'__`\\                                                                                                     ",
            "                                                                                                     | (_/ \\_) || | | |(  ___/(  ___/ | |    ( (_) )| |       | |  ( (_) )| |   | |_ | (_) || ( ) |(  ___/                                                                                                     ",
            "                                                                                                     `\\___x___/'(_) (_)`\\____)`\\____)(___)   `\\___/'(_)       (_)  `\\___/'(_)   `\\__)`\\___/'(_) (_)`\\____)                                                                                                     "};

void writebanner(int START, int END,char A[][1024]){
    int j,i;

    for(j=0;j<6;j++){
        printf("\n  ");
        for(i=START;i<END;i++)
            printf("%c",A[j][i]);
    }
    printf("\n");

}
/** 0 & 75 are nice **/
void banner(int START, int END){	// <START;END> is an interval of visible columns in array

    int i;
    for(i = 0;i<220;i++){
        writebanner(START,END,A);
        START = (START+1)%strlen(A[0]);
        END = (END+1)%strlen(A[0]);

        Sleep(5);
        system(CLEAR);
    }
}
/** END OF BANNER **/


char B[10][1024]={
"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+",
"| | | | |B| | | | |1|E|1| | | | |B| | | | |2|L|2|",
"|1|1|2|2|A|2|2|1|1|0|X|0|1|1|2|2|A|2|2|1|1|0|O|0|",
"|0|5|0|5|N|5|0|5|0|0|T|0|0|5|0|5|N|5|0|5|0|0|S|0|",
"|0|0|0|0|C|0|0|0|0|0|R|0|0|0|0|0|C|0|0|0|0|0|E|0|",
"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"};

/**
*  This function animates the wheel.
**/
void writewheel(int POS){
int i,j;
    printf("\n");
    for(i=0;i<POS*2+1;i++)printf(" ");
    printf("|\n");

    for(i=0;i<POS*2+1;i++)printf(" ");
    printf("V\n");

    for(i=0;i<6;i++){
        printf("%s",B[i]);
        printf("\n");
    }
}

/**
*   Function responsible for correct display of guessed phrase
**/
void print_phrase(State *state){
	int i=0;
	printf("\n PHRASE: \n");
	while(state->PHRASE[i]){
        if(state->PHRASE[i] == '_') printf("-");
		else if( state->LETTER_GUESSED[state->PHRASE[i]-'a'] ) printf("%c",state->PHRASE[i]);
        else printf("_");
        i++;
	}
	printf("\n");
}

/**
*   Function displaying game state on screen
**/
void refresh(State *state ){

	system(CLEAR);
	printf("ROUND %d \n\n", state->NUM_ROUND);

	int i;
	for(i=0; i<state->NUM_PLAYERS; i++){
		if( i == state->CURRENT_PLAYER ) printf(" -->");
		else printf("    ");
		printf("%s: \t%d \n", state->NAMES[i], state->SCORES[i]);
	}
	printf("Chances left: %d\n", state->PLAYERCONTINUE );
	writewheel(state->POSITION);
    print_phrase(state);
}

/**
*   This function writes the final result.
**/
void write_result(State *state){
    system(CLEAR);
    int i,winner,result = 0;
    printf("Final score are:\n");
    for(i=0;i<state->NUM_PLAYERS;i++){
        printf("%s:\t%d\n",state->NAMES[i],state->TOTAL_SCORES[i]);
        if(state->TOTAL_SCORES[i] > result){
            winner = i;
            result = state->TOTAL_SCORES[i];
        }
    }
    printf("\nThe winner is %s with %d Euros\n", state->NAMES[winner], state->TOTAL_SCORES[winner]);
}

#endif
