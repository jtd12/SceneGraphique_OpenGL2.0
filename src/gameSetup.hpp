#ifndef DEF_GAMESETUP_HPP
#define DEF_GAMESETUP_HPP
#include"common/objloader.hpp"
#include"common/skybox.h"
#include"common/car.h"
#include"common/decor.h"
#include"common/decorAnime.hpp"
#include"common/camera.h"
#include"common/particule.hpp"
#include<GL/gl.h>
#include<GL/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>

class setup
{
	public:
		
	setup();
	~setup();
	void init();
	void keyboard(unsigned char key, int x, int y);
	void mouseMove(int mx,int my);
	void specialKey(int key, int x, int y);
	void enablesfog();
	void disablesfog();
	void lighting();
	void EnableLighting();
	void gestionCam();
	void visibilityFOG();
	void drawOtherObject();
	void	visibilityRAIN();
	bool getVisibilityRain();
	void  setVisibilityFOG(bool b);
	bool getVisibilityFOG();
	void  setVisibilityRain(bool b);
	void specialKeyUp(int key, int x, int y);
	void mouseState(int button, int state, int x, int y);
	void update();
	void draw();
	
	private:
	
	skybox *sky;
	vehicule * car;
	std::vector <decor*>  level;
	decorAnime*  ocean;
	decorAnime* particules;
	camera * cam;
	objloader *obj;
	bool up,down,right,left;
	int nTue;	
	bool visibilityRain,visibilityFOG_;
	
	
};

#endif
