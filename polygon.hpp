//
//  polygon.hpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-05.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef polygon_hpp
#define polygon_hpp

#include "connection.h"
#include "point.h"
#include <vector>

struct polygon {
    std::vector<point> points;
    std::vector<connection> connections;
    void addPoint(point p){points.push_back(p);}
    void addConnection(int a,int b,int c){connections.push_back(*new connection(a,b,c));}
    int size = (int)points.size();
};
#endif /* polygon_hpp */
