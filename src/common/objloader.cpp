#include "objloader.hpp"


	face::face(int facen,int f1,int f2,int f3,int t1,int t2,int t3,int m){
		facenum=facen;
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		texcoord[0]=t1;
		texcoord[1]=t2;
		texcoord[2]=t3;
		mat=m;
		four=false;
	}
	face::face(int facen,int f1,int f2,int f3,int f4,int t1,int t2,int t3,int t4,int m){
		facenum=facen;
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		texcoord[0]=t1;
		texcoord[1]=t2;
		texcoord[2]=t3;
		texcoord[3]=t4;
		mat=m;
		four=true;
	}
	
	material::material(const char* na,float al,float n,float ni2,float* d,float* a,float* s,int i,int t)
	{
		name=na;
		alpha=al;
		ni=ni2;
		ns=n;
		dif[0]=d[0];
		dif[1]=d[1];
		dif[2]=d[2];
		
		amb[0]=a[0];
		amb[1]=a[1];
		amb[2]=a[2];
		
		spec[0]=s[0];
		spec[1]=s[1];
		spec[2]=s[2];
		
		illum=i;
		texture=t;
	}
	
	texcoord::texcoord(float a,float b)
	{
		u=a;
		v=b;
	}
int objloader::load(const std::string& filename,std::vector<collisionplane>* collplane)
{


	std::ifstream in(filename.c_str());
	if(!in.is_open())
	{
		out << "Not opened file " << filename << std::endl;
		return -1;
	}
	std::string path=filename.substr(0,((filename.find_last_of('/')+1!=std::string::npos) ? (filename.find_last_of('/')+1):0));
	out << filename << std::endl;
	char buf[1500];
	int curmat=0;
	bool coll=false;
	int z=0;
	int h=-1;
	while(!in.eof())
	{
		in.getline(buf,1500);
		coord.push_back(new std::string(buf));
	}
	for(int i=0;i<coord.size();i++)
	{
		if((*coord[i])[0]=='#')
			continue;
		else if((*coord[i])[0]=='v' && (*coord[i])[1]==' ')
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));
			out << "v " << tmpx << " " << tmpy << " " << tmpz << std::endl;
		}else if((*coord[i])[0]=='v' && (*coord[i])[1]=='n')
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
			out << "vn " << tmpx << " " << tmpy << " " << tmpz << std::endl;
			isnormals=true;
		}else if((*coord[i])[0]=='f')
		{
			int a,b,c,d,e;			
		
			
				
				if(count(coord[i]->begin(),coord[i]->end(),' ')==4) //if this is a quad
            {
                if(coord[i]->find("//")!=std::string::npos) //if it's contain a normal vector, but not contain texture coorinate
                {
                    sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);  //read in this form
                    faces.push_back(new face(b,a,c,d,e,0,0,0,0,curmat));    //and put to the faces, we don't care about the texture coorinate in this case
                                                                                                                                //and if there is no material, it doesn't matter, what is curmat
                }else if(coord[i]->find("/")!=std::string::npos)    //if we have texture coorinate and normal vectors
                {
                    int t[4];   //texture coorinates
                    //read in this form, and put to the end of the vector
                    sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b,&e,&t[3],&b);
                    faces.push_back(new face(b,a,c,d,e,t[0],t[1],t[2],t[3],curmat));
                }else{
                    //else we don't have normal vectors nor texture coorinate
                    sscanf(coord[i]->c_str(),"f %d %d %d %d",&a,&b,&c,&d);
                    faces.push_back(new face(-1,a,b,c,d,0,0,0,0,curmat));       
                }
            }else{  //if it's a triangle
                            //do the same, except we use one less vertex/texture coorinate/face number
                    if(coord[i]->find("//")!=std::string::npos)
                    {
                        sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
                        faces.push_back(new face(b,a,c,d,0,0,0,curmat));
                    }else if(coord[i]->find("/")!=std::string::npos)
                    {
                        int t[3];
                        sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b);
                        faces.push_back(new face(b,a,c,d,t[0],t[1],t[2],curmat));
                    }else{
                        sscanf(coord[i]->c_str(),"f %d %d %d",&a,&b,&c);
                        faces.push_back(new face(-1,a,b,c,0,0,0,curmat));                   
                    }
            }
	}else if((*coord[i])[0]=='u' && (*coord[i])[1]=='s' && (*coord[i])[2]=='e')
	{
		char tmp[200];
		sscanf(coord[i]->c_str(),"usemtl %s",tmp);
		if(strcmp(tmp,"collision")==0)
		{
			coll=true;
		}else{
			coll=false;
			for(int i=0;i<materials.size();i++)
			{
				if(strcmp(materials[i]->name.c_str(),tmp)==0)
				{
					curmat=i;
					out << "curmat=" << i  << std::endl;
					break;
				}
			}
		}
	}else if((*coord[i])[0]=='m' && (*coord[i])[1]=='t' && (*coord[i])[2]=='l' && (*coord[i])[3]=='l')
	{
		char filen[200];
		sscanf(coord[i]->c_str(),"mtllib %s",filen);
		std::string filen2=path+filen;
		std::ifstream mtlin(filen2.c_str());
		if(!mtlin.is_open())
		{
			out << "connot open the material file " << filen2 << std::endl;
			clean();
			return -1;
		}
		ismaterial=true;
		std::vector<std::string> tmp;
		char c[200];
		while(!mtlin.eof())
		{
			mtlin.getline(c,200);
			tmp.push_back(c);
		}
		char name[200];
		char filename[200];
		float amb[3],dif[3],spec[3],alpha,ns,ni;
		int illum;
		unsigned int texture;
		bool ismat=false;
		strcpy(filename,"\0");
//		std::cout << tmp.size() << std::endl;
		for(int i=0;i<tmp.size();i++)
		{
			if(tmp[i][0]=='#')
				continue;
			if(tmp[i][0]=='n' && tmp[i][1]=='e' && tmp[i][2]=='w')
			{
				if(ismat)
				{
					if(strcmp(filename,"\0")!=0 && strcmp(filename,"collision")!=0)
					{
						materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,texture));
						strcpy(filename,"\0");
					}else{
							materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,-1));				
					}
				}
				ismat=false;
				sscanf(tmp[i].c_str(),"newmtl %s",name);
				out << "newmtl " << name << std::endl;
			}else if(tmp[i][0]=='N' && tmp[i][1]=='s')
			{
				sscanf(tmp[i].c_str(),"Ns %f",&ns);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='a')
			{
				sscanf(tmp[i].c_str(),"Ka %f %f %f",&amb[0],&amb[1],&amb[2]);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='d')
			{
				sscanf(tmp[i].c_str(),"Kd %f %f %f",&dif[0],&dif[1],&dif[2]);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='s')
			{
				sscanf(tmp[i].c_str(),"Ks %f %f %f",&spec[0],&spec[1],&spec[2]);
				ismat=true;
			}else if(tmp[i][0]=='N' && tmp[i][1]=='i')
			{
				sscanf(tmp[i].c_str(),"Ni %f",&ni);
				ismat=true;
			}else if(tmp[i][0]=='d' && tmp[i][1]==' ')
			{
				sscanf(tmp[i].c_str(),"d %f",&alpha);
				ismat=true;
			}else if(tmp[i][0]=='i' && tmp[i][1]=='l')
			{
				sscanf(tmp[i].c_str(),"illum %d",&illum);
				ismat=true;
			}else if(tmp[i][0]=='m' && tmp[i][1]=='a')
			{
				sscanf(tmp[i].c_str(),"map_Kd %s",filename);
				bool l=0;
				out << "Opening image: " << filename << std::endl;
				std::string filename2=path+filename;
				for(int i=0;i<loadedTextures.size();i++)
					if(loadedTextures[i]==filename2)
					{
						out << "loading "  << filename2 << std::endl;
						texture=loadedTexturesNum[i];
						l=1;
						break;
					}
				if(l==0)
				texture=text.loadBMP_custom(filename2.c_str());
				ismat=true;
			}
		}
			  if(ismat)   //there is no newmat after the last newmat, so we have to put the last material 'manually'
        {
            if(strcmp(filename,"\0")!=0)
            {
                materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,texture));
            }else{
                    materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,-1));              
            }
        }
	}else if((*coord[i])[0]=='v' && (*coord[i])[1]=='t')
	{
		float u,v;
		sscanf(coord[i]->c_str(),"vt %f %f",&u,&v);
		texturecoordinate.push_back(new texcoord(u,v));
		istexture=true;
	}
}
	if(materials.size()==0)
		ismaterial=false;
	else
		ismaterial=true;
	out << "numvertex :" << vertex.size() << " " << normals.size() << " " << faces.size() << " " << materials.size() << std::endl; 
	//draw
//smoothnormals();
if(isvertexnormal)
        smoothnormals();
    
	int num;
	num=glGenLists(1);
	glNewList(num,GL_COMPILE);
	int last=-1;
 for(int i=0;i<faces.size();i++) //go throught all faces
    {
        if(last!=faces[i]->mat && ismaterial)   //if we have a meterial AND the last material is not the same
        {
            //set all of the material property
            float diffuse[]={materials[faces[i]->mat]->dif[0],materials[faces[i]->mat]->dif[1],materials[faces[i]->mat]->dif[2],1.0};
            float ambient[]={materials[faces[i]->mat]->amb[0],materials[faces[i]->mat]->amb[1],materials[faces[i]->mat]->amb[2],1.0};
            float specular[]={materials[faces[i]->mat]->spec[0],materials[faces[i]->mat]->spec[1],materials[faces[i]->mat]->spec[2],1.0};
            glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
            glMaterialf(GL_FRONT,GL_SHININESS,materials[faces[i]->mat]->ns);
             
            last=faces[i]->mat; //set the current to last
            if(materials[faces[i]->mat]->texture==-1)   //if we don't have texture, disable it, else enable it
                glDisable(GL_TEXTURE_2D);
            else{
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,materials[faces[i]->mat]->texture); //and use it
            }
        }
		if(faces[i]->four)
		{
			GLfloat Jaune[] = {1.0f, 0.7f, 0.7f, 0.25f};
			//glColor4fv(Jaune);          // expliqué après
			//glColor4f(0,0,0,1); //color the shadow black
			glBegin(GL_QUADS);
			
      
                                //basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
                                //I subtract 1 because the index start from 0 in C++
                           //	if(isnormals)   //if there are normals
                 			
                            glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                          if(isvertexnormal)
                    glNormal3f(vertexnormals[faces[i]->faces[0]-1]->x,vertexnormals[faces[i]->faces[0]-1]->y,vertexnormals[faces[i]->faces[0]-1]->z);
                                //draw the faces
                                  if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[0]-1]->u,texturecoordinate[faces[i]->texcoord[0]-1]->v);
 
                                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                                 // glNormal3f(vertexnormals[faces[i]->faces[1]-1]->x,vertexnormals[faces[i]->faces[1]-1]->y,vertexnormals[faces[i]->faces[1]-1]->z);
							           if(isvertexnormal)
                    glNormal3f(vertexnormals[faces[i]->faces[1]-1]->x,vertexnormals[faces[i]->faces[1]-1]->y,vertexnormals[faces[i]->faces[1]-1]->z);
							    if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[1]-1]->u,texturecoordinate[faces[i]->texcoord[1]-1]->v);
							    glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                                 //glNormal3f(vertexnormals[faces[i]->faces[2]-1]->x,vertexnormals[faces[i]->faces[2]-1]->y,vertexnormals[faces[i]->faces[2]-1]->z);
							if(isvertexnormal)
                    glNormal3f(vertexnormals[faces[i]->faces[2]-1]->x,vertexnormals[faces[i]->faces[2]-1]->y,vertexnormals[faces[i]->faces[2]-1]->z);
							      if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[2]-1]->u,texturecoordinate[faces[i]->texcoord[2]-1]->v);
								glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
                                   // glNormal3f(vertexnormals[faces[i]->faces[3]-1]->x,vertexnormals[faces[i]->faces[3]-1]->y,vertexnormals[faces[i]->faces[3]-1]->z);
							if(isvertexnormal)
                    glNormal3f(vertexnormals[faces[i]->faces[3]-1]->x,vertexnormals[faces[i]->faces[3]-1]->y,vertexnormals[faces[i]->faces[3]-1]->z);
								      if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[3]-1]->u,texturecoordinate[faces[i]->texcoord[3]-1]->v);
								glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
                        glEnd();
                }else{
                      glBegin(GL_TRIANGLES);
				if(isnormals)   //if there are normals
                    glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
 
                if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[0]-1]->u,texturecoordinate[faces[i]->texcoord[0]-1]->v);
 
 
                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                
                if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[1]-1]->u,texturecoordinate[faces[i]->texcoord[1]-1]->v);
                
                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                
                
                if(istexture && materials[faces[i]->mat]->texture!=-1)
                    glTexCoord2f(texturecoordinate[faces[i]->texcoord[2]-1]->u,texturecoordinate[faces[i]->texcoord[2]-1]->v);
                
                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
            glEnd();
		}
	}
	glEndList();
	out << "3....." << std::endl;
	clean();
	lists.push_back(num);
	return num;
}

void objloader::clean()
{
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	for(int i=0;i<faces.size();i++)
		delete faces[i];
	for(int i=0;i<normals.size();i++)
		delete normals[i];
	for(int i=0;i<vertex.size();i++)
		delete vertex[i];
	for(int i=0;i<materials.size();i++)
		delete materials[i];
	for(int i=0;i<texturecoordinate.size();i++)
		delete texturecoordinate[i];
	for(int i=0;i<vertexnormals.size();i++)
		delete vertexnormals[i];
	coord.clear();
	faces.clear();
	normals.clear();
	vertex.clear();
	materials.clear();
	texturecoordinate.clear();
	vertexnormals.clear();
}

objloader::~objloader()
{
	for(std::vector<unsigned int>::const_iterator it=texture.begin();it!=texture.end();it++)
	{
		glDeleteTextures(1,&(*it));
	}
	for(std::vector<unsigned int>::const_iterator it=lists.begin();it!=lists.end();it++)
	{
		glDeleteLists(*it,1);
	}
}




GLuint objloader:: loadTexture(const char * filename,bool  useMipMap,int w,int h)
{
 GLuint texture;

  int width, height;
  
  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width=w;
  height=h;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );

return texture;
}

	/*unsigned int num;
	glGenTextures(1,&num);
	SDL_Surface* img=SDL_LoadBMP(filename);
	glBindTexture(GL_TEXTURE_2D,num);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	SDL_FreeSurface(img);
	texture.push_back(num);
	loadedTextures.push_back(filename);
	loadedTexturesNum.push_back(num);
	return num;
*/
objloader::objloader()
{
	ismaterial=false;
	isnormals=false;
	istexture=false;
	isvertexnormal=true;
	out.open("objreport.txt");
}

void objloader::smoothnormals()
{
	for(int i=1;i<vertex.size()+1;i++)
	{
		float vecX=0.0,vecY=0.0,vecZ=0.0;
		int num=0;
		for(int j=0;j<faces.size();j++)
		{
			if(faces[j]->faces[0]==i || faces[j]->faces[1]==i || faces[j]->faces[2]==i || faces[j]->faces[3]==i)
			{
				vecX+=normals[faces[j]->facenum-1]->x;
				vecY+=normals[faces[j]->facenum-1]->y;
				vecZ+=normals[faces[j]->facenum-1]->z;
				num++;
			}
		}
		if(num)
		{
			vecX/=num;
			vecY/=num;
			vecZ/=num;
		}
		float d=sqrt(vecX*vecX+vecY*vecY+vecZ*vecZ);
		if(d)
		{
			vecX/=d;
			vecY/=d;
			vecZ/=d;
		}
		vertexnormals.push_back(new coordinate(vecX,vecY,vecZ));
	}
}


void objloader::loadAnimation(std::vector<unsigned int>& frames, std::string filename, unsigned int num)
{
	char tmp[200];
	std::vector<collisionplane> collP;
	for(int i=0;i<=num;i++)
	{
		if(i<10)
			sprintf(tmp,"_00000%d",i);
		else if(i<100)
			sprintf(tmp,"_0000%d",i);
		else if(i<1000)
				sprintf(tmp,"_000%d",i);
		else if(i<10000)
				sprintf(tmp,"_00%d",i);
		else if(i<100000)
				sprintf(tmp,"_0%d",i);
		else if(i<1000000)
				sprintf(tmp,"_%d",i);
	
		std::string tmp2(filename+tmp);
		tmp2+=".obj";
		unsigned int id=load(tmp2,NULL);
		frames.push_back(id);		
	 } 
}






