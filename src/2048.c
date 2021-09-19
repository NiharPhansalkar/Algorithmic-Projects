/*
Program -: 2048 game
Author -: Nihar Phansalkar
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>    // Used for seeding rand().
#include <ncurses.h> // Provides functions for UI.

int print_board(void);
int make_random(void);
int two_or_four(void);
int player_choice(void);
int check_win(void);
int check_loss(void);
void print_rules(void);
void fill_arr(void);
void slideArr_left(void);
void slideArr_right(void);
void slideArr_up(void);
void slideArr_down(void);
void put_tiles(void); // Defined to reduce redundancy.
void intepreter(int);

#define MY_NULL 0
#define INITIAL_INIT -1
#define WIN 1
#define LOSS 1
#define NO_CHANGE 0
#define GRID_DIMENSION 4
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
// ERR is defined in <ncurses.h>

int board[GRID_DIMENSION][GRID_DIMENSION];
int interpret_row = INITIAL_INIT, interpret_col = INITIAL_INIT, which_num; // ERR for initial initialization.

int main(void)
{
    initscr();            // Start curses mode.
    raw();                // Disable line buffer of stdin.
    keypad(stdscr, TRUE); // Get special keys
    noecho();

    int one_time, check_choice;
    srand(time(0)); // Seed rand() to produce a random batch of numbers.
    put_tiles();
    while (check_win() != WIN && check_loss() != LOSS)
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

        if (check_choice == ERR)
        {
            while (check_choice == ERR)
                check_choice = player_choice();
        }

        switch (check_choice)
        {
        case LEFT:
            slideArr_left();
            break;

        case RIGHT:
            slideArr_right();
            break;

        case UP:
            slideArr_up();
            break;

        case DOWN:
            slideArr_down();
            break;

        default:
            break;
        }

        put_tiles();
        print_board();
        refresh();
    }
    if (check_win() == WIN)
    {
        printw("\n\nCongratulations! You have won the game!\n");
        refresh();
    }
    if (check_loss() == LOSS)
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
    int row, col, flag;
    enum check
    {
        LOW,
        HIGH
    };
    for (row = 0; row < GRID_DIMENSION; row++)
    {
        for (col = 0; col < GRID_DIMENSION; col++)
        {
            if (row == interpret_row - 1 && col == interpret_col - 1)
            {
                if (board[row][col] == 0)
                {
                    flag = LOW;
                    board[row][col] = which_num;
                    break;
                }
                else
                {
                    flag = HIGH;
                    put_tiles();
                    break;
                }
            }
        }
        if (flag == HIGH)
        {
            break;
        }
    }
}

int two_or_four(void) // Returns two or four in the ratio 9:1.
{
    return ((rand() % 10) > 0) ? 2 : 4;
}

int make_random(void) // Generate a random number between 1 and 16 for two and four pop-ups.
{
    int make_num = (rand() % (GRID_DIMENSION * GRID_DIMENSION)) + 1;
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
        return ERR;
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
                return WIN;
            }
            else
            {
                return NO_CHANGE;
            }
        }
    }
    return ERR;
}

int check_loss(void)
{
    int row, col, flag = 0;

    for (row = 0; row < GRID_DIMENSION; row++)
    {
        for (col = 0; col < GRID_DIMENSION; col++)
        {
            if (board[row][col] != 0)
            {
                flag = LOSS;
            }
            else
            {
                flag = NO_CHANGE;
                break;
            }
        }
        if (flag == NO_CHANGE)
        {
            break;
        }
    }
    return flag;
}

int print_board(void) // Print out a 4x4 board.
{
    int vertical, horizontal, p_col = 0;
    static int p_row = INITIAL_INIT, recurse = 1;

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
        p_row = INITIAL_INIT;
        recurse = 1;
        return 0;
    }
    return ERR;
}

void slideArr_left(void) // Modify array as per left key-stroke.
{
    int row_modify, col_modify, check_no_null;
    int temp, sum;

    for (row_modify = 0; row_modify < GRID_DIMENSION; row_modify++)
    {
        for (col_modify = 0; col_modify < GRID_DIMENSION - 1; col_modify++)
        {
            if (board[row_modify][col_modify] == MY_NULL)
            {
                for (check_no_null = col_modify + 1; check_no_null < GRID_DIMENSION; check_no_null++)
                {
                    if (board[row_modify][check_no_null] != MY_NULL)
                    {
                        temp = board[row_modify][check_no_null];
                        board[row_modify][check_no_null] = MY_NULL;
                        board[row_modify][col_modify] = temp;
                        temp = 0;
                        break;
                    }
                }
            }
            if (board[row_modify][col_modify] != MY_NULL)
            {
                check_no_null = col_modify;
                while (board[row_modify][++check_no_null] == MY_NULL && check_no_null < GRID_DIMENSION - 1)
                {
                    ;
                }
                if (board[row_modify][col_modify] == board[row_modify][check_no_null])
                {
                    sum = (board[row_modify][col_modify]) * 2;
                    board[row_modify][col_modify] = sum;
                    board[row_modify][check_no_null] = MY_NULL;
                }
            }
        }
    }
}

void slideArr_right(void) // Modify array as per right key-stroke.
{
    int row_modify, col_modify, check_no_null;
    int temp, sum;

    for (row_modify = 0; row_modify < GRID_DIMENSION; row_modify++)
    {
        for (col_modify = GRID_DIMENSION - 1; col_modify > 0; col_modify--)
        {
            if (board[row_modify][col_modify] == MY_NULL)
            {
                for (check_no_null = col_modify - 1; check_no_null >= 0; check_no_null--)
                {
                    if (board[row_modify][check_no_null] != 0)
                    {
                        temp = board[row_modify][check_no_null];
                        board[row_modify][check_no_null] = MY_NULL;
                        board[row_modify][col_modify] = temp;
                        temp = 0;
                        break;
                    }
                }
            }
            if (board[row_modify][col_modify] != MY_NULL)
            {
                check_no_null = col_modify;
                while (board[row_modify][--check_no_null] == MY_NULL && check_no_null > 0)
                {
                    ;
                }
                if (board[row_modify][col_modify] == board[row_modify][check_no_null])
                {
                    sum = (board[row_modify][col_modify]) * 2;
                    board[row_modify][col_modify] = sum;
                    board[row_modify][check_no_null] = MY_NULL;
                }
            }
        }
    }
}

void slideArr_up(void) // Modify array as per up key-stroke.
{
    int row_modify, col_modify, check_no_null;
    int temp, sum;

    for (col_modify = 0; col_modify < GRID_DIMENSION; col_modify++)
    {
        for (row_modify = 0; row_modify < GRID_DIMENSION - 1; row_modify++)
        {
            if (board[row_modify][col_modify] == MY_NULL)
            {
                for (check_no_null = row_modify + 1; check_no_null < GRID_DIMENSION; check_no_null++)
                {
                    if (board[check_no_null][col_modify] != MY_NULL)
                    {
                        temp = board[check_no_null][col_modify];
                        board[check_no_null][col_modify] = MY_NULL;
                        board[row_modify][col_modify] = temp;
                        temp = 0;
                        break;
                    }
                }
            }
            if (board[row_modify][col_modify] != MY_NULL)
            {
                check_no_null = row_modify;
                while (board[++check_no_null][col_modify] == MY_NULL && check_no_null < GRID_DIMENSION - 1)
                {
                    ;
                }
                if (board[row_modify][col_modify] == board[check_no_null][col_modify])
                {
                    sum = (board[row_modify][col_modify]) * 2;
                    board[row_modify][col_modify] = sum;
                    board[check_no_null][col_modify] = MY_NULL;
                }
            }
        }
    }
}

void slideArr_down(void) // Modify array as per down key-stroke.
{
    int row_modify, col_modify, check_no_null;
    int temp, sum;

    for (col_modify = 0; col_modify < GRID_DIMENSION; col_modify++)
    {
        for (row_modify = GRID_DIMENSION - 1; row_modify > 0; row_modify--)
        {
            if (board[row_modify][col_modify] == MY_NULL)
            {
                for (check_no_null = row_modify - 1; check_no_null >= 0; check_no_null--)
                {
                    if (board[check_no_null][col_modify] != MY_NULL)
                    {
                        temp = board[check_no_null][col_modify];
                        board[check_no_null][col_modify] = MY_NULL;
                        board[row_modify][col_modify] = temp;
                        temp = 0;
                        break;
                    }
                }
            }
            if (board[row_modify][col_modify] != MY_NULL)
            {
                check_no_null = row_modify;
                while (board[--check_no_null][col_modify] == MY_NULL && check_no_null > 0)
                {
                    ;
                }
                if (board[row_modify][col_modify] == board[check_no_null][col_modify])
                {
                    sum = (board[row_modify][col_modify]) * 2;
                    board[row_modify][col_modify] = sum;
                    board[check_no_null][col_modify] = MY_NULL;
                }
            }
        }
    }
}
