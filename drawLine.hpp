//
//  drawLine.hpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-06.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef drawLine_hpp
#define drawLine_hpp

#include <stdio.h>
#include "point.h"
#include <math.h>
#include "edge.h"
#include <map>
using namespace std;
extern float* PixelBuffer;
extern int height;
extern int width;
extern float* Buffer;
extern map<float,int> allocated;
extern map<float, vector3> intensMap;
extern bool startUp;

class drawLine{

public:
//turning on pixels
void makePix(int x,int y, float red, float green, float blue);

//Line drawing algorithm that also gives the points their intensity. Selection is what plane that will be calculated for.
void drawDDA(point p1, point p2,float r, float g, float b, int selection);

//clearing the lines, same as previous just gives the points 0 intensity.
void drawDDAClear(point p1, point p2,float r, float g, float b, int selection);


void makePix2(int x,int y, int red, int green, int blue);
void drawDDA2(point p1, point p2,int r, int g, int b, int selection);
};
#endif /* drawLine_hpp */
