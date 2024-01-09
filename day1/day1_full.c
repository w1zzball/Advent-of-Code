#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int condenseToInts(char *buffer) // condenses e.g "two3five" -> 235
{
    const char *numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; //
    char *numLocation;
    for (int i = 0; i < 9; i++)
    {
        numLocation = strstr(buffer, numbers[i]);
        if (numLocation != NULL)
        {
            *(numLocation + 1) = i + 49; // change second letter in word to be the numeral value
            condenseToInts(buffer);
        }
        else
        {
        }
    }
    return 0;
}

FILE *fileOpenR(char *str) // wrapper for fopen
{
    FILE *fp;
    fp = fopen(str, "r");
    if (fp == NULL)
    {
        printf("error opening file\n");
    }
    else
    {
        printf("file opened sucessfully\n");
        return (fp);
    }
}

int lineToBuffer(FILE *fp, char *buffer, size_t bufferSize) // reads file into buffer line at time, returns 1 for nl,2 for EOF
{
    memset(buffer, 0, sizeof(char) * bufferSize); // clear memory
    char c;
    int i = 0;
    c = fgetc(fp);
    while (1)
    {

        if (c == 10)
        {
            return 1;
        }
        if (c == -1)
        {
            return 2;
        }
        else
        {
            buffer[i] = c;
            c = fgetc(fp);
            i++;
        }
    }
}

int sumBuffer(char *buffer)
{
    int num1, num2 = 0;
    for (int i = 0; i < strlen(buffer); i++)
    {
        char c = buffer[i];
        if (47 < c && c < 58)
        {
            c -= 48;       // convert char to numeric value
            if (num1 != 0) // if there is already a first number
            {
                num2 = c;
            }
            else
            {
                num1 = c;
            }
        }
    }
    return num2==0 ? 11 * num1 : 10 * num1 + num2;//covers the case of only 1 number
}

int main()
{
    int sum;
    int bufferSize = 60;
    char buffer[bufferSize];
    FILE *fp;
    fp = fileOpenR("./input.txt");
    while (lineToBuffer(fp, buffer, bufferSize) != 2)
    {
        condenseToInts(buffer);
        sum += sumBuffer(buffer);
    }
    printf("%d", sum);
}
