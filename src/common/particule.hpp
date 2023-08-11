#ifndef DEF_PARTICULE_HPP
#define DEF_PARTICULE_HPP
#include"vector.h"
#include <gl/gl.h>
#include<gl/glu.h>
#include"menu.hpp"
#include"objloader.hpp"
#include<iostream>
 #ifndef GL_UNSIGNED_SHORT_5_6_5
 #define GL_UNSIGNED_SHORT_5_6_5 0x8363
 #endif
#ifndef M_PI
#define M_PI 3.1415926535
#endif

class particule
{
	public:
particule(const char * filename);
~particule();
void draw();
void update();


	private:
		int part;
		objloader *obj;
	

		
};

#endif
