//
//  gouraud.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-07.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef gouraud_h
#define gouraud_h
#include "point.h"
#include <math.h>
#include <vector>
#include "drawLine.hpp"
#include "triangle.h"
#include "edge.h"




class gouraud{
    
public:
    
    bool static compareX(point p1 , point p2);
    bool static compareY(point p1 , point p2);
    bool static compareZ(point p1 , point p2);


//functiong that collects the points in the outline of the triangle. This also calculates the intensity
std::vector<point> collectPoints(point p1, point p2,int selection);
//Rasterizing on XY plane
void rasterizeXY(point p1,point p2, point p3);

//Used for halftoning
std::vector<point> collectAll(point p1,point p2, point p3);


//rasterizing for XZ plane, same concept as earlier function.Duplicated code, I know..
void rasterizeXZ(point p1,point p2, point p3);

//same for YZ plane
void rasterizeYZ(point p1,point p2, point p3);


//drawing the XY plane black
void rasterizeXYClear(point p1,point p2, point p3);

//drawing the XZ plane black
void rasterizeXZClear(point p1,point p2, point p3);

//drawing the YZ plane black
void rasterizeYZClear(point p1,point p2, point p3);

};

#endif /* gouraud_h */
