/*
@ Author : Anirudh Sathish 
@ Roll No : CS20B1125 

Consider a big single network of any class. Create and calculate the following:
1.      Divide the network into subnets.
2.      Total number of IP addresses
3.      Total number of hosts.
4.      Range of IP Address
5.      Direct and Limited broadcast
address.
6.      Routing Table (Subnet ID, Subnet Mask, and Interface)
*/


// Defining header files 
#define _OPEN_SYS_ITOA_EXT
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>


void printSyntaxErrorMessage()
{
    printf("There is an error in your IP Syntax.\n");
    printf("Reference example : 12.12.251.3 \n");
}

bool validateInput(char *ip_address)
{
    char *ip_addr = ip_address;
    // Negative inputs and size greater than 255
    int length_ip = strlen(ip_addr);

    if(length_ip>15 || length_ip < 7)
    {
        printSyntaxErrorMessage();
        return false;
    }
    // Required 255.255.255.255.0
    if(ip_addr[0] == '.' || ip_addr[length_ip-1] == '.')
    {
        printSyntaxErrorMessage();
        return false;   
    }


    int part_count = 0 ;
    char *token = strtok(ip_addr, ".");
    int integral_value;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        integral_value = atoi(token);
        if(integral_value >256 || integral_value < 0)
        {
            printSyntaxErrorMessage();
            return false;
        }
        part_count++;
        token = strtok(NULL, ".");
    }

    if(part_count != 4)
    {
        printSyntaxErrorMessage();
        return false;
    }


    return true;

}

void integer2Binary(int number,int *array, int index )
{
    int i ;
    int temp[8];
    i = 0 ;

    for(  ; number >0;i++)    
    {  
        temp[i]=number%2;    
        number=number/2;   
    }
    int i_history = i+index;      
    
    int i_curr = index+8  ;

    for(; i_curr > i_history; i_curr--)
    {
        array[i_curr] = 0;
        printf("%d",array[i_curr]);
    }
    i = i -1;
    for( i_curr = i_curr-1  ; i_curr>=index ;i_curr--)    
    {
        array[i_curr] = temp[i]; 
        printf("%d",array[i_curr]);  
        i = i-1;   
    }

}

int classTestForIP(int classCheckInteger)
{
    if(classCheckInteger == 0)
    {
        printf("This is reserved \n");
        return 0;
    }
    else if(classCheckInteger >0 && classCheckInteger <127)
    {
        printf("This is CLASS A \n");
        return 1;
    }
    else if(classCheckInteger == 127)
    {
        printf("Kept for experimental purpose \n");
        return 0;
    }
    else if(classCheckInteger > 127 && classCheckInteger < 192)
    {
        printf("This is class B \n ");
        return 2;
    }
    else if(classCheckInteger > 191 && classCheckInteger < 224)
    {
        printf("This is class C \n");
        return 3;
    }
    else if(classCheckInteger > 223 && classCheckInteger < 240)
    {
        printf("This is class D \n ");
        return 4;
    }
    else if(classCheckInteger > 239 && classCheckInteger < 255)
    {
        printf("This is class E \n ");
        return 5;
    }
    else
    {
        printf("This is for local use \n");
        return 0;
    }
}

// Class Check 
int FindIpClass(char *ip_addr)
{

    // Negative inputs and size greater than 255
    int length_ip = strlen(ip_addr);
    
    int part_count ;
    part_count = 0 ;

    int res_array[32];
    char *token = strtok(ip_addr, ".");
    
    // TO check Class of IP
    int classCheckInteger = atoi(token);

    int val = classTestForIP(classCheckInteger);

    int integral_value ,i;
    integral_value = 0;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    int index = 0 ;

    return val;
}

int checksubpow(int count)
{
    int rem;
    int bitValue = 0 ;
    while(count!=1)
    {
        rem = count %2;
        if(rem != 0)
        {
            return 0;
        }
        else
        {
            count = count/2;
            bitValue++;
        }
    }
    return bitValue; 
}


// Maintaining count of ?
void Subnet(char *ip_addr,int subnet_count,int subnetBit,int host_id_bit)
{
    int length_ip = strlen(ip_addr);
    
    int part_count ;
    part_count = 0 ;

    char res[32] ;
    char res2[32];
    char result[32]="";
    char result2[32] = "";
    char limitedBroadcast[20] = "255.255.255.255";
    char *resu;
    int val;
    
    int arr[4]; 
    char zero[3]="0";
    char *token = strtok(ip_addr, ".");
    int integral_value = 0 ;
    int i = 0;
    char final[32] = "";
    while (token != NULL)
    {
        integral_value = atoi(token);
        arr[i] = integral_value;
        i++; 
        token = strtok(NULL,".");
    }
    char dot[3] = ".";
    int class ;
    char *resu2;
    printf("The host bit count is %d \n",host_id_bit);
    if(host_id_bit <24 && host_id_bit >=16)
    {   
        char *resu = itoa(arr[0],res,10);
        strcat(resu,dot);
        strcat(result,resu);
        for(i = 1 ; i<4; i++)
        {
            if(arr[i] !=0)
            {
                printf("This ip is not being accepted according to the condition we are checking for \n");
                break;
            }
            resu = itoa(arr[i],res,10);
            if(i!=3)
            {
                strcat(resu,dot);
            }
            strcat(result,resu);

        }
        class = 1;
        // if subnet bits < 8 ?
        int j;
        char empty[32] = "";
        char hold_final[32]= "";
        char end[32] = "255";
        int val1;
        if(subnetBit <= 8)
        {
            // From i = 0 to subnetBit -1 
            for(i = subnet_count-1 ; i >= 0 ; i--)
            {
                strcpy(final,empty);
                // Starting arr[0]+"."+ 256- i*256/subnetBit + "." + "0"+"."+"0"
                resu = itoa(arr[0],res,10);
                strcat(final,resu);
                strcat(final,dot);
                strcpy(hold_final,final);
                val = 256 - (i+1)*(256/subnet_count);
                val1 = 256 - (i)*(256/subnet_count)-1;
                resu = itoa(val,res,10);
                resu2 = itoa(val1,res2,10);
                strcat(final,resu);
                strcat(final,dot);

                strcat(hold_final,resu2);
                strcat(hold_final,dot);

                
                
                for(j =2 ; j < 4 ; j++)
                {
                    strcat(final,zero);
                    strcat(hold_final,end);
                    if(j != 3)
                    {
                        strcat(final,dot);
                        strcat(hold_final,dot);
                    }
                }
                // Printing all neccesary information 
                printf("For Subnet %d :" , subnet_count - i);
                printf("\n Starting IP : %s \n", final );
                printf(" Final IP : %s \n",hold_final);
                printf(" Direct Broadcast : %s  \n",hold_final);
                printf(" Limited Broadcast : %s \n",limitedBroadcast);
                printf(" Range: %s - %s \n",final,hold_final);
                printf("\n----------------------------------- \n \n");

                
            }
            
        }
       
        // From i = 0 to subnetBit -1 
        // Starting arr[0]+"."+ "255"+ "." + "255"+ "." + 256- i*256/subnetBit  

        // if subnet bits = 24 
        // Reject 
    }
    else if (host_id_bit <16 && host_id_bit >=8)
    {
        // Deal with first and second octet 
        // Tokenize twice
        for(i = 0 ; i < 2 ; i++)
        {
            resu = itoa(arr[i],res,10);
            strcat(resu,dot);
            strcat(result,resu);

        }
        for(; i<4; i++)
        {
            if(arr[i] !=0)
            {
                printf("This ip is not being accepted according to the condition we are checking for \n");
                break;
            }
            resu = itoa(arr[i],res,10);
            if(i!=3)
            {
                strcat(resu,dot);
            }
            strcat(result,resu);

        }
        class = 2;
        
    }
    else if(host_id_bit >8 && host_id_bit >0)
    {
        // Deal with the first , second and third octet 
        // Tokenize thrice
        for(i = 0 ; i < 3 ; i++)
        {
            resu = itoa(arr[i],res,10);
            strcat(result,resu);
            strcat(result,dot);
        }
        for( ; i<4; i++)
        {
            if(arr[i] !=0)
            {
                printf("This ip is not being accepted according to the condition we are checking for \n");
                break;
            }
            resu = itoa(arr[i],res,10);
            if(i!=3)
            {
                strcat(resu,dot);
            }
            strcat(result,resu);

        }
        class = 3;
        printf("The starting IP is %s \n",result);

    }
    //Print the IP's of all the subnet =s 
}
int main()
{
    // extra space to check if error from users 
    char ip_address[25];
    char ip_address_copy[25];

    printf("\n------------------------------------------------------------\n");
    printf("Class Identification code \n");
    // Prompting the user to enter the ip address 
    printf("Enter the required ip address \n");
    scanf("%s",ip_address);
    
    strcpy(ip_address_copy,ip_address);
    char ip_address_copy2[25];
    strcpy(ip_address_copy2,ip_address);

    // Validate the ip address
    // Format : p.q.r.s
    bool validity = validateInput(ip_address);
    if(validity == false)
    {
        printf("Wrong input \n");
        return 0;
    }

    // Proceed to check the class of the ip address 
    int class_i = FindIpClass(ip_address_copy);

    printf("The class is %d \n",class_i);

    char class[1];
    int host_count , network_count ;
    int host_startingCount;
    int network_startingCount;
    int host_id_bit ;
    int network_id_bit;
    // Coverting the int representation of class to char
    if(class_i == 0)
    {
        printf("You cant subnet here \n");
        return 0;
    }
    else if(class_i == 1)
    {
        network_id_bit = 8;
        host_id_bit= 24;
    }
    else if(class_i == 2)
    {
        network_id_bit = 16;
        host_id_bit= 16;
    }
    else if(class_i == 3)
    {
        network_id_bit = 24;
        host_id_bit= 8;
    }
    else if(class_i == 4)
    {
        printf("You cant subnet here \n");
        return 0;
    }
    else if(class_i == 5)
    {
        printf("You cant subnet here \n");
        return 0;
    }

    

    // Now dealing with the subnets 
    int subnet_count;
    printf("Enter the number of subnets you want to create \n");
    scanf("%d",&subnet_count);

    int subnetBit;

    // Dont come here if subnet is 0
    if(subnet_count == 0 || subnet_count == 1)
    {
        printf("You gave subnets as 0");
        return 0;
    }
    // Check if subnet_count is a power of 2 
    else
    {
        subnetBit = checksubpow(subnet_count);
        if(subnetBit == 0)
        {
            printf("Cant subnet \n");
        }
        else
        {
            printf("The bits for subnet is %d \n" ,subnetBit);
            host_id_bit = host_id_bit-subnetBit;
            printf("The host id bits are %d \n",host_id_bit);
        }
    }
    
    

    Subnet(ip_address_copy2,subnet_count,subnetBit,host_id_bit);



}

