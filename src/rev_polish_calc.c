//Program to make a reverse polish notation calculator.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void get_num(void);
void push(double);
double pop(void);
void operator(char);

#define MAX 100 //Maximum input that can be given.

int main(void)
{
    printf("Please input your numbers.\n\n");
    printf("Type + after your operands to add\nType - after your operands to subtract\nType * after your operands to multiply\nType / after your operands to divide\nType %% after your operands to find remainder\n\n");
    get_num();
    return 0;
}

void get_num(void)
{
    int c, i = 0;
    char num_in[MAX];
    while ((c = getchar()) != EOF) 
    {
        if(c >= '0' && c <= '9' && c != '.')//Input before decimal point
        {
            num_in[i] = c;
            i++;
        }
        if (c == '.')
        {
            num_in[i] = '.';
            i++;
        }
        if(num_in[i-1] == '.')
        {
            if(c >= '0' && c <= '9' && c != '.')// Input after decimal point.
            {
                num_in[i] = c;
                i++;
            }
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        {
            operator((char)c);
        }
        if(c == '\n')
        {
            operator((char)c);
        }
        if(c == ' ')
        {
            break;
        }
    }
    num_in[i] = '\0';
    if(atof(num_in) != 0)
    {    
        push(atof(num_in));
    }
    
}

int p_a_p = 0, push_pos = 0;
double store[MAX];

void push(double oprand)
{
    if(p_a_p < MAX)
    {
        store[p_a_p] = oprand;
        p_a_p++;
        push_pos = p_a_p;
    }
    else
    {
        printf("Stack overflow\n");
    }
        get_num();
    
}

double pop (void)
{
    --push_pos;
    if(push_pos >= 0)
    {
        return (store[push_pos]);
    }
    else
    {
        printf("Stack in empty.\n");
        return 0;
    }
}

void operator(char op)
{
    double op2, result, op3;
    int div;
    switch(op)
    {
        case '+':
            result = pop()+pop();
            push(result);
            break;
        case '-':
            op2 = pop();
            result = pop() - op2;
            push(result);
            break;
        case '*':
            result = pop()*pop();
            push(result);
            break;
        case '/':
            op2 = pop();
            if(op2 != 0)
            {
                result = pop()/op2;
                push(result);
            }
            else
            {
                printf("Can't divide by zero.\n");
                exit(0);
            }
            break;
        case '%':
            op2 = pop();
            op3 = pop();
            div = op3/op2;
            op2 = op2*div;
            result = op3-op2;   
            push(result);
            break;
        case '\n':
            printf("%-3f\n", pop());
            exit(0);
            break;
        default:
            printf("Error.\n");
            break;
    }
}
