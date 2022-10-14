//@Author : Anirudh Sathish 

// Question : Selective Repeat Simulation.

#include<stdio.h>
#include<stdbool.h>

int main()
{


    int FrameCount;
    printf("\nEnter Frame Count : ");
    scanf("%d", &FrameCount);

    int truth ;


    int windowSize ;
    int test, sent_array[100], k=0;

    bool processComplete = false ; // indicating false
    printf("\nEnter the sliding window size: ");
    scanf("%d", &windowSize);

    int window[windowSize];

    char ch;

    for(int i = 1; i <= FrameCount; )
    {
        processComplete = false;
        printf("\n--------Server Side --------\n");

        for (int j = i; j <= FrameCount && j <= i+windowSize-1; j++)
        {   
            printf("\nSent frame: %d", j);
            sent_array[k++] = j;
        }

        for(int h = 0; h<windowSize; h++)
        {
            window[h] = 0;
        }  

        while(processComplete == false)
        {
            processComplete = true;
            printf("\n\n--------Client Side --------\n");

            for (int j = i; j <= FrameCount && j <= i+windowSize-1; j++)
            {   
                if(window[j-i] == 0) 
                {
                    printf("\nAcknowledgement for frame %d ( 1-Yes | 0-No ): ", j);
                    scanf("%d", &window[j-i]);

                    if(window[j-i] == 0)  sent_array[k++] = j;

                    truth *= window[j-i];
                    if(truth == 1)
                    {
                        processComplete = true;
                    }
                    else
                    {
                        processComplete = false;
                    }
                }
            }
        }
        i += windowSize;
    }

    printf("\nAll frames are received\n");
    printf("\nThe Frames which are sent are in the order : ");
    for(int i = 0; i<k; i++) 
    {
        printf("%d ", sent_array[i]);
    }
    printf("\n");

    return 0;
}