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
        evaluate->prev->prev->num=evaluate->prev->num;
        evaluate->prev->num=n3;
        substract();
    }
    else if (n2->data=='-' && n1->data=='-')
    {
        evaluate->prev->num=evaluate->prev->num->next;
        evaluate->prev->prev->num=evaluate->prev->prev->num->next;
        addnod();
        if(!checkzero(evaluate->num)){
        evaluate->num->prev=(Number *)malloc(sizeof(Number));
        evaluate->num->prev->next=evaluate->num;
        evaluate->num=evaluate->num->prev;
        evaluate->num->prev=NULL;
        evaluate->num->data='-';
        }
        
    }
    else{
    n11=n1;
    n22=n2;
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
    int i=0, j=0, k, pull=0, dec1=0, dec2=0;
    if (checkzero(n11))
    {
        n1=copynumber(zero);
        n11=NULL;
        i=1;
    }
    if (checkzero(n22))
    {
        n2=copynumber(zero);
        n22=NULL;
        j=1;
    }
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
            n22=l1->next->next;
            j++;
            continue;
        }
        
        n22=n22->next;
        j++;
    }
    while (n11 != NULL)
    {
         if (n11->data == '.')
        {
            Number *l1;
            l1=n11->prev;
            l1->next=n11->next;
            n11->next->prev=l1;
            dec1=i;
            free(n11);
            n11=l1->next->next;
            i++;
            continue;
        }
        n11=n11->next;
        i++;
    }
    if (dec1 == 0)
    {
        dec1=i;
    }
    if (dec2 == 0)
    {
        dec2=j;
    }
    
    int y1, y2, y3;
    y2=j - dec2;
    y3=i - dec1;
    if (dec1 != i || dec1 != j)
    {
    if (j - dec2 > i - dec1 && !checkzero(n1))
    {
        
        for ( y1 = 0; y1 < y2 - y3; y1++)
        {
            addzero(n1);
            i++;
        }
    }
    else
    {
        if(!checkzero(n2))
        {
        for ( y1 = 0; y1 < y3 - y2  ; y1++)
        {
            addzero(n2);
            j++;
        }
        }
        
    }
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
    if (y2 >= y3 )
    {
        n2=evaluate->num;
        while (n2->next != NULL)
        {
            n2=n2->next;
        }
        
        for ( y1 = 0; y1 < y2; y1++)
        {
            n2=n2->prev;

        }
        if (y2 != 0)
        {
            Number *l;
        l=(Number *)malloc(sizeof(Number));
        l->data='.';
        l->next=n2->next;
        l->next->prev=l;
        l->prev=n2;
        n2->next=l;
        }

        
    }
    if (y2 < y3)
    {
        n2=evaluate->num;
        while (n2->next != NULL)
        {
            n2=n2->next;
        }
        
        for ( y1 = 0; y1 < y3; y1++)
        {
            n2=n2->prev;

        }
        if (y3 != 0)
        {
            Number *l;
        l=(Number *)malloc(sizeof(Number));
        l->data='.';
        l->next=n2->next;
        l->next->prev=l;
        l->prev=n2;
        n2->next=l;
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
    evaluate=evaluate->prev;
    extras();
    evaluate=evaluate->prev;
    extras();
    evaluate=evaluate->next->next;
    p=evaluate;
    Nod  *temp3;
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
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
    n11=n1;
    n22=n2;
    int i=0, j=0, e=1, k, pull=0, dec1=0, dec2=0;
    if (checkzero(n11))
    {
        n1=copynumber(zero);
        n11=NULL;
        i=1;
    }
    if (checkzero(n22))
    {
        n2=copynumber(zero);
        n22=NULL;
        j=1;
    }
    
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
            n22=l1->next->next;
            j++;
            continue;
        }
        n22=n22->next;
        j++;
    }
    while (n11 != NULL)
    {
         if (n11->data == '.')
        {
            Number *l1;
            l1=n11->prev;
            l1->next=n11->next;
            n11->next->prev=l1;
            dec1=i;
            free(n11);
            n11=l1->next->next;
            i++;
            continue;
        }
        n11=n11->next;
        i++;
    }
    int tr=dec1, trw=dec2;
    if (dec1 == 0)
    {
        dec1=i;
    }
    if (dec2 == 0)
    {
        dec2=j;
    }
    int y1, y2, y3;
    y2=j - dec2;
    y3=i - dec1;
    if (dec1 != i || dec1 != j)
    {
    if (j - dec2 > i - dec1 && !checkzero(n1))
    {
        
        for ( y1 = 0; y1 < y2 - y3; y1++)
        {
            addzero(n1);
            i++;
        }
    }
    else if (j - dec2 < i - dec1)
    {
        if(!checkzero(n2))
        {
        for ( y1 = 0; y1 < y3 - y2  ; y1++)
        {
            addzero(n2);
            j++;
        }
        }
        
    }
    }
    while (n1->next != NULL)
    {
        n1=n1->next;
    }
    while (n2->next != NULL)
    {
        n2=n2->next;
    }
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
    int u=compare(evaluate->prev->num, evaluate->prev->prev->num);
    int dec=10;
    if (i==j)
    {
        dec=0;
        max=min=i;
        if (!u)
        {
            Number *l;
            l=n1;
            n1=n2;
            n2=l;
        }
        if (tr != 0 || trw != 0)
        {
            dec=10;
        }
        
        
        
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
            if (i == j && k==min -1)
            {
                dec=0;
            }
            
            n3->data=makepos(dec+n1->data-n2->data+ pull)%10 ;
            if ((i != j && n1->data-n2->data+pull < 0) || ((tr != 0 || trw !=0) && n1->data-n2->data+pull < 0) )
            {
                pull=-1;
            }
            else if ((i==j && n1->data-n2->data+pull < 0) && (tr == 0 && trw ==0) )
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
    dec=10;
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
    if (((u && i==j) || j < i) && !checkzero(n3))
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
    if (y2 >= y3 )
    {
        n2=NULL;
        n2=evaluate->num;
        while (n2->next != NULL)
        {
            n2=n2->next;
        }
        
        for ( y1 = 0; y1 < y2; y1++)
        {
            n2=n2->prev;

        }
        if (y2 != 0)
        {
            Number *l;
        l=(Number *)malloc(sizeof(Number));
        l->data='.';
        l->next=n2->next;
        l->next->prev=l;
        l->prev=n2;
        n2->next=l;
        }

        
    }
    if (y2 < y3)
    {
        n2=evaluate->num;
        while (n2->next != NULL)
        {
            n2=n2->next;
        }
        
        for ( y1 = 0; y1 < y3; y1++)
        {
            n2=n2->prev;

        }
        if (y3 != 0)
        {
            Number *l;
        l=(Number *)malloc(sizeof(Number));
        l->data='.';
        l->next=n2->next;
        l->next->prev=l;
        l->prev=n2;
        n2->next=l;
        }
    }
    extras();
    }
}

void multiply()
{
    int flag=0, i=0, j=0, e=1, dec1=0, dec2=0, y1=0, y2=0, y3=0, chec=0, y4=0;
    evaluate=evaluate->prev;
    extras();
    evaluate=evaluate->prev;
    extras();
    evaluate=evaluate->next->next;
    Nod *p, *q, *next1, *next2, *temp3;
    Number *n2, *n1, *zer, *n11, *n22;
    p=evaluate;
    n2=p->prev->num;
    n1=p->prev->prev->num;
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
        n1=copynumber(zero);
        n2=copynumber(zero);
        
    }
    chec=!(checkzero(n1) + checkzero(n2));
    if (chec)
    {
    n11=n1;
    n22=n2;
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
            n22=l1->next->next;
            j++;
            continue;
        }
        n22=n22->next;
        j++;
    }
    while (n11 != NULL)
    {
         if (n11->data == '.')
        {
            Number *l1;
            l1=n11->prev;
            l1->next=n11->next;
            n11->next->prev=l1;
            dec1=i;
            free(n11);
            n11=l1->next->next;
            i++;
            continue;
        }
        n11=n11->next;
        i++;
    }
    int tr=dec1, trw=dec2;
    if (dec1 == 0)
    {
        dec1=i;
    }
    if (dec2 == 0)
    {
        dec2=j;
    }
    y2=j - dec2;
    y3=i - dec1;
    if (dec1 != i || dec1 != j)
    {
    if (j - dec2 > i - dec1 && !checkzero(n1))
    {
        
        for ( y1 = 0; y1 < y2 - y3; y1++)
        {
            addzero(n1);
            i++;
            y4++;
        }
    }
    else if (j - dec2 < i - dec1)
    {
        if(!checkzero(n2))
        {
        for ( y1 = 0; y1 < y3 - y2  ; y1++)
        {
            addzero(n2);
            j++;
            y4++;
        }
        }
        
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
            if (n2->data==0 && n2->prev == NULL)
            {
                evaluate->num=copynumber(zero);
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
    if (chec)
    {
    if (y2 + y3 != 0 )
    {
        n2=NULL;
        n2=evaluate->num;
        evaluate->num=NULL;
        while (n2->next != NULL)
        {
            n2=n2->next;
        }
        
        for ( y1 = 0; y1 < (y2 + y3 + y4); y1++)
        {
            if ( n2->prev==NULL)
            {
                n2->prev=copynumber(zero);
                n2->prev->next=n2;
            }
            
            n2=n2->prev;

        }
        
        if (y2 + y3 != 0)
        {
        Number *l;
        l=(Number *)malloc(sizeof(Number));
        l->data='.';
        l->next=n2->next;
        l->next->prev=l;
        l->prev=n2;
        n2->next=l;
        }
        while (n2->prev != NULL)
        {
            n2=n2->prev;
        }
        evaluate->num=n2;

        
    }
    }
    extras(); 
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
        if (n->data=='-' || n->data == '.')
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
    evaluate=evaluate->prev;
    extras();
    evaluate=evaluate->prev;
    extras();
    evaluate=evaluate->next->next;
    int i=0, j=0, flag=0, e=1, dec1=0, dec2=0, y1=0, y2=0, y3=0, y4=0, y5=0;
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
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
    Number *one;
    one=(Number *)malloc(sizeof(Number));
    one->data=1;
    one->next=one->prev=NULL;
    if (checkzero(n11) || checkzero(n22) )
    {
        if (checkzero(n11) )
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
        if (n22->data == '.')
        {
            Number *l1;
            l1=n22->prev;
            l1->next=n22->next;
            n22->next->prev=l1;
            dec2=j;
            free(n22);
            n22=l1->next->next;
            j++;
            continue;
        }
        n22=n22->next;
        j++;
    }
    while (n11 != NULL)
    {
         if (n11->data == '.')
        {
            Number *l1;
            l1=n11->prev;
            l1->next=n11->next;
            n11->next->prev=l1;
            dec1=i;
            free(n11);
            n11=l1->next->next;
            i++;
            continue;
        }
        n11=n11->next;
        i++;
    }
    int tr=dec1, trw=dec2;
    if (dec1 == 0)
    {
        dec1=i;
    }
    if (dec2 == 0)
    {
        dec2=j;
    }
    y2=j - dec2;
    y3=i - dec1;
    if (dec1 != i || dec1 != j)
    {
    if (j - dec2 > i - dec1 && !checkzero(n1))
    {
        
        for ( y1 = 0; y1 < y2 - y3; y1++)
        {
            addzero(n1);
            i++;
            y4++;
        }
    }
    else if (j - dec2 < i - dec1)
    {
        if(!checkzero(n2))
        {
        for ( y1 = 0; y1 < y3 - y2  ; y1++)
        {
            addzero(n2);
            j++;
            y5++;
        }
        }
        
    }
    }
    if (((y2 <= y3) && (y2 != 0 && y3 != 0))|| (i==j))
    {
        
        for ( y1 = 0; y1 < 3; y1++)
        {
            addzero(n2);
            y5++;
        }
    }
    n5=copynumber(one);
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
    display();
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
    if (y2 + y3 != 0 ||  i==j)
    {
        n2=NULL;
        n2=evaluate->num;
        evaluate->num=NULL;
        while (n2->next != NULL)
        {
            n2=n2->next;
        }
        printf("%d %d ll", y5, y4);
        for ( y1 = 0; y1 < (y2 - y3 - y4 + y5); y1++)
        {
            if ( n2->prev==NULL)
            {
                n2->prev=copynumber(zero);
                n2->prev->next=n2;
            }
            
            n2=n2->prev;

        }
        
        if (y2 + y3 != 0 || i==j)
        {
        Number *l;
        l=(Number *)malloc(sizeof(Number));
        l->data='.';
        l->next=n2->next;
        l->next->prev=l;
        l->prev=n2;
        n2->next=l;

        }
        while (n2->prev != NULL)
        {
            n2=n2->prev;
        }
        evaluate->num=n2;

        
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
        if (q->data=='.')
        {
        q=q->next;
        }
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
void extras()
{
    Number *zero;
    zero=(Number *)malloc(sizeof(Number));
    zero->data=0;
    zero->next=zero->prev=NULL;
    int flag=0, dot=0;
    if (evaluate->num->data == '-')
    {
        flag = -1;
        evaluate->num=evaluate->num->next;
        evaluate->num->prev=NULL;
    }
    Number *q;
    q=evaluate->num;
    if (!checkzero(q))
    {
    while (q != NULL)
    {
        if (q->data == '.')
        {
            
            dot=-1;
        }
        
        q=q->next;
    }
    if (dot != -1 && !checkzero(evaluate->num))
    {
        q=evaluate->num;
        evaluate->num=NULL;
        while ( q->data == 0)
        {
            q=q->next;
            Number *y;
            y=q->prev;
            q->prev=NULL;
            free(y);
            y=NULL;
        
        }
        if (flag == -1)
        {
            q->prev=(Number *)malloc(sizeof(Number));
            q->prev->next=q;
            q=q->prev;
            q->data='-';
            q->prev=NULL;
            
        }
        evaluate->num=q;
        q=NULL;
    }
    
    if (dot == -1 && !checkzero(evaluate->num))
    {
        q=evaluate->num;
        evaluate->num=NULL;
        while (q->data != '.' && q->data == 0)
        {
            q=q->next;
            Number *y;
            y=q->prev;
            q->prev=NULL;
            free(y);
            y=NULL;
        
        }
        if (q->data == '.')
        {
            q->prev=copynumber(zero);
            q->prev->next=q;
            q=q->prev;
            q->prev=NULL;
        }
        if (flag == -1)
        {
            q->prev=(Number *)malloc(sizeof(Number));
            q->prev->next=q;
            q=q->prev;
            q->data='-';
            q->prev=NULL;
            
        }
        evaluate->num=q;
        q=NULL;
        
    }
    }
    else
    {
        free(evaluate->num);
        evaluate->num=copynumber(zero);
        q=NULL;
        
    }
}
int compare(Number *a, Number * b)
{
    
    while (a != NULL)
    {
        
        if (a->data == '-')
        {
            a=a->next;
        }
        if (b->data== '-')
        {
            b=b->next;
        }
        
        if(a->data > b->data)
        {
            return 1;
        }
        if (a->data < b->data)
        {
            return 0;
        }
        a=a->next;
        b=b->next;
        
        
    }
    return 8;
    
}