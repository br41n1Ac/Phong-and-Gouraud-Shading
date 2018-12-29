//
//  drawLine.cpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "drawLine.hpp"

//turning on pixels
void drawLine::makePix(int x,int y, float red, float green, float blue){
    int pixLoc = (x * 3) + (y * height * 3);
    if(x<=width-2 && y <= height-2 && x >= 0 && y >= 0){
        if(allocated[pixLoc] == 1){
            PixelBuffer[pixLoc + 0] = red;
            PixelBuffer[pixLoc + 1] = green;
            PixelBuffer[pixLoc + 2] = blue;
        }
    }
}

//Line drawing algorithm that also gives the points their intensity. Selection is what plane that will be calculated for.
void drawLine::drawDDA(point p1, point p2,float r, float g, float b, int selection){
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
                    float tempR, tempG, tempB;
                    if(p2.x-p1.x != 0){
                        tempR = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.x + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.x;
                        tempG = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.y + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.y;
                        tempB = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.z + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.z;
                    }else{
                        tempR = ((p2.y-y)/(p2.y-p1.y))*p1.intensities.x + ((y-p1.y)/(p2.y-p1.y))*p2.intensities.x;
                        tempG = ((p2.y-y)/(p2.y-p1.y))*p1.intensities.y + ((y-p1.y)/(p2.y-p1.y))*p2.intensities.y;
                        tempB = ((p2.y-y)/(p2.y-p1.y))*p1.intensities.z + ((y-p1.y)/(p2.y-p1.y))*p2.intensities.z;
                    }
                    makePix(x, y, tempR, tempG, tempB);
                }
                break;
            case 1 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    float tempR, tempG, tempB;
                    if(p2.x-p1.x != 0){
                        tempR = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.x + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.x;
                        tempG = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.y + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.y;
                        tempB = ((p2.x-x)/(p2.x-p1.x))*p1.intensities.z + ((x-p1.x)/(p2.x-p1.x))*p2.intensities.z;
                    }else{
                        tempR = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.x + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.x;
                        tempG = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.y + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.y;
                        tempB = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.z + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.z;
                    }
                    makePix(x+width/2, y, tempR, tempG, tempB);
                }
                break;
            case 2 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    float tempR, tempG, tempB;
                    if(p2.y-p1.y != 0){
                        tempR = ((p2.y-x)/(p2.y-p1.y))*p1.intensities.x + ((x-p1.y)/(p2.y-p1.y))*p2.intensities.x;
                        tempG = ((p2.y-x)/(p2.y-p1.y))*p1.intensities.y + ((x-p1.y)/(p2.y-p1.y))*p2.intensities.y;
                        tempB = ((p2.y-x)/(p2.y-p1.y))*p1.intensities.z + ((x-p1.y)/(p2.y-p1.y))*p2.intensities.z;
                    }else{
                        tempR = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.x + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.x;
                        tempG = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.y + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.y;
                        tempB = ((p2.z-y)/(p2.z-p1.z))*p1.intensities.z + ((y-p1.z)/(p2.z-p1.z))*p2.intensities.z;
                    }
                    makePix(x+height/2, y+height/2, tempR, tempG, tempB);
                }
                break;
            default: break;
        }
    }
}

//clearing the lines, same as previous just gives the points 0 intensity.
void drawLine::drawDDAClear(point p1, point p2,float r, float g, float b, int selection){
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
                    
                    makePix(x, y, r, g, b);
                }
                break;
            case 1 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    
                    makePix(x+width/2, y, r, g, b);
                }
                break;
            case 2 :
                if(x>=0 && x<=width/2 && y>=0 && y<=height/2){
                    
                    makePix(x+height/2, y+height/2, r, g, b);
                }
                break;
            default: break;
        }
    }
}


void drawLine::makePix2(int x,int y, int red, int green, int blue){
    int pixLoc = (x * 3) + (y * height * 3);
    PixelBuffer[pixLoc + 0] = red;
    PixelBuffer[pixLoc + 1] = green;
    PixelBuffer[pixLoc + 2] = blue;
}
void drawLine::drawDDA2(point p1, point p2,int r, int g, int b, int selection){
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
        makePix(x, y, r, g, b);
    }
}


