//
//  halftone.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-08.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef halftone_h
#define halftone_h
#include "gouraud.h"
#include <math.h>
#include <algorithm>
#include "point.h"
#include <vector>
#include "vectors.h"
#include "drawLine.hpp"
#include <set>
#include <map>
#include "polygon.hpp"

extern float* PixelBuffer;
extern int height;
extern int width;
extern polygon poly;
extern std::map<float,int> allocated;

class halftone{
    
public:
void fillMegPix3(int tone, point p1);
void drawMegapix (int tone, point p1,point p2, point p3,int selection);
void drawMegapixXZ (int tone, point p1,point p2, point p3,int selection);
void drawMegapixYZ (int tone, point p1,point p2, point p3,int selection);

};

    




#endif /* halftone_h */
