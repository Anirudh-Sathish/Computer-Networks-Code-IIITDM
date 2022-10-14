/* Code for Cyclic Redundacy Check*/

//including all the header files 
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

/*
    Defining the functions part
                                     */

//Appending zeroes function 
char *appendZeroes(char *msg , int msgLen , int newLen)
{
    char *arr;
    if(newLen>0)
    {
        arr = malloc(newLen*sizeof(char));
    }
    int i = 0;
    for(; i<newLen;i++)
    {
        if(i<msgLen)
        {
            arr[i] = *msg;
            msg++;
        }
        else
        {
            arr[i]='0';
        }
    }
    return arr;
}

char *getRemainder(char*res , char *key , int lenKey, int lenMsg ,int lenTotal)
{
    // Initalization 
    int i = 0 ;
    int j = 0 ;
    int t = 0 ;
    int k = 0 ;
    char *remainder ;
    if((lenKey-1>0))
    {
        remainder = malloc((lenKey-1)*sizeof(char));
    }
    
    // Applying the procedure 
    for(; i <lenMsg;i++)
    {
        if((*(res+i)) =='1')
        {
            for( j = i ; j < i+lenKey; j++)
            {
                t = j-i;
                if((*(res+j)) == key[t])
                {
                    (*(res+j)) ='0';
                }
                else
                {
                    (*(res+j)) = '1';
                }
            }
        }
    }
    // Obtaining the remainder 
    for(; i<lenTotal; i++)
    {
        remainder[k]= (*(res+i));
        k++;
    }
    return remainder;
}
 


//The main part 
int main()
{
    //Setting up the char strings to hold the message and the key 
 
    char msg[100] , key[40];


    printf("Enter the message ");
    scanf("%s",&msg);
    printf("Enter the key ");
    scanf("%s",&key);
    
    //Obtaining the lengths of the msg and the key part 
    int lenMsg,lenKey;
    lenMsg = strlen(msg);
    lenKey = strlen(key);

    //Appending the message with the lenKey-1 bits

    //Obtaining total length of the expected resultant 
    int lenTotal;
    lenTotal = lenMsg+lenKey;

    //initalizing a charcter array to hold the resultant of the append 
    // By having res pointing to the adress of the first element 
    char *res; 

    //initalizing this 
    if(lenTotal-1>0)
    {
        res = malloc((lenTotal-1)*sizeof(char));
    }
    
    // Now appending the required zeros to it 
    res = appendZeroes(msg,lenMsg,lenTotal-1);

    // for obtaining the remainder 

    char *remainder ;
    if((lenKey-1>0))
    {
        remainder = malloc((lenKey-1)*sizeof(char));
    }
    remainder = getRemainder(res,key,lenKey,lenMsg,lenTotal);
    printf("The remainder remainder is %s \n",remainder);

    res = strcat(msg,remainder);
    printf("The encoded message is %s \n",res); 
    printf("Enter the message u recieved ");
    scanf("%s",res);
    printf("Checking if it is the right message \n");

    //Checking if the remainder is 0 to ascertain the genuinity of the message 
    remainder = getRemainder(res,key,lenKey,lenMsg,lenTotal);
    printf("The remainder is %s \n",remainder);

    int lenrem = strlen(remainder);
    int val = 0 ;
    int i;

    for(i = 0 ; i<(lenKey-1);i++)
    {
        if(remainder[i] !='0')
        {
            val = 1;
        }
    }

    if(val == 0)
    {
        printf("The message you have recieved is correct \n");
    }
    else
    {
        printf("The message you have recieved seems to have been corrputed \n");
    }
    
    
    return 0;
}