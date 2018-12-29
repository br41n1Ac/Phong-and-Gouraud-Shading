//
//  edge.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-07.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef edge_h
#define edge_h
#include <vector>
#include "point.h"
#include "vectors.h"
struct edge{
    std::vector<point>points;
    vector3 eg;
    point p1,p2;
    edge();
    edge(point p12, point p22): p1(p12), p2(p22) {points.push_back(p12);points.push_back(p22);};
    
    
};

#endif /* edge_h */
