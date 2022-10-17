#include<stdio.h>
#include<stdlib.h>
#define MAX 8

int stack[MAX];
int top = -1;

void push( int item)
{
    if(top == MAX-1)
    {
        printf("Stack is full \n");
    }
    else
    {
        top+=1;
        stack[top]= item;
    }
}
int pop()
{
    if(top == -1)
    {
        printf("Stack is empty \n");
        return 0;
    }
    else
    {
        int item = stack[top];
        stack[top] = -1;
        top-=1;
        return item;
    }
    return 0;
}
int peek()
{
    return top;
}


int integer2Binary(int num)
{
    int rem;
    while(num != 0)
    {
        rem = num%2;
        push(rem);
        num = num/2;
    }
}

int *integer2BinaryMain(int num)
{
    integer2Binary(num);
    int bitsCount = peek()+1;
    int bitsPadded = 8 -bitsCount; 
    
    int ele;
    // array of integers
    int *binArray;
    binArray = malloc(8*sizeof(int));
    int i =0;
    
    // Pad extra bits if they are not present 
    if(bitsPadded != 0 )
    {
        for(; i < bitsPadded ; i++)
        {
            binArray[i] = 0 ;
        }
    }
    for(; i < 8; i++)
    {
        binArray[i] = pop();
    }
    

    printf("The binary array is \n");
    for( i = 0 ; i < 8 ; i++)
    {
        printf("%d",binArray[i]);
    }

    printf("\n");
    return binArray;
}


int main()
{
    int *arr , *arb ;

    arr = integer2BinaryMain(20);
    int i ;

    printf("Berack \n");
    for(i = 0 ; i < 8; i++)
    {
        printf("%d",arr[i]);
    }
    printf("\n");

    arb = integer2BinaryMain(255);
    printf("Arant \n");
    for(i = 0 ; i < 8; i++)
    {
        printf("%d",arb[i]);
    }
    printf("\n");

    
  
}