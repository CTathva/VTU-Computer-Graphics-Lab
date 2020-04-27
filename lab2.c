#include<stdio.h>
#include<GL/glut.h>
float house[5][2]={{200,100},{400,100},{300,300}};
float h=200,k=100,theta;
void drawtriangle()
{
	glBegin(GL_LINE_LOOP);
	glVertex2fv(house[0]);
	glVertex2fv(house[1]);
	glVertex2fv(house[2]);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawtriangle();
	glTranslatef(h,k,0);
	glRotatef(theta,0,0,1);
	glTranslatef(-h,-k,0);
	drawtriangle();
	glFlush();
}
void init()
{
	gluOrtho2D(-700,700,-700,700);
}
void main(int argc,char** argv)
{
	printf("Enter the rotation angle.\n");
	scanf("%f",&theta);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(350,350);
	glutCreateWindow("house:C Tathva");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}

