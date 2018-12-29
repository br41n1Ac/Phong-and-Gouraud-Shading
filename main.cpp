

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "point.h"
#include "connection.h"
#include <vector>
#include <math.h>
#include "polygon.hpp"
#include "vectors.h"
#include "drawLine.hpp"
#include "phong.h"
#include "gouraud.h"
#include "triangle.h"
#include "halftone.h"
#include <set>
#include <map>


using namespace std;

point focal(0,0,0);
int height=600,width=600;
float *PixelBuffer;
point light = {0.5,0.5,1};
float phong_const;
float i_a=0.5, i_l = 0.8;
float n_const;
vector3 ka;
vector3 kd;
vector3 ks(1.0, 1.0, 1.0);
vector <vector3> intens;
polygon poly;

map<float,int> allocated;
vector<triangle> trianglesXY;
vector<polygon> polygons;
map <point,vector3> normals;
string inputFile = "/Users/simonakesson/Document/ECS 175/assignment3/assignment3/assignment3/test_scene.txt";
string outputFile = "/Users/simonakesson/Document/ECS 175/assignment2/assignment2/test.txt";
int shade;
bool startUp;
class halftone* ht;
class gouraud* gou;
class phong* ph;

//creating the triangles based on the connections in the input file.
void createTriangles(){
    for(polygon pol : polygons){
        for(connection con: pol.connections){
        trianglesXY.push_back(*new triangle(pol.points[con.a],pol.points[con.b],pol.points[con.c])); // creates triangles out of the input file based on connections
    ht-> drawMegapix(shade, pol.points[con.a], pol.points[con.b], pol.points[con.c],0); //halftoning for XY plane
       ht-> drawMegapixXZ(shade, pol.points[con.a], pol.points[con.b], pol.points[con.c],1); // halftoning for XZ plane
       ht-> drawMegapixYZ(shade, pol.points[con.a], pol.points[con.b], pol.points[con.c],2); //halftoning for YZ plane
        }
        
    }
}

// method for recalculating and clearing the polygons so that it can be redrawn according to the level of half-toning
void reTone(){
    
    for(polygon pol : polygons){
        for(connection con: pol.connections){
            gou->rasterizeXYClear(pol.points[con.a], pol.points[con.b], pol.points[con.c]); //clearing XY plane
            gou->rasterizeXZClear(pol.points[con.a], pol.points[con.b], pol.points[con.c]); // clearing XZ plane
            gou->rasterizeYZClear(pol.points[con.a], pol.points[con.b], pol.points[con.c]); //clearing YZ plane

        }
    }
    allocated.clear();
    for(polygon pol : polygons){
        for(connection con: pol.connections){
         ht->   drawMegapix(shade, pol.points[con.a], pol.points[con.b], pol.points[con.c],0); //Reallocating on/off pixels in XY plane
          ht->  drawMegapixXZ(shade, pol.points[con.a], pol.points[con.b], pol.points[con.c],1); //Reallocating on/off pixels in XZ plane
         ht->   drawMegapixYZ(shade, pol.points[con.a], pol.points[con.b], pol.points[con.c],2); //Reallocating on/off pixels in YZ plane
        }
        
    }

}


void setup2(){

}



vector <vector3> intens1;
float calcDistance(point p1,point p2){
    float dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
    return dist;
}

//sorting the triangles based on the Z value for the XY-plane
vector<triangle> sortTriangles(vector<triangle> vecT){
    bool sorted = false;
    while(1){
        sorted = true;
        for(int i = 0; i < vecT.size()-1; i++){
            if(vecT[i].centerZ < vecT[i+1].centerZ){
                triangle tempTri = vecT[i];
                vecT[i] = vecT[i+1];
                vecT[i+1] = tempTri;
                sorted=false;
            }
        }
        if(sorted==true){
            break;
            }
        }
    return vecT;
}
//sorting the triangles based on the Y value for the XZ-plane
vector<triangle> sortTrianglesXZ(vector<triangle> vecT){
    bool sorted = false;
    while(1){
        sorted = true;
        for(int i = 0; i < vecT.size()-1; i++){
            if(vecT[i].centerY < vecT[i+1].centerY){
                triangle tempTri = vecT[i];
                vecT[i] = vecT[i+1];
                vecT[i+1] = tempTri;
                sorted=false;
            }
        }
        if(sorted==true){
            break;
        }
        
    }
    return vecT;
}

//sorting the triangles based on the X value for the YZ-plane
vector<triangle> sortTrianglesYZ(vector<triangle> vecT){
    bool sorted = false;
    while(1){
        sorted = true;
        for(int i = 0; i < vecT.size()-1; i++){
            if(vecT[i].centerX < vecT[i+1].centerX){
                triangle tempTri = vecT[i];
                vecT[i] = vecT[i+1];
                vecT[i+1] = tempTri;
                sorted=false;
            }
        }
        if(sorted==true){
            break;
        }
        
    }
    return vecT;
}
// painter's  algorithm, sorts the triangles based on depth, and then rasterize them in order.
void painter (int selection){
    vector<triangle> triangleSorted;
    switch (selection){
        case 0 : triangleSorted = sortTriangles(trianglesXY);break;
        case 1 : triangleSorted = sortTrianglesXZ(trianglesXY);break;
        case 2 : triangleSorted = sortTrianglesYZ(trianglesXY);break;
        default: break;
    }

    for(int j = 0; j< triangleSorted.size();j++){
        intens1 = ph->phongLightTriangle(triangleSorted[j],focal);
        for(int i = 0; i < triangleSorted[j].points.size(); i++){
            triangleSorted[j].points[i].intensities = intens1[i];
            
        }
        switch(selection){
            case 0 : gou->rasterizeXY(triangleSorted[j].points[0], triangleSorted[j].points[1], triangleSorted[j].points[2]);break;
            case 1 : gou->rasterizeXZ(triangleSorted[j].points[0], triangleSorted[j].points[1], triangleSorted[j].points[2]);break;
            case 2 : gou->rasterizeYZ(triangleSorted[j].points[0], triangleSorted[j].points[1], triangleSorted[j].points[2]);break;
            default: break;
        }
    }
}

//reads the input file
void readFile(){
    
    std::ifstream file(inputFile);
    std::string str;
    int nbrPoly;
    int nbrConn;
    if (!file) {
        cout << "Unable to open file";
        exit(1);
    }
    int counter = 0;
    polygon poly;
    std::string delimiter = " ";
    while(std::getline(file, str)){
        if(counter==0) {
            nbrPoly = stoi(str);
            counter++;
        }
        else if(str == ""){
            for(int i = 0; i<poly.points.size(); i++){
            }
            if(poly.points.size() !=0){
                polygons.push_back(poly);
            }
            poly = *new polygon();
        }
        else if(str.length() < 3){
            if(counter==1){
                poly.size=stoi(str);
                counter++;
            }else{
                nbrConn = stoi(str);
            }
        }
        else if(str.length() == 5){
            std::string con1 = str.substr(0, str.find(delimiter));
            std::string temps = str.substr(con1.length()+1);
            std::string con2 = temps.substr(0, temps.find(delimiter));
            std::string con3 = str.substr(con2.length() + con1.length()+1);
            poly.addConnection(stoi(con1)-1,stoi(con2)-1,stoi(con3)-1);
        }else{
            std::string xcord = str.substr(0, str.find(delimiter));
            std::string temps = str.substr(xcord.length()+1);
            std::string ycord = temps.substr(0, temps.find(delimiter));
            std::string zcord = str.substr(ycord.length() + xcord.length()+1);
  //          std::cout << xcord << " " << ycord<< " " <<zcord << " \n";
            point p = *new point(stof(xcord),stof(ycord),stof(zcord));
            poly.addPoint(p);
        }
    }
}
//function for the input of the keyboard while running
void keyboard(int key, int x, int y){
    switch (key) {
        case '1' : {
            float kar,kag,kab;
            std::cout <<"\n Enter the new values for K_a example: 0.2 0.3 0.7 \n";
            cin>>kar >> kag >> kab;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>kar>>kag>>kab;
            }
            ka = {kar,kag,kab};
            break;
        }
        case '2' : {
            float kdr,kdg,kdb;
            std::cout <<"\n Enter the new values for K_d example: 0.8 0.6 0.8 \n";
            cin>>kdr >> kdg >> kdb;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>kdr>>kdg>>kdb;
            }
            kd = {kdr,kdg,kdb};
            break;
        }
        case '3' : {
            float ksr,ksg,ksb;
            std::cout <<"\n Enter the new values for K_s example: 1.0 0.6 1.0 \n";
            cin>>ksr >> ksg >> ksb;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>ksr>>ksg>>ksb;
            }
            ks= {ksr,ksg,ksb};
            break;
        }
        case '4' :{
            float xcord,ycord,zcord;
            std::cout <<"\n Enter the new coordinates for the focal point example: 0.5 0.5 -2.0 \n";
            cin>>xcord >> ycord >> zcord;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>xcord>>ycord>>zcord;
            }
            focal= {xcord,ycord,zcord};
            break;
        }
        case '5' : {
            float xlight,ylight,zlight;
            std::cout <<"\n Enter the new coordinates for the light source point example: 0.5 0.5 2.0 \n";
            cin>>xlight >> ylight >> zlight;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>xlight>>ylight>>zlight;
            }
            light= {xlight,ylight,zlight};
            break;
        }
        case '6' : {
            float phng;
            std::cout <<"\n Enter the new phong constant(n), example: 5 \n";
            cin>> phng;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>> phng;
            }
            n_const = phng;
            break;
        }
        case '7' : {
            float aint;
            std::cout <<"\n Enter the new intensity for ambient light(I_a), example: 0.5 \n";
            cin>> aint;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>> aint;
            }
            i_a = aint;
            break;
        }
        case '8' : {
            float lint;
            std::cout <<"\n Enter the new intensity for light source intensity(I_d), example: 0.8 \n";
            cin>> lint;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>> lint;
            }
            i_l = lint;
            break;
        }
        case '9' : {
            int t;
            std::cout <<"\n Enter the level of brightness in halftoning, example: 7 \n";
            cin>> t;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>> t;
            }
            shade = t;
            reTone();
            break;
        }
        case '0' : {
            exit(0);
            break;
        }
    }
    
    glutPostRedisplay();
    std::cout<<"Select option 1-9 by clicking on window and pressing number. \n\n 1: Change k_a/ambient coefficient. \n     Current point: "<<ka.x<<  " " << ka.y << " " << ka.z << "  \n\n 2: Change k_d/diffuse coefficient. \n     Current point: "<<kd.x<<  " " << kd.y << " " << kd.z << "  \n\n 3: Change k_s/specular coefficient \n     Current point: "<<ks.x<<  " " << ks.y << " " << ks.z << "\n\n 4: Change position for focal point.\n     Current point: "<<focal.x<<  " " << focal.y << " " << focal.z << " \n\n"<< " 5: Change position for light source. \n     Current position: "<<light.x<<  " " << light.y << " " << light.z << " \n\n"<<" 6: Change the phong constant. \n     Current constant: " << n_const<< "\n\n 7: Change ambient light intensity.\n     Current intensity: "<<i_a<<" \n\n 8: Change light source intensity\n     Current intensity: "<<i_l<<" \n\n 9: Set half-toning level \n     Current level: "<<shade<<"  \n\n 0: Exit program \n\n";
}


void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    painter(0);
    painter(1);
    painter(2);
    setup2();
    glDrawPixels(height, width, GL_RGB, GL_FLOAT, PixelBuffer);
    glFlush(); 
    glutSwapBuffers ();
}
   
    

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    focal = {0.5,-0.75,1};
    ka = {0.3, 0.4, 0.7};
    kd = {0.6, 0.8, 1.0};
    ks = {1.0, 1.0, 1.0};
    n_const=1;
    shade = 9;
    intens = ph->phongLight(poly,focal); //retrieves the phong insensities for all points.
    for(int i = 0; i < poly.points.size(); i++){
        poly.points[i].intensities = intens[i];
    }
    startUp = true;
    PixelBuffer = new float[height * width * 3];
    allocated = *new map<float, int>();
    readFile();
    createTriangles();
    std::cout<<"Select option 1-9 by clicking on window and pressing number. \n\n 1: Change k_a/ambient coefficient. \n     Current point: "<<ka.x<<  " " << ka.y << " " << ka.z << "  \n\n 2: Change k_d/diffuse coefficient. \n     Current point: "<<kd.x<<  " " << kd.y << " " << kd.z << "  \n\n 3: Change k_s/specular coefficient \n     Current point: "<<ks.x<<  " " << ks.y << " " << ks.z << "\n\n 4: Change position for focal point.\n     Current point: "<<focal.x<<  " " << focal.y << " " << focal.z << " \n\n"<< " 5: Change position for light source. \n     Current position: "<<light.x<<  " " << light.y << " " << light.z << " \n\n"<<" 6: Change the phong constant. \n     Current constant: " << n_const<< "\n\n 7: Change ambient light intensity.\n     Current intensity: "<<i_a<<" \n\n 8: Change light source intensity\n     Current intensity: "<<i_l<<" \n\n 9: Set half-toning level \n     Current level: "<<shade<<"  \n\n 0: Exit program \n\n";
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100); //set window position
    glutCreateWindow("Assignment 3"); //create and set main window title
    glClearColor (0,0,0,0); //clears the buffer of OpenGL
    glutDisplayFunc(display);  //callbacks display function
    glutSpecialFunc(keyboard);
    glutMainLoop();//main display loop, -will display until terminate
    return 0;
}
