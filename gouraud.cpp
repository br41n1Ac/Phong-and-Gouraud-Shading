//
//  gouraud.cpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "gouraud.h"

std::vector<point>ps;

bool gouraud::compareX(point p1 , point p2){return (p1.x < p2.x);}
bool gouraud::compareY(point p1 , point p2){return (p1.y < p2.y);}
bool gouraud::compareZ(point p1 , point p2){return (p1.z < p2.z);}
class drawLine dL;

//functiong that collects the points in the outline of the triangle. This also calculates the intensity
std::vector<point> gouraud::collectPoints(point p1, point p2,int selection){
    std::vector<point> points;
    points.push_back(p1);
    points.push_back(p2);
    float deltax = 0, deltay = 0, x = 0, y = 0, dist=0, incy, incx;
    switch(selection){
        case 0 :
            deltax = p2.x-p1.x; deltay = p2.y-p1.y; x = p1.x; y = p1.y;
            break;
        case 1 :
            deltax = p2.x-p1.x; deltay = p2.z-p1.z; x = p1.x; y = p1.z;
            break;
        case 2 :
            deltax = p2.y-p1.y; deltay = p2.z-p1.z; x = p1.y; y = p1.z;
            break;
    }
    if(fabs(deltax) > fabs(deltay)){
        dist = fabs(deltax);
    } else{
        dist  = fabs(deltay);
    }
    incx = deltax/dist;
    incy = deltay/dist;
    
    for(int i=0; i<dist; i++){
        x+=incx;
        y+=incy;
        
        switch(selection){
            case 0 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    point temp = *new point(round(x),round(y),0);
                    if(p2.x-p1.x != 0){
                        temp.intensities.x = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.x + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.x;
                        temp.intensities.y = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.y + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.y;
                        temp.intensities.z = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.z + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.z;
                    }else{
                        temp.intensities.x = ((p2.y-y)/(p2.y-p1.y))*p1.intensities.x + ((y-p1.y)/(p2.y-p1.y))*p2.intensities.x;
                        temp.intensities.y = ((p2.y-y)/(p2.y-p1.y))*p1.intensities.y + ((y-p1.y)/(p2.y-p1.y))*p2.intensities.y;
                        temp.intensities.z = ((p2.y-y)/(p2.y-p1.y))*p1.intensities.z + ((y-p1.y)/(p2.y-p1.y))*p2.intensities.z;
                    }
                    
                    points.push_back(temp);
                }
                break;
            case 1 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    point temp = *new point(round(x),0,round(y));
                    if(p2.x-p1.x != 0){
                        temp.intensities.x = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.x + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.x;
                        temp.intensities.y = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.y + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.y;
                        temp.intensities.z = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.z + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.z;
                    }else{
                        temp.intensities.x = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.x + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.x;
                        temp.intensities.y = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.y + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.y;
                        temp.intensities.z = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.z + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.z;
                    }
                    points.push_back(temp);
                }
                break;
            case 2 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    point temp = *new point(0,round(x),round(y));
                    if(p2.y-p1.y != 0){
                        temp.intensities.x = ((p2.y-x)/(p2.y-p1.y))*p1.intensities.x + ((x-p1.y)/(p2.y-p1.y))*p2.intensities.x;
                        temp.intensities.y = ((p2.y-x)/(p2.y-p1.y))*p1.intensities.y + ((x-p1.y)/(p2.y-p1.y))*p2.intensities.y;
                        temp.intensities.z = ((p2.y-x)/(p2.y-p1.y))*p1.intensities.z + ((x-p1.y)/(p2.y-p1.y))*p2.intensities.z;
                    }else{
                        temp.intensities.x = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.x + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.x;
                        temp.intensities.y = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.y + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.y;
                        temp.intensities.z = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.z + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.z;
                    }
                    points.push_back(temp);
                }
                break;
        }
    }
    return points;
}
//Rasterizing on XY plane
void gouraud::rasterizeXY(point p1,point p2, point p3){
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 0); //collect the points on the first edge
    std::sort(e1.points.begin(), e1.points.end(), compareY);
    edge e2 = edge(p1, p3); //collect the points on the second edge
    e2.points = collectPoints(p1, p3, 0);
    std::sort(e2.points.begin(), e2.points.end(), compareY);
    edge e3 = edge(p2, p3); //collect the points on the third edge
    e3.points = collectPoints(p2, p3, 0);
    std::sort(e3.points.begin(), e3.points.end(), compareY);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.y == pe2.y){
                dL.drawDDA(pe1, pe2, 0, 0, 0, 0);
            }
        }
        for(point pe3 : e3.points){
            
            if(pe1.y == pe3.y){
                dL.drawDDA(pe1, pe3, 0, 0, 0, 0);
                
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.y == pe2.y){
                dL.drawDDA(pe2, pe3, 0, 0, 0, 0);
            }
        }
    }
}

//Used for halftoning
std::vector<point> gouraud::collectAll(point p1,point p2, point p3){
    std::vector<point> tempP1;
    std::vector<point> tempP2;
    std::vector<point> tempP3;
    std::vector<point> all;
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 0);
    sort(e1.points.begin(), e1.points.end(), compareY);
    edge e2 = edge(p1, p3);
    e2.points = collectPoints(p1, p3, 0);
    sort(e2.points.begin(), e2.points.end(), compareY);
    edge e3 = edge(p2, p3);
    e3.points = collectPoints(p2, p3, 0);
    sort(e3.points.begin(), e3.points.end(), compareY);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.y == pe2.y){
                tempP1 = collectPoints(pe1, pe2, 0);
            }
        }
        for(point pe3 : e3.points){
            
            if(pe1.y == pe3.y){
                tempP2 = collectPoints(pe1, pe3, 0);
                
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.y == pe2.y){
                tempP3 = collectPoints(pe2, pe3, 0);
            }
        }
    }
    for(point p : tempP1){
        all.push_back(p);
    }
    for(point p : tempP1){
        all.push_back(p);
    }
    for(point p : tempP1){
        all.push_back(p);
    }
    return all;
}


//rasterizing for XZ plane, same concept as earlier function.Duplicated code, I know..
void gouraud::rasterizeXZ(point p1,point p2, point p3){
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 1);
    sort(e1.points.begin(), e1.points.end(), compareZ);
    edge e2 = edge(p1, p3);
    e2.points = collectPoints(p1, p3, 1);
    sort(e2.points.begin(), e2.points.end(), compareZ);
    edge e3 = edge(p2, p3);
    e3.points = collectPoints(p2, p3, 1);
    sort(e3.points.begin(), e3.points.end(), compareZ);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.z == pe2.z){
                dL.drawDDA(pe1, pe2, 0, 0, 0, 1);
            }
        }
        for(point pe3 : e3.points){
            
            if(pe1.z == pe3.z){
                dL.drawDDA(pe1, pe3, 0, 0, 0, 1);
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.z == pe2.z){
                dL.drawDDA(pe3, pe2, 0, 0, 0, 1);
            }
        }
    }
}

//same for YZ plane
void gouraud::rasterizeYZ(point p1,point p2, point p3){
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 2);
    sort(e1.points.begin(), e1.points.end(), compareZ);
    edge e2 = edge(p1, p3);
    e2.points = collectPoints(p1, p3, 2);
    sort(e2.points.begin(), e2.points.end(), compareZ);
    edge e3 = edge(p2, p3);
    e3.points = collectPoints(p2, p3, 2);
    sort(e3.points.begin(), e3.points.end(), compareZ);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.z == pe2.z){
                
                dL.drawDDA(pe1, pe2, 0, 0, 0, 2);
            }
        }
        for(point pe3 : e3.points){
            if(pe1.z == pe3.z){
                dL.drawDDA(pe1, pe3, 0, 0, 0, 2);
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.z == pe2.z){
                dL.drawDDA(pe3, pe2, 0, 0, 0, 2);
            }
        }
    }
    
}


//drawing the XY plane black
void gouraud::rasterizeXYClear(point p1,point p2, point p3){
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 0);
    sort(e1.points.begin(), e1.points.end(), compareY);
    edge e2 = edge(p1, p3);
    e2.points = collectPoints(p1, p3, 0);
    sort(e2.points.begin(), e2.points.end(), compareY);
    edge e3 = edge(p2, p3);
    e3.points = collectPoints(p2, p3, 0);
    sort(e3.points.begin(), e3.points.end(), compareY);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.y == pe2.y){
                dL.drawDDAClear(pe1, pe2, 0, 0, 0, 0);
            }
        }
        for(point pe3 : e3.points){
            
            if(pe1.y == pe3.y){
                dL.drawDDAClear(pe1, pe3, 0, 0, 0, 0);
                
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.y == pe2.y){
                dL.drawDDAClear(pe2, pe3, 0, 0, 0, 0);
            }
        }
    }
    
}

//drawing the XZ plane black
void gouraud::rasterizeXZClear(point p1,point p2, point p3){
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 1);
    sort(e1.points.begin(), e1.points.end(), compareZ);
    edge e2 = edge(p1, p3);
    e2.points = collectPoints(p1, p3, 1);
    sort(e2.points.begin(), e2.points.end(), compareZ);
    edge e3 = edge(p2, p3);
    e3.points = collectPoints(p2, p3, 1);
    sort(e3.points.begin(), e3.points.end(), compareZ);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.z == pe2.z){
                dL.drawDDAClear(pe1, pe2, 0, 0, 0, 1);
            }
        }
        for(point pe3 : e3.points){
            
            if(pe1.z == pe3.z){
                dL.drawDDAClear(pe1, pe3, 0, 0, 0, 1);
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.z == pe2.z){
                dL.drawDDAClear(pe3, pe2, 0, 0, 0, 1);
            }
        }
    }
}

//drawing the YZ plane black
void gouraud::rasterizeYZClear(point p1,point p2, point p3){
    edge e1 = edge(p1, p2);
    e1.points = collectPoints(p1, p2, 2);
    sort(e1.points.begin(), e1.points.end(), compareZ);
    edge e2 = edge(p1, p3);
    e2.points = collectPoints(p1, p3, 2);
    sort(e2.points.begin(), e2.points.end(), compareZ);
    edge e3 = edge(p2, p3);
    e3.points = collectPoints(p2, p3, 2);
    sort(e3.points.begin(), e3.points.end(), compareZ);
    for(point pe1 : e1.points){
        for(point pe2 : e2.points ){
            if(pe1.z == pe2.z){
                
                dL.drawDDAClear(pe1, pe2, 0, 0, 0, 2);
            }
        }
        for(point pe3 : e3.points){
            if(pe1.z == pe3.z){
                dL.drawDDAClear(pe1, pe3, 0, 0, 0, 2);
            }
        }
    }
    for(point pe2 : e2.points){
        for(point pe3 : e3.points ){
            if(pe3.z == pe2.z){
                dL.drawDDAClear(pe3, pe2, 0, 0, 0, 2);
            }
        }
    }
    
}

