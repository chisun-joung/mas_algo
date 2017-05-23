#include <stdio.h>
#include "closestpair.h"

int main()
{
    int count = 0;
    double min_dist = 0;
    Point points[] = {{2, 5}, {15, 30}, {40, 50},
                        {5, 2}, {15, 10}, {10, 5}};
    
    count = sizeof(points) / sizeof(Point);
    min_dist = closestPair(points, count);
    printf("점들은 모두 %d개이며, 가장 가까운 두 점의 거리는 %f 입니다 \n",
        count, min_dist);
    
    return 0;
}
