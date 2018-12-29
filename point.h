//
//  point.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-05.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//


#ifndef point_h
#define point_h
#include "vectors.h"
class point {
public:
    float x,y,z;
    vector3 intensities;
    point();
    point(float, float, float);
};


#endif /* point_h */
