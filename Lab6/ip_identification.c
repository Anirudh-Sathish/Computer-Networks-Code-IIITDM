// @Author : Anirudh Sathish 
// RollNo : CS20B1125 

// Question 1 

/*
1.
Write a program to identify
the class of a given IP address.
Prompt the user to enter an IP address,
validate the IP address and identify its class. 
Convert the given IP address to
binary;
based on the IP address identify the class
and display the output.
*/


// Defining header files 
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

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

void classTestForIP(int classCheckInteger)
{
    if(classCheckInteger == 0)
    {
        printf("This is reserved \n");
    }
    else if(classCheckInteger >0 && classCheckInteger <127)
    {
        printf("This is CLASS A \n");
    }
    else if(classCheckInteger == 127)
    {
        printf("Kept for experimental purpose \n");
    }
    else if(classCheckInteger > 127 && classCheckInteger < 192)
    {
        printf("This is class B \n ");
    }
    else if(classCheckInteger > 191 && classCheckInteger < 224)
    {
        printf("This is class C \n");
    }
    else if(classCheckInteger > 223 && classCheckInteger < 240)
    {
        printf("This is class D \n ");
    }
    else if(classCheckInteger > 239 && classCheckInteger < 255)
    {
        printf("This is class E \n ");
    }
    else
    {
        printf("This is for local use \n");
    }
}

// Class Check 
void FindIpClass(char *ip_addr)
{

    // Negative inputs and size greater than 255
    int length_ip = strlen(ip_addr);
    
    int part_count ;
    part_count = 0 ;

    int res_array[32];
    char *token = strtok(ip_addr, ".");
    
    // TO check Class of IP
    int classCheckInteger = atoi(token);

    classTestForIP(classCheckInteger);

    int integral_value ,i;
    integral_value = 0;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    int index = 0 ;
    while (token != NULL)
    {
        integral_value = atoi(token);
        integer2Binary(integral_value,res_array,index);
        part_count++;
        index = index+8;
        token = strtok(NULL, ".");
    }

    printf("\n");
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
    // Validate the ip address
    // Format : p.q.r.s
    bool validity = validateInput(ip_address);
    if(validity == false)
    {
        printf("Wrong input \n");
        return 0;
    }

    // Proceed to check the class of the ip address 
    FindIpClass(ip_address_copy);


}

