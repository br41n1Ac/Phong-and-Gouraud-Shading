//
//  triangle.cpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "triangle.h"
#include "point.h"


triangle::triangle(point po1,point po2, point po3) : p1(po1),p2(po2),p3(po3){
    
    setMaxX();
    setMaxY();
    setMaxZ();
    findCenter();
    setMinX();
    setMinY();
    setMinZ();
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    point center={centerX,centerY,centerZ};
}

void triangle::setMaxX(){
    if(p1.x>=p2.x){
        if(p1.x>=p3.x){
            maxX = p1.x;
        }else{
            maxX = p3.x;
        }
    }else{
        maxX = p2.x;
    }
}
void triangle::setMaxY(){
    if(p1.y>=p2.y){
        if(p1.y>=p3.y){
            maxY = p1.y;
        }else{
            maxY = p3.y;
        }
    }else{
        maxY = p2.y;
    }
}
void triangle::setMaxZ(){
    if(p1.z>=p2.z){
        if(p1.z>=p3.z){
            maxZ = p1.z;
        }else{
            maxZ = p3.z;
        }
    }else{
        maxZ = p2.z;
    }
}

void triangle::findCenter(){
    
    centerX = (p1.x+p2.x+p3.x)/3;
    centerY = (p1.y+p2.y+p3.y)/3;
    centerZ = (p1.z+p2.z+p3.z)/3;
    
}
void triangle::setMinX(){
    if(p1.x<=p2.x){
        if(p1.x<=p3.x){
            minX = p1.x;
        }else{
            minX = p3.x;
        }
    }else{
        minX = p2.x;
    }
}
void triangle::setMinY(){
    if(p1.y<=p2.y){
        if(p1.y<=p3.y){
            minY = p1.y;
        }else{
            minY = p3.y;
        }
    }else{
        minY = p2.y;
    }
}
void triangle::setMinZ(){
    if(p1.z<=p2.z){
        if(p1.z<=p3.z){
            minZ = p1.z;
        }else{
            minZ = p3.z;
        }
    }else{
        minZ = p2.z;
    }
}



