/* Anirudh Sathish 
   CS20B1125
   */

/* Character Count */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *charCount( char *msg , int msglen , int blockNum)
{
    //Block length calculations 
    int blockLen = msglen/blockNum-1;
    char blockLength , blockfinalLength;
    blockLength = blockLen+'0';

    // Adding extra bits for the last block 
    int extra = msglen - (blockLen*blockNum);

    // Block len of the last block
    int last_blockLen = blockLen+extra;
    blockfinalLength = last_blockLen+'0';

    // TotalLen 
    int totalLen = msglen+blockNum;

    // Forming the required resultant 
    char *resultant;
    if(totalLen >0)
    {
        resultant = malloc(totalLen*sizeof(char));
    }
    int blockcount = 0;
    int i;
    int t = 0 ;
    if(blockNum == 1)
    {
        for(i = 0 ; i< totalLen ; i++)
        {
            if(i%blockLen == 0 )
            {
                resultant[i] = blockfinalLength+1;
            }
            else
            {
                resultant[i] = msg[t];
                t++; 
            }
        }
    }
    else
    {
        for(i = 0 ; i< totalLen ; i++)
        {
            if(i%(blockLen+1) == 0 && blockcount < blockNum-1)
            {
                resultant[i] = blockLength+1;
                blockcount++;
            }
            else if(i%(blockLen+1) == 0 && blockcount== blockNum-1)
            {
                resultant[i] = blockfinalLength+1;
                blockcount++;
            }
            else
            {
                resultant[i] = msg[t];
                t++; 
            }
        }
    } 

    printf("The resultant is %s \n",resultant);

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

    int blockNum;
    printf("Enter the number of blocks \n");
    scanf("%d",&blockNum);

    char *charCountResultant ;
    charCountResultant = charCount(data ,dataSize,blockNum);

}