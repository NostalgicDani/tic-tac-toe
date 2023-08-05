// tic tac toe
// date: aug 3, 4
// worked on first local play on a seperate file, then pc, then merged the two.

// libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// using
using std::cin;
using std::cout;

// global variables
char spot[10]={'b', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int win = -1;                                                     // integer to determine whether there is a win on board
int player = 1, choice;                                           // sets up player and player choice
int pc;                                                           // acts as index and naming the pc choice
char mark;                                                        // for the local game
bool victory;                                                     // to not to do win and defend
bool danger;                                                      // to not do defend and random
bool restart = true;                                              // works with restart function
bool isRandom;                                                    // whether easy or hard mode
bool isLocal;                                                     // whether local or pc mode
int pwins = 0;                                                    // player wins saved after rematches
int pcwins = 0;                                                   // pc wins saved after rematches
int p1wins = 0;                                                   // p1 wins saved after rematches
int p2wins = 0;                                                   // p2 wins saved after rematches
int draws = 0;                                                    // draws saved after rematches
int pcdraws = 0;
int playChoice;                                                   // user's choice for one or two player mode


//declare functions
void board();               // prints board
int checkwin();             // checks if there is a win, returns whether win, draw, or in progress
void change();              // checks the user's input and updates the array
void pc_defend();           // allows for the pc to defend against user || hard mode
void pc_win();              // allows for the pc to win if possible     || hard mode
void pc_rand();             // allows for the pc to randomly choose if there is no win/defend || play on easy
void restart_choice();      // asks whether user would like rematch and updates bool restart based on input
void player_choice();       // one player or two player

//                                            gameplay loop functions                                                                     //

// local game loop function
void local_game(){
    do {
    board();
        player = (player%2) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("\nPlayer %d, pick a number - ", player);
        cin >> choice;
        
        change();
        win = checkwin();
        player++;
    } while (win == -1);
    board();
    if(win == 1) {
        if (player == 1){
            p1wins += 1;
        } else {
            p2wins += 1;
        }
        board();
      cout<<"Player "<< --player<<" won \n";
    } else {
        draws += 1;
        board();
        cout<<"Game draw\n";
    }
}

// pc game loop function
void pc_game(){

    // easy or hard
        char ehchoice;
        do {
        // system("clear");
        printf("\nWould you like to play against easy or hard? (e/h) - "); // determine whether pc random or not
        cin >> ehchoice;
        if (ehchoice == 'e') {
            isRandom = true;
        } else if (ehchoice == 'h') {
            isRandom = false;
        }
        } while(ehchoice != 'e' && ehchoice != 'h');

 // gameplay loop
 do {
     // player
        mark = 'X';
        do {
            // end loop
            win = checkwin();
            if (win == 1 || win == 0)
                break;

            // user input
            board();
            printf("\n   Pick a number - ");
            cin >> choice;
            change();

            // update player
            player = 2;
        } while(player == 1);

     // computer play
        do {
            // end loop
            win = checkwin();
            if (win == 1 || win == 0)
                break;

            if (isRandom == false){  // hard mode
            pc_win();
            if (victory == false){
            pc_defend();
            }
            if (victory == false && danger == false){
                pc_rand();
            }

            } else if (isRandom == true){ // easy mode
                pc_rand();
            }
                
            cin.ignore();
                
            //update terminal 
            board();
            printf("\nPC played %d", pc);
            cin.ignore();

            // update player
            player = 1;
        } while (player == 2);

    // end loop when game is not in progress        
 } while (win == -1);
 board(); // update board to be final
    if (win == 1){
    // players are switched because the next player loop plays until win is determined, ergo break
        if (player == 1){ 
            pcwins += 1; 
            board();
            printf("\nThe pc beat you\n");
        } else if (player == 2) {
            pwins += 1;
            board();
            printf("\nYou beat the if-else statements (pc)!\n");
        }
    }
    if (win == 0) {
        pcdraws += 1;
        board();
        printf("Game draw\n");
    }
}

// ----------------------------------------------------------------------------

int main(){
    system("clear");
    printf("\n\nWelcome to Tic Tac Toe :)\n");
    printf("\nPress ENTER to continue");
        cin.ignore();
    player_choice();   

      std::srand(static_cast<unsigned>(std::time(nullptr))); // needed for random choice?

    //gameplay loop
    do {
        if (isLocal == true){
            local_game();
        }
        else if (isLocal == false){
            pc_game();             
        }
        restart_choice();    
    } while(restart == true);
    
    //end game
        system("clear");
        printf(" Final game results \n\n");
        // do both because the user may play pc and local matches
            printf(" Player 1 (X) - %d | Player 2 (O) - %d | Draws - %d\n\n", p1wins, p2wins, draws);
            printf(" Player (X) - %d | PC (O) - %d | Draws - %d\n\n", pwins, pcwins, pcdraws);
            cin.ignore();
    return 0;
}

// ----------------------------------------------------------------------------
/*                                 functions                                 */

// pc chooses at random, either on easy mode, or when no danger or victory
void  pc_rand(){
    std::vector<int> availableSpots;

    for (int i = 1; i <= 9; i++) {
        if (spot[i] >= '1' && spot[i] <= '9') {
            availableSpots.push_back(i);
        }
    }

    if (!availableSpots.empty()) {
        int randomIndex = std::rand() % availableSpots.size();
        pc = availableSpots[randomIndex];
        spot[pc] = 'O';
    }
}

// pc attempts to win
void pc_win(){
    // diagonal win - bottom missing
     if (spot[1] == 'O' && spot[5] == 'O' && spot[9] == '9') {
        victory = true;
        danger = true;
        spot[9] = 'O';
        pc = 9;
     }
     else if (spot[3] == 'O' && spot[5] == 'O' && spot[7] == '7') {
        victory = true;
        danger = true;
        spot[7] = 'O';
        pc = 7;
     }
    // diagonal win - top missing
     else if (spot[9] == 'O' && spot[5] == 'O' && spot[1] == '1') {
        victory = true;
        danger = true;
        spot[1] = 'O';
        pc = 1;
     }
     else if (spot[7] == 'O' && spot[5] == 'O' && spot[3] == '3') {
        victory = true;
        danger = true;
        spot[3] = 'O';
        pc = 3;
     }
    // horizontal win - left missing
     else if (spot[2] == 'O' && spot[3] == 'O' && spot[1] == '1'){
            victory = true;
            danger = true;
            spot[1] = 'O';
            pc = 1;
     }
     else if (spot[5] == 'O' && spot[6] == 'O' && spot[4] == '4'){
            victory = true;
            danger = true;
            spot[4] = 'O';
            pc = 4;
     }
     else if (spot[8] == 'O' && spot[9] == 'O' && spot[7] == '7'){
            victory = true;
            danger = true;
            spot[7] = 'O';
            pc = 7;
     }
    // horizontal win - middle missing
    else if (spot[1] == 'O' && spot[3] == 'O' && spot[2] == '2'){
            victory = true;
            danger = true;
            spot[2] = 'O';
            pc = 2;
     }
     else if (spot[4] == 'O' && spot[6] == 'O'  && spot[5] == '5'){
            victory = true;
            danger = true;
            spot[5] = 'O';
            pc = 5;
     }
     else if (spot[7] == 'O' && spot[9] == 'O' && spot[8] == '8'){
            victory = true;
            danger = true;
            spot[8] = 'O';
            pc = 8;
     }
     // horizontal win - right missing
    else if (spot[1] == 'O' && spot[2] == 'O' && spot[3] == '3'){
            victory = true;
            danger = true;
            spot[3] = 'O';
            pc = 3;
     }
     else if (spot[4] == 'O' && spot[5] == 'O' && spot[6] == '6'){
            victory = true;
            danger = true;
            spot[6] = 'O';
            pc = 6;
     }
     else if (spot[7] == 'O' && spot[8] == 'O' && spot[9] == '9'){
            victory = true;
            danger = true;
            spot[9] = 'O';
            pc = 9;
     }
    // vertical win - bottom missing
     else if (spot[1] == 'O' && spot[4] == 'O' && spot[7] == '7'){
            victory = true;
            danger = true;
            spot[7] = 'O';
            pc = 7;
     }
     else if (spot[2] == 'O' && spot[5] == 'O' && spot[8] == '8'){
            victory = true;
            danger = true;
            spot[8] = 'O';
            pc = 8;
     }
     else if (spot[3] == 'O' && spot[6] == 'O' && spot[9] == '9'){
            victory = true;
            danger = true;
            spot[9] = 'O';
            pc = 9;
     }
    // vertical win - top missing
     else if (spot[7] == 'O' && spot[4] == 'O' && spot[1] == '1'){
            victory = true;
            danger = true;
            spot[1] = 'O';
            pc = 1;
        }
     else if (spot[8] == 'O' && spot[5] == 'O' && spot[2] == '2'){
            victory = true;
            danger = true;
            spot[2] = 'O';
            pc = 2;
     }
     else if (spot[9] == 'O' && spot[6] == 'O' && spot[3] == '3'){
            victory = true;
            danger = true;
            spot[3] = 'O';
            pc = 3;
     }
    // vertical win - middle missing
     else if (spot[1] == 'O' && spot[7] == 'O' && spot[4] == '4'){
            victory = true;
            danger = true;
            spot[4] = 'O';
            pc = 4;
     }
     else if (spot[2] == 'O' && spot[8] == 'O' && spot[5] == '5'){
            victory = true;
            danger = true;
            spot[5] = 'O';
            pc = 5;
     }
     else if (spot[3] == 'O' && spot[9] == 'O' && spot[6] == '6'){
            victory = true;
            danger = true;
            spot[6] = 'O';
            pc = 6;
     } 
     else {
            victory = false;
            danger = false;
     }
}

// pc defend
void pc_defend(){
    // auto pick unless middle is taken
    if (spot[5] == '5') {
        danger = true;
        spot[5] = 'O';
        pc = 5;
    }
    // diagonal defense - bottom missing
     else if (spot[1] == 'X' && spot[5] == 'X' && spot[9] == '9') {
        danger = true;
        spot[9] = 'O';
        pc = 9;
     }
     else if (spot[3] == 'X' && spot[5] == 'X' && spot[7] == '7') {
        danger = true;
        spot[7] = 'O';
        pc = 7;
     }
    // diagonal defense - top missing
     else if (spot[9] == 'X' && spot[5] == 'X' && spot[1] == '1') {
        danger = true;
        spot[1] = 'O';
        pc = 1;
     }
     else if (spot[7] == 'X' && spot[5] == 'X' && spot[3] == '3') {
        danger = true;
        spot[3] = 'O';
        pc = 3;
     }
    // horizontal defense - left missing
     else if (spot[2] == 'X' && spot[3] == 'X' && spot[1] == '1'){
            danger = true;
            spot[1] = 'O';
            pc = 1;
     }
     else if (spot[5] == 'X' && spot[6] == 'X' && spot[4] == '4'){
            danger = true;
            spot[4] = 'O';
            pc = 4;
     }
     else if (spot[8] == 'X' && spot[9] == 'X' && spot[7] == '7'){
            danger = true;
            spot[7] = 'O';
            pc = 7;
     }
    // horizontal defense - middle missing
     else if (spot[1] == 'X' && spot[3] == 'X' && spot[2] == '2'){
            danger = true;
            spot[2] = 'O';
            pc = 2;
     }
     else if (spot[4] == 'X' && spot[6] == 'X'  && spot[5] == '5'){
            danger = true;
            spot[5] = 'O';
            pc = 5;
     }
     else if (spot[7] == 'X' && spot[9] == 'X' && spot[8] == '8'){
            danger = true;
            spot[8] = 'O';
            pc = 8;
     }
    // horizontal defense - right missing
     else if (spot[1] == 'X' && spot[2] == 'X' && spot[3] == '3'){
            danger = true;
            spot[3] = 'O';
            pc = 3;
     }
     else if (spot[4] == 'X' && spot[5] == 'X' && spot[6] == '6'){
            danger = true;
            spot[6] = 'O';
            pc = 6;
     }
     else if (spot[7] == 'X' && spot[8] == 'X' && spot[9] == '9'){
            danger = true;
            spot[9] = 'O';
            pc = 9;
     }
    // vertical defense - bottom missing
     else if (spot[1] == 'X' && spot[4] == 'X' && spot[7] == '7'){
            danger = true;
            spot[7] = 'O';
            pc = 7;
     }
     else if (spot[2] == 'X' && spot[5] == 'X' && spot[8] == '8'){
            danger = true;
            spot[8] = 'O';
            pc = 8;
     }
     else if (spot[3] == 'X' && spot[6] == 'X' && spot[9] == '9'){
            danger = true;
            spot[9] = 'O';
            pc = 9;
     }
    // vertical defense - top missing
     else if (spot[7] == 'X' && spot[4] == 'X' && spot[1] == '1'){
            danger = true;
            spot[1] = 'O';
            pc = 1;
        }
     else if (spot[8] == 'X' && spot[5] == 'X' && spot[2] == '2'){
            danger = true;
            spot[2] = 'O';
            pc = 2;
     }
     else if (spot[9] == 'X' && spot[6] == 'X' && spot[3] == '3'){
            danger = true;
            spot[3] = 'O';
            pc = 3;
     }
    // vertical defense - middle missing
     else if (spot[1] == 'X' && spot[7] == 'X' && spot[4] == '4'){
            danger = true;
            spot[4] = 'O';
            pc = 4;
     }
     else if (spot[2] == 'X' && spot[8] == 'X' && spot[5] == '5'){
            danger = true;
            spot[5] = 'O';
            pc = 5;
     }
     else if (spot[3] == 'X' && spot[9] == 'X' && spot[6] == '6'){
            danger = true;
            spot[6] = 'O';
            pc = 6;
     } 
     else {
            danger = false;
     }
}

// update board
void board(){
    system("clear");
    printf("\n               Tic Tac Toe\n\n");
    if (isLocal == true){
        printf(" Player 1 (X) - %d | Player 2 (O) - %d | Draws - %d\n\n", p1wins, p2wins, draws);
    } else if (isLocal == false){
    printf(" Player (X) - %d | PC (O) - %d | Draws - %d\n\n", pwins, pcwins, pcdraws);
    }
    printf("                 |     |       \n");
    printf("              %c  |  %c  |  %c  \n", spot[1], spot[2], spot[3]);
    printf("            _____|_____|_____\n");
    printf("                 |     |       \n");
    printf("              %c  |  %c  |  %c  \n", spot[4], spot[5], spot[6]);
    printf("            _____|_____|_____\n");
    printf("                 |     |       \n");
    printf("              %c  |  %c  |  %c  \n\n", spot[7], spot[8], spot[9]);
    
}

// update player choice
void change(){
      if (choice == 1 && spot[1] == '1')
            spot[1] = mark;
        else if (choice == 2 && spot[2] == '2')
            spot[2] = mark;
        else if (choice == 3 && spot[3] == '3')

            spot[3] = mark;
        else if (choice == 4 && spot[4] == '4')

            spot[4] = mark;
        else if (choice == 5 && spot[5] == '5')

            spot[5] = mark;
        else if (choice == 6 && spot[6] == '6')

            spot[6] = mark;
        else if (choice == 7 && spot[7] == '7')

            spot[7] = mark;
        else if (choice == 8 && spot[8] == '8')

            spot[8] = mark;
        else if (choice == 9 && spot[9] == '9')

            spot[9] = mark;
        else
        {
            cout<<"Invalid move ";

            player--;
            cin.ignore();
            cin.get();
}
}


// self-explanatory
int checkwin(){
    if (spot[1] == spot[2] && spot[2] == spot[3])
        return 1;
    else if (spot[4] == spot[5] && spot[5] == spot[6])
        return 1;
    else if (spot[7] == spot[8] && spot[8] == spot[9])
        return 1;
    else if (spot[1] == spot[4] && spot[4] == spot[7])
        return 1;
    else if (spot[2] == spot[5] && spot[5] == spot[8])
        return 1;
    else if (spot[3] == spot[6] && spot[6] == spot[9])
        return 1;
    else if (spot[1] == spot[5] && spot[5] == spot[9])
        return 1;
    else if (spot[3] == spot[5] && spot[5] == spot[7])
        return 1;
    else if (spot[1] != '1' && spot[2] != '2' && spot[3] != '3' 
          && spot[4] != '4' && spot[5] != '5' && spot[6] != '6' 
          && spot[7] != '7' && spot[8] != '8' && spot[9] != '9')
        return 0;
    else
        return -1;
}

// restart
void restart_choice(){
    char rchoice;
    printf("Would you like to play again? (y/n) - ");
    cin >> rchoice;
    cin.ignore();
    if (rchoice == 'y'){
        spot[0] = 'o'; // reset the board
        spot[1] = '1';
        spot[2] = '2';
        spot[3] = '3';
        spot[4] = '4';
        spot[5] = '5';
        spot[6] = '6';
        spot[7] = '7';
        spot[8] = '8';
        spot[9] = '9';
        player = 1;   // start from player one
        win = -1;     // allow the game to start again
        board();
        restart = true;  // continue the loop
        player_choice(); // ask whether to do one or two player
    } else {
        restart = false; // end the loop
    }
}

// one player or two player
void player_choice(){
    do {
    system("clear");
    printf("\nWould you like to play: \n\n");
    printf("1. Versus Local\n");
    printf("2. Versus PC\n");
    printf("\nPick a number - ");
    cin >> playChoice;
    if (playChoice == 1){
        isLocal = true;
    } else if (playChoice == 2){
        isLocal = false;
    }
    } while(playChoice != 1 && playChoice != 2);
}