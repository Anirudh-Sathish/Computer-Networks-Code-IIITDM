/* Anirudh Sathish */
/* Bit Stuffing
   CN LAB 4
   */

// Write comments 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*Add flag at the begining and end */
char *insertFlag(char *msg , int msgLen)
{
    char flag[8] = "01111110";

    // Insert the flag at the end and the begining of the message 
    char *afterFlagInsertionMsg ;
    int totalLen = msgLen+16;

    // Allocating memory to the message 
    if(totalLen >0)
    {
        afterFlagInsertionMsg = malloc(totalLen*sizeof(char));
    }
    
    int i = 0,t = 0;
    // Inerting the flag at the begining 
    for(; i < 8 ; i++)
    {
        afterFlagInsertionMsg[i] = flag[i];
    }
    // Placing the data 
    for(;i<msgLen+8;i++,t++)
    {
        afterFlagInsertionMsg[i] = msg[t];
    }
    // Inserting the flag at the end 
    for(t = 0;i<msgLen+16;i++,t++)
    {
        afterFlagInsertionMsg[i] = flag[t];
    }
    return afterFlagInsertionMsg;
}
/* bitStuffMe()
   To add bit stuffs */

char *bitStuffMe(char *msg , int len)
{
    struct Node *curr = NULL , *head = NULL;
    int i ;
    int consecutive_one_Counter = 0 ;
    char prev ='0',curr_char ='0', zero = '0';
    int count = 0 ;

    int see1 = 0 , one_count = 0 ;

    // For finding the length of the resultant array 
    for(i = 8 ; i < len-8 ; i++)
    {
        // Check if there are five consecutive_ones 
        // Maintain a curr and prev 
        curr_char = msg[i];
        if(see1 == 0 && curr_char == '1')
        {
            see1 = 1;
            one_count = 1;
        }
        else if(see1 == 1 && curr_char == '0')
        {
            see1 = 0 ;
            one_count = 0;
        }
        else if(see1 == 1 && curr_char == '1')
        {
            one_count +=1;
        }
        if(one_count == 5)
        {
            printf("The index here is %d \n",i-8);
            count++;
            one_count = 0 ;
        }
    }

    char *resultant ;

    len = len+count;
    if(len > 0)
    {
        resultant = malloc(len*sizeof(char));
    }
    consecutive_one_Counter = 0 ;
    see1 = 0 , one_count = 0 ;
    int t = 0;

    // For the first 8 flag bits 
    for( i = 0 ; i < 8 ; i++)
    {
        resultant[t] = msg[i];
        t++;
    }

    for(i = 8 ; i < len-8 ; i++)
    {
        // Check if there are five consecutive_ones 
        // Maintain a curr and prev 
        curr_char = msg[i];
        resultant[t] = msg[i];
        if(see1 == 0 && curr_char == '1')
        {
            see1 = 1;
            one_count = 1;
        }
        else if(see1 == 1 && curr_char == '0')
        {
            see1 = 0 ;
            one_count = 0;
        }
        else if(see1 == 1 && curr_char == '1')
        {
            one_count +=1;
        }
        if(one_count == 5)
        {
            one_count = 0 ;
            t++;
            resultant[t] = zero;
        }
      
        t++;
    }
    // For the final 8 flag bits 
    for( i = len-8 ; i < len ; i++)
    {
        resultant[t] = msg[i];
        t++;
    }

    return resultant;
}

int main()
{
    /* Taking Input 
       */
    char * message;
    int inputLen ;
    printf("Enter the length of your message \n");
    scanf("%d" ,&inputLen);

    if(inputLen>0)
    {
        message = malloc(inputLen*sizeof(char));
    }

    printf("Enter the message \n");
    scanf("%s",message);

    message = insertFlag(message,inputLen);
    printf("The message after flag addition is %s \n",message);



    char *bitstuffedres ;
    int totalLen = inputLen+16;
    bitstuffedres = bitStuffMe(message,totalLen);
    printf("The resultant \n%s \n",bitstuffedres);
}
