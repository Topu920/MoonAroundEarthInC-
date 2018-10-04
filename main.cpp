#include<windows.h>
#include<GL/glu.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <GL/glut.h>
using namespace std;

//Makes the image into a texture, and returns the id of the texture
GLuint LoadTextureRAW(const char *filename, int width, int height)
{
  GLuint textureId;
unsigned char *data;
     FILE *file;

    //CODE SEGMENT 1
     // open texture data
     file = fopen(filename, "r");
     if (file == NULL) return 0;

     // allocate buffer
     data = (unsigned char*) malloc(width * height * 4);

     //read texture data
     fread(data, width * height * 4, 1, file);
     fclose(file);
  for(int i = 0; i < width * height ; ++i)
{
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];
    //B = data[index];
    data[index] = R;
    data[index+2] = B;
}
  glGenTextures(1, &textureId); //Make room for our texture
  glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
  //Map the image to the texture
  glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D

         0,                            //0 for now
         GL_RGB,                       //Format OpenGL uses for image
         width, height,  //Width and height
         0,                            //The border of the image
         GL_RGB, //GL_RGB, because pixels are stored in RGB format
         GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                           //as unsigned number
         data);               //The actual pixel data
  delete(data);
  return textureId; //Returns the id of the texture
}
GLuint textureId1,textureID2,textureId3; //The id of the textur
GLUquadric *quad;
 double a;
double moon;
void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  quad = gluNewQuadric();
  textureId1 = LoadTextureRAW("earthmap.bmp", 1000, 500);
  textureID2=LoadTextureRAW("moon.bmp",1024,720);
    textureId3 = LoadTextureRAW("space.bmp", 1000, 500);

}
void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0, (float)w / (float)h, 1.0, 200.0);
}
void drawmoon()
{
    glEnable(GL_TEXTURE_2D);

  glPushMatrix();{
        glRotatef(moon,0,0,1);
     glTranslatef(3,3,-8);
        glRotatef(90,1,0,0);
                glRotatef(a*3,0,1,0);
             glScalef(1.5,1,1.5);
              glBindTexture(GL_TEXTURE_2D, textureID2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          gluQuadricTexture(quad,1);
        gluSphere(quad,.5,20,20);
        }glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}
void earth()
{
    glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
       const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
     a = t*90.0;
    glPushMatrix();{
        glTranslatef(0.0f, 0.0f, -10.0f);
  glRotatef(176.5,1.0f,2.0f,2.0f);
        glRotated(a*3,0,0,1);
  gluQuadricTexture(quad,1);
    gluSphere(quad,2,20,20);
    }glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void background()
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId3);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPushMatrix();
  {
      glTranslatef(0.0f, 0.0f, -10.0f);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-8.0f, -7.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(7.0f, -7.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(7.0f, 7.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-8.0f, 7.0f, 0.0f);
	glEnd();

	}glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    background();
    earth();
    drawmoon();
  glutSwapBuffers();
}

void update(int value)
{
    moon+=1;
    if(moon>360)
    {
        moon=moon-360;
    }
    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  PlaySound("dil.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("earth-moon");
  initRendering();
  glutDisplayFunc(drawScene);
  glutTimerFunc(25,update,0);
  glutReshapeFunc(handleResize);
  glutMainLoop();
  return 0;
}
