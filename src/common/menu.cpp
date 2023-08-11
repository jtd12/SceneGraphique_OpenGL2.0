#include"menu.hpp"



void menu(int num)
{
	
  if(num == 0){
    glutDestroyWindow(m.window);
    exit(0);
  }else{
   m.value = num;
  }
  glutPostRedisplay();
 

}

void menu2(int num)
{
	
  if(num == 0){
    glutDestroyWindow(m.window);
    exit(0);
  }else{
   m.value = num;
  }
  glutPostRedisplay();
 

}

void menu3(int num)
{
	
  if(num == 0){
    glutDestroyWindow(m.window);
    exit(0);
  }else{
   m.value = num;
  }
  glutPostRedisplay();
 

}

void menuP(int num){
 if(num == 0){
    glutDestroyWindow(m.window);
    exit(0);
  }else{
    m.value = num;
  }
  glutPostRedisplay();
  

}

void createMenu()
{


	m.nSousmenu1 = glutCreateMenu(menu);
	
	glutAddMenuEntry("Enable Light", 1);
	glutAddMenuEntry("Disable Light", 5);
	
	m.nSousmenu2 = glutCreateMenu(menu2);
	glutAddMenuEntry("SPEED+", 6);
	glutAddMenuEntry("SPEED-", 7);
	
	m.nSousmenu3 = glutCreateMenu(menu3);
	glutAddMenuEntry("ENABLE RAIN", 8);
	glutAddMenuEntry("DISABLE RAIN", 9);
	glutAddMenuEntry("ENABLE FOG", 10);
	glutAddMenuEntry("DISABLE FOG", 11);
	
	m.nMenuprincipal = glutCreateMenu(menuP);
	
	glutAddSubMenu("Light", m.nSousmenu1);
	glutAddSubMenu("Water Velocity", m.nSousmenu2);
	
	glutAddSubMenu("WEATHER", m.nSousmenu3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}
