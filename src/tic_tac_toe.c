#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <ncurses.h> // Contains UI functions.

void fill_2darr(int);
void interpret(int);
void call_all_functions(int);
int print_info_board(int);
int take_input(void);
int check_winner(void);

#define MAX_ARR_SIZE 15

int need_chars = 0, interpret_row = -1, interpret_col = -1, total_moves = 1, zero_or_one = 0;
char nums_x_o[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

int main(void)
{
    initscr(); // Start curses mode.
    raw();     // Disable line buffer of stdin.
    noecho();  // Don't echo for getch().

    printw("\n");
    refresh();
    fill_2darr(-1);
    print_info_board(0);
    printw("Player 1 is 'X' and player 2 is 'O'. Please enter number on the cell to put respective tokens.\n");
    refresh();
    for (total_moves = 1; total_moves <= 9; total_moves++)
    {
        if (total_moves % 2 == 0)
        {
            zero_or_one = 1;
        }
        else
        {
            zero_or_one = 0;
        }
        call_all_functions(zero_or_one);
        if (check_winner() == 1)
        {
            if (zero_or_one == 0)
            {
                printw("The winner is : player %d\n\nCONGRATULATIONS!!!\n", 1);
                refresh();
                getch();
            }
            if (zero_or_one == 1)
            {
                printw("The winner is : player %d\n\nCONGRATULATIONS!!!\n", 2);
                refresh();
                getch();
            }
            break;
        }
        else
        {
            continue;
        }
    }
    endwin(); // End curses mode.
    return 0;
}

void call_all_functions(int which_player)
{
    int grid_no;
    grid_no = take_input();
    interpret(grid_no);
    fill_2darr(which_player);
    print_info_board(0);
}

void fill_2darr(int flag)
{
    int row, column;
    for (row = 0; row < 3; row++)
    {
        for (column = 0; column < 3; column++)
        {
            if (row == interpret_row - 1 && column == interpret_col - 1)
            {
                if (flag == 0 && nums_x_o[row][column] != 'X' && nums_x_o[row][column] != 'O')
                {
                    nums_x_o[row][column] = 'X';
                }
                else if (flag == 1 && nums_x_o[row][column] != 'O' && nums_x_o[row][column] != 'X')
                {
                    nums_x_o[row][column] = 'O';
                }
                else
                {
                    total_moves -= 1;
                    printw("A token is already present in this spot.\n");
                    refresh();
                }
            }
        }
    }
}

int print_info_board(int recursions)
{
    int vertical, horizontal;
    static int recursive_counter = 1, manipulate_row = 0, manipulate_col = 0;
    if (recursions == 0)
    {
        printw("\t %s\n\n", "TIC TAC TOE");
        refresh();
    }
    for (vertical = 0; vertical < 24; vertical++)
    {
        printw(" ");
        refresh();
        if (vertical % 8 == 0 && vertical != 0)
        {
            printw("|");
            refresh();
        }
        if (vertical % 4 == 0 && vertical % 8 != 0 && vertical != 0)
        {
            printw("%c", nums_x_o[manipulate_row][manipulate_col++]);
            refresh();
            if (vertical % 16 == 0)
            {
                manipulate_row++;
            }
        }
    }
    printw("\n");
    refresh();
    if (recursions != 2)
    {
        for (horizontal = 0; horizontal <= 25; horizontal++)
        {
            printw("-");
            refresh();
            if (horizontal % 8 == 0 && horizontal != 0 && horizontal != 24)
            {
                printw("-");
                refresh();
                printw("|");
                refresh();
            }
        }
    }
    printw("\n");
    refresh();
    if (recursions < 2)
    {
        print_info_board(recursive_counter++);
    }
    else
    {
        manipulate_row = 0;
        manipulate_col = 0;
        recursive_counter = 1;
        return 0;
    }
    return -1;
}

int take_input(void)
{
    int key;
    key = getch();
    if (key >= 48 && key < 58)
    {
        clear();
        refresh();
        return (key - 48);
    }
    else
    {
        clear();
        printw("Please enter the number present on the screen. Press any key to play further.\n");
        refresh();
        take_input();
    }
    return -1;
}

void interpret(int determine) // Convert box number into row and column.
{
    if (determine % 3 == 0)
    {
        interpret_col = 3;
        interpret_row = determine / 3;
    }
    else if (determine % 3 == 1)
    {
        interpret_col = 1;
        interpret_row = (determine / 3) + 1;
    }
    else if (determine % 3 == 2)
    {
        interpret_col = 2;
        interpret_row = (determine / 3) + 1;
    }
}

int check_winner(void) // All winning conditions for the game.
{
    if (nums_x_o[0][0] == nums_x_o[1][1] && nums_x_o[0][0] == nums_x_o[2][2])
    {
        return 1;
    }
    else if ((nums_x_o[0][0] == nums_x_o[0][1] && nums_x_o[0][1] == nums_x_o[0][2]) ||
             (nums_x_o[1][0] == nums_x_o[1][1] && nums_x_o[1][0] == nums_x_o[1][2]) ||
             (nums_x_o[2][0] == nums_x_o[2][1] && nums_x_o[2][0] == nums_x_o[2][2]))
    {
        return 1;
    }
    else if ((nums_x_o[0][0] == nums_x_o[1][0] && nums_x_o[0][0] == nums_x_o[2][0]) ||
             (nums_x_o[0][1] == nums_x_o[1][1] && nums_x_o[0][1] == nums_x_o[2][1]) ||
             (nums_x_o[0][2] == nums_x_o[1][2] && nums_x_o[0][2] == nums_x_o[2][2]))
    {
        return 1;
    }
    else if ((nums_x_o[0][0] == nums_x_o[1][1] && nums_x_o[0][0] == nums_x_o[2][2]) ||
             (nums_x_o[0][2] == nums_x_o[1][1] && nums_x_o[1][1] == nums_x_o[2][0]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}