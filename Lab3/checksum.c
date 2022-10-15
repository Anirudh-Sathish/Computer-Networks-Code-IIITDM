/*
        Lab 2 : Checksum 
        @Author : Anirudh Sathish 
*/

// Defining the header files 

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>


// Function to compliment an array 
char *findcompliment(char *array , int block)
{
    int i = 0 ;
    for(; i <block ; i++)
    {
        if(array[i] == '1')
        {
            array[i] = '0';
        }
        else if(array[i] == '0')
        {
            array[i] = '1';
        }
    }
    return array;
}

// Function ot perform binary addition on two arrays 
char *binaryAddition(char *array , char *msg , int block , int i )
{
    int t , carry , num1 , num2 , val ,j; 
    t = block-1 ;
    carry = 0 ;
    for(j = i+block-1; j >= i ; j--)
    {
        num1 = array[t]-48;
        num2 = msg[j]-48;
        val = num1+num2+carry;

        // Various cases 
        if(val == 0)
        {
            carry = 0 ;
            array[t] = '0';
        }
        else if(val == 1)
        {
            carry = 0 ;
            array[t] = '1';
        }
        else if(val == 2)
        {
            carry = 1 ;
            array[t] = '0';
        }
        else if(val == 3)
        {
            carry = 1 ;
            array[t] = '1';
        }
        t--;
    }
    if(carry == 1)
    {
        char *newarr ;
        int l ;
        if(block > 0)
        {
            newarr = malloc(block*sizeof(char));
        }
        for(l = 0 ; l <block-1; l++)
        {
            newarr[l] = '0';
        }
        newarr[l] = '1';
        t = block-1 ;
        carry = 0;
        for(j = i+block-1; j >= i ; j--)
        {

            num1 = array[t]-48;
            num2 = newarr[t]-48;
            val = num1+num2+carry;

            // Various cases 
            if(val == 0)
           {
                carry = 0 ;
                array[t] = '0';
            }
            else if(val == 1)
           {
                carry = 0 ;
                array[t] = '1';
            }
            else if(val == 2)
            {
                carry = 1 ;
                array[t] = '0';
            }
            else if(val == 3)
           {
                carry = 1 ;
                array[t] = '1';
            }
            t--;
        }
    }
    return array;
}
// Function to find the checksum resultant encoded array
char *findCheckSumResult(char *msg , int msgLen , int totalLen , int block)
{
    char *array ;
    char *res;
    int i ;

    // Initalizing an array to hold the final addition value 
    if(block>0)
    {
        array = malloc(block*sizeof(char));
    }
    for(i = 0 ; i <block ; i++)
    {
        array[i] = '0';
    }

    int j, t , carry ;
    for( i = 0 ; i<msgLen ;)
    {
        // Perform binary addition on the part blocks 
        array = binaryAddition(array , msg , block , i);
        i = i+block;
    }
    char *afterComplement ;
    afterComplement = findcompliment(array,block);
    printf("The array to be appended is %s \n",afterComplement);

    if(totalLen > 0)
    {
        res = malloc(totalLen*sizeof(char));
    }
    for(i = 0 ; i < msgLen; i++)
    {
        res[i] = msg[i];
    }
    j = 0 ;
    for ( ; i < totalLen ; i++)
    {
        res[i] = array[j];
        j++;
    }
    return res;
}

int VerifyCheckSum(char *Checkmsg , int msgLen , int totalLen , int block)
{
    char *array ;
    char *res;
    int i ;

    // Initalizing an array to hold the final addition value 
    if(block>0)
    {
        array = malloc(block*sizeof(char));
    }
    for(i = 0 ; i <block ; i++)
    {
        array[i] = '0';
    }

    int j, t , carry ;
    for( i = 0 ; i<msgLen ;)
    {
        // Perform binary addition on the part blocks 
        array = binaryAddition(array , Checkmsg , block , i);
        i = i+block;
    }
    char *afterComplement ;
    afterComplement = findcompliment(array,block);
    t = 0 ;
    for(; i <totalLen ;i++)
    {
        if(Checkmsg[i] != afterComplement[t])
        {
            return 0;
        }
        t++;
    }
    return 1;
}

int main()
{
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

    totalLen = total_msg_Len+blockdiv;
    printf("The new message is %s \n", newMsg);

    resultant = findCheckSumResult(newMsg,total_msg_Len,totalLen,blockdiv);

    printf("The encoded array for checksum is %s \n",resultant);

    /*-------------------------------------------------------------------------------*/
    /*--------------------Receiver's Side --------------------------------------*/
     // Initalising 
    char * checkmsg ;
    if(totalLen > 0)
    {
        checkmsg = malloc(totalLen * sizeof(char));
    }

    printf("Enter the message you recieved , so that it can be checked for Correctness according to Checksum \n");
    scanf("%s",checkmsg);
    // CheckingLen
    int checkmsgLen = strlen(checkmsg);
    int value = VerifyCheckSum(checkmsg,total_msg_Len,checkmsgLen,blockdiv);
    if(value == 0)
    {
        printf("The message has become corrupted \n");
    }
    else if(value == 1)
    {
        printf("The message is not corrupted \n");
    }

    return 0;
    
}
