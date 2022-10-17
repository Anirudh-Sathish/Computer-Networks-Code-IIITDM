// @Author : Anirudh Sathish
// @ROll No : CS20B1125
// Enter ip of the syntax 12.0.0.0 or 150.0.0.0 or 200.0.0.0 as given in question

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#define MAX 8

int stack[MAX];
int top = -1;



void push( int item)
{
    if(top == MAX-1)
    {
        printf("Stack is full \n");
    }
    else
    {
        top+=1;
        stack[top]= item;
    }
}
int pop()
{
    if(top == -1)
    {
        printf("Stack is empty \n");
        return 0;
    }
    else
    {
        int item = stack[top];
        stack[top] = -1;
        top-=1;
        return item;
    }
    return 0;
}
int peek()
{
    return top;
}
int integer2Binary(int num)
{
    int rem;
    while(num != 0)
    {
        rem = num%2;
        push(rem);
        num = num/2;
    }
}
int *integer2BinaryMain(int num)
{
    integer2Binary(num);
    int bitsCount = peek()+1;
    int bitsPadded = 8 -bitsCount; 
    
    int ele;
    // array of integers
    int *binArray;
    binArray = malloc(8*sizeof(int));
    int i =0;
    
    // Pad extra bits if they are not present 
    if(bitsPadded != 0 )
    {
        for(; i < bitsPadded ; i++)
        {
            binArray[i] = 0 ;
        }
    }
    for(; i < 8; i++)
    {
        binArray[i] = pop();
    }
    

    printf("The binary array is \n");
    for( i = 0 ; i < 8 ; i++)
    {
        printf("%d",binArray[i]);
    }

    printf("\n");
    return binArray;
}
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

// Class Check 
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

char subnetMask[32];

struct ip DetermineSubnetMask(int subnetBit,int HostIDBit, struct ip subnetMask , int networkIDbit)
{
    if(networkIDbit == 8)
    {
        subnetMask.octet[0] = 255;
        
        // Second octet
        if(subnetBit > 16)
        {
            subnetMask.octet[1] = 255;
            subnetMask.octet[2] = 255;
            int oct_value = 24-subnetBit;
            int i , sum = 0;
            for(i = 7 ; i >= oct_value; i--)
            {
                sum+=pow(2,i);
            }
            subnetMask.octet[3] = sum;
        }
        else if(subnetBit == 16)
        {
            subnetMask.octet[2] = 255;
            subnetMask.octet[3] = 255;
            subnetMask.octet[4] = 0;
        }
        else if(subnetBit >8 && subnetBit<16)
        {
            subnetMask.octet[1] = 255;
            int oct_value = 16-subnetBit;
            int i , sum = 0;
            for(i = 7 ; i >= oct_value; i--)
            {
                sum+=pow(2,i);
            }
            subnetMask.octet[2] = sum;
            subnetMask.octet[3] = 0;
        }
        else if(subnetBit == 8)
        {
            subnetMask.octet[1] = 255;
            subnetMask.octet[2] = 0;
            subnetMask.octet[3] = 0;
        }
        else if(subnetBit < 8)
        {
            int oct_value = 8-subnetBit;
            int i , sum = 0;
            for(i = 7 ; i >= oct_value; i--)
            {
                sum+=pow(2,i);
            }
            subnetMask.octet[1] = sum;
            subnetMask.octet[2] = 0;     
            subnetMask.octet[3] = 0;       
        }

    }
    else if(networkIDbit == 16)
    {
        subnetMask.octet[0] = 255;
        subnetMask.octet[1] = 255;
        
        if(subnetBit >8 && subnetBit<16)
        {
            subnetMask.octet[2] = 255;
            int oct_value = 16-subnetBit;
            int i , sum = 0;
            for(i = 7 ; i >= oct_value; i--)
            {
                sum+=pow(2,i);
            }
            subnetMask.octet[3] = sum;
        }
        else if(subnetBit == 8)
        {
            subnetMask.octet[2] = 255;
            subnetMask.octet[3] = 0;
        }
        else if(subnetBit < 8)
        {
            int oct_value = 8-subnetBit;
            int i , sum = 0;
            for(i = 7 ; i >= oct_value; i--)
            {
                sum+=pow(2,i);
            }
            subnetMask.octet[2] = sum;
            subnetMask.octet[3] = 0;
        }
    }
    else if(networkIDbit == 24 )
    {
        subnetMask.octet[0] = 255;
        subnetMask.octet[1] = 255;
        subnetMask.octet[2] = 255;

        if(subnetBit < 8)
        {
            int oct_value = 8-subnetBit;
            int i , sum = 0;
            for(i = 7 ; i >= oct_value; i--)
            {
                sum+=pow(2,i);
            }
            subnetMask.octet[3] = sum;
        }
    }
    return subnetMask;
}
struct ip complement(struct ip subnetMask , struct ip subnetMaskComplement)
{
    int i ;
    for(i = 0 ; i < 4 ;i++)
        subnetMaskComplement.octet[i] = 255 -subnetMask.octet[i];

    return subnetMaskComplement;  
}

struct route
{
    struct ip startingIp;
    int interface;
    struct ip subnetMask;
};

void Subnet(int subnetCount , struct ip user_ip , struct ip subnetMask , struct ip subnetMaskCompliment , struct route RoutingTable[])
{

    struct ip firstAddresses[subnetCount];
    struct ip lastAddresses[subnetCount];
    
    int i,j , val ,val2,val3;
    int carry = 0;
    int flag = 1;
    for(i = 0 ; i < 4 ; i++)
        firstAddresses[0].octet[i] = user_ip.octet[i];
    for(i = 0 ; i < subnetCount ; i++)
    {
        for(j = 0 ; j < 4 ; j++)
        {
            val2 = firstAddresses[i].octet[j];
            val3 = subnetMaskCompliment.octet[j] ;
            lastAddresses[i].octet[j] = val2 | val3 ; 
        }
            
        for(j = 3 ; j >=0  ; j--)
        {
            if(carry == 0 && flag == 1)
            {
                if(j == 3)
                {
                    val = lastAddresses[i].octet[j] +1;
                }
                else
                {
                    val = lastAddresses[i].octet[j] ;
                }
                if(val >255)
                {
                    val = 0 ;
                    carry = 1;
                    firstAddresses[i+1].octet[j] = val ;
                }
                else
                {
                    flag = 0;
                    carry = 0;
                    firstAddresses[i+1].octet[j] = val ;
                }
            }
            else if(carry == 1 && flag == 1)
            {
                val = lastAddresses[i].octet[j] + 1;
                if(val >255)
                {
                    val = 0 ;
                    carry = 1;
                    firstAddresses[i+1].octet[j] = val ;
                }
                else
                {
                    carry = 0;
                    flag = 1;
                    firstAddresses[i+1].octet[j] = val ;
                }  
            }
            else if(flag == 0)
            {
                val = lastAddresses[i].octet[j] ;
                firstAddresses[i+1].octet[j] = val ;
            }
        }
        flag = 1;
        
    }
    int t;
    for (t = 0 ; t < subnetCount ; t++)
        {
            printf("Subnet %d : \n",t+1);
            RoutingTable[t].interface= t+1;
            printf("First Address : %d.%d.%d.%d \n",firstAddresses[t].octet[0],
            firstAddresses[t].octet[1],firstAddresses[t].octet[2],firstAddresses[t].octet[3] );
            RoutingTable[t].startingIp= firstAddresses[t];
            printf("Last : %d.%d.%d.%d \n",lastAddresses[t].octet[0],
            lastAddresses[t].octet[1],lastAddresses[t].octet[2],lastAddresses[t].octet[3] );
            printf("Direct BroadCast : %d.%d.%d.%d \n",lastAddresses[t].octet[0],
            lastAddresses[t].octet[1],lastAddresses[t].octet[2],lastAddresses[t].octet[3] );
            printf("Limited BroadCast : 255.255.255.255 \n");
            printf("Subnet mask : \n");
            printf("%d.%d.%d.%d \n",subnetMask.octet[0],subnetMask.octet[1],subnetMask.octet[2],subnetMask.octet[3]);   
            RoutingTable[t].subnetMask = subnetMask;
        }
        printf(" -------------Routing Table--------- \n");
        printf("Subnet ID     |SubnetMask     |Interface    \n");
        for(t = 0 ; t < subnetCount ; t++)
        {
            printf("%d.%d.%d.%d    ",RoutingTable[t].startingIp.octet[0],RoutingTable[t].startingIp.octet[1],RoutingTable[t].startingIp.octet[2],RoutingTable[t].startingIp.octet[3]);
            printf("%d.%d.%d.%d     ",RoutingTable[t].subnetMask.octet[0],RoutingTable[t].subnetMask.octet[1],RoutingTable[t].subnetMask.octet[2],RoutingTable[t].subnetMask.octet[3]);
            printf("Interface %d \n",RoutingTable[t].interface);
        }
    
    
    
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
    host_count = pow(2,host_id_bit) -(2*subnet_count);
    printf("Hosts : %d \n",host_count);

    printf("\n \n ----------------------------------- \n \n");
    struct ip subnet_mask , subnet_maskComplement;
    subnet_mask = DetermineSubnetMask(subnetBit,host_id_bit,subnet_mask,network_id_bit);
    subnet_maskComplement = complement(subnet_mask,subnet_maskComplement);
    
    struct route routingTable[subnet_count];
    struct ip userInput_ip;
    userInput_ip = seperateAndSaveIp(userInput_ip,ip_address_copy2);
    Subnet(subnet_count,userInput_ip,subnet_mask,subnet_maskComplement,routingTable);

}
