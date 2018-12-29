//
//  phong.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-06.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef phong_h
#define phong_h
#include "point.h"
#include <math.h>
#include "vectors.h"
#include "polygon.hpp"
#include <vector>
#include "triangle.h"
#include <map>


class phong{
public:




//normalizing vectors
vector3 normalize(vector3 vec);

//making a vector out of two points
vector3 buildVector(point v1,point v2);

//calculating the cross product of two vectors
vector3 crossProduct(vector3 v1, vector3 v2);

//calculating the dot product of two vectors
float dotProduct (vector3 v1, vector3 v2);

//making the reflection vector
vector3 reflectionVec(vector3 lightVec, vector3 normVec);

//function that calculates the intensity
std::vector<vector3> phongLight(polygon poly,point ff);

//calculating the phong intensities for all points in triangle
std::vector<vector3> phongLightTriangle(triangle tri,point ff);
};
#endif /* phong_h */
