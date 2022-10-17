#include<stdio.h>
#include<stdlib.h>

struct route
{
    char startingIp[32];
    char LastIp[32];
    char DirectBroadcast[32];
    char LimitedBroadcast[32] ;
    int interface;
    char subnetMask[32];
};

