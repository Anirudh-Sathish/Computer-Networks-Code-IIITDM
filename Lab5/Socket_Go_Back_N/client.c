// Client Side 

// Currently gives out cummulative acknowledgement

// Try mixing it up to include independent acknolwedgement 
// Also add a timer feature 



// Header Files 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>


// To determine the dynamic window allowed 
int WindowFunc(int i , int WindowSize , int FrameCount)
{
    if(FrameCount < WindowSize)
    {
        return FrameCount;
    }
    else
    {
        if(WindowSize +i < FrameCount)
        {
            return (WindowSize+i);
        }
        else
        {
            return FrameCount;
        }
    }
}



int main()
{
	int clientSocket_fd ;
	char send_data[50], recv_data[50];
	struct sockaddr_in serverAddress ;
	printf("\n \n The client has started running \n ");

    int TotalFrameCount ;
    int WindowSize ;
    
    // Taking input
    printf("Enter the total number of frames \n");
    scanf("%d",&TotalFrameCount);
    printf("Enter the frame size \n ");
    scanf("%d",&WindowSize);

	
	// Trying to establish connection 
	clientSocket_fd = socket(AF_INET,SOCK_STREAM,0);
	
	if(clientSocket_fd == -1)
	{
		printf("Error  , now exiting ");
		exit(-1);
	}
	int portNo;
	printf("Enter the port number \n");
	scanf("%d",&portNo);

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons( portNo);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	bzero(&(serverAddress.sin_zero),8);

	int connection_fd;
	int size ;
	size = sizeof(struct sockaddr);
	connection_fd = connect(clientSocket_fd , (struct sockaddr*)&serverAddress ,size); 

	if(connection_fd == -1)
	{
  		printf("Exit due to error\n");
  		exit(-1);
  	}
  	
  	int packetNo;
  	int DataToBeSent;
  	int count , i;
	int arr_1[TotalFrameCount];
	int arr_2[TotalFrameCount];
    for(i = 0 ; i < TotalFrameCount;i++)
    {
        printf("The packet number is : %d \n",i );
        arr_1[i] = i;
  	 	printf("Enter data \n ");
  	 	scanf("%d",&arr_2[i]);   
    }
    int start = 0 ;
    int End = 0 ;
    int keepCount ;


    int WindowIllusion = WindowFunc(start,WindowSize,TotalFrameCount);
    while(1)
  	{
        for(i = start ; i < WindowIllusion;i++)
        {
            printf("\n ------------------------------------------------ \n");
            printf("Packet number: %d \n",i );
  	 	    printf("Data :  %d \n ",arr_2[i]);  
  	
        }
        
        // To send it 
        for(i = start ; i< WindowIllusion ; i++)
        {
            // Sending the value to server 
  	 	    send(clientSocket_fd ,&arr_1[i],sizeof(arr_1[i]),0);
  	 	    send(clientSocket_fd ,&arr_2[i] , sizeof(arr_2[i]),0);
        }

        keepCount = i ;

        
        //printf("\nHere now \n");
  	 	recv(clientSocket_fd , &count,sizeof(count),0);
        
        

  	 	i = recv(clientSocket_fd, recv_data , 50 , 0 );
  	 	recv_data[i] = '\0';
  	 	printf(" \n %s %d",recv_data,count);
        int length = strlen(recv_data);
        //printf("\nThe length is %d \n",length);           

        // If acknowledgement is recived it should become the bottom value
        if(length <= 4)
        {
            start = keepCount;
            WindowIllusion = WindowFunc(count,WindowSize,TotalFrameCount);
            //printf("Start to %d \n",start);
            //printf("The illusion is %d \n",WindowIllusion);
        }
        else
        {
            start = count;
        }

        if(start == TotalFrameCount)
        {
            break;
        }
        
  	}
    while(1)
    {
        int send_z =-1;
        send(clientSocket_fd ,&send_z,sizeof(send_z),0);
        printf("\nWaiting for acknowledgemnet \n");
        recv(clientSocket_fd , &count,sizeof(count),0);     
  	    i = recv(clientSocket_fd, recv_data , 50 , 0 );
  	    recv_data[i] = '\0';
  	    printf(" \n %s %d",recv_data,count);
        
        int fin_len = strlen(recv_data);
        if(fin_len <= 4)
        {
            break;
        }
    }

  	close(clientSocket_fd); 	 
  	return 0 ;
}