/* 
                    Lab 2 : Computer Networks
                    Assgn : Vertical Redundancy Check 
                    @Author : Anirudh Sathish 
*/

// Defeining the header files 
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>


// To Find the minimum of two integers 
int findmin( int a , int b)
{
    if( a> b)
    {
        return b ;
    }
    else
    {
        return a;
    }
}

// Function for the sender to Check if the recieved message satisfies even parity
int checkMessageEvenParity(char *checkmsg ,int block , int checkMsgLen)
{
    int i = 0 ;
    int j , t;
    t = 0;
    int count_1;
    int value_setter = 0;

    // Go parsing through whole 
    for(; i< checkMsgLen;)
    {
        count_1 = 0;
        // for the length of the block 
        for(t = i ; t < i+block ; t++)
        {
            if(checkmsg[t] == '1')
            {
                count_1++;
            }
        }
        // Odd number of 1's 
        if(count_1%2 != 0)
        {
            // odd number of 1's will imply , the bit should be 1 
            // If it is 0 , then the encoding is wrong 
            if(checkmsg[t] != '1')
            {
                return 0;
            }
            t++;
        }
        else
        {
            // even number of 1's will impy , the bit should be 0
            // If it is 1 , then the encoding is wrong
            if(checkmsg[t] == '1')
            {
                return 0;
            }
            t++;
        }
        i = t;
    }  
    return 1;
}


// Encoding by Even parity 
char *EvenParityarray(char * msg , int block , int TotalLen ,int msgLen)
{
    // To maintain a resultant encoded array 
    char * res ;
    if(TotalLen > 0)
    {
        res = malloc(TotalLen * sizeof(char));
    }
    // Parse through to set the resultant array values 
    int i = 0 ;
    int j ,t;
    t = 0;
    int value_setter = 0;
    int count_1 ;

    // Parsing through the message length 
    for(; i <msgLen ;)
    {
        // Variable to keep track of count of 1's
        count_1 = 0 ;


        // Finding the minimum of the msgLen and the iterator summed with blocklength 
        //Solving for the boundary case 
        value_setter = findmin(i+block,msgLen);

        //Finding the parity as well as the resultant encoded array
        for(j = i ; j < value_setter ; j++)
        {
            res[t] = msg[j];
            t++;
            // If 1 , then increase the count of 1's 
            if(msg[i] == '1')
            {
                count_1++;
            }
        }
        // If no of ones are odd -> set the resultant part as 1 
        if(count_1%2 != 0)
        {
            res[t] = '1';
        }
        // Even no of ones -> resultant part as 0
        else
        {
            res[t] ='0';
        }
        t++;
        // Jump i's value to that of j , since we have seen through all those elements
        i = j;
    }
    // return the resultant encoded array
    return res;
}

int main()
{
    // Taking the message and block input 
    char msg[100] ;
    int blockdiv , resultantmsgLen;
    char *resultant ;

    // Taking input from the user
    printf("Enter the message \n");
    scanf("%s",msg);
    printf("Enter the block size \n");
    scanf("%d",&blockdiv);

    // Finding the resultant lengths
    int msgLen = strlen(msg);
    int val ,totalLen , rem; 


    val = msgLen/blockdiv;
    rem = msgLen%blockdiv;
    char *newMsg ;
    int k ;
    // If message Length is not a multiple of block , then the totalLen has to be increased 
    int tl_msg;
    tl_msg = msgLen+rem;
    printf("The tl len is %d \n",tl_msg);
    int phi = 0;
    if(tl_msg > 0)
    {
        newMsg = malloc(tl_msg*sizeof(char));
        k = 0;
        for( ; k < rem ; k++)
        {
            newMsg[k] = '0';
        }
        for(;k<tl_msg;k++)
        {
            newMsg[k] = msg[phi];
            phi++;
        }
    }
    int msgLeni = tl_msg;
    printf("The new message len is %d \n",msgLeni);
    val = tl_msg/blockdiv;

    printf("The new message is %s \n", newMsg);

    totalLen = tl_msg+val;
    printf("The total length is %d \n",totalLen);
    resultant = EvenParityarray(newMsg,blockdiv,totalLen,tl_msg);

    printf("The resultant encoded array according to even parity should be %s \n",resultant);

    printf("Verification Code \n");

/*------------------------------------------------------------------------------*/
/*----------------------To check from the sender's side ------------------------*/
    
    // Initalising 
    char * checkmsg ;
    if(totalLen > 0)
    {
        checkmsg = malloc(totalLen * sizeof(char));
    }

    //Taking input 
    printf("Enter the message to verify \n");
    scanf("%s",checkmsg);

    // CheckingLen
    int checkmsgLen = strlen(checkmsg);
    int value = checkMessageEvenParity(checkmsg,blockdiv,checkmsgLen);
    if(value == 1)
    {
        printf("Value not corrupted \n");
    }
    else{
        printf("Corrupted message !!!! \n");
    }
    
    return 0;
}
