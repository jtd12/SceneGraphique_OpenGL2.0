#ifndef DEF_SKYBOX_H
#define DEF_SKYBOX_H
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

class skybox
{
	public:
skybox(const char * filename);
~skybox();
void drawSkybox();
void update();
float getRot();

	private:
		int sky;
		objloader *obj;
		float rot;

		
};

#endif
