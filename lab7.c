#include<stdio.h>
#include<GL/glut.h>
float v[][3]={{-1,-0.5,0},{1,-0.5,0},{0,1,0},{0,0,1}};
int n;
void triangle(float *p,float *q,float *r)
{
	glVertex3fv(p);
	glVertex3fv(q);
	glVertex3fv(r);
}
void tetra(float *a,float *b,float *c,float *d)
{
	glColor3f(1,0,0);
	triangle(a,b,c);
	glColor3f(0,1,0);
	triangle(a,b,d);
	glColor3f(0,0,1);
	triangle(b,c,d);
	glColor3f(0,0,0);
	triangle(a,d,c);
}
void divide_tetra(float *a,float *b,float *c,float *d,int m)
{
	float mid[6][3];
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)
		{
			mid[0][j]=(a[j]+b[j])/2;
			mid[1][j]=(a[j]+c[j])/2;
			mid[2][j]=(a[j]+d[j])/2;
			mid[3][j]=(b[j]+c[j])/2;
			mid[4][j]=(b[j]+d[j])/2;
			mid[5][j]=(c[j]+d[j])/2;
		}
		divide_tetra(a,mid[1],mid[0],mid[2],m-1);
		divide_tetra(b,mid[0],mid[3],mid[4],m-1);
		divide_tetra(c,mid[1],mid[3],mid[5],m-1);
		divide_tetra(d,mid[2],mid[4],mid[5],m-1);
	}
	else
		tetra(a,b,c,d);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0],v[1],v[2],v[3],n);
	glEnd();
	glFlush();
}
void init(void)
{
	glClearColor(1,1,1,1);
	glOrtho(-2,2,-2,2,-10,10);
}
int main(int argc,char* *argv)
{	
	printf("Enter the number of divisions:");
	scanf("%d", &n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutCreateWindow("3D Sierpinski Gasket: C Tathva");
	init();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
