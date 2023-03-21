#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stack
{
    char opera;
    int order;
    struct stack *next;
}Stack;
Stack *stak=NULL;
typedef struct  number{
    int data;
    struct number *next;
    struct number *prev;
}Number;

typedef struct nod
{
    Number *num;
    char oper;
    struct nod *prev;
    struct nod *next;
}Nod;
Nod *evaluate=NULL;

void pushnod( Number *, char );
void pushstack( char , int );
void popstack();
void addnod();
void substract();
Number* copynumber( Number *);
void addzero(Number *s);
void display();