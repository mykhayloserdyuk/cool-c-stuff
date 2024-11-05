#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    FILE *in = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[1]);
            printf("File not readable\n");
            exit(EXIT_FAILURE);
        }
    }

    int width = 0;
    int length = 0;
    bool valid = checkLab(in, &width, &length);
    if(valid){
        printf("Laberynth is valid\n");
        printf("The max len is %d\n", length);
        printf("The max width is %d\n", width);
    }
    else{
        printf("Laberynth is not correct\n");
        exit(EXIT_FAILURE);
    }
    Lab_p lab = createLab(in, width, length);
    initCost(lab);
    //printf("calculating Costs\n");
    calcCosts(lab, 0, lab->startx, lab->starty);
    //printf("claculated costs\n");
    printLab(lab);
    printf("\n");
    showWay(lab, lab->endx, lab->endy);
    printLab(lab);
    

}

