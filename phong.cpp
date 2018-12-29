//
//  phong.cpp
//  assignment3
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "phong.h"

extern point p1;
extern point p2;
extern point p3;
extern float i_a;
extern float i_l;
extern float phong_const;
extern float n_const;
extern vector3 ka;
extern vector3 kd;
extern vector3 ks;
extern point light;
extern int width;
extern int height;
float c_alpha;
extern std::map <point,vector3> normals;


bool operator<(point const &a, point const &b)
{
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}
//normalizing vectors
vector3 phong::normalize(vector3 vec){
    float l=0;
    l = sqrt(pow(vec.x,2)+pow(vec.y,2)+pow(vec.z,2));
    vec.x = vec.x/l;
    vec.y = vec.y/l;
    vec.z = vec.z/l;
    return vec;
}

//making a vector out of two points
vector3 phong::buildVector(point v1,point v2){
    vector3 tempVec;
    tempVec.x = (v2.x - v1.x);
    tempVec.y = (v2.y - v1.y);
    tempVec.z = (v2.z - v1.z);
    return normalize(tempVec);;
}

//calculating the cross product of two vectors
vector3 phong::crossProduct(vector3 v1, vector3 v2){
    vector3 tempVec;
    tempVec.x = v1.y*v2.z - v1.z*v2.y;
    tempVec.y = v1.z*v2.x - v1.x*v2.z;
    tempVec.z = v1.x*v2.y - v1.y*v2.x;
    return normalize(tempVec);
}
//calculating the dot product of two vectors
float phong::dotProduct (vector3 v1, vector3 v2){
    float a = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    return a;
}
//making the reflection vector
vector3 phong::reflectionVec(vector3 lightVec, vector3 normVec){
    vector3 tempVec;
    tempVec.x = 2*dotProduct(normVec, lightVec)*normVec.x - lightVec.x;
    tempVec.y = 2*dotProduct(normVec, lightVec)*normVec.y - lightVec.y;
    tempVec.z = 2*dotProduct(normVec, lightVec)*normVec.z - lightVec.z;
    return normalize(tempVec);
}

//function that calculates the intensity
std::vector<vector3> phong::phongLight(polygon poly,point ff){
    std::vector<vector3>intensities;
    vector3 intensity_p, refl, view,lightVec;
    float maxR=0,maxG=0,maxB=0;
    vector3 normVec(0,0,0);
    float const_c,distf;
    for(int i = 0; i < poly.points.size(); i++){
        int a,b;
        vector3 uVec, vVec;
        switch (i){
            case 0 : a = 1; b = 2; break;
            case 1 : a = 2; b = 0; break;
            case 2 : b = 0; a = 1; break;
            case 3 : b = 2; a = 0; break;
            default: b = 0; a = i-1; break;
        }
        
        int winDelta = fmax(width,height);
        point p (poly.points[i].x/winDelta,poly.points[i].y/winDelta,poly.points[i].z/winDelta);
        view = buildVector(p,ff);
        lightVec = buildVector(p,light);
        const_c = sqrt((pow(light.x-p.x,2)+pow(light.y-p.y,2)+pow(light.z-p.z,2))); //calculating constant
        distf = sqrt((pow(ff.x-p.x,2)+pow(ff.y-p.y,2)+pow(ff.z-p.z,2))); //distance to focalpoint
        uVec = buildVector(poly.points[a], p);
        vVec = buildVector(poly.points[b], p);
        normVec = crossProduct(uVec, vVec);
        refl  = reflectionVec(lightVec, normVec);
        
        float c_alpha = dotProduct(normVec, lightVec);
        float c_beta = dotProduct(refl, view);
        if( c_beta <= 0){ //if they are on the same side but not in reflection area
            intensity_p.x = ka.x*i_a + (i_l/(distf+const_c))*(kd.x*c_alpha);
            intensity_p.y = ka.y*i_a + (i_l/(distf+const_c))*(kd.y*c_alpha);
            intensity_p.z = ka.z*i_a + (i_l/(distf+const_c))*(kd.z*c_alpha);
            //   intensity_p = normalize(intensity_p);
            
        }else{ //if focal point is in reflection area
            intensity_p.x = ka.x*i_a + (i_l/(distf+const_c))*(kd.x*c_alpha + ks.x*(pow(c_beta,n_const)));
            intensity_p.y = ka.y*i_a + (i_l/(distf+const_c))*(kd.y*c_alpha + ks.y*(pow(c_beta,n_const)));
            intensity_p.z = ka.z*i_a + (i_l/(distf+const_c))*(kd.z*c_alpha + ks.z*(pow(c_beta,n_const)));
            // intensity_p = normalize(intensity_p);
        }
        // std::cout << intensity_p.x<<"\n";
        if(intensity_p.x >= maxR){ // used for normalizing
            maxR = intensity_p.x;
        }
        if(intensity_p.y >= maxG){
            maxG = intensity_p.y;
        }
        if(intensity_p.z >= maxB){
            maxB = intensity_p.z;
        }
        intensities.push_back((intensity_p));
    }
    for(int i = 0; i<intensities.size();i++){
        intensities[i].x = intensities[i].x/maxR;
        intensities[i].y = intensities[i].y/maxG;
        intensities[i].z = intensities[i].z/maxB;
    }
    //    std::cout << intensities.size()<<"\n";
    return intensities;
}

//calculating the phong intensities for all points in triangle
std::vector<vector3> phong::phongLightTriangle(triangle tri,point ff){
    std::vector<vector3>intensities;
    vector3 intensity_p, refl, view,lightVec;
    float maxR=0,maxG=0,maxB=0;
    vector3 normVec(0,0,0);
    float const_c,distf;
    for(int i = 0; i < tri.points.size(); i++){
        int a,b;
        vector3 uVec, vVec;
        switch (i){
            case 0 : a = 1; b = 2; break;
            case 1 : a = 2; b = 0; break;
            case 2 : a = 0; b = 1; break;
            case 3 : a = 1; b = 2; break;
            default: b = 0; a = i-1; break;
        }
        
        int winDelta = fmax(width,height);
        point p (tri.points[i].x/winDelta,tri.points[i].y/winDelta,tri.points[i].z/winDelta);
        //   std::cout<<p.x<<" "<< p.y<<" "<< p.z<<" \n";
        // point tempP = poly.points[i];
        view = buildVector(p,ff);
        lightVec = buildVector(p,light);
        const_c = sqrt((pow(light.x-p.x,2)+pow(light.y-p.y,2)+pow(light.z-p.z,2))); //calculating constant
        distf = sqrt((pow(ff.x-p.x,2)+pow(ff.y-p.y,2)+pow(ff.z-p.z,2))); // calculating distance to Focal point
        uVec = buildVector(tri.points[a], p);
        vVec = buildVector(tri.points[b], p);
        if(normals.count(tri.points[i])){ //if normal for point already calculated.
            normVec = normals[tri.points[i]];
            
        }else {
            normVec = crossProduct(uVec, vVec);
        }
        //  normVec = crossProduct(uVec, vVec);
        refl  = reflectionVec(lightVec, normVec);
        point addP ={tri.points[i].x,tri.points[i].y,tri.points[i].z};
        normals.insert({tri.points[i], normVec});
        c_alpha = dotProduct(normVec, lightVec);
        float c_beta = dotProduct(refl, view);
        
        if( c_beta < 0){ //if on the same side but not in reflection area
            intensity_p.x = ka.x*i_a + (i_l/(distf+const_c))*(kd.x*c_alpha);
            intensity_p.y = ka.y*i_a + (i_l/(distf+const_c))*(kd.y*c_alpha);
            intensity_p.z = ka.z*i_a + (i_l/(distf+const_c))*(kd.z*c_alpha);
            //   intensity_p = normalize(intensity_p);
            
        }else{ // in reflection area
            intensity_p.x = ka.x*i_a + (i_l/(distf+const_c))*(kd.x*c_alpha + ks.x*(pow(c_beta,n_const)));
            intensity_p.y = ka.y*i_a + (i_l/(distf+const_c))*(kd.y*c_alpha + ks.y*(pow(c_beta,n_const)));
            intensity_p.z = ka.z*i_a + (i_l/(distf+const_c))*(kd.z*c_alpha + ks.z*(pow(c_beta,n_const)));
            // intensity_p = normalize(intensity_p);
        }
        // std::cout << intensity_p.x<<"\n";
        if(intensity_p.x >= maxR){
            maxR = intensity_p.x;
        }
        if(intensity_p.y >= maxG){
            maxG = intensity_p.y;
        }
        if(intensity_p.z >= maxB){
            maxB = intensity_p.z;
        }
        
        
        intensities.push_back((intensity_p));
        
    }
    for(int i = 0; i<intensities.size();i++){
        if(!(c_alpha > 0 && dotProduct(normVec, view)>0) || !(c_alpha < 0 && dotProduct(normVec, view)<0)){ //if focal and light not on the same side
            intensity_p.x = ka.x*i_a;
            intensity_p.y = ka.y*i_a;
            intensity_p.z = ka.z*i_a;
        }else{
            
            intensities[i].x = intensities[i].x/maxR;
            intensities[i].y = intensities[i].y/maxG;
            intensities[i].z = intensities[i].z/maxB;
        }
    }
    //    std::cout << intensities.size()<<"\n";
    return intensities;
}

