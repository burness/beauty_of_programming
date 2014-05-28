#ifndef PUBLICHEADER_H
#define PUBLICHEADER_H

#define NDEBUG

#ifndef NDEBUG
    #define TR {printf("\nTrace-----Line:%d   in File: %s\n",__LINE__,__FILE__);fflush(stdout);}
#else
    #define TR /**/
#endif

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>

const int X_MAX = 10;
const int Y_MAX = 15;
struct Map
{
    int disorderCount;
    int xMax,yMax;
    int map[X_MAX][Y_MAX];
};

using namespace std;
#endif // PUBLICHEADER_H
