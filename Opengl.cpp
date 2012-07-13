#include "stdafx.h"
#include "Includeall.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

int openglCanvasHandle;
int openglCanvasHdc;
int openglCanvasHeight;
int openglCanvasWidth;
int openglCanvasResize;
int openglSizeX;
int openglSizeY;
int openglSizeZ;
int openglLedSpacing;
int openglLedSize;
int openglBlackLeds;
int openglViewerCenterX;
int openglViewerCenterY;
int openglViewerDistance;
float openglViewerAngleY;
float openglViewerAngleX;
unsigned char openglVideoBuffer[3*LATTICE_MAX_SIZE];
int openglRenderQuality;
int openglShowBase;
int openglShowAxis;
int openglShowLattice;

void openglResizeCanvas()
{

	glMatrixMode (GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SwapBuffers((HDC)openglCanvasHdc);
 	glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, openglCanvasWidth, openglCanvasHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(GLfloat)openglCanvasWidth/(GLfloat)openglCanvasHeight,1.0f,98304.0f);
}


void openglInit()
{
	static HGLRC hRC;
	int pixelFormat;

	openglCanvasHdc = (long)GetDC((HWND)openglCanvasHandle);
    PIXELFORMATDESCRIPTOR pfd =
    {   
        sizeof(PIXELFORMATDESCRIPTOR),  // size
            1,                          // version
            PFD_SUPPORT_OPENGL |        // OpenGL window
            PFD_DRAW_TO_WINDOW |        // render to window
            PFD_DOUBLEBUFFER,           // support double-buffering
            PFD_TYPE_RGBA,              // color type
            8,                         // prefered color depth
            0, 0, 0, 0, 0, 0,           // color bits (ignored)
            0,                          // no alpha buffer
            0,                          // alpha bits (ignored)
            0,                          // no accumulation buffer
            0, 0, 0, 0,                 // accum bits (ignored)
            8,                         // depth buffer
            0,                          // no stencil buffer
            0,                          // no auxiliary buffers
            PFD_MAIN_PLANE,             // main layer
            0,                          // reserved
            0, 0, 0,                    // no layer, visible, damage masks
    };
    pixelFormat = ChoosePixelFormat((HDC)openglCanvasHdc, &pfd);
    SetPixelFormat((HDC)openglCanvasHdc, pixelFormat, &pfd);
    hRC = wglCreateContext((HDC)openglCanvasHdc);
    int a=wglMakeCurrent((HDC)openglCanvasHdc, hRC);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(1028, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	GLfloat lmodel_ambient[] = { (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	GLfloat light_ambient[] = {0.4, 0.4, 0.4};
	GLfloat light_diffuse[] = {0.5, 0.5, 0.5};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	openglResizeCanvas();
	
	openglSizeX=8;
	openglSizeY=8;
	openglSizeZ=8;
	openglLedSpacing=50;
	openglLedSize=8;
	openglViewerCenterX=0;
	openglViewerCenterY=0;
	openglViewerAngleY=70;
	openglViewerAngleX=200;
	openglViewerDistance=1150;

}

void openglDrawBase()
{
	GLfloat rd1,rd2,rd3;
	glTranslatef((openglSizeX-1)*openglLedSpacing/2, (openglSizeY-1)*openglLedSpacing/2, 0);

	rd1=(openglSizeX-1)*openglLedSpacing;
	rd2=-100;
	rd3=-(openglSizeY-1)*openglLedSpacing;

	glPushMatrix();
	glBegin(GL_QUADS);								// Draw A Quad
		glColor3f((GLfloat)60/255,(GLfloat)60/255,(GLfloat)60/255);
		glVertex3f( (GLfloat)rd1, (GLfloat)rd2,-(GLfloat)rd3);					// Top Right Of The Quad (Top)
		glVertex3f(-(GLfloat)rd1, (GLfloat)rd2,-(GLfloat)rd3);					// Top Left Of The Quad (Top)
		glVertex3f(-(GLfloat)rd1, (GLfloat)rd2, (GLfloat)rd3);					// Bottom Left Of The Quad (Top)
		glVertex3f( (GLfloat)rd1, (GLfloat)rd2, (GLfloat)rd3);					// Bottom Right Of The Quad (Top)
		glVertex3f( (GLfloat)rd1,-(GLfloat)rd2, (GLfloat)rd3);					// Top Right Of The Quad (Bottom)
		glVertex3f(-(GLfloat)rd1,-(GLfloat)rd2, (GLfloat)rd3);					// Top Left Of The Quad (Bottom)
		glVertex3f(-(GLfloat)rd1,-(GLfloat)rd2,-(GLfloat)rd3);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( (GLfloat)rd1,-(GLfloat)rd2,-(GLfloat)rd3);					// Bottom Right Of The Quad (Bottom)
		glColor3f((GLfloat)40/255,(GLfloat)40/255,(GLfloat)40/255);
		glVertex3f( (GLfloat)rd1, (GLfloat)rd2, (GLfloat)rd3);					// Top Right Of The Quad (Front)
		glVertex3f(-(GLfloat)rd1, (GLfloat)rd2, (GLfloat)rd3);					// Top Left Of The Quad (Front)
		glVertex3f(-(GLfloat)rd1,-(GLfloat)rd2, (GLfloat)rd3);					// Bottom Left Of The Quad (Front)
		glVertex3f( (GLfloat)rd1,-(GLfloat)rd2, (GLfloat)rd3);					// Bottom Right Of The Quad (Front)
		glVertex3f( (GLfloat)rd1,-(GLfloat)rd2,-(GLfloat)rd3);					// Top Right Of The Quad (Back)
		glVertex3f(-(GLfloat)rd1,-(GLfloat)rd2,-(GLfloat)rd3);					// Top Left Of The Quad (Back)
		glVertex3f(-(GLfloat)rd1, (GLfloat)rd2,-(GLfloat)rd3);					// Bottom Left Of The Quad (Back)
		glVertex3f( (GLfloat)rd1, (GLfloat)rd2,-(GLfloat)rd3);					// Bottom Right Of The Quad (Back)
		glColor3f((GLfloat)80/255,(GLfloat)80/255,(GLfloat)80/255);
		glVertex3f(-(GLfloat)rd1, (GLfloat)rd2, (GLfloat)rd3);					// Top Right Of The Quad (Left)
		glVertex3f(-(GLfloat)rd1, (GLfloat)rd2,-(GLfloat)rd3);					// Top Left Of The Quad (Left)
		glVertex3f(-(GLfloat)rd1,-(GLfloat)rd2,-(GLfloat)rd3);					// Bottom Left Of The Quad (Left)
		glVertex3f(-(GLfloat)rd1,-(GLfloat)rd2, (GLfloat)rd3);					// Bottom Right Of The Quad (Left)
		glVertex3f( (GLfloat)rd1, (GLfloat)rd2,-(GLfloat)rd3);					// Top Right Of The Quad (Right)
		glVertex3f( (GLfloat)rd1, (GLfloat)rd2, (GLfloat)rd3);					// Top Left Of The Quad (Right)
		glVertex3f( (GLfloat)rd1,-(GLfloat)rd2, (GLfloat)rd3);					// Bottom Left Of The Quad (Right)
		glVertex3f( (GLfloat)rd1,-(GLfloat)rd2,-(GLfloat)rd3);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad
	glPopMatrix();
}

void openglHandler()
{
	if (openglCanvasResize)
	{
		openglResizeCanvas();
		openglCanvasResize=0;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glTranslatef(openglViewerCenterX, openglViewerCenterY, -openglViewerDistance);
	glRotatef((float)openglViewerAngleY, 1.0f, 0.0f, 0.0f);
    glRotatef((float)openglViewerAngleX, 0.0f, -1.0f, 0.0f);

/*
	glTranslatef((GLfloat)((int)(x)*80-600), -50-(GLfloat)((openglSizeZ-1.0)/2.0*openglLedSpacing/10.0), 0);
	glTranslatef((GLfloat)(((x-(GLfloat)((openglSizeX-1.0)/2.0))*openglLedSpacing)), (GLfloat)(z-(GLfloat)((openglSizeZ-1.0)/2.0))*openglLedSpacing, (GLfloat)(y-(GLfloat)((openglSizeY-1.0)/2.0))*openglLedSpacing);

	openglDrawColumn(20, 50, 20);
*/
	if (openglShowAxis)
		openglDrawAxis();
	if (openglShowLattice)
		openglDrawLattice();
	if (openglShowBase)
		openglDrawBase();

	SwapBuffers((HDC)openglCanvasHdc);
}

void openglClearCanvas()
{
	if (openglCanvasResize)
	{
		openglResizeCanvas();
		openglCanvasResize=0;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SwapBuffers((HDC)openglCanvasHdc);
}

void openglDrawAxis()
{
	GLUquadric *myQuad_axis;
	myQuad_axis=gluNewQuadric();
	GLfloat x,y,z;

	glPushMatrix();
	glRotatef((GLfloat)90,(GLfloat)0,(GLfloat)1,(GLfloat)0);
	glTranslatef((GLfloat)((openglSizeY)*openglLedSpacing/2.0+openglLedSize),-(GLfloat)((openglSizeZ)*openglLedSpacing/2.0+openglLedSize),-(GLfloat)((openglSizeX)*openglLedSpacing/2.0+openglLedSize));
	glColor4f((GLfloat)1,(GLfloat)0,(GLfloat)0,(GLfloat)1);
	gluCylinder( myQuad_axis, 2.0,2.0, (openglSizeX)*openglLedSpacing+openglLedSize, 6, 1 );
	glTranslatef((GLfloat)0, (GLfloat)0, (GLfloat)(openglSizeX)*openglLedSpacing+openglLedSize);
	gluCylinder( myQuad_axis, 6, 1, 20, 6, 1 );
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)90,(GLfloat)0,(GLfloat)0,(GLfloat)1);
	glTranslatef(-(GLfloat)((openglSizeZ)*openglLedSpacing/2.0+openglLedSize),(GLfloat)((openglSizeX)*openglLedSpacing/2.0+openglLedSize),-(GLfloat)((openglSizeY)*openglLedSpacing/2.0+openglLedSize));
	glColor4f((GLfloat)0,(GLfloat)1,(GLfloat)0,(GLfloat)1);
	gluCylinder( myQuad_axis, 2.0,2.0, (openglSizeY)*openglLedSpacing+openglLedSize, 6, 1 );
	glTranslatef((GLfloat)0, (GLfloat)0, (GLfloat)(openglSizeY)*openglLedSpacing+openglLedSize);
	gluCylinder( myQuad_axis, 6, 1, 20, 6, 1 );
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)-90,(GLfloat)1,(GLfloat)0,(GLfloat)0);
	glTranslatef(-(GLfloat)((openglSizeX)*openglLedSpacing/2.0+openglLedSize),(GLfloat)((openglSizeY)*openglLedSpacing/2.0+openglLedSize),-(GLfloat)((openglSizeZ)*openglLedSpacing/2.0+openglLedSize));
	glColor4f((GLfloat)0,(GLfloat)0,(GLfloat)1,(GLfloat)1);
	gluCylinder( myQuad_axis, 2.0,2.0, (openglSizeZ)*openglLedSpacing+openglLedSize, 6, 1 );
	glTranslatef((GLfloat)0, (GLfloat)0, (GLfloat)(openglSizeZ)*openglLedSpacing+openglLedSize);
	gluCylinder( myQuad_axis, 6, 1, 20, 6, 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(GLfloat)((openglSizeX)*openglLedSpacing/2.0+openglLedSize),-(GLfloat)((openglSizeZ)*openglLedSpacing/2.0+openglLedSize),-(GLfloat)((openglSizeY)*openglLedSpacing/2.0+openglLedSize));
	glColor4f((GLfloat)0,(GLfloat)1,(GLfloat)0,(GLfloat)1);
	gluSphere(myQuad_axis, 3, 6, 6);
	glPopMatrix();

	gluDeleteQuadric(myQuad_axis);
}
void openglDrawCube(float rd)
{
	glBegin(GL_QUADS);								// Draw A Quad
		glVertex3f( (GLfloat)rd, (GLfloat)rd,-(GLfloat)rd);					// Top Right Of The Quad (Top)
		glVertex3f(-(GLfloat)rd, (GLfloat)rd,-(GLfloat)rd);					// Top Left Of The Quad (Top)
		glVertex3f(-(GLfloat)rd, (GLfloat)rd, (GLfloat)rd);					// Bottom Left Of The Quad (Top)
		glVertex3f( (GLfloat)rd, (GLfloat)rd, (GLfloat)rd);					// Bottom Right Of The Quad (Top)
		glVertex3f( (GLfloat)rd,-(GLfloat)rd, (GLfloat)rd);					// Top Right Of The Quad (Bottom)
		glVertex3f(-(GLfloat)rd,-(GLfloat)rd, (GLfloat)rd);					// Top Left Of The Quad (Bottom)
		glVertex3f(-(GLfloat)rd,-(GLfloat)rd,-(GLfloat)rd);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( (GLfloat)rd,-(GLfloat)rd,-(GLfloat)rd);					// Bottom Right Of The Quad (Bottom)
		glVertex3f( (GLfloat)rd, (GLfloat)rd, (GLfloat)rd);					// Top Right Of The Quad (Front)
		glVertex3f(-(GLfloat)rd, (GLfloat)rd, (GLfloat)rd);					// Top Left Of The Quad (Front)
		glVertex3f(-(GLfloat)rd,-(GLfloat)rd, (GLfloat)rd);					// Bottom Left Of The Quad (Front)
		glVertex3f( (GLfloat)rd,-(GLfloat)rd, (GLfloat)rd);					// Bottom Right Of The Quad (Front)
		glVertex3f( (GLfloat)rd,-(GLfloat)rd,-(GLfloat)rd);					// Top Right Of The Quad (Back)
		glVertex3f(-(GLfloat)rd,-(GLfloat)rd,-(GLfloat)rd);					// Top Left Of The Quad (Back)
		glVertex3f(-(GLfloat)rd, (GLfloat)rd,-(GLfloat)rd);					// Bottom Left Of The Quad (Back)
		glVertex3f( (GLfloat)rd, (GLfloat)rd,-(GLfloat)rd);					// Bottom Right Of The Quad (Back)
		glVertex3f(-(GLfloat)rd, (GLfloat)rd, (GLfloat)rd);					// Top Right Of The Quad (Left)
		glVertex3f(-(GLfloat)rd, (GLfloat)rd,-(GLfloat)rd);					// Top Left Of The Quad (Left)
		glVertex3f(-(GLfloat)rd,-(GLfloat)rd,-(GLfloat)rd);					// Bottom Left Of The Quad (Left)
		glVertex3f(-(GLfloat)rd,-(GLfloat)rd, (GLfloat)rd);					// Bottom Right Of The Quad (Left)
		glVertex3f( (GLfloat)rd, (GLfloat)rd,-(GLfloat)rd);					// Top Right Of The Quad (Right)
		glVertex3f( (GLfloat)rd, (GLfloat)rd, (GLfloat)rd);					// Top Left Of The Quad (Right)
		glVertex3f( (GLfloat)rd,-(GLfloat)rd, (GLfloat)rd);					// Bottom Left Of The Quad (Right)
		glVertex3f( (GLfloat)rd,-(GLfloat)rd,-(GLfloat)rd);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad
}

void openglDrawPyramid(float rd)
{
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glVertex3f( 0.0f, rd, 0.0f);					// Top Of Triangle (Front)
		glVertex3f(-rd,-rd, rd);					// Left Of Triangle (Front)
		glVertex3f( rd,-rd, rd);					// Right Of Triangle (Front)
		glVertex3f( 0.0f, rd, 0.0f);					// Top Of Triangle (Right)
		glVertex3f( rd,-rd, rd);					// Left Of Triangle (Right)
		glVertex3f( rd,-rd, -rd);					// Right Of Triangle (Right)
		glVertex3f( 0.0f, rd, 0.0f);					// Top Of Triangle (Back)
		glVertex3f( rd,-rd, -rd);					// Left Of Triangle (Back)
		glVertex3f(-rd,-rd, -rd);					// Right Of Triangle (Back)
		glVertex3f( 0.0f, rd, 0.0f);					// Top Of Triangle (Left)
		glVertex3f(-rd,-rd,-rd);					// Left Of Triangle (Left)
		glVertex3f(-rd,-rd, rd);					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid

}
void openglDrawLattice()
{

	GLUquadric *myQuad;
	int x,y,z;
	int xx;
	GLfloat rd;
	unsigned char r,g,b;
	int displayLed;
	int k;

	
	myQuad=gluNewQuadric();



		for(z=0;z<openglSizeZ;z++)
			for(y=0;y<openglSizeY;y++)
				for(x=0;x<openglSizeX;x++)
				{
					rd=openglLedSize;//OPENGL_LED_RADIUS;

					glPushMatrix();
					glTranslatef((GLfloat)(((x-(GLfloat)((openglSizeX-1.0)/2.0))*openglLedSpacing)), (GLfloat)(z-(GLfloat)((openglSizeZ-1.0)/2.0))*openglLedSpacing, (GLfloat)(y-(GLfloat)((openglSizeY-1.0)/2.0))*openglLedSpacing);
							
					r=openglVideoBuffer[(z*openglSizeY+y)*openglSizeX+x+0*LATTICE_MAX_SIZE];
					g=openglVideoBuffer[(z*openglSizeY+y)*openglSizeX+x+1*LATTICE_MAX_SIZE];
					b=openglVideoBuffer[(z*openglSizeY+y)*openglSizeX+x+2*LATTICE_MAX_SIZE];

					if ((openglBlackLeds==3)&(r==0)&(g==0)&(b==0))
						r=g=b=60;

					glColor4ub(r,g,b,255);		

					if (!((openglBlackLeds==1)&(r==0)&(g==0)&(b==0)))
					{
						if (openglRenderQuality==1)					
							gluSphere(myQuad, rd, 12, 12);
						if (openglRenderQuality==2)					
							gluSphere(myQuad, rd, 6, 6);
						if (openglRenderQuality==3)					
							//openglDrawCube(0.707*rd);
							gluSphere(myQuad, rd, 3, 3);
						if (openglRenderQuality==4)					
							//openglDrawPyramid(0.707*rd);
							gluSphere(myQuad, rd, 3, 2);
					}


					glPopMatrix();
				}
	

	gluDeleteQuadric(myQuad);
}