#ifndef OBJLOADER_H
#define OBJLOADER_H
#include<stdio.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <algorithm>
#include "collisionplane.h"
#include"texture.hpp"
#include <cstdlib>
#include<GL/gl.h>
#include<GL/glu.h>
#include<cmath>
#include <map>
#define MAXLEVEL 4
#define M_PI    3.14159265358979323846

using namespace std;



float MAP(float au32_IN, float au32_INmin, float au32_INmax, float au32_OUTmin, float au32_OUTmax);




struct coordinate
{

	float x,y,z;

	coordinate(float a,float b,float c): x(a),y(b),z(c){
	}
};




struct material{
	std::string name;
	float alpha,ns,ni;
	float dif[3],amb[3],spec[3];
	int illum;
	int texture;
	material(const char* na,float al,float n,float ni2,float* d,float* a,float* s,int i,int t);
};


struct texcoord{
	float u,v;
	texcoord(float a,float b);
};



struct face{
		float vis;
		float nx,ny,nz;
	int facenum;
	bool four;
	int faces[4];
	int texcoord[4];
	int mat;
	face(int facen,int f1,int f2,int f3,int t1,int t2,int t3,int m);
	face(int facen,int f1,int f2,int f3,int f4,int t1,int t2,int t3,int t4,int m);
};


class objloader
{

public: 

objloader();
~objloader();
int load(const std::string& filename,std::vector<collisionplane>* collplane);
void loadAnimation(std::vector<unsigned int>& frames, std::string filename, unsigned int num);
void calculNormale();
void calculVisibilite();
void mouseMove(int mx,int my);
	//void dessineSceneXY();
	//void dessineSceneYZ();
	//void dessineSceneXZ();
void update();
void draw();
textures text;


 

private:
void smoothnormals();
std::vector<material*> materials;   //all materials
std::vector<texcoord*> texturecoordinate;   //all texture coorinate (UV coordinate)
std::vector<std::string*> coord;
std::vector<coordinate*> vertex;
std::vector<face*> faces;
std::vector<std::string> loadedTextures;
	std::vector<int> loadedTexturesNum;
std::vector<coordinate*> vertexnormals;
std::vector<coordinate*>normals;
std::vector<unsigned int> texture;//the id for all the textures (so we can delete the textures after use it)
bool ismaterial,isnormals,istexture,isvertexnormal;    //obvious
GLuint loadTexture(const char * filename,bool  useMipMap,int w,int h);
 std::vector<unsigned int> lists;    //the id for all lists (so we can delete the lists after use it)
void clean(); 
std::ofstream out;
};

#endif
