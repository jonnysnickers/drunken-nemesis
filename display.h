#ifndef DISPLAY_H
#define DISPLAY_H

#include<stdio.h>
#include<string.h>
#include<time.h>
#include "state.h"

#ifdef _WIN32
    #include<windows.h>
    #define CLEAR "cls"
#elif __linux__
    #define Sleep sleep
    #define CLEAR "clear"
    #include<unistd.h>
#endif



/** START OF BANNER **/
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
void banner(int START, int END){

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
"|0|0|0|0|B|0|0|0|0|1|E|1|0|0|0|0|B|0|0|0|0|2|L|2|",
"|1|1|2|2|A|2|2|1|1|0|X|0|1|1|2|2|A|2|2|1|1|0|O|0|",
"|0|5|0|5|N|5|0|5|0|0|T|0|0|5|0|5|N|5|0|5|0|0|S|0|",
"|0|0|0|0|C|0|0|0|0|0|R|0|0|0|0|0|C|0|0|0|0|0|E|0|",
"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"};

//Draws the wheel
void writewheel(int POS){
int i,j;
    printf("\n");
    for(i=0;i<POS*2+1;i++)
        printf(" ");
    printf("|\n");

    for(i=0;i<POS*2+1;i++)
        printf(" ");
    printf("V\n");

    for(i=0;i<6;i++){
        printf("%s",B[i]);
        printf("\n");
    }
}

//Function responsible for correct display of guessed phrase
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

//Function displaying game state on screen
void refresh(State *state,int act_player){

	system(CLEAR);
	printf("ROUND %d \n\n", state->NUM_ROUND);

	int i;
	for(i=0; i<state->NUM_PLAYERS; i++){
		if( i == act_player ) printf(" -->");
		else printf("    ");
		printf("%s: %d \n", state->NAMES[i], state->SCORES[i]);
	}
	writewheel(state->POSITION);
    print_phrase(state);
}

#endif
