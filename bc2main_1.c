
#include "bc2.c"

int main()
{
    char infix[100];
    printf("Enter the infix expression:");
    gets(infix);
    int i=0;
    while (infix[i] != '\0')
    {   
        if (isdigit(infix[i]) || (infix[i]=='-' && isdigit(infix[i+1])))
        {
            Number *head=NULL,*temp=NULL;
            int k=0;
            while (infix[i] != ' ')
            {
                if (k==0)
                {
                    head=(Number *)malloc(sizeof(Number));
                    if (infix[i] == '-')
                    {
                        printf("%c o", infix[i]);
                        head->data=infix[i];
                    }
                    else
                    {
                        head->data=infix[i]- '0';
                    }
                    head->next=head->prev=NULL;
                    temp=head;
                    k++;
                }
                else
                {
                    temp->next=(Number *)malloc(sizeof(Number));
                    temp->next->prev=temp;
                    temp=temp->next;
                    if (infix[i] == '.')
                    {
                        temp->data=infix[i];
                    }
                    else
                    {
                        temp->data=infix[i]- '0';
                    }
                    temp->next=NULL;

                }
                
                i++;
            }
            pushnod(head, '\0');
            
        }
        switch (infix[i])
        {
            case '+':
                pushstack( '+', 10);
                break;
            case '-':
                pushstack( '-', 11);
                break;
            case '*':
                pushstack( '*', 20);
                break;
            case '/':
                pushstack( '/', 20);
                break;
            case '(':
                pushstack('(', 5);
                break;
            case ')':
                popstack();
                break;



        }
        i++;   
    }
    Nod *temp;
    temp=evaluate;
    while (stak != NULL)
    {
        if(stak->next == NULL)
        {
            popstack();
            break;
        }
        else if (stak->opera != '(')
        {
            popstack();
            continue;
        }
        stak=stak->next;
        
    }
    displayev();
    printf("\n");
    while (evaluate != NULL)
    {
        if (evaluate->oper=='+')
        {
            addnod();
            display();
            printf("\n");
            continue;

           
        }
        if (evaluate->oper=='-')
        {
            substract();
            display();
            printf("\n");
            continue;
            
        }
        if (evaluate->oper=='*')
        {
            multiply();
            display();
            printf("\n");
            continue;
            
        }
        if (evaluate->oper=='/')
        {
            divide();
            display();
            printf("\n");
            continue;
            
        }
        if (evaluate->next != NULL)
        {
            evaluate=evaluate->next;
        }
        else
        {
            break;
        } 
    }
    printf("i");
    display();
    
    

}
