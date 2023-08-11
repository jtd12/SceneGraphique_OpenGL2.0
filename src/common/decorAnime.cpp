#include"decorAnime.hpp"

decorAnime::decorAnime(std::vector<unsigned int> & anim,unsigned int na,vector3d pos,int sp,
		const char * nam)
{
			frames=anim;
			normalAnimation=na;
			speed=sp;
			name=nam;
			curPos=pos;
			curFrame=1;
		
}

decorAnime::~decorAnime()
{
	
}


void decorAnime::update(int f)
{
	curFrame++;
	if(curFrame>=f)
	 curFrame=1;
}

void decorAnime::draw()
{
	glPushMatrix();

	glTranslatef(curPos.x,curPos.y,curPos.z);
	glCallList(frames[curFrame]);

	glPopMatrix();
}

void decorAnime::setSpeed(int sp,int frameLimit)
{
	curFrame+=sp;
	
	if(curFrame>=frameLimit)
	{
		curFrame=1;
	}
	

}
