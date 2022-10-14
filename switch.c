/*
Anirudh Sathish 
CS20B1125 
CN Lab 3
Switch Case */

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


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
 
void CRC()
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
}

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

void VRC()
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
}

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


void LRC()
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
}

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

void CheckSum()
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
}

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

void Hamming()
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

int main()
{
    int option ;
    do
    {
        printf("Chose an option \n");
        printf("Press 1 for CRC with even Parity \n");
        printf("Press 2 for VRC with even Parity \n");
        printf("Press 3 for LRC with even Parity \n");
        printf("Press 4 for Checksum \n");
        printf("Press 5 for Hamming  \n");
        printf("Press 6 for Exit \n");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                // do CRC
                CRC(); 
                break;
            case 2:
                // do VRC
                VRC();
                break;
            case 3:
                // do LRC
                LRC();
                break;
            case 4:
                // do Checksum
                CheckSum(); 
                break;
            case 5:
                // do Checksum
                Hamming(); 
                break;
            case 6:
                // Exit 
                printf("You have decided to exit \n");
                break;
            default:
                // Wrong input 
                printf("You have entered the wrong input , Chose right");
                break;
        }
       
    } while (option != 6);
    
}