// @ Author : Anirudh Sathish 

// Go back N Simulation 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


int *Rec(int *window , int N,int start)
{
// Validate input
	int j ;
	printf(" \n------------------------------------------------ \n\n ");
	for(	j = 0 ; j < N ; j++)
	{
		if(window[j] > 0)
		{
			printf("ACK %d \n",start+j+1);
			printf("Data %d \n",window[j]);
			window[j] = 0;
		}
		else
		{
			window[j] = -2;
		}

	}
	printf(" \n------------------------------------------------ \n\n ");
	return window;

}

int *Channel(int mode,int *array, int N,int start)
{
// Mode 0 is gets code from sende
	int decider ,j;

	printf(" \n------------------------------------------------ \n\n ");
	//printf("In channel \n ");
	for(	j = 0 ; j < N ; j++)
	{
		// creted noise 
		decider = rand()%2;
		if(decider ==0)
		{ 
			array[j] = -1;}
			//printf("%d \n",array[j]);
		}

		// Now send the array to the rec
	int *res = Rec(array,N,start);
	return res ;
}

int main()
{
	int msgArray[10] = {5,6,7,8,9,20,34,56,22,12};
	int i,j;
	int N = 3;
	//Replace 10 by message array length
	int start = 0 ;
	int windowEnd = N ;
	int windowArray[N] ;

	int value ;
	int changeValue ;
	changeValue = 10-N;
	int t = N;
	int *arr; 	
	while(start !=10 && t > 0)
	{

		if(start>changeValue)
		{
  			t = N-(start-changeValue);
		}
		printf("Sending the array \n");
		for(	j = 0 ; j < t ; j++)
		{
			windowArray[j] = msgArray[j+start];
			printf("%d \n",windowArray[j]);

		}

		// Send the array
 		arr = Channel(0,windowArray,t,start);



		for(	j = 0 ; j < t ; j++)
		{
			if(arr[j] ==0)
			{
				start +=1;
	 		}
			else
			{
				break;
			}
		}
		
 
		
	}

}
