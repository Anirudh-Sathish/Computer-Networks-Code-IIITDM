#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ip
{
    // For saving the octet
    int octet[4];

    // For saving the binary versions of the octet
    int octet1[8];
    int octet2[8];
    int octet3[8];
    int octet4[8];
};

struct ip seperateAndSaveIp(struct ip input_addr , char* ip_addr)
{
    printf("The IP address input is %s \n",ip_addr);
    char *token = strtok(ip_addr, ".");
    int i = 0;
    int integral_value;
    while (token != NULL)
    {
        integral_value = atoi(token);
        //arr[i] = integral_value;
        input_addr.octet[i] = integral_value;
        i++; 
        token = strtok(NULL,".");
    }

    return input_addr;
}


int main()
{
    char ip_addr[32] = "123.0.0.0";
    
    struct ip userInput_ip;

    int i ;
    userInput_ip = seperateAndSaveIp(userInput_ip,ip_addr);
    for(i = 0 ; i < 4 ; i++)
    {
        printf("Octet %d : %d \n",i,userInput_ip.octet[i]);
    }
    int v1 = 5;
    int v2 = 7;
    printf("AND IS %d ",~v2);


}