//
//  main.c
//  Countdown
//
//  Created by Ray Conlin on 26/03/2016.
//  Copyright © 2016 Raymond Conlin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
// you will need <window.h> instead of <unistd> if you are on windows

//Functions

#define systm 1;// you can change this to a 1000 if you are on windows.

int letter_round(int players, int picker);

char letter_selection(char letter);

void timer();

int check_letter(char answer[], char selection[]);

int letter_there(char answer[], char selection[], int failstate);

int letters_available(char answer[], char selection[], int failstate);

int word_exsist(char answer[], int failstate);

void largest_word(char selection[]);

void round_tally(int players);

int player_creation();

//********************************************************************
//Global variables

int players_score[4];

char players_names[4][21];

char dictionary[100] = "/Users/Ray/Desktop/Computer Science Assignments/Programming/Personal Project/webster.txt";

//********************************************************************
// Testing variables

char test_selection[11] = "dermatepn";
char test_answer[11] = "raabits";


//********************************************************************
//Main

int main(int argc, const char * argv[]) {
    
//    letter_there(test_answer, test_selection, 0);
//    letters_available(test_answer, test_selection, 0);
//    word_exsist(test_answer);
//    largest_word(test_selection);
//    int player_creation();
    
    
    
//  Setup
    srand(time(NULL));
    
    for (int i = 0; i<4; i++) {
        players_names[i][0] = '\0';
        players_score[i] = 0;
    }
    
    
//  Introduction
    printf("Welcome to countdown.\n\n");
    printf("I am Raymond Conlin and I shall be your host today.\n\n");
    printf("Lets get to it then.\n");
    
    int players = player_creation();
    
//  Letters round instruction
    printf("So during the letters round you will be asked if you want a consonant or a vowel.\n");
    printf("Please input 'v' or 'c' respetively as your choice.\n");
    printf("If not I shall ferociously taunt you for your ineptitude.\n\n");
    
//********************************************************************
    
    int picker = 0;
    int continue_play = 1;
    while (continue_play == 1){
        
    continue_play = letter_round(players, picker%players);
        
    }
//  Victor
    
    int winner = 0;
    
    for (int i = 0; i<players; i++) {
        if (players_score[winner]< players_score[i]) {
            winner = i;
        }
    }
    
    printf("Well done %s, you are todays winner with a score of %d\n\n", players_names[winner], players_score[winner]);
    
    return 0;
}

//********************************************************************

//Defined functions

// Letter round format
int letter_round(int players, int picker){
    char choice;
    char selection[11];
    int i = 0;
    char answer[11];
    int continue_play = 0;
    
    while(i<9){
        selection[i] = '#';
        
        fflush(stdin);
        printf("So %s would you like a vowel or a consonant?", players_names[picker]);
        printf("\n");
        fflush(stdin);
        scanf("\n%c", &choice);
        fflush(stdin);
        
        
        selection[i] = letter_selection(choice);
        printf("\n");
        if (selection[i] != '#') {
            for (int j = 0; j<i+1; j++) {
                printf("%c", selection[j]);
                if (i!= j) {
                    printf("-");
                }
                else{
                    printf("   :%d remaining", 8-i);
                }
            }
            printf("\n\n");
            i++;
        }
        
        
    }
    
    //Letters have been selected the Game now begins
    printf("\n");
    printf("So your letters for this letters round are\n\n");
    for (int j = 0; j<9; j++) {
        printf("%c", selection[j]);
        if (8 != j) {
            printf("-");
        }
        selection[j] = tolower(selection[j]);
    }
    printf("\n\nYou now have 30 seconds to find the largest word given the letters above, good luck!\n");
    
    
    timer();
    
    for (int i = 0; i<players; i++) {
        printf("So %s what did you get", players_names[i]);
        printf("\n");
        fflush(stdin);
        scanf("%s", answer);
        players_score[i] += check_letter(answer, selection);
        
        
    }
    
    printf("Now that the round is over I reveal that one of the largest words available.\n\n");
    largest_word(selection);
    round_tally(players);
    
    printf("Would you like to contiue playing?\n1: Yes\n0: No\n");
    scanf("%d", &continue_play);
    printf("\n");
    
    return continue_play;
}

//********************************************************************

// Letter selector (Frequencies of occurance)
char letter_selection(char letter){
    
    char select;
    
    if (letter == 'v') {
        int num = rand()%67 ;
        
        if (num < 14) {
            select = 'A';
        }
        else if (num<35){
            select = 'E';
        }
        else if (num<48){
            select = 'I';
        }
        else if (num<61){
            select = 'O';
        }
        else{
            select = 'U';
        }
    }
    else if (letter == 'c'){
        int num = rand()%74;
        
        if (num<1) {
            select = 'B';
        }
        else if (num<4){
            select = 'C';
        }
        else if (num<10){
            select = 'D';
        }
        else if (num<12){
            select = 'F';
        }
        else if (num<15){
            select = 'G';
        }
        else if (num<17){
            select = 'H';
        }
        else if (num<18){
            select = 'J';
        }
        else if (num<19){
            select = 'K';
        }
        else if (num<24){
            select = 'L';
        }
        else if (num<28){
            select = 'M';
        }
        else if (num<36){
            select = 'N';
        }
        else if (num<40){
            select = 'P';
        }
        else if (num<41){
            select = 'Q';
        }
        else if (num<50){
            select = 'R';
        }
        else if (num<59){
            select = 'S';
        }
        else if (num<68){
            select = 'T';
        }
        else if (num<69){
            select = 'V';
        }
        else if (num<70){
            select = 'W';
        }
        else if (num<71){
            select = 'X';
        }
        else if (num<72){
            select = 'Y';
        }
        else{
            select = 'Z';
        }
        
        
    }
    else{
        printf("What did I tell you????\n");
        printf("You have left me no choice.\n");
        printf("You couldn't get water out of a boot if the instructions were on the heel.\n");
        printf("Now that I have taunted you we can progress.\n");
        select = '#';
    }
    return select;
}

//********************************************************************

//The famous clock (You will need to multiply everything by

void timer(){
    int temp = systm;
    sleep(20*temp);
    
    
    for(int i =10;i>0;i--){
        if (i == 7) {
            printf("The music starts. (you know what im talking about)\n");
        }
        printf("%d\n", i);
        sleep(1*temp);
    }
    printf("Times up, put your pens down and lets see what ye got\n");
}

//********************************************************************

int check_letter(char answer[], char selection[]){
    int score = 0;
    int failstate = 0;
    
    failstate = letter_there(answer, selection, failstate);
    
    failstate = letters_available(answer, selection, failstate);
    
    if (failstate == 0){
    failstate = word_exsist(answer, failstate);
    }
    
    switch (failstate) {
        case 11:
            printf("You have used a letter which was not available to you unfortunatly.\nBetter luck next time.\n\n");
            break;
            
        case 12:
            printf("You have used a letter more times than available.\nSorry but better luck next time.\n\n");
            break;
            
        case 13:
            printf("I'm afraid that word does not exsist acording to the webster dictionary.\n\n");
            break;
            
        default:
            score = failstate;
            if (failstate == 9) {
                score = 18;
            }
            printf("Well done you have earned %lu points\n\n", strlen(answer));
            break;
            
    }
    
    return score;
}

//********************************************************************

int letter_there(char answer[], char selection[], int failstate){
    char temp[2];
    temp[1] = '\0';
    
    for (int i = 0; i<strlen(answer); i++) {
        temp[0] = answer[i];
        if (strstr(selection, temp) == NULL){
            failstate = 11;
            
        }
    }
    
    return failstate;
}

//********************************************************************

int letters_available(char answer[], char selection[], int failstate){
    int i = 0;
    char letters[10];
    int k = 0;
    int j = 0;
    int availability[9];
    
    answer[strlen(answer)+1] = '\0';
    selection[9] = '\0';
    
    
    for (i=0; i<10; i++) {
        letters[i] = '\0';
        if(i<9){
        availability[i] = 0;
        }
    }
    
    // Gets list of unique letters in the selection
    for (i = 0; i<9; i++) {
        int found = 0;
        for(j = k; j >= 0; j--){
            
            if(selection[i] == letters[j]){
                found = 1;
            }
        }
        if (found == 0){
            letters[k] = selection[i];
            k++;
        }
    }
    
    //Tallys up all the times they appear
    for (i = 0; i<9; i++) {
        for(j=0;j<9;j++){
            if(letters[i] == selection[j]){
                availability[i]++;
            }
        }
    }
    
    // Checks how many times the letters are used in the answer
    for (i = 0; i<strlen(letters); i++) {
        for (j=0; j<k; j++) {
            if(answer[i] == letters[j] && letters[j] != '\0'){
                availability[j]--;
            }
        }
    }
    
    //If a availability[i] is below 0 it means that the user made a word using a letter more times than was available
    for (i=0; i<k; i++) {
        if(availability[i] < 0){
            failstate = 12;
        }
    }
    
    if (strlen(answer)>9) {
        failstate = 12;
    }
    
    return failstate;
}

//********************************************************************

int word_exsist(char answer[], int failstate){
    FILE *dict;
    char buffer[30];
    int success = 0;
    
    dict = fopen(dictionary, "r");
    
    while (!feof(dict)) {
        fscanf(dict, "%s", buffer);
        if (strcmp(buffer, answer)==0) {
            success = 1;
        }
    }
    
    if (success == 0) {
        failstate = 13;
    }
    else{
        failstate = strlen(answer);
    }
    
    
    return failstate;
}

//********************************************************************

void largest_word(char selection[]){
    FILE *dict;
    char buffer[30];
    char max[11];
    int i = 0;
    for (i = 0; i<11; i++) {
        max[i] = '\0';
    }
    
    dict = fopen(dictionary, "r");
    
    while (!feof(dict)) {
        fscanf(dict, "%s", buffer);
        if (letters_available(buffer, selection, 0) == 0 && letter_there(buffer, selection, 0) == 0) {
            if(strlen(buffer)> strlen(max)){
                strcpy(max, buffer);
            }
        }
    }
    
    printf("%s was in fact one the largest word available.\n", max);
}

//********************************************************************

void round_tally(int players){
    printf("\n\nSo at the end of that round the scores stand at:\n");
    
    for (int i=0; i<players; i++) {
        printf("%s: %d\n", players_names[i], players_score[i]);
        printf("Time for the next round\n\n");
    }
}

//********************************************************************

int player_creation(){
    int players = 0;
    int players_check = 0;
    int i = 0;
    
    printf("How many players will be playing today?\n");
    printf("(1-4 players)\n");
    
    players_check = 0;
    
    while (players_check == 0) {
        
        scanf("%d", &players);
        
        if (players < 1) {
            printf("\nI am fairly certain you need at least 1 player to play a game.\nPlease enter another number\n");
        }
        else if (players > 4){
            printf("\nLets be honest, you dont have that many friends.\nPlease enter another number\n");
        }
        else{
            printf("Very well then there will be %d players.\n\n", players);
            players_check = 1;
        }
    }
    
    printf("Please enter your names\n");
    printf("Must be under 20 character, if not we will just call you Slagathor.\n\n");
    for (i = 0; i < players; i++) {
        printf("Player %d : ", i+1);
        fflush(stdin);
        scanf("%s", players_names[i]);
        printf("\n");
        if (i<4) {
            players_names[i+1][0] = '\0';
        }
        
        if (strlen(players_names[i])>19) {
            strcpy(players_names[i], "Slagathor");
        }
    }
    
    return players;
}







