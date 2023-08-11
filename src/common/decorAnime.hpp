
#ifndef DEF_DECORANIME_HPP
#define DEF_DECORANIME_HPP
#include<stdio.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include"vector.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>

class decorAnime
{
	public:
	decorAnime(std::vector<unsigned int> & anim,unsigned int na,vector3d pos,int sp,
		const char * nam);
	~decorAnime();
	void draw();
	void update(int f);
	void setSpeed(int sp,int frameLimit);
	
	private:
		
				std::vector<unsigned int> frames;
				unsigned int outerview;
				unsigned int normalAnimation;
				vector3d position;
				vector3d aimPosition;
				vector3d aimRotation;
				vector3d rotation;
				vector3d curPos;
				unsigned int speed;
				unsigned int curFrame;
				std::string name;

};
#endif
