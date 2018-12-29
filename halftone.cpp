//
//  halftone.cpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "halftone.h"

class gouraud* gour;
void halftone::fillMegPix3(int tone, point p1){
    int temp[9];
    for(int i = 0; i < 9; i++){
        temp[i] = 0;
    }
    
    int pixLoc1 = (p1.x * 3) + (p1.y * height * 3);
    int pixLoc2 = ((p1.x+width/2) * 3) + (p1.z * height * 3);
    int pixLoc3 = ((p1.y +width/2)* 3) + ((p1.z+height/2) * height * 3);
    int sum = 0;
    if(tone<9){
        while(sum < tone){
            for(int i = 0; i < 9; i++){
                int randNbr = rand() % 2;
                if(temp[i]!=1){
                    temp[i] = randNbr;
                }
                sum += randNbr;
                if(sum == tone){
                    break;
                }
                //std::cout << randNbr <<" \n";
            }
        }
    }else{
        for(int i = 0; i < 9; i++){
            temp[i] = 1;
        }
    }
    random_shuffle(std::begin(temp), std::end(temp));
    for(int i = 0; i < 9; i++){
        if(i<3){
            allocated.insert({pixLoc1+i,temp[0]});
            allocated.insert({pixLoc2+i,temp[0]});
            allocated.insert({pixLoc3+i,temp[0]});
        }
        if(i<6 && i>=3){
            allocated.insert({pixLoc1+i,temp[1]});
            allocated.insert({pixLoc2+i,temp[1]});
            allocated.insert({pixLoc3+i,temp[1]});
        }else{
            allocated.insert({pixLoc1+i,temp[2]});
            allocated.insert({pixLoc2+i,temp[2]});
            allocated.insert({pixLoc3+i,temp[2]});
        }
    }
    for(int i = 0; i < 9; i++){
        if(i<3){
            allocated.insert({pixLoc1+i+height*3,temp[3]});
            allocated.insert({pixLoc2+i+height*3,temp[3]});
            allocated.insert({pixLoc3+i+height*3,temp[3]});
        }
        if(i<6 && i>=3){
            allocated.insert({pixLoc1+i+height*3,temp[4]});
            allocated.insert({pixLoc2+i+height*3,temp[4]});
            allocated.insert({pixLoc3+i+height*3,temp[4]});
        }else{
            allocated.insert({pixLoc1+i+height*3,temp[5]});
            allocated.insert({pixLoc2+i+height*3,temp[5]});
            allocated.insert({pixLoc3+i+height*3,temp[5]});
        }
    }
    for(int i = 0; i < 9; i++){
        if(i<3){
            allocated.insert({pixLoc1+i+height*6,temp[6]});
            allocated.insert({pixLoc2+i+height*6,temp[6]});
            allocated.insert({pixLoc3+i+height*6,temp[6]});
        }
        if(i<6 && i>=3){
            allocated.insert({pixLoc1+i+height*6,temp[7]});
            allocated.insert({pixLoc2+i+height*6,temp[7]});
            allocated.insert({pixLoc3+i+height*6,temp[7]});
        }else{
            allocated.insert({pixLoc1+i+height*6,temp[8]});
            allocated.insert({pixLoc2+i+height*6,temp[8]});
            allocated.insert({pixLoc3+i+height*6,temp[8]});
        }
    }
}




void halftone::drawMegapix (int tone, point p1,point p2, point p3,int selection){
    std::vector<point> edge1 = gour->collectPoints(p1, p2, selection);
    std::vector<point> edge2 = gour->collectPoints(p1, p3, selection);
    std::vector<point> edge3 = gour->collectPoints(p2, p3, selection);
    sort(edge1.begin(),edge1.end(), gouraud::compareY);
    sort(edge2.begin(),edge2.end(), gouraud::compareY);
    sort(edge3.begin(),edge3.end(), gouraud::compareY);
    point temp(0,0,0);
   std::vector<std::vector<point>> lines;
    std::vector<point> startEdge;
    std::vector<point> edges1;
    std::vector<point> edges2;
    std::vector<point> xypoints = gour->collectAll(p1, p2, p3);
    if(edge1[0].y <= edge2[0].y){
        if(edge1[0].y <= edge3[0].y){
            if(edge1[0].x <= edge3[0].x){
                startEdge = edge1;
                edges1 = edge3;
                edges2 = edge2;
            }else{
                startEdge = edge3;
                edges1 = edge1;
                edges2 = edge2;
            }
            
        }else{
            if(edge1[0].x <= edge2[0].x){
                startEdge = edge1;
                edges1 = edge2;
                edges2 = edge3;
            }else{
                startEdge = edge2;
                edges1 = edge1;
                edges2 = edge3;
            }
        }
    }else{
        if(edge2[0].y <= edge3[0].y){
            if(edge2[0].x <= edge3[0].x){
                startEdge = edge2;
                edges1 = edge3;
                edges2 = edge1;
            }else{
                startEdge = edge3;
                edges1 = edge2;
                edges2 = edge1;
            }
        }
    }
    
    for (int i = 0; i < startEdge.size()-1; i++){
        for(int j  = 0; j< edges1.size(); j++){
            
            if(startEdge[i].y ==  edges1[j].y){
                for(point p : gour->collectPoints(startEdge[i], edges1[j],0)){
                    //    std::cout << p.intensities.x<< "here \n";
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
    
    for (int i = 0; i < startEdge.size()-1; i++){
        for(int j  = 0; j< edges2.size(); j++){
            
            if(startEdge[i].y ==  edges2[j].y){
                for(point p : gour->collectPoints(startEdge[i], edges2[j],0)){
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
    for (int i = 0; i < edges1.size()-1; i++){
        for(int j  = 0; j< edges2.size(); j++){
            
            if(edges1[i].y ==  edges2[j].y){
                for(point p : gour->collectPoints(edges1[i], edges2[j],0)){
                    //std::cout<<startEdge[i].x<<" , "<< startEdge[i].y << " " << edges2[j].x << " , "<< edges2[j].y <<" \n";
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
}

void halftone::drawMegapixXZ (int tone, point p1,point p2, point p3,int selection){
    vector<point> edge1 = gour->collectPoints(p1, p2, selection);
    vector<point> edge2 = gour->collectPoints(p1, p3, selection);
    vector<point> edge3 = gour->collectPoints(p2, p3, selection);
    sort(edge1.begin(),edge1.end(), gouraud::compareZ);
    sort(edge2.begin(),edge2.end(), gouraud::compareZ);
    sort(edge3.begin(),edge3.end(), gouraud::compareZ);
    point temp(0,0,0);
    vector<point> startEdge;
    vector<point> edges1;
    vector<point> edges2;
    
    if(edge1[0].z <= edge2[0].z){
        if(edge1[0].z <= edge3[0].z){
            if(edge1[0].x <= edge3[0].x){
                startEdge = edge1;
                edges1 = edge3;
                edges2 = edge2;
            }else{
                startEdge = edge3;
                edges1 = edge1;
                edges2 = edge2;
            }
            
        }else{
            if(edge1[0].x <= edge2[0].x){
                startEdge = edge1;
                edges1 = edge2;
                edges2 = edge3;
            }else{
                startEdge = edge2;
                edges1 = edge1;
                edges2 = edge3;
            }
        }
    }else{
        if(edge2[0].z <= edge3[0].z){
            if(edge2[0].x <= edge3[0].x){
                startEdge = edge2;
                edges1 = edge3;
                edges2 = edge1;
            }else{
                startEdge = edge3;
                edges1 = edge2;
                edges2 = edge1;
            }
        }
    }
    
    for (int i = 0; i < startEdge.size()-1; i++){
        for(int j  = 0; j< edges1.size(); j++){
            
            if(startEdge[i].z ==  edges1[j].z){
                for(point p : gour->collectPoints(startEdge[i], edges1[j],selection)){
                    
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
    
    for (int i = 0; i < startEdge.size()-1; i++){
        for(int j  = 0; j< edges2.size(); j++){
            
            if(startEdge[i].z ==  edges2[j].z){
                for(point p : gour->collectPoints(startEdge[i], edges2[j],selection)){
                    fillMegPix3(tone, p);
                }
                break;
            }
        }
    }
    for (int i = 0; i < edges1.size()-1; i++){
        for(int j  = 0; j< edges2.size(); j++){
            
            if(edges1[i].z ==  edges2[j].z){
                for(point p : gour->collectPoints(edges1[i], edges2[j],selection)){
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
}
void halftone::drawMegapixYZ (int tone, point p1,point p2, point p3,int selection){
    std::vector<point> edge1 = gour->collectPoints(p1, p2, selection);
    std::vector<point> edge2 = gour->collectPoints(p1, p3, selection);
    std::vector<point> edge3 = gour->collectPoints(p2, p3, selection);
    std::sort(edge1.begin(),edge1.end(), gouraud::compareZ);
    std::sort(edge2.begin(),edge2.end(), gouraud::compareZ);
    std::sort(edge3.begin(),edge3.end(), gouraud::compareZ);
    point temp(0,0,0);
    std::vector<point> startEdge;
    std::vector<point> edges1;
    std::vector<point> edges2;
    
    if(edge1[0].z <= edge2[0].z){
        if(edge1[0].z <= edge3[0].z){
            if(edge1[0].y <= edge3[0].y){
                startEdge = edge1;
                edges1 = edge3;
                edges2 = edge2;
            }else{
                startEdge = edge3;
                edges1 = edge1;
                edges2 = edge2;
            }
            
        }else{
            if(edge1[0].x <= edge2[0].x){
                startEdge = edge1;
                edges1 = edge2;
                edges2 = edge3;
            }else{
                startEdge = edge2;
                edges1 = edge1;
                edges2 = edge3;
            }
        }
    }else{
        if(edge2[0].z <= edge3[0].z){
            if(edge2[0].y <= edge3[0].y){
                startEdge = edge2;
                edges1 = edge3;
                edges2 = edge1;
            }else{
                startEdge = edge3;
                edges1 = edge2;
                edges2 = edge1;
            }
        }
    }
    
    for (int i = 0; i < startEdge.size()-1; i++){
        for(int j  = 0; j< edges1.size(); j++){
            
            if(startEdge[i].z ==  edges1[j].z){
                for(point p : gour->collectPoints(startEdge[i], edges1[j],selection)){
                    
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
    
    for (int i = 0; i < startEdge.size()-1; i++){
        for(int j  = 0; j< edges2.size(); j++){
            
            if(startEdge[i].z ==  edges2[j].z){
                for(point p : gour->collectPoints(startEdge[i], edges2[j],selection)){
                    fillMegPix3(tone, p);
                }
                break;
            }
        }
    }
    for (int i = 0; i < edges1.size()-1; i++){
        for(int j  = 0; j< edges2.size(); j++){
            
            if(edges1[i].z ==  edges2[j].z){
                for(point p : gour->collectPoints(edges1[i], edges2[j],selection)){
                    fillMegPix3(tone,p);
                }
                break;
            }
        }
    }
}

