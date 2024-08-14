#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>

// project finished
// beginner c project
// date: Oct 13, 2023

// 3 dot loading function
int three_dots(int times){

    for(int j = 0; j < times; j++){ // loop repeats "times"x

        for(int i = 0; i < 3; i++){ // loop controls each time a "." is printed and when it resets

            printf(".");    // prints "."
            fflush(stdout); // clears characters caught in the buffer
            usleep(200000); // delay

            if(i == 2){        // executes when the 3rd "." is printed (goal: reset "."s)
                printf("\b\b\b");  // delete the last 3 characters ...
                printf("   "); // replace all periods with spaces
                printf("\b\b\b");  // delete the last 3 characters again (necessary over /r for the finish function)
            }
        }
    }
    return 0;
}
int bar(){

    int bar_len = 60; // length of the bar

    for (int i = 0; i < bar_len; i++){ // loop through the length of the bar
        printf("."); //prints the '.'s

        if(i == bar_len-1){ // executes just before the loop ends (goal: print the empty bar)
            printf("]");    // prints the ending ]
            printf("\r");   // resets the carret to the beginning of the line

            for(int k = 0; k < bar_len; k++){  //executes just before the loop ends (goal: print the full bar )
                fflush(stdout); // empty buffer
                usleep(50000); // delay
                if(k == 0){     // if the carret is as the beginning of the line
                    printf("[");// print the beginning [
                }
                else{
                    printf("#");// else print the "filling" character: #
                }
            }

        }
        else if (i == 0){
            printf("\b["); // prints the opening [ (before the '.'s are cleared)
        }

    }

    return 0;
}

// second bar demo
int bar_two(){
    int bar_len = 60; // length of the bar

    for (int i = 0; i < bar_len; i++){ // loop through the length of the bar
        if(i == 1){        // at the start of the bar ...
            printf("\b["); // deleat the last character and print the opening [
        }
        else{
            printf("."); // anywhere else, print a '.'
        }
        if(i == bar_len-1){ // executes just before the end of the bar (goal: to make sure it ends correctly)
            printf("..]");  // print the ending ]

            for(int j = 0; j < 5; j++){     // loop determins how many times the bar loads (5 in this case)
                printf("\r");           // moves the carret to the beginning of the line

                for(int k = 0; k < bar_len; k++){  // executes for the length of the bar (goal: move the '###' forward)
                    printf("\b\b\b");   // removes the last 3 characters printed
                    fflush(stdout);     // clears input buffer
                    usleep(35000);      // delay

                    if(k == 0){             // smooth transition at the beginning, pretty much the same as the previous if statement
                        printf("\033[1D");  // moves the carret 2 spaces back
                        printf("[#..");     // prints the new '###'
                        printf("\033[1C");  // moves the carret 2 spaces forward (to give it the effect of the carret being ahead of the '###')
                    }
                    else if(k == 1){        // another smooth transition
                        printf("\033[3D");
                        printf("[##");
                        printf("\033[3C");
                    }
                    else if (k == bar_len-1){   // ending for the bar
                        printf("\033[2D");
                        printf("...]");
                        printf("\033[2C");
                    }
                    else{                   // default '###' sliding forward (except for for the first 2 indexes and just before the end)
                        printf("\033[2D");
                        printf(".###");
                        printf("\033[2C");
                    }

                }

            }

        }

    }

    return 0;
}

// spinning bar function
int spinning(){

    char loading_string[] = "|\\-/";

    for (int i = 0; i < 8; i++){ // amount of the times the bar should spin

        for (int j = 0; j < strlen(loading_string); j++){ // cycle through the loading segments
            char current_char = loading_string[j];        // char that get's the current loading segment from loading string
            printf("\r%s ",&current_char);      // moves the carret to the beginnning of the line and prints the current segment
            usleep(100000);     // delay
            fflush(stdout);     // clear output buffer
            printf("\r");       // moves the carret to the beginning of the line
        }
    }
    printf("\r");
    usleep(300000);
    printf(" ");
    return 0;
}

// main function
int main(){

    char input; // user input
    int finish = 0; // whether or not to finish the program

    //prompt:
    printf("Select one of the loading options:\n\tA) three dots\n\tB) bar\n\tC) bar 2\n\tE) spinning bar\n\tF) finish\n");

    while (finish == 0){  // selection loop

        printf("\t");       // starts the user input on an indent
        scanf("%c",&input); // gets user input
        getchar();

        // input options:
        switch(input){
            case 'a':
            case 'A': three_dots(10);
                      finish = 1;
                      break;
            case 'b':
            case 'B': bar();
                      finish = 1;
                      break;
            case 'c':
            case 'C': bar_two();
                      finish = 1;
                      break;
            case 'e':
            case 'E': spinning();
                      finish = 1;
                      break;
            case 'f':
            case 'F': printf("\nfinishing");  // finish option
                      three_dots(3);        // uses progress bar
                      printf("...\n");
                      finish = 1;
                      break;
            default: printf("That wasn't one of the options\n");
                      break;
        }
    }
    printf("\nend\n");
    return 0;
}
