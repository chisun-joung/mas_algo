#include "mazebacktracking.h"

int checkValidPos(int mazeArray[HEIGHT][WIDTH], MapPosition pos)
{
    if (pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT) {
        if (mazeArray[pos.y][pos.x] != WALL && mazeArray[pos.y][pos.x] != VISIT) {
            return 1;
        }
    }
    return 0;
}

void maze_BackTracking(int mazeArray[HEIGHT][WIDTH],
                       MapPosition endPos,
                       MapPosition currentPos,
                       MapPosition *pPath,
                       int *pStep)
{
    int step = *pStep;
    mazeArray[currentPos.y][currentPos.x] = VISIT;
    pPath[step] = currentPos;
    
    if (currentPos.x == endPos.x && currentPos.y == endPos.x) {
        return;
    }
    else {
        for(int i = 0; i < NUM_DIRECTIONS; i++) {
            MapPosition newPos = {0};
            newPos.x = currentPos.x + DIRECTION_OFFSETS[i][0];
            newPos.y = currentPos.y + DIRECTION_OFFSETS[i][1];
            
            if (checkValidPos(mazeArray, newPos)) {
                *pStep = step + 1;
                maze_BackTracking(mazeArray, endPos, newPos, pPath, pStep);
            }
        }
    }
}

void printMaze(int mazeArray[HEIGHT][WIDTH])
{
    int i, j;
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            if (mazeArray[i][j] == WALL) {
                printf("*");
            }
            else if (mazeArray[i][j] == VISIT) {
                printf("O");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void showPath(int mazeArray[HEIGHT][WIDTH], MapPosition *pPath, int step)
{
    int resultArray[HEIGHT][WIDTH] = {0,};
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if (mazeArray[i][j] == WALL) {
                resultArray[i][j] = WALL;
            }
        }
    }
    for(int i = 0; i <= step; i++) {
        int x = pPath[i].x;
        int y = pPath[i].y;
        
        if (i > 0)
            printf("->");
        printf("(%d,%d)", y, x);
        
        resultArray[y][x] = VISIT;
    }
    printf("\n");
    printMaze(resultArray);
}
