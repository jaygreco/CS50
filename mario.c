#include <stdio.h>
#include <string.h>

//Prints mario blocks of a specified height using array tricks.

//string reversing for print function
char* strrev(char *str)
{
    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

//Decide how long of an array is needed.
//add and extra byte for the null terminator
int arrayLength(int height) {
    return height + 2;
}

//internal print formatting function
//unsafe, no error checking is going on here
void _printPyramids(int height) {
    for (int i=0; i<height; i++) {
        //declare the 'framebuffer' array
        char fb[arrayLength(height)];

        //fill leading spaces first
        int spaces = height - i - 1;
        int index;
        for (index=0; index<spaces; index++) {
            fb[index] = ' ';
        }

        //fill blocks
        for (;(index-spaces)<i+1; index++) {
            fb[index] = '#';
        }

        //fill space
        fb[index++] = ' ';
        fb[index] = '\0';

        //print to console window (first half)
        printf("%s", fb);

        //todo: flip and print second half
        strrev(fb);
        printf("%s", fb);

        //print newline
        printf("\n");
    }
}

int main(void) {

    while (1) {
        int height = -1;;
        printf("Height: ");
        scanf("%d", &height);

        if ((height > 23) || (height < 0)) {
            //try again
            height = -1;
        }
        else {
            //print the blocks and exit
            _printPyramids(height);

            //exit
            break;
        }
    }
    return 0;
}