#include"particule.hpp"


particule::particule(const char * filename)
{
		obj=new objloader();
		part=obj->load(filename,NULL);
        rot=0.0f;
}
 
particule::~particule()
{
      
}




void particule::update()
{

}


void particule:: draw()
{
	
    glPushMatrix();
    if(m.value==1)
     glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
    glScaled(3,3,3);
    glCallList(part);
    if(m.value==1)
      glEnable(GL_LIGHTING);
   	glPopMatrix();
  
       
}
 
