// including necessary libraries

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std; // this one line of code will make our lives way easier

// initializing global variables and moltto necessario structs

int difficultyLevel;
int height;
int width;
int moveX;
int moveY;
int input;
int bombs;

int number_of_games;

bool restart;

char** board;
bool** mines;

const char HIDDEN = '-';
const char EMPTY = ' ';
const char FLAG = 'F';
const char MINE = '*';

// colors :)
const string green("\033[1;32m");
const string boarder_color("\u001b[38;5;105m");
const string reset("\033[0m");

struct thePlayer
{ // a struct for defining player's information
    char name[100];
    int moves;
    double points;
    time_t gameTime;
    bool won;
};

// using prototype of our functions

int MENU();

void GREATINGS(char*, int);

void STORY();

void RULES();

void PLAYING_GAME(char**, bool**, thePlayer&);

void PRINT_BOARD(char **);

void REVEAL(char **, bool **, int, int);

int COUNT_BOMBS(bool **, int, int);

void INITIALIZE_MAP(char **, bool **, int, int);

bool GAMEOVER(bool**, int, int);

bool WIN();

int LOAD_LEADERBOARD(thePlayer *);

void SAVE_LEADERBOARD(thePlayer *, int);

void SORT_LEADERBOARD(thePlayer *, int);

void PRINT_LEADERBOARD(thePlayer *, int);

// main

int main()
{
    number_of_games = 0;
    SetConsoleOutputCP(CP_UTF8); // nice!

    srand(static_cast<unsigned>(time(0)));
    menu :
    int option;
    option = MENU();

    char playerName[100];
    restart :
    if (restart)
    {
        option = 1;
        restart = false;
    }

    if (option == 1) // new game
    {
        number_of_games++;
        STORY();
        getch();
        RULES();
        getch();
        GREATINGS(playerName, option);
        thePlayer currentPlayer;
        strcpy(currentPlayer.name, playerName);
        currentPlayer.points = 0;
        currentPlayer.moves = 0;
        currentPlayer.won = false;

        time_t startTime = time(nullptr);
        while (true) 
        {
            PLAYING_GAME(board, mines, currentPlayer);
            if (GAMEOVER(mines, moveX, moveY))
            {
                system("cls");
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        if (mines[i][j]) {
                            board[i][j] = MINE;
                        }
                    }
                }
                PRINT_BOARD(board);
                cout << "\n YOU LOST! ";
                cout << "\n PRESSE ANY BITTON TO TERMINATE ";
                currentPlayer.won = false;
                currentPlayer.points = 0;
                currentPlayer.gameTime = time(nullptr) - startTime;
                SAVE_LEADERBOARD(&currentPlayer, 1);
                getch();
                return 0;
            } 
            if (input == 'q' || input == 'Q') 
            {
                system("cls");
                cout << " THANKS FOR PLAYING THE GAME \n\n PRESS ANY BUTTON TO TERMINATE ";
                getch();
                return 0;
            }
            if (input == 'r' || input == 'R')
            {
                restart = true;
                goto restart;
            } 
            if (WIN())
            {
                cout << "\n YOU WON!";
                cout << "\n PRESSE ANY BITTON TO TERMINATE ";
                currentPlayer.won = true;
                currentPlayer.points = bombs;
                currentPlayer.gameTime = time(nullptr) - startTime;
                SAVE_LEADERBOARD(&currentPlayer, 1);
                getch();
            }
        }
        
    } 
    else if (option == 2) // leaderboard
    {
        thePlayer leaderboard[100];
        int count = LOAD_LEADERBOARD(leaderboard);
        SORT_LEADERBOARD(leaderboard, count);
        PRINT_LEADERBOARD(leaderboard, count);
        getch();
        goto menu;
    }
    else // exit (we handled the non between 1-3 numbers)
    {
        if (number_of_games == 0) 
        {
            return 0;
        }
        else 
        {
            system("cls");
            cout << " THANKS FOR PLAYING THE GAME \n\n PRESS ANY BUTTON TO TERMINATE ";
            getch();
        }
        
    }

    return 0;
}

// this function will show the menu of the game and you can choose what you want to do with this function
int MENU()
{
    // PlaySound(TEXT("data/Gravity.wav"), NULL, SND_FILENAME | SND_ASYNC);
    system("cls");

    // █ ░ ╗ ╚ ═ ╔ ╝ ║

    cout << " THIS IS SUPPOSED TO BE THE MENU OF THE GAME :( \n\n";
    cout << "███░░██░█░░░████░  █████░░░███████████░███░░\n█░░██░░███░███░░█  █░░░█░░░██░░░█░░░█░░██░░█\n█████░░██░█░████░  █████░█░█████████░░█░████\n█░░██░░██░░░██░░█  ░░░███░███░░░█░░░█░░░█░░█\n███░░██░█░░░████░  ███░█░░░██████████░░░█░░█\n"; 

    cout << boarder_color << "╔════════════════╗\n";
    cout << boarder_color << "║" << reset << " 1. NEW GAME    " << boarder_color << "║\n";
    cout << boarder_color << "╚════════════════╝\n";
    cout << boarder_color << "╔════════════════╗\n";
    cout << boarder_color << "║" << reset << " 2. LEADERBOARD " << boarder_color << "║\n";
    cout << boarder_color << "╚════════════════╝\n";
    cout << boarder_color << "╔════════════════╗\n";
    cout << boarder_color << "║"  << reset <<" 3. EXIT        " << boarder_color << "║\n";
    cout << boarder_color << "╚════════════════╝\n" << reset;
    cout << "WHAT IS YOUR OPTION : ";
    int option;
    cin >> option;
    
    while (option < 1 || option > 3)
    {
        cout << " PLEASE ENTER A NUMBER BETWEEN 1-3 ";
        cin >> option;
    }

    return option;
}

// this function will tell the story of the game
void STORY()
{
    system("cls");
    cout << "IN THE CLOSE FUTURE WHEN AFTER ALL THE NOT THAT NATURAL DISASTERS WHEN ALMOST ALL THE EARTH WAS  NOT  THAT  LIVABLE \n";
    cout << "THERE WAS A VERY GOOD AND WISE MAYOR WHO BUILT A CITY AND LET ALL THE HUMANS FROM ALL AROUND  THE  WORLD ENTER  HIS \n";
    cout << "CITY. \"GOOD AND VERY WISE\" I SADI, HMM,  ABOUT THAT LET ME TELL YOU THE SOMETHING DON'T TRUST  EVERYONE SO   EASILY \n";
    cout << "THE MAYOR WAS PRAYED LIKE A GOD, SO HE WENT ROGUE AND HE PUNISHED EVERYONE HE DIDN'T LIKE  AND  THE  PEOPLE  WASN'T \n";
    cout << "THAT POWERFUL TO STAND AGAINST HIM. BUT HE WAS TIRED OF BEING POWERFUL, SO HE SETUPED A GAME,  A  CHALLENG  AND  IF \n";
    cout << "ENYONE COULD BEAT THAT GAME HE WOULD GAVE THAT PERSON THE CONTROL OF MANAGING THE CITY. BUT ENYONE WHO  EVER  TIRED \n";
    cout << "TO BEAT THE GAME WAS DRIVEN CRAZY AND LOST HIS MIND. IT WASN'T ANY EASY GAME, IT WAS THE GAME OF   \"LIFE AND DEATH\" \n";
    cout << "BUT THERE WAS ONE PERSON WHO WAS... KIND OF DIFFERENT. HE STEPED UP TO THE PALACE OF THE MAYOR  AND  BEGAN THE GAME \n";
    cout << "IN HOPE OF FREEING THE PEOPLE... \n\n";
    cout << "inspired by the serie Secret Level S1.E14,\"Honor of Kings : The Way of All Things\"";
}

// this function will print the rules of the game
void RULES()
{   
    system("cls");
    cout << boarder_color << "╔" << reset;
    for (int i = 0; i < 101; i++) {
        cout << boarder_color << "═" << reset;
    }
    cout << boarder_color << "╗\n" << reset;
    cout << boarder_color << "║" << reset << "YOYO! THIS IS THE RULES OF THE GAME :                                                                " << boarder_color << "║" << reset << "\n" << boarder_color << "║" << reset << "1. THE FIRST MOVE WILL BE SAFE                                                                       " << boarder_color << "║" << reset << "\n" << boarder_color << "║" << reset << "2. IF YOU HIT THE FIRST BOMB YOU BOOM!                                                               " << boarder_color << "║" << reset << "\n" << boarder_color << "║" << reset << "3. IF YOU WANT TO WIN THE GAME YOU HAVE TO OPEN EVERY NON-BOMB CELL                                  " << boarder_color << "║" << reset << "\n" << boarder_color << "║" << reset << "4. IF YOU FLAG A CELL YOU CAN'T IMMEDIATELY OPEN IT, YOU HAVE TO FIRST UNFLAG IT THEN YOU CAN OPEN IT" << boarder_color << "║" <<reset << "\n";
    cout << boarder_color << "╚" << reset;
    for (int i = 0; i < 101; i++) {
        cout << boarder_color << "═" << reset;
    }
    cout << boarder_color << "╝\n" << reset;
}

// thiss function will take player's name and difficulty and dimensions and first move that player want
void GREATINGS(char *playerName, int option)
{
    system("cls");

    cout << " PLEASE ENTER YOUR NAME : ";
    cin >> playerName;

    system("cls");

    cout << " PLEASE CHOOSE THE DIFFICULTY OF YOUR GAME : \n\n";
    cout << boarder_color << "╔════════════╗\n";
    cout << boarder_color << "║" << reset << " 1. EASY    " << boarder_color << "║\n";
    cout << boarder_color << "╚════════════╝\n";
    cout << boarder_color << "╔════════════╗\n";
    cout << boarder_color << "║" << reset << " 2. NORMAL  " << boarder_color << "║\n";
    cout << boarder_color << "╚════════════╝\n";
    cout << boarder_color << "╔════════════╗\n";
    cout << boarder_color << "║"  << reset <<" 3. HARD    " << boarder_color << "║\n";
    cout << boarder_color << "╚════════════╝\n" << reset;
    cout << "WHAT IS YOUR CHOICE : ";
    cin >> difficultyLevel;

    while (difficultyLevel < 1 || difficultyLevel > 3)
    {
        cout << "WRONG DIFFICULTY LEVEL CHOSEN PLEASE ENTER NUMBER BETWEEN 1-3";
        cin >> difficultyLevel;
    }

    system("cls");

    cout << " PLEASE ENTER HEIGHT AND WIDTH OF YOUR GAME : ";
    cin >> height >> width;

    while ((option  == 1 && height * width < 6) || (option == 2 && height * width < 4) || (option == 3 && height * width < 2)) {
        system("cls");
        cout << " PLEASE ENTER GREATER NUMBERS : ";
        cin >> height >> width;
    }

    system("cls");

    board = new char *[height];
    mines = new bool *[height];
    for (int i = 0; i < height; i++)
    {
        board[i] = new char[width];
        mines[i] = new bool[width];
    }
    int firstX, firstY;

    cout << " PLEASE ENTER THE COORDINATES OF YOUR FIRST MOVE : ";
    cin >> firstX >> firstY;

    while (firstX < 0 || firstX >= height || firstY < 0 || firstY >= width)
    {
        system("cls");
        cout << " WRONG COORDINATES! PLEASE TRY AGAIN : ";
        cin >> firstX >> firstY;
    }

    moveX = firstX;
    moveY = firstY;

    INITIALIZE_MAP(board, mines, firstX, firstY);
}

// this function will generate the first map of the game (placing bombs, hidding cells, counting the number of bombs around each cell)
void INITIALIZE_MAP(char **board, bool **mines, int firstX, int firstY)
{
    if (difficultyLevel == 1) {
        bombs = height * width / 6;
    } else if (difficultyLevel == 2) {
        bombs = height * width / 4;
    } else if (difficultyLevel == 3) {
        bombs = height * width / 2;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = HIDDEN;
            mines[i][j] = false;
        }
    }

    srand(static_cast<unsigned int>(time(0))); // seed for random number generating
    int placedBooms = 0;
    while (placedBooms < bombs)
    {
        int x = rand() % height;
        int y = rand() % width;

        if (abs(x - firstX) <= 1 && abs(y - firstY) <= 1) // not placing any bomb around the first chosen cell
            continue;

        if (!mines[x][y]) 
        {
            mines[x][y] = true;
            placedBooms++;
        }
    }
    
    REVEAL(board, mines, moveX, moveY);
    PRINT_BOARD(board);
}

// the most importanto function for runing the game
void PLAYING_GAME(char **board, bool **mines, thePlayer &currentPlayer)
{
    system("cls");
    PRINT_BOARD(board);

    input = getch();
    if (input == 224)
    {
        input = getch();
        if (input == 77 && moveY < width - 1) moveY++; // Right
        else if (input == 80 && moveX < height - 1) moveX++; // Down
        else if (input == 75 && moveY > 0) moveY--; // Left
        else if (input == 72 && moveX > 0) moveX--; // Up
    }

    if (input == 'o' || input == 'O') 
    {
        REVEAL(board, mines, moveX, moveY);
        currentPlayer.moves++;
    } 
    else if (input == 'f' || input == 'F')
    {
        if (board[moveX][moveY] == FLAG)
        {
            board[moveX][moveY] = HIDDEN;
        }
        else if (board[moveX][moveY] != FLAG)
        {
            board[moveX][moveY] = FLAG;
        }
    }
    
    // WIN(mines, moveX, moveY);
}

// this function will print the game's board every time a move played by the user
void PRINT_BOARD(char **board)
{
    cout << " WELCOME TO BOMBSWEEPER! \n\n";
    cout << boarder_color << "╔" << reset;
    for (int i = 0; i < 3 * width; i++) {
        cout << boarder_color << "═" << reset;
    }
    cout << boarder_color << "╗\n" << reset;
    for (int i = 0; i < height; i++) {
        cout << boarder_color << "║" << reset;
        for (int j = 0; j < width; j++) {
            // Highlight the last chosen cell   
                if (i == moveX && j == moveY) 
                {
                    cout << " " << green << board[i][j] << reset << " "; // green   background
                }
                else 
                {
                    cout << " " << board[i][j] << " ";
                }
            }
    
        cout << boarder_color << "║" << reset;
        cout << endl;
    }
    cout << boarder_color << "╚" << reset;
    for (int i = 0; i < 3 * width; i++) {
        cout << boarder_color << "═" << reset;
    }
    cout << boarder_color << "╝\n" << reset;
    cout << " PRESS O FOR OPENING THE CELL \n PRESS F FOR FLAGING THE CELL \n";
    cout << " PRESS Q FOR EXITING GAME \n PRESS R FOR RESTRATING THE GAME ";
}

// this function counts how many bombs are around a specific cell
int COUNT_BOMBS(bool **mines, int x, int y)
{
    int count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue; // Skip the cell itself
            int newX = x + i;
            int newY = y + j;
            // Check that it's not out of bounds
            if (newX >= 0 && newX < height && newY >= 0 && newY < width) {
                if (mines[newX][newY]) {
                    count++;
                }
            }
        }
    }
    return count;
}

// this recursive function will reveal all the cells around a the cell we want 
// and if the cell is 0 it will reveal all the cells around it until there is no 0 cell around the last revealed cell
void REVEAL(char **board, bool **mines, int x, int y)
{
    if (x < 0 || x >= height || y < 0 || y >= width || board[x][y] != HIDDEN)
        return;

    int numBombs = COUNT_BOMBS(mines, x, y);
    board[x][y] = '0' + numBombs; // Display the number of bombs around the cell

    if (numBombs == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    REVEAL(board, mines, x + i, y + j);
                }
            }
        }
    }
}

// this function will tell if the game is won or no
bool WIN()
{
    // Check if the game is solved (all non-mine cells are revealed)
    bool allRevealed = true;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!mines[i][j] && board[i][j] == HIDDEN) {
                allRevealed = false;
                break;
            }
        }
    }
    
    if (allRevealed) {
        return true;
    }
    return false;
}

// this is function to tell if the game is lost or no
bool GAMEOVER(bool **mines, int x, int y)
{
    if (board[x][y] != HIDDEN && board[x][y] != FLAG) {
        return mines[x][y];
    }
    return false;
}

// this function will tell you how many players we have in our leaderboard
int LOAD_LEADERBOARD(thePlayer *leaderboard)
{
    ifstream file("leaderboard.txt");
    int count = 0;
    while (file >> leaderboard[count].name >> leaderboard[count].points >> leaderboard[count].gameTime >> leaderboard[count].moves >> leaderboard[count].won)
    {
        count++;
    }
    file.close();
    return count;
}

// this function will save the information of our player
void SAVE_LEADERBOARD(thePlayer *leaderboard, int count)
{
    ofstream file("leaderboard.txt", ios::app);
    for (int i = 0; i < 1 ; i++) {
        file << leaderboard[i].name << " " << leaderboard[i].points << " " << leaderboard[i].gameTime << " " << leaderboard[i].moves << " " << leaderboard[i].won << endl;
    }
    file.close();
}

// this function will sort the information of our players
void SORT_LEADERBOARD(thePlayer *leaderboard, int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (leaderboard[j].points < leaderboard[j + 1].points) {
                swap(leaderboard[j].points, leaderboard[j + 1].points);// swap is a function to change the position of the two thnigs
            }
            if (leaderboard[j].points == leaderboard[j + 1]. points) {
                if (leaderboard[j].gameTime < leaderboard[j + 1].gameTime) {
                    swap(leaderboard[j].points, leaderboard[j + 1].points);
                }
            }
        }
    }
}

// this function will print the information of our players
void PRINT_LEADERBOARD(thePlayer *leaderboard, int count)
{
    system("cls");
    cout << "NAME --> POINTS GAMETIME(s) MOVES WON/LOST\n";
    if (count == 0)
    {
        cout << "No games played yet. Leaderboard is empty.\n";
    }
    else 
    {
        for (int i = 0; i < count; i++) {
            cout << leaderboard[i].name << " -->   " << leaderboard[i].points << "      " << leaderboard[i].gameTime << "      " << leaderboard[i].moves << "        ";
            if (leaderboard[i].won == true) {
                cout << "WIN" << endl;
            } else {
                cout << "LOST" << endl;
            }
        }
    }
}