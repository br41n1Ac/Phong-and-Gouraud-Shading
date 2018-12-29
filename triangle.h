//
//  triangle.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-07.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef triangle_h
#define triangle_h
#include "edge.h"
#include "point.h"
class triangle{
 public:
    float maxX,maxY,maxZ,minX,minY,minZ;
    float centerX,centerY,centerZ;
    point p1,p2,p3;
    //triangle();
    triangle(point,point,point);
    std::vector<point> points;
    void setMaxX();
    void setMaxY();
    void setMaxZ();
    void findCenter();
    void setMinX();
    void setMinY();
    void setMinZ();
};


#endif /* triangle_h */
