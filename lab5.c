#include<stdio.h>
#include<GL/glut.h>
float xmin=50,ymin=50,xmax=100,ymax=100;
float xvmin=200,yvmin=200,xvmax=400,yvmax=400;
int RIGHT=8,LEFT=2,TOP=4,BOTTOM=1;
float sx,sy,vx1,vy1,vx2,vy2;
float X1,Y1,X2,Y2;
int compute(float x,float y)
{
	int code=0;
	if(y > ymax)
		code = TOP;

	else if(y < ymin)
		code = BOTTOM;                                                                                              

	if(x > xmax)
		code = RIGHT;

	else if(x < xmin)
		code = LEFT;
	return code;
}
void cohen(float X1,float Y1,float X2,float Y2)
{
	float x,y;
	int  accept=0,done=0,code_p,code_q,code;

	code_p=compute(X1,Y1);
	code_q=compute(X2,Y2);
	do
     	{
		if(!(code_p | code_q))
		{
			accept=1;
			done=1;
		}
		else if(code_p & code_q)
			done=1;
		else
		{
			code=code_p ? code_p : code_q;
			if(code & TOP)
			{
				x=X1+(X2-X1)*(ymax-Y1)/(Y2-Y1);
				y=ymax;
			}
			else if(code & BOTTOM)
			{
				x=X1+(X2-X1)*(ymin-Y1)/(Y2-Y1);
				y=ymin;
			}
			else if(code & RIGHT)
			{
				y=Y1+(Y2-Y1)*(xmax-X1)/(X2-X1);
				x=xmax;
			}
			else
			{
				y=Y1+(Y2-Y1)*(xmin-X1)/(X2-X1);
				x=xmin;
			}
			if(code==code_p)
			{
				X1=x;
				Y1=y;
				code_p=compute(X1,Y1);
			}
			else
			{
				X2=x;
				Y2=y;
				code_q=compute(X2,Y2);
			}
		}
	}while(!done);

     if(accept)
	 {
		 sx=(xvmax-xvmin)/(xmax-xmin);
		 sy=(yvmax-yvmin)/(ymax-ymin);
		 vx1=xvmin+(X1-xmin)*sx;
		 vy1=xvmin+(Y1-ymin)*sy;
		 vx2=xvmin+(X2-xmin)*sx;
		 vy2=xvmin+(Y2-ymin)*sy;
		 
	 }
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,1,1);
	glLineWidth(2);
// The below code is used to draw a enterd lines
	glBegin(GL_LINES);
	glVertex2d(X1,Y1);
	glVertex2d(X2,Y2);
	glEnd();

	glColor3f(1,1,1);
// The below code is used to draw a window.
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();

	cohen(X1,Y1,X2,Y2);

	 glColor3f(1,1,1);
// The below code is for the view port 
	glBegin(GL_LINE_LOOP);
		 glVertex2f(xvmin,yvmin);
		 glVertex2f(xvmax,yvmin);
		 glVertex2f(xvmax,yvmax);
		 glVertex2f(xvmin,yvmax);
	 glEnd();

		 glColor3f(1,1,1);
// The clipped coordinates at the viewport.
	 glBegin(GL_LINES);
		 glVertex2d(vx1,vy1);
		 glVertex2d(vx2,vy2);
	 glEnd();
    glFlush();
}
void myinit()
{
	glClearColor(0,0,0,1);
	gluOrtho2D(0,500,0,500);
}
void main(int argc,char **argv)
{
	printf("\n Enter the points\n");
	scanf("%f%f%f%f",&X1,&Y1,&X2,&Y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("cohen sutherland: C Tathva");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}

