#include<stdio.h>

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

int main()
{
    int p1,p2,p3;
    push(3);
    p1= peek();
    printf("The value is %d \n",p1);
    push(4);
    p2=peek();
    printf("The value is %d \n",p2);
    push(5);
    p3=peek();
    printf("The value is %d \n",p3);

    p1= pop();
    printf("The value is %d \n",p1);
    p2=pop();
    printf("The value is %d \n",p2);
    p3=pop();
    printf("The value is %d \n",p3);


    

}