#ifndef DEF_MENU_HPP
#define DEF_MENU_HPP
#include <gl/gl.h>
#include<gl/glu.h>
#include<stdio.h>
#include"vector.h"
#include<vector>
#include<C:\library\freeglut\include\GL\freeglut.h>

void menu(int num);
void createMenu();


struct menu_
{
	
int value; 
int window;
int nSousmenu1; 
int nMenuprincipal;


};

extern menu_ m;


#endif


