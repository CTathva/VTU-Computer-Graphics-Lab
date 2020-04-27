#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>                                                                                                                                       
float x1=200,y1=200,x2=100,y2=300,x3=200,y3=400,x4=300,y4=300;
float le[500],re[500];
void edgedetect(float x1,float y1,float x2,float y2)
{
	float mx,x,temp;
	int i;
           if((y2-y1)<0)
             {
                   temp=y1;y1=y2;y2=temp;         
                   temp=x1;x1=x2;x2=temp;
            }
            if((y2-y1)!=0)
                mx=(x2-x1)/(y2-y1);
             else
                mx=x2-x1;

            x=x1;
           for(i=y1;i<=y2;i++)
           {
             if(x < le[i])
                  le[i] = x;
             if(x > re[i])
                  re[i] = x;
             x+=mx;
            }
     }
void draw_pixel(int x,int y)
{
       glColor3f(1,1,0);
       glPointSize(2);
       glBegin(GL_POINTS);
            glVertex2i(x,y);
       glEnd();
   glFlush();
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{

	int i,y;
         for(i=0;i<500;i++)
            {
                le[i]=500;
                re[i]=0;
            }
           edgedetect(x1,y1,x2,y2);
           edgedetect(x2,y2,x3,y3);
           edgedetect(x3,y3,x4,y4);
            edgedetect(x4,y4,x1,y1);

         for(y=0;y<500;y++)
          {
               if(le[y]<=re[y])
               for(i=le[y];i<re[y];i++)
                    draw_pixel(i,y);
          }

     }
void display()
{
glClear(GL_COLOR_BUFFER_BIT);	
glColor3f(0, 0, 1);
 glBegin(GL_LINE_LOOP);
     glVertex2f(x1,y1);
     glVertex2f(x2,y2);
     glVertex2f(x3,y3);
     glVertex2f(x4,y4);
 glEnd();

      scanfill(x1,y1,x2,y2,x3,y3,x4,y4);

      glFlush();
}

void init()
{
        glClearColor(0,0,0,1);
        gluOrtho2D(0,700,0,700);
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Polygon Filling : C Tathva");
    glutDisplayFunc(display);
   init();
    glutMainLoop();
}
