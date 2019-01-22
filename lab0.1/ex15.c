#include <stdio.h>
float far2cel(float fahr){
    return (5.0/9.0)*(fahr-32);
}
int main()
{
    printf("Enter the temperature in Fahrenheit: \n");
    float fahr;
    scanf("%f", &fahr);
    printf("\n  %0.3f F = %0.3f C \n", fahr, far2cel(fahr));
}