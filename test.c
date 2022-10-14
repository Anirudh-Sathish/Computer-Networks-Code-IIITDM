
/* Anirudh Sathish 
   Lab 3 
   Hamming 
   CS20B1125
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


// If function returns 1 , then satisfies power 2 diviosion 
// Else returns 0
int isPow(int index , int length)
{
    int val = 1;
    int prg_ssr = 1 ; 
    while(val != index && prg_ssr< length)
    {
        val = pow(2,prg_ssr);
        prg_ssr++;
    }
    if(val == index)
    {
        return 1;
    }
    return 0;
}
int findParityBits(char *msg , int length)
{
    int parity_count = 0 ;
    int i = 1 ;
    int t ; 
    for(t = 0 ; t < length ; t++)
    {
        if(i == 1)
        {
            parity_count++;
            t--;
        }
        else
        {
            if(isPow(i,length) == 1)
            {
                parity_count++;
                t--;
            }
        }
        i++;
    } 
    printf("The parity count is %d \n",parity_count);
    return parity_count;

}

char XOR(char a , char b )
{
    char char_1 = '1';
    char char_0 = '0';

    if(a == b)
    {
        return char_0;
    }
    return char_1;
}

char flagfunc(char *msg , int index , int totalLen)
{
    int total_count = 0 ;

    int i = index ;
    char val ;
    if(index == 1)
    {
        while( i <= totalLen)
        {
            i = i+2;
            if( i <= totalLen)
            {
                if(total_count == 0)
                {
                    val = msg[totalLen-i];
                }
                else
                {
                    val = XOR(val, msg[totalLen-i]);
                }
            }
            total_count++;
        }
        return val;
    }
    int curr_count = 1 ;
    // For indexes greater than 2 

  
    while( i <= totalLen)
    {
        if(curr_count == 0)
        {
            curr_count++;
        }
        i = i+1 ;
        curr_count++;
        if(i <=totalLen && curr_count <=index && curr_count >= 0)
        {
            if(total_count == 0)
            {
                val = msg[totalLen-i];
            }
            else
            {
                
                val = XOR(val , msg[totalLen-i]);
            }
            total_count++;
        }
        else if(curr_count > index)
        {
            curr_count = index*(-1);
        }
    }
    return val; 
}

char *workonEven(char *msg , int msgLen , int parity_count)
{
    int totalLen = parity_count+ msgLen;
    // Creating an array to hold the result  
    char *resultant ; 
    if(totalLen > 0)
    {
        resultant = malloc(totalLen *sizeof(char));
    }
    int t = msgLen-1 , i ;
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i , msgLen) !=1)
        {
            resultant[totalLen-i] = msg[t];
            t--;
        }
    }
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i,msgLen) == 1)
        {
            char ch ;
            ch = flagfunc(resultant , i , totalLen);
            resultant[totalLen-i] = ch;
        }
    }
    return resultant;

}

char *workonOdd(char *msg , int msgLen , int parity_count)
{
    int totalLen = parity_count+ msgLen;
    // Creating an array to hold the result  
    char *resultant ; 
    if(totalLen > 0)
    {
        resultant = malloc(totalLen *sizeof(char));
    }
    int t = msgLen-1 , i ;
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i , msgLen) !=1)
        {
            resultant[totalLen-i] = msg[t];
            t--;
        }
    }
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i,msgLen) == 1)
        {
            char ch ;
            ch = flagfunc(resultant , i , totalLen);
            if (ch =='1')
            {
                ch = '0';
            }
            else if(ch == '0')
            {
                ch = '1';
            }
            resultant[totalLen-i] = ch;
        }
    }
    return resultant;

}

void errorcheck(char *parity , int parity_count)
{
    int i ,j;
    int summation_index = 0 ;
    int temp ;  
    for(i = 0 ; i < parity_count ; i++)
    {
        if(parity[i] == '1')
        {
            j = i+1;
            temp = pow(2,(parity_count-j));
            summation_index+= temp;
        }
        else if(parity[i] == '0')
        {
            summation_index+= 0;
        }
    }
    printf("The index where error is %d \n",summation_index);
    printf("This index is given in terms of Parity index \n");
    printf("In this case P%d \n",summation_index);
}
void VerifyHamming(char *msg , int totalLen , int parity_count , int msgLen)
{
    // holding a parity array 
    char *parity;
    if(parity_count > 0)
    {
        parity = malloc(parity_count*sizeof(char));
    }
    // Creating an array to hold the result  
    char *resultant ; 
    if(totalLen > 0)
    {
        resultant = malloc(totalLen *sizeof(char));
    }
    int i ;
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i , msgLen) !=1)
        {
            resultant[totalLen-i] = msg[totalLen-i];
        }
    }
    int inequality_count = 0 ;
    int t = 1; 
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i,msgLen) == 1)
        {
            resultant[totalLen-i] = flagfunc(resultant , i , totalLen);
            if(resultant[totalLen-i] != msg[totalLen-i])
            {
                inequality_count++;
                parity[parity_count-t] = '1';
            }
            else
            {
                parity[parity_count-t] = '0';
            }
            t++;
        }
    }
    printf("The parrity array is %s \n",parity);
    if(inequality_count > 0)
    {
        errorcheck(parity,parity_count);
    }
    else
    {
        printf("No errors \n");
    }
}

void VerifyHammingOddpar(char *msg , int totalLen , int parity_count , int msgLen)
{
    // holding a parity array 
    char *parity;
    if(parity_count > 0)
    {
        parity = malloc(parity_count*sizeof(char));
    }
    // Creating an array to hold the result  
    char *resultant ; 
    if(totalLen > 0)
    {
        resultant = malloc(totalLen *sizeof(char));
    }
    int i ;
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i , msgLen) !=1)
        {
            resultant[totalLen-i] = msg[totalLen-i];
        }
    }
    int inequality_count = 0 ;
    int t = 1; 
    for(i = 1 ; i < totalLen+1 ; i++)
    {
        if(isPow(i,msgLen) == 1)
        {
            resultant[totalLen-i] = flagfunc(resultant , i , totalLen);
            if(resultant[totalLen-i] != msg[totalLen-i])
            {
                inequality_count++;
                parity[parity_count-t] = '0';
            }
            else
            {
                parity[parity_count-t] = '1';
            }
            t++;
        }
    }
    printf("The parrity array is %s \n",parity);
    if(inequality_count > 0)
    {
        errorcheck(parity,parity_count);
    }
    else
    {
        printf("No errors \n");
    }
}

int main()
{
    int option ;
    printf("Press 1 for even Parity \n");
    printf("Press 2 for odd Parity \n");

    scanf("%d",&option);

    //Take parity input 
    // Getting input for the length of the message
    int length ;
    printf("Enter the length of the message u want to check hammings code ");
    scanf("%d", &length);

    // Intialising the message array 
    char *msg ; 
    if(length > 0)
    {
        msg = malloc(length*sizeof(char));
    }
    printf("Kindly enter the message to be checked \n");
    scanf("%s" ,msg);

    printf("the message recieved was %s \n" ,msg);

    int parity_count ;
    // Finds the parity bits 
    parity_count = findParityBits(msg , length);
    printf("The parity bit count is %d \n",parity_count);

    char *res;
    if(option == 1)
    {
        res = workonEven(msg , length , parity_count);
    }
    else if(option ==2)
    {
        res = workonOdd(msg , length , parity_count);
    }
    else
    {
        return 0;
    }
    
    printf("The Encoded message is %s \n",res);


    /* RECIEVERS SIDE VERIFICATION */
    char *recMessage ;
    int totalL = length + parity_count;

    if(totalL >0)
    {
       recMessage = malloc(totalL*sizeof(char));
    }
    printf("Enter message , we will check verification \n");
    scanf("%s",recMessage);

    if (option == 1)
    {
        VerifyHamming(recMessage,totalL,parity_count,length);
    }
    else if (option ==2)
    {
        VerifyHammingOddpar(recMessage,totalL,parity_count,length);
    }

}