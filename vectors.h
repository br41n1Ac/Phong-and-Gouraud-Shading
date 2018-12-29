//
//  vectors.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-06.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef vectors_h
#define vectors_h
struct vector3{
    float x,y,z;
    vector3() : x(0), y(0) ,z(0){};
    vector3(float a, float b, float c) : x(a), y(b), z(c) {};
};

#endif /* vectors_h */
