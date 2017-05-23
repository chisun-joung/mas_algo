#ifndef mazebacktracking_h
#define mazebacktracking_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WIDTH 8
#define HEIGHT 8

typedef struct MapPositionType
{
    int x;				// 현재 위치 x좌표.
    int y;				// 현재 위치 y좌표.
} MapPosition;

static int DIRECTION_OFFSETS[][2] = {
    {0, -1},		// 위쪽으로 이동.
    {1, 0},			// 오른쪽으로 이동.
    {0, 1},			// 아래쪽으로 이동.
    {-1, 0}			// 왼쪽으로 이동.
};
#define NUM_DIRECTIONS sizeof(DIRECTION_OFFSETS)/sizeof(int[2])

enum PosStatus { NOT_VISIT = 0, WALL = 1 , VISIT = 2  };

void printMaze(int mazeArray[HEIGHT][WIDTH]);

void maze_BackTracking(int mazeArray[HEIGHT][WIDTH],
                       MapPosition endPos,
                       MapPosition currentPos,
                       MapPosition *pPath,
                       int *pStep);

void showPath(int mazeArray[HEIGHT][WIDTH], MapPosition *pPath, int step);

#endif
