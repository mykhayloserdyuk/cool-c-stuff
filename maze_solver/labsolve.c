#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int checkLab(FILE *Lab, int *maxWid, int *maxLeng){
    bool hasEnd = false;
    bool hasStart = false;
    int maxLength = 0;
    int maxWidth = 0;
    int tempWidth = 0;
    
    char currChar;

    while((currChar = fgetc(Lab)) != EOF){
        
        if(currChar == '\n'){
            if(maxWidth < tempWidth){
                maxWidth = tempWidth;
            }
            maxLength++;
            tempWidth = 0;
        }
        else{
            tempWidth++;

            if(currChar == 'X')
            {  
                if(hasEnd){
                    return 0;
                }
                hasEnd = true;
            }
            else if (currChar == 'S')
            {
                if(hasStart){
                    return 0;
                }
                hasStart = true;
            }
        }
    }

    *maxWid = maxWidth;
    *maxLeng = maxLength; 
    rewind(Lab);
    return 1;
    
}

Lab_p createLab(FILE *Lab, int maxWid, int maxLen){

    char currChar;
    int xindex=0;
    int yindex=0;
    Lab_p Maze;
    Maze = malloc(sizeof(LabCell));
    Maze->maxlen = maxLen;
    Maze->maxwidth = maxWid;

    while((currChar = fgetc(Lab)) != EOF){
        if(currChar == '\n'){
            yindex++;
            xindex = 0;
        }
        else{

            if(currChar == 'X')
            {  
                Maze->endx = xindex;
                Maze->endy = yindex;
            }
            else if (currChar == 'S')
            {
                Maze->startx = xindex;
                Maze->starty =yindex;
            }
            Maze->lab[yindex][xindex] = currChar;
            xindex++;

        }
    }
    rewind(Lab);
    return Maze;
}
int printLab(Lab_p Maze)
{
    for(int i = 0; i <= Maze->maxlen; i++){
        for(int e = 0; e <= Maze->maxwidth; e++){
            printf("%c", Maze->lab[i][e]);
        }
        printf("\n");
    }
    return 1;
}

void calcCosts(Lab_p maze, int currCost, int currx, int curry)
{
    switch (maze->lab[curry][currx])
    {
        case ' ':
            maze->cost[curry][currx] = currCost;
            break;
        case 'S':
            maze->cost[curry][currx] = 0;
            break;
        case '#':
            return;
        case 'X':
            maze->cost[curry][currx] = currCost;
            return;
    }

    currCost++;
  
    // Horizontal and vertical movement
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  
    for (int i = 0; i < 4; i++) {
        int nextx = currx + directions[i][0];
        int nexty = curry + directions[i][1];

        if (nextx >= 0 && nextx <= maze->maxwidth && nexty >= 0 && nexty <= maze->maxlen) {
            if (maze->cost[nexty][nextx] > currCost) {
                calcCosts(maze, currCost, nextx, nexty);
            }
        }
    }
}


int printCost(Lab_p Maze)
{
    for(int i = 0; i <= Maze->maxlen; i++){
        for(int e = 0; e <= Maze->maxwidth; e++){
            printf("%d%d%d", Maze->cost[i][e]/100, Maze->cost[i][e]/10, Maze->cost[i][e]);
        }
        printf("\n");
    }
    return 1;
}


int initCost(Lab_p Maze){
    for(int i = 0; i <= Maze->maxlen; i++){
        for(int e = 0; e <= Maze->maxwidth; e++){
            Maze->cost[i][e]=998;
        }
    }
    return 1;
}

void showWay(Lab_p Maze, int endx, int endy)
{
    //printf("current Cords x: %d, y: %d\n", endx, endy);
    int currCost = Maze->cost[endy][endx];
    Maze->lab[endy][endx] = '.';

    // top
    if (Maze->cost[endy - 1][endx] == currCost - 1)
    {
        showWay(Maze, endx, endy - 1);
    }
    // bottom
    else if (Maze->cost[endy + 1][endx] == currCost - 1)
    {
        showWay(Maze, endx, endy + 1);
    }
    // left
    else if (Maze->cost[endy][endx - 1] == currCost - 1)
    {
        showWay(Maze, endx - 1, endy);
    }
    // right
    else if (Maze->cost[endy][endx + 1] == currCost - 1)
    {
        showWay(Maze, endx + 1, endy);
    }
    // top left
    else if (Maze->cost[endy - 1][endx - 1] == currCost - 1)
    {
        showWay(Maze, endx - 1, endy - 1);
    }
    // top right
    else if (Maze->cost[endy - 1][endx + 1] == currCost - 1)
    {
        showWay(Maze, endx + 1, endy - 1);
    }
    // bottom left
    else if (Maze->cost[endy + 1][endx - 1] == currCost - 1)
    {
        showWay(Maze, endx - 1, endy + 1);
    }
    // bottom right
    else if (Maze->cost[endy + 1][endx + 1] == currCost - 1)
    {
        showWay(Maze, endx + 1, endy + 1);
    }
}
