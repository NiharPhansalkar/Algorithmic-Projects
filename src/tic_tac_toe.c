#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void fill_2darr(int);
void interpret(int);
void call_all_functions(int);
int print_info_board(int);
int take_input(void);
int check_winner(void);

#define MAX_ARR_SIZE 15

int need_chars = 0, interpret_row = -1, interpret_col = -1, total_moves = 1, zero_or_one = 0;
char nums_x_o[3][3] = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};

int main(void)
{
    printf("\n");
    fill_2darr(-1);
    print_info_board(0);
    printf("Player 1 is 'X' and player 2 is 'O'. Please enter number on the cell to put respective tokens.\n");
    for(total_moves = 1; total_moves <= 9; total_moves++)
    {
        if(total_moves%2 == 0)
        {
            zero_or_one = 1;
        }
        else
        {
            zero_or_one = 0;
        }
        call_all_functions(zero_or_one);
        if(check_winner() == 1)
        {
            if(zero_or_one == 0)
            {
                printf("The winner is : player %d\n\n CONGRATULATIONS!!!", 1);
            }
            if(zero_or_one == 1)
            {
                printf("The winner is : player %d\n\n CONGRATULATIONS!!!", 2);
            }
            break;
        }
        else
        {
            continue;
        }
    }
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
    for(row = 0; row<3; row++)
    {
        for(column = 0; column<3; column++)
        {
            if(row == interpret_row-1 && column == interpret_col-1)
            {
                if(flag == 0 && nums_x_o[row][column] != 'X' && nums_x_o[row][column] != 'O')
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
                    printf("A token is already present in this spot.\n");
                }
            }
        }
    }    
}

int print_info_board(int recursions)
{
    int vertical, horizontal; 
    static int recursive_counter = 1, manipulate_row = 0, manipulate_col = 0;
    if(recursions == 0)
    {
        printf("\t %s\n\n", "TIC TAC TOE");
    }
    for(vertical = 0; vertical < 24; vertical++)
    {
        printf(" ");
        if(vertical%8 == 0 && vertical != 0)
        {
            printf("|");
        }
        if(vertical%4 == 0 && vertical%8 != 0 && vertical != 0)
        {
            printf("%c", nums_x_o[manipulate_row][manipulate_col++]);
            if(vertical%16 == 0)
            {
                manipulate_row++;
            }
        }
    }
    printf("\n");
    if(recursions != 2)
    {
        for(horizontal = 0; horizontal <= 25; horizontal++)
        {
            printf("-");
            if(horizontal%8 == 0 && horizontal != 0 && horizontal != 24)
            {
                printf("-");
                printf("|");
            }
        }
    }
    printf("\n");
    if(recursions < 2)
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
}

int take_input(void)
{
    char store[MAX_ARR_SIZE];
    char* traverse = store;
    fgets(store, MAX_ARR_SIZE, stdin);
    store[strlen(store) - 1] = '\0';
    if(strlen(store) >= 2)
    {
        printf("Please enter the digit number as seen on the screen.\n");
        call_all_functions(zero_or_one);
    }
    else
    {
        while(*traverse != '\0')
        {
            if(!isdigit(*traverse))
            {
                printf("Please enter the digit number as seen on the screen.\n");
                call_all_functions(zero_or_one);
            }
            traverse++;
        }
    }
    return (atoi(store));   
}

void interpret(int determine)
{
    if(determine%3 == 0)
    {
        interpret_col = 3;
        interpret_row = determine/3;
    }
    else if (determine%3 == 1)
    {
        interpret_col = 1;
        interpret_row = (determine/3)+1;
    }
    else if(determine%3 == 2)
    {
        interpret_col = 2;
        interpret_row = (determine/3)+1;
    }
}

int check_winner(void)
{
    if(nums_x_o[0][0] == nums_x_o[1][1] && nums_x_o[0][0] == nums_x_o[2][2])
    {
        return 1;
    }
    else if((nums_x_o[0][0] == nums_x_o[0][1] && nums_x_o[0][1] == nums_x_o[0][2]) || 
            (nums_x_o[1][0] == nums_x_o[1][1] && nums_x_o[1][0] == nums_x_o[1][2]) || 
            (nums_x_o[2][0] == nums_x_o[2][1] && nums_x_o[2][0] == nums_x_o[2][2]))
    {
        return 1;
    }
    else if((nums_x_o[0][0] == nums_x_o[1][0] && nums_x_o[0][0] == nums_x_o[2][0]) || 
            (nums_x_o[0][1] == nums_x_o[1][1] && nums_x_o[0][1] == nums_x_o[2][1]) ||
            (nums_x_o[0][2] == nums_x_o[1][2] && nums_x_o[0][2] == nums_x_o[2][2]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}