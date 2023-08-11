#include"gameSetup.hpp"

string IntToString(int a)
{
    ostringstream temp;
    temp << a;
    return temp.str();
}


setup::setup()
{

car=new vehicule();
sky=new skybox("data/sky/sky.obj");
obj=new objloader();
int numbers=27;



for(int i=1;i<=numbers;i++)
{

		if(i<10)
		{
	std::string str=IntToString(i);
		
	std::string str2 = std::string("data/models/decor0"+str+".obj"); 
//	const char * chaine = str2.c_str();
	level.push_back(new decor(str2.c_str()));
	printf("%s ",str2.c_str());
}

if(i>=10 && i<100)
{
	std::string str=IntToString(i);
	std::string str2 = std::string("data/models/decor"+str+".obj"); 
//	const char * chaine = str2.c_str();
	level.push_back(new decor(str2.c_str()));
	printf("%s ",str2.c_str());
}

	

}

/*
level.push_back(new decor("data/models/decor02.obj"));
level.push_back(new decor("data/models/decor03.obj"));
level.push_back(new decor("data/models/decor04.obj"));
level.push_back(new decor("data/models/decor05.obj"));
level.push_back(new decor("data/models/decor06.obj"));
level.push_back(new decor("data/models/decor07.obj"));
level.push_back(new decor("data/models/decor08.obj"));
level.push_back(new decor("data/models/decor09.obj"));

level.push_back(new decor("data/models/decor10.obj"));
level.push_back(new decor("data/models/decor11.obj"));
level.push_back(new decor("data/models/decor12.obj"));
level.push_back(new decor("data/models/decor13.obj"));
level.push_back(new decor("data/models/decor14.obj"));
level.push_back(new decor("data/models/decor15.obj"));
level.push_back(new decor("data/models/decor16.obj"));

level.push_back(new decor("data/models/decor17.obj"));
level.push_back(new decor("data/models/decor18.obj"));
level.push_back(new decor("data/models/decor19.obj"));
level.push_back(new decor("data/models/decor20.obj"));
level.push_back(new decor("data/models/decor21.obj"));
level.push_back(new decor("data/models/decor22.obj"));
level.push_back(new decor("data/models/decor23.obj"));
level.push_back(new decor("data/models/decor24.obj"));
level.push_back(new decor("data/models/decor25.obj"));

level.push_back(new decor("data/models/decor26.obj"));
level.push_back(new decor("data/models/decor27.obj"));
*/

std::vector<unsigned int> anim;
obj->loadAnimation(anim,"data/water/water",200);
ocean=new decorAnime(anim,anim[0],vector3d(0.0,0,0.0),0,"ocean");

std::vector<unsigned int> animPart;
//obj->loadAnimation(animPart,"data/pluie/particule",50);
//particules=new decorAnime(animPart,animPart[0],vector3d(0.0,0,0.0),0,"particules");

cam=new camera();
m.value=0;
m.window=0;
createMenu();
up=false;
down=false;
right=false;
left=false;
visibilityRain=false;
visibilityFOG_=false;
//lightMovement=vector3d(10.0f,20.0f,-100.0f);


}



setup::~setup()
{
delete car;
for(int i=0;i<level.size();i++)
delete level[i];
delete sky;
delete cam;
delete obj;
delete ocean;
//delete particules;
}

void setup::mouseMove(int mx,int my)
{
	cam->control(mx,my);
}
void setup:: mouseState(int button, int state, int x, int y)
{
	cam->mouse( button,  state,  x,  y);
}
void setup::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		
	case 's' :
		case 'S' :
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		
			if (nTue==0)
			{
				printf ("\nMenu detache.\n");
				printf ("Pour le reattacher\n");
				printf ("\tau bouton gauche, taper g ou G\n\tau bouton droit, taper d ou D\n\tau bouton du milieu, taper m ou M\n\n");
				nTue=1;
			}
			break;


		case 'g':
			case 'G' :
			
			glutSetMenu ( m.nSousmenu1 ); // Choisit le menu courant
			glutAttachMenu(GLUT_RIGHT_BUTTON); // Attache le menu au bouton gauche
			nTue=0;
			break;

		case 'c':
		case 'C': 
		car->ouvrirPorte1();
		glutPostRedisplay();
		break;
		
		case 'v':
		case 'V': 
		car->ouvrirPorte2();
		glutPostRedisplay();
		break;
		     
	}
}
void setup::specialKey(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			up=true;
		
		glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			down=true;
		
		glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			right=true;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			left=true;
			glutPostRedisplay();
			break;	
			
	}
}

void setup::specialKeyUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			up=false;
	
		glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			down=false;
		
		glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			right=false;
	
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			left=false;
	
			glutPostRedisplay();
			break;	
			
	}
}


void setup::enablesfog()
{

glEnable(GL_FOG) ;
GLfloat fogcolor[4] = {0.7, 0.75, 0.8, 0.9} ;
GLint fogmode = GL_EXP ;
glFogi (GL_FOG_MODE, fogmode) ;
glFogfv(GL_FOG_COLOR, fogcolor) ;
glFogf(GL_FOG_DENSITY, 0.00015f) ;
glFogf(GL_FOG_START, 80.0) ;
glFogf(GL_FOG_END, 8500.0) ;



}

void setup::disablesfog()
{
glDisable(GL_FOG) ;
	
}

void setup::lighting()
{
	     
		
                        //positionnement de la lumière avec les différents paramètres
            if(m.value==5)
            {
			
        EnableLighting();
        }
        if(m.value==1)
        {
        	 glDisable(GL_LIGHTING);
        	 glDisable(GL_LIGHT0);
		}
		
	
}





void setup::update()
{
	gestionCam();
	//ocean->update(250);
	//particules->update(50);
	car->update();
	sky->update();
	
		if(m.value==6)
	{
		ocean->setSpeed(2,250);
	}
	
		if(m.value==7)
	{
		ocean->setSpeed(1,250);
	}
	else
	{
		ocean->setSpeed(1,250);
	}
	
	
	
}

void setup::gestionCam()
{
	
	if(up)
	{
		 if(cam->getPitch()!=90 && cam->getPitch()!=-90)
			cam->moveCamera(0);
		cam->moveCameraUp(180.0);
	}
	
	if(down)
	{
		 if(cam->getPitch()!=90 && cam->getPitch()!=-90)
			cam->moveCamera(180);
		cam->moveCameraUp(0.0);
	}
	
	if(right)
	{
			cam->moveCamera(-90);
	}
	
	if(left)
	{
			cam->moveCamera(90);
	}
}


void setup::draw()
{

		lighting();

		visibilityFOG();
	

	cam->update();
	
	 glTranslated(0,0,-10);
	 //cam->update();
	

 glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 

    glDepthMask(GL_FALSE); //disable the depth mask

    glEnable(GL_STENCIL_TEST); //enable the stencil testing

    glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); //set
	

   for(int i=1;i<level.size();i++)
	  level[i]->draw();
	  glPushMatrix();
	  car->draw();
		glPopMatrix();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //enable

    glDepthMask(GL_TRUE); //enable the depth mask

    glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //set the stencil


    glDisable(GL_TEXTURE_2D); //disable texturing of the 

    glDisable(GL_DEPTH_TEST); //disable depth testing of the

    glPushMatrix();
   	
   	
    glScalef(1.0f, 1.0f, -1.0f); //flip the shadow vertically
 	glTranslated(0,20,0);
	glRotatef(20,0,1,0); //rotate the square
	
    glColor4f(0,0,0,1); //color the shadow black
    level[0]->draw();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST); //enable depth testing
    glEnable(GL_TEXTURE_2D); //enable texturing

    glDisable(GL_STENCIL_TEST); //disable the stencil testing

//end

    glEnable(GL_BLEND); //enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
glColor4f(1,1,1,0.7);
glRotatef(20,0,1,0); //rotate the square
	  level[0]->draw();


    glDisable(GL_BLEND); //disable alpha blending
    glPushMatrix();
    EnableLighting();
    car->draw();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPopMatrix();
    glPushMatrix();
  	EnableLighting();
  for(int i=1;i<level.size();i++)

    level[i]->draw();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    drawOtherObject();
     glPopMatrix();

	//angle++;

}

void setup::EnableLighting()
{
			GLfloat ambient[] = {0.25f,0.25f,0.25f,0.4f};
	        GLfloat diffuse[] = {0.99f,0.99f,0.99f,0.49f};
	        GLfloat light0_position [] = {10.0f, 200.0f, -1000.0f, 1.0f};
	        GLfloat specular_reflexion[] = {0.6f,0.9f,0.9f,1.0f};
	        GLubyte shiny_obj = 128;
        
        
	 		glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
            glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
            glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
             glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
            glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
}


void setup::drawOtherObject()
{
	
	glPushMatrix();
	
	glRotated(sky->getRot(),0,0.5,0);
	glScaled(3,3,3);
	sky->drawSkybox();
	glPopMatrix();

	glPushMatrix();
	
	visibilityRAIN();
	
	
	glPopMatrix();
	
	
	glPushMatrix();


	glEnable(GL_BLEND) ;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
	glScaled(6,6,6);
	glColor4f(1,1,1,.75f); //color the shadow black
	ocean->draw();
	glDisable(GL_BLEND);


	glPopMatrix();
}

void setup::visibilityRAIN()
{
		if(m.value==8)
	{
	 setVisibilityRain(true);
	}
	
	if(m.value==9)
	{
	setVisibilityRain(false);	
	}
	
	if(getVisibilityRain())
	{
	
	glScaled(3.4,3.4,3.4);
	//particules->draw();
	}
	
}

void setup::visibilityFOG()
{
			if(m.value==10)
	{
		 setVisibilityFOG(true);
	}
	
		if(m.value==11)
	{
		 setVisibilityFOG(false);
	}
	
	
		if(getVisibilityFOG())
	{
	
	enablesfog();
	}
	
		if(getVisibilityFOG()==false)
	{
	
	disablesfog();
	}
}

void setup::setVisibilityFOG(bool b)
{
	visibilityFOG_=b;
}

bool setup::getVisibilityFOG()
{
	return visibilityFOG_;
}

void setup::setVisibilityRain(bool b)
{
	visibilityRain=b;
}

bool setup::getVisibilityRain()
{
	return visibilityRain;
}
