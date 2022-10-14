/*
        Lab 2 : LRC 
        @Author : Anirudh Sathish
        Roll_no : CS20B1125 
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>


// Function to invert 
char invert(char ch)
{
    if (ch =='1')
    {
        ch = '0';
    }
    else if(ch =='0')
    {
        ch ='1';
    }
    return ch;
}
// Function for LRC Even Parity 
char *LRCbyEvenParity(char *msg , int msgLen , int totalLen , int index)
{
    char *parityArray , *results;
    int i , j , mod , value , val , k  , indice;

    // Creating and initializing the parity array 
    if(index > 0)
    {
        parityArray = malloc(index*sizeof(char));
    }
    for(i = 0 ; i < index ; i++)
    {
        parityArray[i] = '0';
    }
    // Finding the actual parity bit values 
    for(j = 0 ; j < msgLen ; j++)
    {
        // If a one is noticed , then it is added to the respective parity bit array
        if(msg[j] == '1')
        {
            mod = j%index;
            value = parityArray[mod];
            val = invert(value);
            parityArray[mod] = val;

        }
    }

    if(totalLen >0)
    {
        results = malloc(totalLen*sizeof(char));
    }

    indice = 0 ;

    for(k = 0 ; k < msgLen;k++)
    {
        results[k] = msg[k];
    }
    for(;k <totalLen;k++)
    {
        results[k]= parityArray[indice];
        indice++;
    }
    printf("The parity array is %s \n",parityArray);
    return results;
}

// Function to check for the Sender if the message was LRC Even Parity
int CheckLRCEvenParity(char *checkMsg , int msgLen , int checkMsgLen , int index)
{
    char *parityArray , *results;
    int i , j , mod , value , val , k  , indice;

    // Creating and initializing the parity array 
    if(index > 0)
    {
        parityArray = malloc(index*sizeof(char));
    }
    for(i = 0 ; i < index ; i++)
    {
        parityArray[i] = '0';
    }

    for(j = 0 ; j < msgLen ; j++)
    {
        // If a one is noticed , then it is added to the respective parity bit array
        if(checkMsg[j] == '1')
        {
            mod = j%index;
            value = parityArray[mod];
            val = invert(value);
            parityArray[mod] = val;

        }
    }
    indice = 0;
    for(; j < checkMsgLen;j++)
    {
        if(checkMsg[j] != parityArray[indice])
        {
            return 0;
        }
        indice++;
    }
    return 1;
}


int main()
{
    // Taking the message and block input 
    char msg[100] ;
    int blockdiv , resultantmsgLen;
    char *resultant ;
    int val ,totalLen , rem; 
    char *newMsg ;
    int k ;
    int total_msg_Len , index , truth ;

    // Taking input from the user
    printf("Enter the message \n");
    scanf("%s",msg);
    printf("Enter the block size \n");
    scanf("%d",&blockdiv);

    // Finding the resultant lengths
    int msgLen = strlen(msg);
    rem = msgLen%blockdiv;
    
    // If message length is not a multiple of block , we have to append zeros
    //equal to the number of remainders
    total_msg_Len = msgLen+rem;
    printf("The Final message array length is %d \n",total_msg_Len);
    int phi = 0;

    // Creating the array 
    if(total_msg_Len > 0)
    {
        newMsg = malloc(total_msg_Len*sizeof(char));
        k = 0;
        for( ; k < rem ; k++)
        {
            newMsg[k] = '0';
        }
        for(;k<total_msg_Len;k++)
        {
            newMsg[k] = msg[phi];
            phi++;
        }
    }
    val = total_msg_Len/blockdiv;

    index = blockdiv;

    printf("The new message is %s \n", newMsg);

    totalLen = total_msg_Len+index;
    printf("The total length is %d \n",totalLen);

    resultant = LRCbyEvenParity(newMsg,total_msg_Len,totalLen,index);
    printf("The resultant array even parity encoded array is %s \n",resultant);

/* -------------------------------------------------------------------------*/
/*------------------------Reciever Side --------------------------*/
     // Initalising 
    char * checkmsg ;
    if(totalLen > 0)
    {
        checkmsg = malloc(totalLen * sizeof(char));
    }

    printf("Enter the message you recieved , so that it can be checked for Correctness according to LRC even parity \n");
    scanf("%s",checkmsg);
    // CheckingLen
    int checkmsgLen = strlen(checkmsg);
    truth = CheckLRCEvenParity(checkmsg,total_msg_Len,checkmsgLen,index);
    if(truth == 1)
    {
        printf("Value not corrupted \n");
    }
    else{
        printf("Corrupted message !!!! \n");
    }
    return 0;    
}