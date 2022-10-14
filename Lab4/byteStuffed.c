/* Anirudh Sathish 
   CS20B1125
   */

/* Byte Stuffing */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Add flag at the begining and end */
char *insertFlag(char *msg , int msgLen , char *flag , int flagSize)
{


    // Insert the flag at the end and the begining of the message 
    char *afterFlagInsertionMsg ;
    int totalLen = msgLen+2*(flagSize);

    // Allocating memory to the message 
    if(totalLen >0)
    {
        afterFlagInsertionMsg = malloc(totalLen*sizeof(char));
    }
    
    int i = 0,t = 0;
    // Inerting the flag at the begining 
    for(; i < flagSize ; i++)
    {
        afterFlagInsertionMsg[i] = flag[i];
    }
    // Placing the data 
    for(;i<msgLen+flagSize;i++,t++)
    {
        afterFlagInsertionMsg[i] = msg[t];
    }
    // Inserting the flag at the end 
    for(t = 0;i<msgLen+2*flagSize;i++,t++)
    {
        afterFlagInsertionMsg[i] = flag[t];
    }
    return afterFlagInsertionMsg;
}

char *byteStuffed(char *msg , int len , char *flag , int flagSize)
{
    // Defining the escape sequence
    // Escape sequence will be inserted if flag is found in text 
    // In such case it will be inserted before the flag
    // Simmilarly if escape sequence is found in text 
    // Escape sequence will be pushed before it 
    char escapeSequence[8] = "11111110";

    //Defining the total Length 
    int totalLen = len;

    // Defining substrings 
    char *substring1 ,*substring2 , *flag_substring , *escape_substring;
    if(flagSize>0)
    {
        substring1 = malloc(flagSize*sizeof(char));
        flag_substring = malloc(flagSize*sizeof(char));
    }
    substring2 = malloc(8*sizeof(char));
    

    char *str1 = malloc(strlen(flag));
    char *str2 = malloc(strlen(escapeSequence));
    char *str3 = malloc(strlen(flag));
    char *str4 = malloc(strlen(escapeSequence));

    int ptrDistance ;
    // Check if there is any need for escape sequences to be inserted
    int count = 0 , i ,t = 0 , stringMatch;
    for(i = 0; i < len ; i++)
    {
        // Check i < len 
        if(i<len)
        {
            // Have a pointer at i 
            // And to a distance of t
            //Take a substring
            substring1 = strncpy(str1,msg+t,flagSize);
            // Take that substring and check if there is a match to
            // the flag 

            // To avoid dealing with the null character causing comparision errors 
            flag_substring = strncpy(str3,flag,flagSize);
            stringMatch = strcmp(substring1,flag_substring);
            
            if(stringMatch == 0)
            {
                // If there is a match , move up the count
                // Move the count by the escape sequence value
                count += 8;
                // Also , move the value of i , by flag
                // Same goes to t
                i+= flagSize;
                t+=flagSize;
            } 
        }

        // Check i < len 
        if(i<len)
        {
            // Have a pointer at i 
            // And to a distance of t
            //Take a substring
            substring2 = strncpy(str2,msg+t,8);
            // Take that substring and check if there is a match to
            // the flag 

            // To avoid dealing with the null character causing comparision errors 
            escape_substring = strncpy(str4,escapeSequence,8);
            
            stringMatch = strcmp(substring2,escape_substring);
            
            if(stringMatch == 0)
            {
                // If there is a match , move up the count
                // Move the count by the escape sequence value
                count += 8;
                // Also , move the value of i , by flag
                // Same goes to t
                i+= 8;
                t+=8;
            } 
        }
        t++;
    }

    printf("Count goes like %d \n",count);

    char *resultant ;
    int resultant_count = len+count;
    if(resultant_count >0)
    {
        resultant = malloc(resultant_count*sizeof(char));
    }
    printf("The resultant count is %d \n",resultant_count);
    t = 0 ;
    int k = 0;
    int change_occured = 0;

    char *substring3 ,*substring4 , *flag_substringi , *escape_substringi;
    if(flagSize>0)
    {
        substring1 = malloc(flagSize*sizeof(char));
        flag_substring = malloc(flagSize*sizeof(char));
    }
    substring4 = malloc(8*sizeof(char));
    

    char *str5 = malloc(strlen(flag));
    char *str6 = malloc(strlen(escapeSequence));
    char *str7 = malloc(strlen(flag));
    char *str8 = malloc(strlen(escapeSequence));
    for(i = 0; i < len ;)
    {
        // Check i < len 
        if(i<resultant_count && i+flagSize < resultant_count)
        {
            // Have a pointer at i 
            // And to a distance of t
            //Take a substring
            substring3 = strncpy(str5,msg+i,flagSize);
            // Take that substring and check if there is a match to
            // the flag 


            // To avoid dealing with the null character causing comparision errors 
            flag_substringi = strncpy(str7,flag,flagSize);
            stringMatch = strcmp(substring3,flag_substringi);
            
            if(stringMatch == 0)
            {
                //Now that match is found
                //Insert the escape sequence before the flag
                count = 8 ;
                k = 0;
                while(count !=0)
                {
                    resultant[t] = escapeSequence[k];
                    count--;
                    t++;
                    k++;
                }
                count = flagSize;
                while(count != 0 )
                {
                    resultant[t] = msg[i];
                    count--;
                    t++;
                    i++;
                }
                change_occured = 1;
            }
        }

        // Check i < len 
        if(i<resultant_count && change_occured == 0 && i+8<resultant_count)
        {
            // Have a pointer at i 
            // And to a distance of t
            //Take a substring
            substring4 = strncpy(str6,msg+i,8);
            // Take that substring and check if there is a match to
            // the flag 

            // To avoid dealing with the null character causing comparision errors 
            escape_substringi = strncpy(str8,escapeSequence,8);
            stringMatch = strcmp(substring4,escape_substringi);
            
            if(stringMatch == 0)
            {
                //Now that match is found
                //Insert the escape sequence before the flag
                count = 8 ;
                k = 0;
                while(count !=0)
                {
                    resultant[t] = escapeSequence[k];
                    count--;
                    t++;
                    k++;
                }
                count = 8;
                while(count != 0 )
                {
                    resultant[t] = msg[i];
                    count--;
                    t++;
                    i++;
                }
                change_occured = 1;
            }
            
        }
        if(change_occured == 1)
        {
            change_occured = 0;
        } 
        else
        {
            resultant[t] = msg[i];
            t++;
            i++;
        }
    }

    printf("The resultant after byte stuffing is %s \n",resultant);

    char *afterFlagMsg = insertFlag(resultant,resultant_count,flag , flagSize);
    printf("The after flag string is %s \n",afterFlagMsg);

    return afterFlagMsg;


}


int main()
{
    int dataSize ;
    printf("Enter the size of the data you want to enter  \n");
    scanf("%d",&dataSize);

    char *data;
    if(dataSize>0)
    {
        data = malloc(dataSize*sizeof(char));
    }
    printf("Enter the data \n");
    scanf("%s",data);
    printf("The data is %s  \n",data);

    int flagSize;
    printf("Enter the size of your flag \n");
    scanf("%d",&flagSize);

    char *flag;
    if(flagSize > 0)
    {
        flag = malloc(flagSize*sizeof(char));
    }
    printf("Enter the flag \n");
    scanf("%s",flag);
    

    int totalLen = dataSize+2*(flagSize);

    // Do byte stuffing 
    char *byteStuffedMsg = byteStuffed(data,dataSize,flag,flagSize);

}