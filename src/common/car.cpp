#include"car.h"

roue::roue(const char * filename)
{
	obj=new objloader();
	roue_=obj->load(filename,NULL);
}

roue::~roue()
{
	delete obj;
}
void roue::update()
{
	
}
void roue::draw()
{
	glPushMatrix();
	glCallList(roue_);
	glPopMatrix();
}

tb::tb(const char * filename)
{
	obj=new objloader();
	tb_=obj->load(filename,NULL);
}
tb::~tb()
{
	delete obj;
}
void tb::update()
{
	
}
void tb::draw()
{
	glPushMatrix();
	glCallList(tb_);
	glPopMatrix();
}


porte_vitre::porte_vitre(const char * filename)
{
	obj=new objloader();
	porte_vitre_=obj->load(filename,NULL);
}
porte_vitre::~porte_vitre()
{
	delete obj;
}
void porte_vitre::update()
{
	
}
void porte_vitre::draw()
{
	
		glPushMatrix();
		if(m.value==1)
	//	glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND) ;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
		glCallList(porte_vitre_);
		glDisable(GL_BLEND) ;
		//glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
}
void porte::setRotPorte(float r)
{
	rotPorte+=r;
}
void porte::setRotPorteEgal(float r)
{
	rotPorte=r;
}
float porte::getRotPorte()
{
	return rotPorte;
}
porte::porte(const char * filename)
{
	obj=new objloader();
	rotPorte=0.0f;
	p1_vitre=new porte_vitre("data/camionnete_vitres_porte1.obj");
	p2_vitre=new porte_vitre("data/camionnete_porte2_vitres.obj");
	porte_=obj->load(filename,NULL);
}
porte::~porte()
{
	delete obj;
	delete 	p1_vitre;
	delete 	p2_vitre;
}
void porte::update()
{
	p1_vitre->update();
	p2_vitre->update();
}
void porte::draw()
{
		glPushMatrix();
		p1_vitre->draw();
		p2_vitre->draw();
		glCallList(porte_);
		glPopMatrix();
}

vitres::vitres()
{
	obj=new objloader();
	vitres_=obj->load("data/vehicule/camionnete_vitres.obj",NULL);
}
vitres::~vitres()
{
	delete obj;
}

void vitres::update()
{
	
}
void vitres::draw()
{
	glPushMatrix();
	if(m.value==1)
	// glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND) ;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
	glCallList(vitres_);
	glDisable(GL_BLEND) ;
//	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}


volant::volant()
{
	obj=new objloader();
	volant_=obj->load("data/vehicule/volant.obj",NULL);
}
volant::~volant()
{
	delete obj;
}

void volant::update()
{
	
}

void volant::draw()
{
	glPushMatrix();
	glTranslated(-3,0,-4.95);
	glCallList(volant_);
	glPopMatrix();
}


vehicule::vehicule()
{
	
	obj=new objloader();	
	car=obj->load("data/vehicule/camionnete.obj",NULL);
	
	
	for(int i=0;i<4;i++)
	 wheel.push_back(new roue("data/vehicule/camionnete_roue.obj"));

	v=new vitres();
	door.push_back(new porte("data/vehicule/camionnete_porte1.obj"));
	door.push_back(new porte("data/vehicule/camionnete_porte2.obj"));
	tab=new tb("data/vehicule/camionnete_tb.obj");
	vv=new volant();

}

vehicule::~vehicule()
{
	delete obj;
	delete v;
	delete vv;
	for(int i=0;i<door.size();i++)
	  delete door[i];
	delete tab;
	for(int i=0;i<wheel.size();i++)
	 delete wheel[i];

}

void vehicule::update()
{
	v->update();
	vv->update();
	for(int i=0;i<door.size();i++)
	 door[i]->update();
	tab->update();
	for(int i=0;i<wheel.size();i++)
	 wheel[i]->update();


}
void vehicule::ouvrirPorte1()
{
	door[0]->setRotPorte(-0.5f);
	if(door[0]->getRotPorte()<-75.0f)
	{
		door[0]->setRotPorteEgal(-75.0f);
	}
}
void vehicule::ouvrirPorte2()
{
	door[1]->setRotPorte(0.5f);
	if(door[1]->getRotPorte()>75.0f)
	{
		door[1]->setRotPorteEgal(75.0f);
	}
}

void vehicule::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslated(-500,-300,800);
	glScaled(30,30,30);	
	glPushMatrix();
	glTranslated(0,0,-5.5);
	glRotated(door[0]->getRotPorte(),0,0.5,0);
	door[0]->draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0,0,5.5);
	glRotated(door[1]->getRotPorte(),0,0.5,0);
	door[1]->draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(3,-11.5,-8);
	wheel[0]->draw();
	glTranslated(-26,0,0);
	wheel[1]->draw();
	glTranslated(0,0,15);
	wheel[2]->draw();
	glTranslated(26,0,0);
	wheel[3]->draw();
	glPopMatrix();
	
	glPushMatrix();
	v->draw();
	vv->draw();
	tab->draw();
	glCallList(car);
	glPopMatrix();
}
