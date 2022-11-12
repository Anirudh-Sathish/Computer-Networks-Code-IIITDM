#include <stdio.h>
 
int highestPowerof2(unsigned int n)
{
    // Invalid input
    if (n < 1)
        return 0;
    int res = 1;
    // Try all powers starting from 2^1
    for (int i = 0; i < 8 * sizeof(unsigned int); i++) 
    {
        printf("I : %d \n",i);
        int curr = 1 << i;
        printf("Curr : %d \n",curr);
        // If current power is more than n, break
        if (curr > n)
            break;
        res = curr;
    }
    return res;
}
 
// Driver code
int main()
{
    int n = 10;
    printf("%d", highestPowerof2(n));
    return 0;
}