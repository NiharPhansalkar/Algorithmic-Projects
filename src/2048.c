/*
Program -: 2048 game
Made by -: Nihar Phansalkar
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>    // Used for seeding rand().
#include <ncurses.h> // Provides functions for UI.

int print_board(void);
int make_random(void); // Gives 2 or 4 pseudo-randomly.
int two_or_four(void); // Defined to give 2 and 4 in the ratio 9:1
int player_choice(void);
int check_win(void);
int check_loss(void);
void print_rules(void);
void fill_arr(void);
void slideArr(int);
void put_tiles(void); // Defined to reduce redundancy.
void intepreter(int);

#define UPPER_LIM 16 // Max limit for random numbers to be in.
#define GRID_DIMENSION 4
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int board[GRID_DIMENSION][GRID_DIMENSION];
int interpret_row = -1, interpret_col = -1, which_num;

int main(void)
{
    initscr();            // Start curses mode.
    raw();                // Disable line buffer of stdin.
    keypad(stdscr, TRUE); // Get special keys
    noecho();

    int one_time, check_choice;
    srand(time(0)); // Seed rand() to produce a random batch of numbers.
    put_tiles();
    while (check_win() != 1 && check_loss() != 1)
    {
        if (one_time == 0)
        {
            put_tiles();
            print_board();
            printw("\n");
            refresh();
            one_time++;
        }
        print_rules();
        check_choice = player_choice();
        if(check_choice == -1)
        {
            while(check_choice == -1)
                check_choice = player_choice();
        }
        slideArr(check_choice);
        put_tiles();
        print_board();
        refresh();
    }
    if(check_win() == 1)
    {
        printw("\n\nCongratulations! You have won the game!\n");
        refresh();
    }
    if(check_loss() == 1)
    {
        printw("\n\n You have lost. Please restart.\n");
    }
    getch();
    endwin(); // End curses mode.
    return 0;
}

void print_rules(void)
{
    printw("\nWELCOME TO THE GAME OF 2048!\n");
    printw("Please use the arrow keys to play the game.\n\n");
    printw("Arrow up -> Shifts the digits upwards.\n");
    printw("Arrow down -> Shifts the digits downwards.\n");
    printw("Arrow left -> Shifts the digits towards left.\n");
    printw("Arrow right -> Shifts the digits towards right.\n\n");
    printw("Get sum of all the numbers to 2048 and you win!\n");
    printw("\nGOOD LUCK!\n\n");
    refresh();
}

void put_tiles(void)
{
    which_num = two_or_four();
    intepreter(make_random());
    fill_arr();
}

void fill_arr(void)
{
    int row, col, flag = 0;
    for (row = 0; row < GRID_DIMENSION; row++)
    {
        for (col = 0; col < GRID_DIMENSION; col++)
        {
            if (row == interpret_row - 1 && col == interpret_col - 1)
            {
                if (board[row][col] == 0)
                {
                    flag = 1;
                    board[row][col] = which_num;
                    break;
                }
                else
                {
                    flag = 1;
                    put_tiles();
                    break;
                }
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
}

int two_or_four(void) // Returns two or four in the ratio 9:1.
{
    if (rand() % 10 > 0)
    {
        return 2;
    }
    else
    {
        return 4;
    }
}

int make_random(void) // Generate a random number between 1 and 16 for two and four pop-ups.
{
    int make_num = (rand() % 16) + 1;
    return make_num;
}

void intepreter(int block_num) // Find out row and column where random 2 or 4 should appear.
{
    if (block_num % GRID_DIMENSION == 0)
    {
        interpret_col = 4;
        interpret_row = block_num / GRID_DIMENSION;
    }
    else
    {
        interpret_col = block_num % GRID_DIMENSION;
        interpret_row = (block_num / GRID_DIMENSION) + 1;
    }
}

int player_choice(void)
{
    switch (getch())
    {
    case KEY_LEFT:
        clear();
        refresh();
        return LEFT;

    case KEY_RIGHT:
        clear();
        refresh();
        return RIGHT;

    case KEY_UP:
        clear();
        refresh();
        return UP;

    case KEY_DOWN:
        clear();
        refresh();
        return DOWN;

    default: 
        clear();
        printw("Please press the arrow keys only.\n");
        refresh();
        print_board();
        refresh();
        return -1;
    }
}

int check_win(void)
{
    int row, col;
    for (row = 0; row < GRID_DIMENSION; row++)
    {
        for (col = 0; col < GRID_DIMENSION; col++)
        {
            if (board[row][col] == 2048)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return -1;
}

int check_loss(void)
{
    int row, col, flag = 0;

    for (row = 0; row < GRID_DIMENSION; row++)
    {
        for (col = 0; col < GRID_DIMENSION; col++)
        {
            if(board[row][col] != 0)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
                break;
            }
        }
        if(flag == 0)
        {
            break;
        }
    }
    return flag;
}

int print_board(void) // Print out a 4x4 board.
{
    int vertical, horizontal, p_col = 0;
    static int p_row = -1, recurse = 1;

    if (recurse != 1)
    {
        for (vertical = 0; vertical < 40; vertical++)
        {
            if (vertical % 8 == 2 && vertical != 34)
            {
                if (board[p_row][p_col] != 0)
                {
                    printw("%d", board[p_row][p_col]);
                    refresh();
                    p_col++;
                }
                else
                {
                    p_col++;
                    printw(" ");
                    refresh();
                }
            }
            else
            {
                printw(" ");
                refresh();
            }
        }
    }

    printw("\n");
    refresh();

    for (horizontal = 0; horizontal < 33; horizontal++)
    {
        if (horizontal % 8 == 0)
        {
            printw("|");
            refresh();
        }
        else
        {
            printw("-");
            refresh();
        }
    }

    printw("\n");
    refresh();

    if (recurse <= GRID_DIMENSION)
    {
        ++recurse;
        p_row++;
        print_board();
    }
    else
    {
        p_row = -1;
        recurse = 1;
        return 0;
    }
    return -1;
}

void slideArr(int slide) // Modify array as per key-stroke.
{
    int row_modify, col_modify, check_no_null;
    int temp, sum;

    if(slide == LEFT)
    {
        for(row_modify = 0; row_modify < GRID_DIMENSION; row_modify++)
        {
            for(col_modify = 0; col_modify < GRID_DIMENSION-1; col_modify++)
            {
                if(board[row_modify][col_modify] == 0)
                {
                    for(check_no_null = col_modify+1; check_no_null < GRID_DIMENSION; check_no_null++) // Search for number.
                    {
                        if(board[row_modify][check_no_null] != 0) // Swap to proper position if number is found.
                        {
                            temp = board[row_modify][check_no_null];
                            board[row_modify][check_no_null] = 0;
                            board[row_modify][col_modify] = temp;
                            temp = 0;
                            break;
                        }
                    }
                }
                if(board[row_modify][col_modify] != 0)
                {
                    check_no_null = col_modify;
                    while(board[row_modify][++check_no_null] == 0 && check_no_null < GRID_DIMENSION-1)
                    {
                        ;
                    }
                    if(board[row_modify][col_modify] == board[row_modify][check_no_null]) // Add values.
                    {
                        sum = (board[row_modify][col_modify]) * 2;
                        board[row_modify][col_modify] = sum;
                        board[row_modify][check_no_null] = 0;
                    }
                }
            }
        }
    }
    else if (slide == RIGHT)
    {
        for(row_modify = 0; row_modify < GRID_DIMENSION; row_modify++)
        {
            for(col_modify = GRID_DIMENSION-1; col_modify > 0; col_modify--)
            {
                if(board[row_modify][col_modify] == 0)
                {
                    for(check_no_null = col_modify-1; check_no_null >= 0; check_no_null--)
                    {
                        if(board[row_modify][check_no_null] != 0)
                        {
                            temp = board[row_modify][check_no_null];
                            board[row_modify][check_no_null] = 0;
                            board[row_modify][col_modify] = temp;
                            temp = 0;
                            break;
                        }
                    }
                }
                if(board[row_modify][col_modify] != 0)
                {
                    check_no_null = col_modify;
                    while(board[row_modify][--check_no_null] == 0 && check_no_null > 0)
                    {
                        ;
                    }
                    if(board[row_modify][col_modify] == board[row_modify][check_no_null])
                    {
                        sum = (board[row_modify][col_modify]) * 2;
                        board[row_modify][col_modify] = sum;
                        board[row_modify][check_no_null] = 0;
                    }
                }
            }
        }
    }
    else if (slide == UP)
    {
        for(col_modify = 0; col_modify < GRID_DIMENSION; col_modify++)
        {
            for(row_modify = 0; row_modify < GRID_DIMENSION-1; row_modify++)
            {
                if(board[row_modify][col_modify] == 0)
                {
                    for(check_no_null = row_modify+1; check_no_null < GRID_DIMENSION; check_no_null++)
                    {
                        if(board[check_no_null][col_modify] != 0)
                        {
                            temp = board[check_no_null][col_modify];
                            board[check_no_null][col_modify] = 0;
                            board[row_modify][col_modify] = temp;
                            temp = 0;
                            break;
                        }
                    }
                }
                if(board[row_modify][col_modify] != 0)
                {
                    check_no_null = row_modify;
                    while(board[++check_no_null][col_modify] == 0 && check_no_null < GRID_DIMENSION-1)
                    {
                        ;
                    }
                    if(board[row_modify][col_modify] == board[check_no_null][col_modify])
                    {
                        sum = (board[row_modify][col_modify]) * 2;
                        board[row_modify][col_modify] = sum;
                        board[check_no_null][col_modify] = 0;
                    }
                }
            }
        }
    }
    else if (slide == DOWN)
    {
        for(col_modify = 0; col_modify < GRID_DIMENSION; col_modify++)
        {
            for(row_modify = GRID_DIMENSION-1; row_modify > 0; row_modify--)
            {
                if(board[row_modify][col_modify] == 0)
                {
                    for(check_no_null = row_modify-1; check_no_null >= 0; check_no_null--)
                    {
                        if(board[check_no_null][col_modify] != 0)
                        {
                            temp = board[check_no_null][col_modify];
                            board[check_no_null][col_modify] = 0;
                            board[row_modify][col_modify] = temp;
                            temp = 0;
                            break;
                        }
                    }
                }
                if(board[row_modify][col_modify] != 0)
                {
                    check_no_null = row_modify;
                    while(board[--check_no_null][col_modify] == 0 && check_no_null > 0)
                    {
                        ;
                    }
                    if(board[row_modify][col_modify] == board[check_no_null][col_modify])
                    {
                        sum = (board[row_modify][col_modify]) * 2;
                        board[row_modify][col_modify] = sum;
                        board[check_no_null][col_modify] = 0;
                    }
                }
            }
        }
    }
}