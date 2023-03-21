#include "bc2.h"

void pushstack( char d, int val)
{
    Stack  *new;
    printf("(%c) ", d);
    if (stak != NULL && stak->order > val && d!= '(')
    {
            popstack(stak);
            new=(Stack *)malloc(sizeof(Stack));
            new->opera=d;
            new->order=val;
            new->next=stak;
            stak=new;
    }
    else
    {
        new=(Stack *)malloc(sizeof(Stack));
        new->opera=d;
        new->order=val;
        new->next=stak;
        stak=new;

    }
    
     
}
void pushnod(Number *numb, char d)
{
    Nod *temp;
    temp=evaluate;
    if (evaluate == NULL)
    {
        evaluate=(Nod *)malloc(sizeof(Nod));
        evaluate->num=numb;
        evaluate->oper=d;
        evaluate->prev=evaluate->next=NULL;

    }
    else
    {
        while (temp->next != NULL)
        {
            temp=temp->next;
        }
        temp->next=(Nod *)malloc(sizeof(Nod));
        temp->next->prev=temp;
        temp=temp->next;
        temp->oper=d;
        temp->num=numb;
        temp->next=NULL;

        
    }
    
    
}
void popstack()
{
    Stack *temp, *q;
    temp=stak;
    q=NULL;
    int k=0;
    while (temp != NULL && stak->opera != '(')
    {
        q=temp;
        pushnod(NULL, temp->opera);
        if (temp->next== NULL)
        {
            free(q);
            q=NULL;
            stak=temp=NULL;
        }
        else
        {
            stak=stak->next;
            temp=temp->next;
            free(q);
            q=NULL;
        }
        
        
    }
    
}
void addnod()
{
    printf("[%d][%d]", evaluate->prev->num->data, evaluate->prev->prev->num->data);
    Nod *p;
    p=evaluate;
    Nod  *temp3;
    temp3=p->prev->prev->prev;
    Number *n1, *n2, *n3, *n11, *n22;
    n1=p->prev->num;
    n2=p->prev->prev->num;
    if (n1->data=='-' && n2->data != '-')
    {
        evaluate->prev->num=evaluate->prev->num->next;
        evaluate->prev->num->prev=NULL;
        substract();
    }
    else if (n2->data=='-' && n1->data != '-')
    {
        evaluate->prev->prev->num=evaluate->prev->prev->num->next;
        n3=evaluate->prev->prev->num;
        n3->prev=NULL;
        evaluate->prev->prev->num=evaluate->prev->num;
        evaluate->prev->num=n3;
        substract();
    }
    else if (n2->data=='-' && n1->data=='-')
    {
        evaluate->prev->num=evaluate->prev->num->next;
        evaluate->prev->prev->num=evaluate->prev->prev->num->next;
        evaluate->prev->prev->num->prev=NULL;
        evaluate->prev->num->prev=NULL;
        addnod();
        evaluate->num->prev=(Number *)malloc(sizeof(Number));
        evaluate->num->prev->next=evaluate->num;
        evaluate->num=evaluate->num->prev;
        evaluate->num->prev=NULL;
        evaluate->num->data='-';
        if (checkzero(evaluate->num))
    {
        if (evaluate->num->data == '-')
        {
            evaluate->num=evaluate->num->next;
            evaluate->num->prev=NULL;
        }
        
    }
        
    }
    else{
    n11=n1;
    n22=n2;
    int i=0, j=0, k, pull=0, dec1=0, dec2=0;
    while (n22 != NULL)
    {
        if (n22->data == '.')
        {
            Number *l1;
            l1=n22->prev;
            l1->next=n22->next;
            n22->next->prev=l1;
            dec2=j;
            free(n22);
            n22=l1->next;
            j++;
            continue;
        }
        
        n22=n22->next;
        j++;
    }
    while (n11 != NULL)
    {
        n11=n11->next;
        i++;
    }
    while (n1->next != NULL)
    {
        n1=n1->next;
    }
    while (n2->next != NULL)
    {
        n2=n2->next;
    }
    int max, min;
    if (i > j)
    {
        max=i;
        min=j;
    }
    if (j > i)
    {
        max=j;
        min=i;
        Number *l;
        l=n1;
        n1=n2;
        n2=l;
    }
    if (i==j)
    {
        max=min=i;
    }
    for ( k = 0; k < min; k++)
        {
            if(k==0){
            n3=(Number *)malloc(sizeof(Number));
            n3->next=NULL;
            n3->prev=NULL;
            }
            if (k!=0)
            {
                n3->prev=(Number *)malloc(sizeof(Number));
                n3->prev->next=n3;
                n3=n3->prev;
                n3->prev=NULL;
            }

            n3->data=(n1->data+n2->data+ pull)%10 ;
            pull=(n1->data+n2->data+pull)/10;
            if(k != min-1){
            n1=n1->prev;
            n2=n2->prev;
            }
        }
    for ( k = 0; k < max-min; k++)
        {
            n3->prev=(Number *)malloc(sizeof(Number));
            n3->prev->next=n3;
            n3=n3->prev;
            n3->data=(n1->prev->data+pull)%10;
            pull=(n1->prev->data+pull)/10;
            n1=n1->prev;

        }
    if (pull != 0)
    {
        n3->prev=(Number *)malloc(sizeof(Number));
        n3->prev->next=n3;
        n3=n3->prev;
        n3->prev=NULL;
        n3->data=pull;
    }
    if (temp3 == NULL)
    {
        p->oper='\0';
        p->num=n3;
        free(p->prev->prev);
        p->prev->prev=NULL;
        free(p->prev);
        p->prev=NULL;
    }
    else
    {
        p->oper='\0';
        p->num=n3;
        free(p->prev->prev);
        p->prev->prev=NULL;
        free(p->prev);
        p->prev=temp3;
        temp3->next=p;
        
    }
    if (checkzero(evaluate->num))
    {
        if (evaluate->num->data == '-')
        {
            evaluate->num=evaluate->num->next;
            evaluate->num->prev=NULL;
        }
        
    }
    }
}
int makepos(int num)
{
    if (num < 0)
    {
        return num *=-1;
    }
    else
    {
        return num;
    }
    
    
}
void substract()
{
    Nod *p;
    p=evaluate;
    Nod  *temp3;
    temp3=p->prev->prev->prev;
    Number *n1, *n2, *n3, *n11, *n22;
    n1=p->prev->num;
    n2=p->prev->prev->num;
    if (n1->data == '-' && n2->data != '-')
    {
        evaluate->prev->num=evaluate->prev->num->next;
        evaluate->prev->num->prev=NULL;
        addnod();
    }
    else if(n1->data == '-' && n2->data =='-')
    {
        evaluate->prev->num=evaluate->prev->num->next;
        evaluate->prev->num->prev=NULL;
        Number *l;
        l=evaluate->prev->num;
        evaluate->prev->prev->num=evaluate->prev->prev->num->next;
        evaluate->prev->prev->num->prev=NULL;
        evaluate->prev->num=evaluate->prev->prev->num;
        evaluate->prev->prev->num=l;
        substract();
        l=NULL;
    }
    else if (n1->data != '-' && n2->data =='-')
    {
        evaluate->prev->num->prev=(Number *)malloc(sizeof(Number));
        evaluate->prev->num->prev->next=evaluate->prev->num;
        evaluate->prev->num=evaluate->prev->num->prev;
        evaluate->prev->num->data='-';
        evaluate->prev->num->prev=NULL;
        addnod();
    }
    else
    {
        printf("pp");
    n11=n1;
    n22=n2;
    n1=n2=NULL;
    int i=0, j=0, e=1, k, pull=0;
    if (checkzero(n22))
    {
        n22=NULL;
        j++;
    }
    if (checkzero(n11))
    {
        n11=NULL;
        i++;
    }
    
    while (n22 != NULL)
    {
        if (n22->data==0 && e != 0)
        {
            n22=n22->next;
            Number *y;
            y=n22->prev;
            n22->prev=NULL;
            free(y);
            y=NULL;
        }
        if (n22->data != 0 || e==0)
        {
            e=0;
            if (j==0)
            {
                n2=n22;
            }
            j++;
            n22=n22->next;
        }
        
        
    }
    e=1;
    while (n11 != NULL)
    {
        if (n11->data==0 && e != 0)
        {
            n11=n11->next;
            n11->prev=NULL;
            Number *y;
            y=n11->prev;
            n11->prev=NULL;
            free(y);
            y=NULL;
        }
        if (n11->data != 0 || e==0)
        {
            e=0;
            if (i==0 )
            {
                n1=n11;
            }
            i++;
            n11=n11->next;
        }
    }
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
    if (n1 == NULL)
    {
        n1=copynumber(zero);
    }
    if (n2==NULL)
    {
        n2=copynumber(zero);
    }
    
    while (n1->next != NULL)
    {
        n1=n1->next;
    }
    while (n2->next != NULL)
    {
        n2=n2->next;
    }
    printf("%d %d j", n1->data, n2->data);
    int max, min, f;
    if (i > j)
    {
        max=i;
        min=j;
    }
    if (j > i)
    {
        max=j;
        min=i;
        Number *l;
        l=n1;
        n1=n2;
        n2=l;
    }
    int dec=10;
    if (i==j)
    {
        dec=0;
        max=min=i;
        
    }
    for ( k = 0; k < min; k++)
        {
            if(k==0){
            n3=(Number *)malloc(sizeof(Number));
            n3->next=NULL;
            n3->prev=NULL;
            }
            if (k!=0)
            {
                n3->prev=(Number *)malloc(sizeof(Number));
                n3->prev->next=n3;
                n3=n3->prev;
                n3->prev=NULL;
            }
            n3->data=makepos(dec+n1->data-n2->data)%10 + pull;
            if (i != j && n1->data-n2->data+pull < 0)
            {
                pull=-1;
            }
            else if (i==j && n2->data-n1->data+pull < 0 )
            {
                f=-1;
            }
            
            else
            {
                pull=0;
            }
            if(n2->prev != NULL){
            n1=n1->prev;
            n2=n2->prev;
            }
        }
    for ( k = 0; k < max-min; k++)
        {
            n3->prev=(Number *)malloc(sizeof(Number));
            n3->prev->next=n3;
            n3=n3->prev;
            n3->data=makepos(dec+n1->prev->data+pull)%10;
            if (n1->prev->data+pull < 0)
            {
                pull=-1;
            }
            else
            {
                pull=0;
            }
            n1=n1->prev;

        }
    if (f == -1 || j < i)
    {
        n3->prev=(Number *)malloc(sizeof(Number));
        n3->prev->next=n3;
        n3=n3->prev;
        n3->prev=NULL;
        n3->data='-';
    }
    
    if (temp3 == NULL)
    {
        p->oper='\0';
        p->num=n3;
        free(p->prev->prev);
        p->prev->prev=NULL;
        free(p->prev);
        p->prev=NULL;
    }
    else
    {
        p->oper='\0';
        p->num=n3;
        free(p->prev->prev);
        p->prev->prev=NULL;
        free(p->prev);
        p->prev=temp3;
        temp3->next=p;
        
    }
    if (checkzero(evaluate->num))
    {
        if (evaluate->num->data == '-')
        {
            evaluate->num=evaluate->num->next;
            evaluate->num->prev=NULL;
        }
        
    }
    
    }
}

void multiply()
{
    int flag=0, i=0, j=0, e=1;
    Nod *p, *q, *next1, *next2, *temp3;
    Number *n2, *n1, *zer, *n11, *n22;
    p=evaluate;
    n2=p->prev->num;
    n1=p->prev->prev->num;
    printf("%d", checkzero(n2));
    temp3=p->prev->prev->prev;
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
    if (n1->data == '-')
    {
        flag=flag-1;
        n1=n1->next;
    }
    if (n2->data == '-')
    {
        flag=flag-1;
        n2=n2->next;
        n2->prev=NULL;
    }
    if (checkzero(n1) + checkzero(n2) )
    {
        printf("pp");
        n1=copynumber(zero);
        n2=copynumber(zero);
        
    }
    if (!(checkzero(n1) + checkzero(n2)) )
    {
    n11=n1;
    n22=n2;
    n1=n2=NULL;
    while (n22 != NULL)
    {
        if (n22->data==0 && e != 0)
        {
            n22=n22->next;
            Number *y;
            y=n22->prev;
            n22->prev=NULL;
            free(y);
            y=NULL;
        }
        if (n22->data != 0 || e==0)
        {
            e=0;
            if (j==0)
            {
                n2=n22;
            }
            j++;
            n22=n22->next;
        }
        
        
    }
    e=1;
    while (n11 != NULL)
    {
        if (n11->data==0 && e != 0)
        {
            n11=n11->next;
            n11->prev=NULL;
            Number *y;
            y=n11->prev;
            n11->prev=NULL;
            free(y);
            y=NULL;
        }
        if (n11->data != 0 || e==0)
        {
            e=0;
            if (i==0 )
            {
                n1=n11;
            }
            i++;
            n11=n11->next;
        }
    }
    i=0;
    }   
    while (n2->next != NULL)
    {
        n2=n2->next;
        
    }
    q=p->next;
    p->next=(Nod *)malloc(sizeof(Nod));
    next1=p->next;
    next1->num=NULL;
    next1->prev=p;
    next1->oper='\0';
    next1->next=(Nod *)malloc(sizeof(Nod));
    next2=next1->next;
    next2->next=NULL;
    next2->prev=next1;
    next2->oper='\0';
    next2->num=NULL;
    p=NULL;
    while (n2 != NULL )
    {
        
        if (i==0)
        {
            for ( j = 0; j < n2->data; j++)
            {
                if (j == 0)
                {
                    evaluate->prev->num=copynumber(n1);
                    evaluate->prev->prev->num=copynumber(zero);
                    addnod();
                }
                else
                {
                    evaluate->prev=(Nod *)malloc(sizeof(Nod));
                    evaluate->prev->next=evaluate;
                    evaluate->prev->oper='\0';
                    evaluate->prev->prev=(Nod *)malloc(sizeof(Nod));
                    evaluate->prev->prev->next=evaluate->prev;
                    evaluate->prev->prev->prev=NULL;
                    evaluate->prev->prev->oper='\0';
                    evaluate->prev->num=copynumber(n1);
                    evaluate->prev->prev->num=copynumber(evaluate->num);
                    addnod();

                }
                
                
            }
            if (n2->data==0 && n2->prev == NULL)
            {
                break;
            }
            if (n2->data==0 && n2->prev != NULL)
            {
                evaluate->num=copynumber(zero);
            }
            evaluate->next->num=copynumber( evaluate->num);
            evaluate->next->next->num=copynumber( evaluate->num);
            
        }
        else
        {
            for ( j = 0; j < n2->data; j++)
            {
               
                if (j == 0)
                {
                    evaluate->prev=(Nod *)malloc(sizeof(Nod));
                    evaluate->prev->next=evaluate;
                    evaluate->prev->oper='\0';
                    evaluate->prev->prev=(Nod *)malloc(sizeof(Nod));
                    evaluate->prev->prev->next=evaluate->prev;
                    evaluate->prev->prev->prev=NULL;
                    evaluate->prev->prev->oper='\0';
                    evaluate->prev->num=copynumber(n1);
                    evaluate->prev->prev->num=copynumber(zero);
                    addnod();
                }
                else
                {
                    evaluate->prev=(Nod *)malloc(sizeof(Nod));
                    evaluate->prev->next=evaluate;
                    evaluate->prev->oper='\0';
                    evaluate->prev->prev=(Nod *)malloc(sizeof(Nod));
                    evaluate->prev->prev->next=evaluate->prev;
                    evaluate->prev->prev->prev=NULL;
                    evaluate->prev->prev->oper='\0';
                    evaluate->prev->num=copynumber(n1);
                    evaluate->prev->prev->num=copynumber(evaluate->num);
                    addnod();

                }
                
                
            }
            if (n2->data==0 && n2->prev != NULL)
            {
                evaluate->num=copynumber(zero);
            }
            int k;
            for ( k = 0; k < i; k++)
            {
                addzero(evaluate->num);
            }
            evaluate->next->num=copynumber(evaluate->next->next->num);
            evaluate=evaluate->next->next;
            addnod();
            evaluate->prev=NULL;
            if (n2->prev != NULL)
            {
            evaluate->prev=(Nod *)malloc(sizeof(Nod));
            evaluate->prev->next=evaluate;
            evaluate=evaluate->prev;
            evaluate->oper='\0';
            evaluate->num=NULL;
            evaluate->prev=(Nod *)malloc(sizeof(Nod));
            evaluate->prev->next=evaluate;
            evaluate=evaluate->prev;
            evaluate->prev=NULL;
            evaluate->num=NULL;
            evaluate->oper='\0';
            }
        }
        n2=n2->prev;
        i++;
    }
    printf("ii");
    if (n2 != NULL)
    {
        if (n2->data==0 && n2->prev == NULL)
    {
        evaluate->num=(Number *)malloc(sizeof(Number));
        evaluate->num->data=0;
        free(evaluate->prev);
        free(evaluate->prev->prev);
        free(evaluate->next->next);
        free(evaluate->next);
        evaluate->num->next=evaluate->num->prev=NULL;
        evaluate->oper='\0';
        
    }
    }
    
    if (flag==-1)
    {
        evaluate->num->prev=(Number *)malloc(sizeof(Number));
        evaluate->num->prev->next=evaluate->num;
        evaluate->num=evaluate->num->prev;
        evaluate->num->data='-';
        evaluate->num->prev=NULL;
    }
    
    
    if (temp3 != NULL)
    {
        temp3->next=evaluate;
        evaluate->prev=temp3;
        evaluate->oper='\0';
        evaluate->next=q;
        q->prev=evaluate;
        

    }
    if (temp3 == NULL)
    {
        evaluate->prev=NULL;
        evaluate->oper='\0';
        if (q==NULL)
        {
          evaluate->next=NULL;  
        }
        else
        {
            evaluate->next=q;
            q->prev=evaluate;
        }
        
    } 
}
Number* copynumber(Number *tocopy)
{
    Number *copyto;
    int i=0;
    while (tocopy != NULL)
    {
        if (i==0)
        {
            copyto=(Number *)malloc(sizeof(Number));
            copyto->data=tocopy->data;
            copyto->prev=NULL;
            copyto->next=NULL;
        }
        else
        {
           copyto->next=(Number *)malloc(sizeof(Number));
           copyto->next->prev=copyto;
           copyto=copyto->next;
           copyto->data=tocopy->data;
           copyto->next=NULL; 
        }
        tocopy=tocopy->next;
        i++;
        
        
    }
    while (copyto->prev != NULL)
    {
        copyto=copyto->prev;
    }
    return copyto;
    
    
    
    
}
void initialisenod(Nod *s)
{
    s->oper='\0';
    s->num=NULL;
    s->prev=NULL;
}
void addzero(Number *s)
{
    while (s->next != NULL)
    {
        s=s->next;
    }
    s->next=(Number *)malloc(sizeof(Number));
    s->next->data=0;
    s->next->prev=s;
    s->next->next=NULL;
    
}
void display()
{
    Number *n;
    n=evaluate->num;
    while (n != NULL)
    {
        if (n->data=='-')
        {
            printf("%c", n->data);
        }
        else{
        printf("%d", n->data);
        }
        n=n->next;
    }
}
void displayev()
{
    Nod *p;
    p=evaluate;
    while (p != NULL)
    {
        if (p->oper != '\0')
        {
            /* code */
            printf("%c ", p->oper);
        }
        p=p->next;
    }
}
void divide()
{
    int i=0, j=0, flag=0, e=1;
    Nod *p, *q, *temp3;
    Number *n3, *n4, *n5, *n1, *n2, *ll, *n11, *n22;
    p=evaluate;
    q=p->next;
    temp3=p->prev->prev->prev;
    n1=p->prev->num;
    n2=p->prev->prev->num;
    if (n1->data == '-')
    {
        flag=flag-1;
        n1=n1->next;
    }
    if (n2->data == '-')
    {
        flag=flag-1;
        n2=n2->next;
        n2->prev=NULL;
    }
    n11=n1;
    n22=n2;
    n1=n2=NULL;
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
    Number *one;
    one=(Number *)malloc(sizeof(Number));
    one->data=1;
    one->next=one->prev=NULL;
    if (checkzero(n11) || checkzero(n22))
    {
        if (checkzero(n11) * (!checkzero(n22)))
        {
            printf("Error ,denominator zero during division");
            evaluate->next=evaluate->prev=NULL;
        }
        else
        {
            evaluate->prev->num=copynumber(zero);
            multiply();

        }
        
        
    }
    else
    {
    while (n22 != NULL)
    {
        if (n22->data==0 && e != 0)
        {
            n22=n22->next;
            Number *y;
            y=n22->prev;
            n22->prev=NULL;
            free(y);
            y=NULL;
        }
        if (n22->data != 0 || e==0)
        {
            e=0;
            if (j==0)
            {
                n2=n22;
            }
            j++;
            n22=n22->next;
        }
        
        
    }
    e=1;
    while (n11 != NULL)
    {
        if (n11->data==0 && e != 0)
        {
            n11=n11->next;
            n11->prev=NULL;
            Number *y;
            y=n11->prev;
            n11->prev=NULL;
            free(y);
            y=NULL;
        }
        if (n11 != NULL)
        {
        if (n11->data != 0 || e==0)
        {
            e=0;
            if (i==0 )
            {
                n1=n11;
            }
            i++;
            n11=n11->next;
        }
        }
    }
    n5=copynumber(one);
    if (n1==NULL)
    {
        printf("Error , denominator got value 0.");
        evaluate->next=NULL;
        evaluate->prev=NULL;
    }
    if (n2==NULL)
    {
        evaluate->prev->prev->num=copynumber(zero);
        multiply();
    }
    if (n1 != NULL && n2 != NULL)
    {
    int ext=1;
    while (n5->data != '-' && ext != 0  )
    {
        ext=0;
        n3=n4=NULL;
        if(evaluate->prev != NULL)
        {
            n3=copynumber(n1);
            evaluate->prev->num=n3;
            n4=copynumber(n2);
            evaluate->prev->prev->num=n4;
            substract();
            n5=copynumber(evaluate->num);
            evaluate->num=copynumber(zero);
            if (n5->data == '-')
            {
                break;
            }
            evaluate->next=(Nod *)malloc(sizeof(Nod));
            evaluate->next->prev=evaluate;
            evaluate->next->oper='\0';
            evaluate->next->num=copynumber(one);
            evaluate=evaluate->next;
            evaluate->next=(Nod *)malloc(sizeof(Nod));
            evaluate->next->prev=evaluate;
            evaluate=evaluate->next;
            evaluate->oper='\0';
            evaluate->next=NULL;
            evaluate->num=NULL;
            addnod();
            

        }
        else 
        {
            Nod *p1, *p2, *p3, *p4;
            evaluate->prev=(Nod *)malloc(sizeof(Nod));
            p1=evaluate->prev;
            p1->next=evaluate;
            p1->oper='\0';
            p1->num=copynumber(evaluate->num);
            p1->prev=(Nod *)malloc(sizeof(Nod));
            p2=p1->prev;
            p2->next=p1;
            p2->oper='\0';
            p2->prev=(Nod *)malloc(sizeof(Nod));
            p3=p2->prev;
            p3->next=p2;
            p3->oper='\0';
            p3->num=copynumber(n1);
            p3->prev=(Nod *)malloc(sizeof(Nod));
            p4=p3->prev;
            p4->next=p3;
            p4->oper='\0';
            p4->prev=NULL;
            p4->num=copynumber(n5);
            evaluate=evaluate->prev->prev;
            substract();
            p3=p4=NULL;
            n5=copynumber(evaluate->num);
            if (n5->data != '-')
            {
                p2->num=copynumber(one);
            }
            else
            {
                p2->num=copynumber(zero);
            }
            
            evaluate=evaluate->next->next;
            addnod();
            p1=p2=NULL;
        }
        ll=n5;
        while (ll != NULL)
        {
            if (ll->data != 0)
            {
                ext=1;

            } 
            ll=ll->next;
        }
        
        
    }
    if (flag==-1)
    {
        evaluate->num->prev=(Number *)malloc(sizeof(Number));
        evaluate->num->prev->next=evaluate->num;
        evaluate->num=evaluate->num->prev;
        evaluate->num->data='-';
        evaluate->num->prev=NULL;
    }
     if (temp3 != NULL)
    {
        temp3->next=evaluate;
        evaluate->prev=temp3;
        evaluate->oper='\0';
        evaluate->next=q;
        q->prev=evaluate;
        

    }
    if (temp3 == NULL)
    {
        evaluate->prev=NULL;
        evaluate->oper='\0';
        if (q==NULL)
        {
          evaluate->next=NULL;  
        }
        else
        {
            evaluate->next=q;
            q->prev=evaluate;
        }
        
    } 
    }
    }
    

}
int checkzero(Number *q)
{
    int i=0;
    if (q->data=='-')
    {
        q=q->next;
    }
    
    while (q != NULL)
    {
        if (q->data != 0)
        {
            i=1;
        }
        
        q=q->next;

    }
    if (i==0)
    {
        return 1;
    }
    if (i != 0)
    {
        return 0;
    }
    
    
    
    
}