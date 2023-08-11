#include"decor.h"

decor::decor(const char * filename)
{
		obj=new objloader();
		sol=obj->load(filename,NULL);
	
		
}
decor::~decor()
{
	delete obj;
}
void decor::update()
{

}
void decor::draw()
{
	glPushMatrix();	
	
	glScaled(3,3,3);
	glCallList(sol);
	glPopMatrix();
}
