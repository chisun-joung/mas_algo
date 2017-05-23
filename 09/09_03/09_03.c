#include <stdio.h>
#include "mazebacktracking.h"

int main(int argc, char *argv[])
{
    MapPosition startPos = {0}, endPos = {0};
    MapPosition  *pPath = NULL;
    int step = 0;
    
    int mazeArray[HEIGHT][WIDTH] = {
        {0, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 0}
	};
    
    startPos.x = 0;
    startPos.y = 0;
    endPos.x = 7;
    endPos.y = 7;
    
    pPath = (MapPosition*)malloc(sizeof(MapPosition) * HEIGHT * WIDTH);
    if (pPath != NULL) {
        memset(pPath, 0, sizeof(MapPosition) * HEIGHT * WIDTH);
        
        printf("미로\n");
        printMaze(mazeArray);
        
        maze_BackTracking(mazeArray,
                          endPos,
                          startPos,
                          pPath,
                          &step);
        printf("\n경로\n");
        showPath(mazeArray, pPath, step);
        
        free(pPath);
    }

    return 0;
}
