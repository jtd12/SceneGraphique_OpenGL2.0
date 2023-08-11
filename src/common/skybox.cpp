#include"skybox.h"


skybox::skybox(const char * filename)
{
		obj=new objloader();
		sky=obj->load(filename,NULL);
        rot=0.0f;
}
 
skybox::~skybox()
{
      
}




void skybox::update()
{
rot+=0.1f;
}

float skybox::getRot()
{
return rot;	
}

void skybox:: drawSkybox()
{
	
    glPushMatrix();

    glScaled(3,3,3);
    glCallList(sky);
   
   	glPopMatrix();
  
       
}
 
