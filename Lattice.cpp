#include "stdafx.h"
#include "includeall.h"
#include "windows.h"
#include <fstream>
#include "math.h"

Lattice *lattice;

int latticeNewAnimationFrames;
int latticeNewAnimationLatticeX;
int latticeNewAnimationLatticeY;
int latticeNewAnimationLatticeZ;

int latticeLatticeType;
int latticeLatticeCustom;
int latticeLatticeCreateNew;

int latticeSelectedFrameFirst;
int latticeSelectedFrameLast;
int latticeSelectedFrameCurrent;
int latticeSelectionMade;
int latticeActiveFrame;
int latticeActiveFrameSource;
int latticeOpenAnimationFile;
char latticeOpenAnimationFileName[256+3+1];
int latticeOpenAnimationFileNameLength;
char latticeAnimationTitle[32];
int latticeSaveAnimationFile;
char latticeSaveAnimationFileName[256+3+1];
int latticeSaveAnimationFileNameLength;


void latticeInit()
{
	lattice=new Lattice();
	latticeNewAnimationFrames=LATTICE_DEFAULT_FRAMES;
	latticeNewAnimationLatticeX=LATTICE_DEFAULT_SIZE_X;
	latticeNewAnimationLatticeY=LATTICE_DEFAULT_SIZE_Y;
	latticeNewAnimationLatticeZ=LATTICE_DEFAULT_SIZE_Z;
	lattice->newAnimation();
	lattice->cleanFrames(0,lattice->getFrameCount());
//	lattice->testPatternRainbow(0);
	geometryInit();
}

Lattice::Lattice(void)
{

}

Lattice::~Lattice(void)
{
	delete frame;
}

int Lattice::newAnimation(void)
{
	if ((latticeNewAnimationLatticeX<0)|(latticeNewAnimationLatticeX>LATTICE_MAX_X)|
		(latticeNewAnimationLatticeY<0)|(latticeNewAnimationLatticeZ>LATTICE_MAX_Z)|
		(latticeNewAnimationLatticeZ<0)|(latticeNewAnimationLatticeZ>LATTICE_MAX_Z))
			return LATTICE_ERROR_WRONG_SIZE;

//	if (frame!=0)
//		delete [] frame;
	frame=new Frame[latticeNewAnimationFrames];
 	frameCount=latticeNewAnimationFrames;
	sizeX=latticeNewAnimationLatticeX;
	sizeY=latticeNewAnimationLatticeY;
	sizeZ=latticeNewAnimationLatticeZ;
	return 0;
}

int Lattice::testPatternRainbow(int f)
{
	int x,y,z;
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;
	for(x=0;x<sizeX;x++)
		for(y=0;y<sizeY;y++)
			for(z=0;z<sizeZ;z++)
			{
				frame[f].red[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=x*255/sizeX;
				frame[f].green[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=y*255/sizeY;
				frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=z*255/sizeZ;
			}
	return 0;
	
}
int Lattice::copyFrame(int f, unsigned char* buffer)
{
	int i;
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;
	for(i=0;i<LATTICE_MAX_SIZE;i++)
	{
		buffer[i]=frame[f].red[i];
		buffer[i+LATTICE_MAX_SIZE]=frame[f].green[i];
		buffer[i+2*LATTICE_MAX_SIZE]=frame[f].blue[i];
	}
}
int Lattice::copyFrameForUsb(int f, unsigned char* buffer)
{
	int i;
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;
	for(i=0;i<sizeX*sizeY*sizeZ;i++)
	{
		buffer[i]=frame[f].red[i];
		buffer[i+sizeX*sizeY*sizeZ]=frame[f].green[i];
		buffer[i+2*sizeX*sizeY*sizeZ]=frame[f].blue[i];
	}
}
int Lattice::drawVoxel(int f, int x, int y, int z, int r, int g, int b)
{
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;
	if ((x<0)|(x>sizeX)|(y<0)|(y>sizeY)|(z<0)|(z>sizeZ))
		return LATTICE_ERROR_WRONG_VOXEL;

	frame[f].red[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=r;
	frame[f].green[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=g;
	frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=b;
}
int Lattice::setCanvasStep(double step)
{
	this->canvasStep=step;
	this->canvasMinX=-this->sizeX*this->canvasStep/2;
	this->canvasMaxX=this->sizeX*this->canvasStep/2;
	this->canvasMinY=-this->sizeY*this->canvasStep/2;
	this->canvasMaxY=this->sizeY*this->canvasStep/2;
	this->canvasMinZ=-this->sizeZ*this->canvasStep/2;
	this->canvasMaxZ=this->sizeZ*this->canvasStep/2;
	return 1;
}

double Lattice::getCanvasStep()
{
	return this->canvasStep;
}
double Lattice::getCanvasMinX()
{
	return this->canvasMinX;
}
double Lattice::getCanvasMaxX()
{
	return this->canvasMaxX;
}
double Lattice::getCanvasMinY()
{
	return this->canvasMinY;
}
double Lattice::getCanvasMaxY()
{
	return this->canvasMaxY;
}
double Lattice::getCanvasMinZ()
{
	return this->canvasMinZ;
}
double Lattice::getCanvasMaxZ()
{
	return this->canvasMaxZ;
}

int Lattice::drawCube(int f, int x1, int y1, int z1, int x2, int y2, int z2, int r, int g, int b)
{
	int p;
	int x,y,z;
	p=0;
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;

	if (x1<0)	{x1=0;	p++;}		if (x1>=sizeX)	{x1=sizeX-1;	p++;}
	if (x2<0)	{x2=0;	p++;}		if (x2>=sizeX)	{x2=sizeX-1;	p++;}
	if (y1<0)	{y1=0;	p++;}		if (y1>=sizeY)	{y1=sizeY-1;	p++;}
	if (y2<0)	{y2=0;	p++;}		if (y2>=sizeY)	{y2=sizeY-1;	p++;}
	if (z1<0)	{z1=0;	p++;}		if (z1>=sizeZ)	{z1=sizeZ-1;	p++;}
	if (z2<0)	{z2=0;	p++;}		if (z2>=sizeZ)	{z2=sizeZ-1;	p++;}
	
	if (p==6)
		return LATTICE_ERROR_WRONG_VOXEL;
	
	for(x=x1;x<=x2;x++)
		for(y=y1;y<=y2;y++)
			for(z=z1;z<=z2;z++)
			{
				frame[f].red[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=r;
				frame[f].green[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=g;
				frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=b;
			}

	return 0;
}
int Lattice::drawTorus(int f, double centerX, double centerY, double centerZ, double angleStart, double angleEnd, double radiusX, double radiusY, double radius, double rotationX, double rotationY, double rotationZ, double rotationAngleX, double rotationAngleY, double rotationAngleZ, int r, int g, int b)
{
	int p;
	int x,y,z;
	int i,j,k;
	p=0;
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;

	double canvasX;
	double canvasY;
	double canvasZ;

	double canvasTempX;
	double canvasTempY;
	double canvasTempZ;

	int iterations;
	double ellipseX;
	double ellipseY;

	double dd;

	double radius_sq;
	radius_sq=radius*radius;
	double ck;
	double canvasStep_sq;
	canvasStep_sq=canvasStep*canvasStep;
	double angle;

	for(i=0;i<sizeX;i++)
		for(j=0;j<sizeY;j++)
			for(k=0;k<sizeZ;k++)
			{
				canvasX=(i-sizeX/2+0.5)*canvasStep;
				canvasY=(j-sizeY/2+0.5)*canvasStep;
				canvasZ=(k-sizeZ/2+0.5)*canvasStep;


				canvasX=canvasX-rotationX;
				canvasY=canvasY-rotationY;
				canvasZ=canvasZ-rotationZ;

				canvasTempX=canvasX*geometryCos(rotationAngleZ)-canvasY*geometrySin(rotationAngleZ);
				canvasTempY=canvasX*geometrySin(rotationAngleZ)+canvasY*geometryCos(rotationAngleZ);
				canvasX=canvasTempX;
				canvasY=canvasTempY;

				canvasTempX=canvasX*geometryCos(rotationAngleY)+canvasZ*geometrySin(rotationAngleY);
				canvasTempZ=-canvasX*geometrySin(rotationAngleY)+canvasZ*geometryCos(rotationAngleY);
				canvasX=canvasTempX;
				canvasZ=canvasTempZ;

				canvasTempY=canvasY*geometryCos(rotationAngleX)-canvasZ*geometrySin(rotationAngleX);
				canvasTempZ=canvasY*geometrySin(rotationAngleX)+canvasZ*geometryCos(rotationAngleX);
				canvasY=canvasTempY;
				canvasZ=canvasTempZ;

				canvasX=canvasX+rotationX;
				canvasY=canvasY+rotationY;
				canvasZ=canvasZ+rotationZ;

				canvasX=canvasX-centerX;
				canvasY=canvasY-centerY;
				canvasZ=canvasZ-centerZ;

				DistancePointEllipse(canvasX, canvasY, radiusX, radiusY, 1e-08, 32, iterations, ellipseX, ellipseY);
				
				angle=geometryArcTan(ellipseX/abs(ellipseY));
				if (ellipseY>0)
					angle=90-angle;
				else
					angle=270+angle;
	
				if (((angleStart<=angleEnd)&(angle>=angleStart)&(angle<=angleEnd))|((angleStart>=angleEnd)&((angle>=angleStart)|(angle<=angleEnd))))
				{
					dd=sqrt((ellipseX-canvasX)*(ellipseX-canvasX)+(ellipseY-canvasY)*(ellipseY-canvasY)+(canvasZ)*(canvasZ));

					if (dd<radius)
					{
						if ((255-r)>frame[f].red[LATTICE_GET_PIXEL_ADDRESS(i,j,k)])
							frame[f].red[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]+=r;
						else
							frame[f].red[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]=255;
						if ((255-g)>frame[f].green[LATTICE_GET_PIXEL_ADDRESS(i,j,k)])
							frame[f].green[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]+=g;
						else
							frame[f].green[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]=255;
						if ((255-b)>frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(i,j,k)])
							frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]+=b;
						else
							frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]=255;
					}
					else
						if (dd<(radius+canvasStep))
						{
							ck=1-(dd-radius)/canvasStep;
						if ((255-r*ck)>frame[f].red[LATTICE_GET_PIXEL_ADDRESS(i,j,k)])
							frame[f].red[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]+=r*ck;
						else
							frame[f].red[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]=255;
						if ((255-g*ck)>frame[f].green[LATTICE_GET_PIXEL_ADDRESS(i,j,k)])
							frame[f].green[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]+=g*ck;
						else
							frame[f].green[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]=255;
						if ((255-b*ck)>frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(i,j,k)])
							frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]+=b*ck;
						else
							frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(i,j,k)]=255;
						}
				}
			}
	return 0;
}

int Lattice::cleanFrame(int f)
{
	int x,y,z;
	if (f>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;
	for(x=0;x<sizeX;x++)
		for(y=0;y<sizeY;y++)
			for(z=0;z<sizeZ;z++)
			{
				frame[f].red[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=0;
				frame[f].green[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=0;
				frame[f].blue[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=0;
			}
}
int Lattice::cleanFrames(int fStart, int fCount)
{
	int x,y,z,i;
	int t;
	t=fStart+fCount;
	if (fStart>=frameCount)
		return LATTICE_ERROR_WRONG_FRAME;
	if (t>frameCount)
		return LATTICE_ERROR_WRONG_FRAME;

	for(i=fStart;i<(fStart+fCount);i++)
		for(x=0;x<sizeX;x++)
			for(y=0;y<sizeY;y++)
				for(z=0;z<sizeZ;z++)
				{
					frame[i].red[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=0;
					frame[i].green[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=0;
					frame[i].blue[LATTICE_GET_PIXEL_ADDRESS(x,y,z)]=0;
				}
}
int Lattice::getFrameCount()
{
	return frameCount;
}
int Lattice::getSizeX()
{
	return sizeX;
}
int Lattice::getSizeY()
{
	return sizeY;
}
int Lattice::getSizeZ()
{
	return sizeZ;
}
int Lattice::getSize()
{
	return sizeX*sizeY*sizeZ;
}

int latticeHandler()
{
	if (latticeSaveAnimationFile==1)
	{
		lattice->saveFile();
		latticeSaveAnimationFile=0;
	}
	if (latticeOpenAnimationFile==1)
	{
		lattice->openFile();
		latticeOpenAnimationFile=0;
	}
	if (latticeLatticeCreateNew)
	{
		lattice->newAnimation();
		SendMessageW((HWND)threadCoreFrmFramesHandler,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_FRAME_LIST,latticeNewAnimationFrames);
		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_LATTICE_SIZE,((lattice->getSizeX()*LATTICE_MAX_Y)+lattice->getSizeY())*LATTICE_MAX_Z+lattice->getSizeZ());
		latticeLatticeCreateNew=0;
	}
	if (latticeSelectionMade)
	{
		latticeActiveFrame=latticeSelectedFrameCurrent;
		latticeActiveFrameSource=0;
		latticeSelectionMade=0;
	}
	if (playbackPlaying)
	{
		if (playbackSelectionOnly)
		{
			if (playbackRepeat)
				if (latticeActiveFrame<(latticeSelectedFrameLast))
					latticeActiveFrame++;
				else
					latticeActiveFrame=latticeSelectedFrameFirst;
			else
				if (latticeActiveFrame<(latticeSelectedFrameLast))
					latticeActiveFrame++;
				else
					playbackPlaying=0;
		}
		else
		{
			if (playbackRepeat)
				latticeActiveFrame=(latticeActiveFrame+1)%lattice->getFrameCount();
			else
				if (latticeActiveFrame<(lattice->getFrameCount()-1))
					latticeActiveFrame++;
				else
					playbackPlaying=0;
		}
	}

	return 0;
}

int Lattice::saveFile()
{
	int i;
	int j;
	char buf[LATTICE_MAX_SIZE];

	unsigned char bufferOutHeader[HEADER_SIZE];
	
	for(i=0;i<HEADER_SIZE;i++)
		bufferOutHeader[i]=0;


	bufferOutHeader[PLAYBACK_OFFSET_FILEID]=0x4C;
	bufferOutHeader[PLAYBACK_OFFSET_FILEID+1]=0x73;
	bufferOutHeader[PLAYBACK_OFFSET_FILETYPE]=0x01;
	bufferOutHeader[PLAYBACK_OFFSET_RTAID]=0x00;
	*(int*)(&bufferOutHeader[PLAYBACK_OFFSET_FRAMECOUNT])=frameCount;
	

	bufferOutHeader[PLAYBACK_OFFSET_LATTICESIZE]=lattice->getSizeX();
	bufferOutHeader[PLAYBACK_OFFSET_LATTICESIZE+1]=lattice->getSizeY();
	bufferOutHeader[PLAYBACK_OFFSET_LATTICESIZE+2]=lattice->getSizeZ();


	const char* title=latticeAnimationTitle;
	int p;
	p=0;
	while (title[p]!=0)
	{
		bufferOutHeader[PLAYBACK_OFFSET_ANIMATIONTITLE+p]=title[p];
		p++;
	}
	bufferOutHeader[PLAYBACK_OFFSET_ANIMATIONTITLE+p]=0;

	std::ofstream fout(latticeSaveAnimationFileName, std::ios_base::out | std::ios_base::binary);
	if (!fout.is_open()) return 1;

	fout.write((const char*)bufferOutHeader, HEADER_SIZE);

	i=0;
	for(i=0;i<frameCount;i++)
	{
		for(j=0;j<sizeX*sizeY*sizeZ;j++)
			buf[j]=frame[i].red[j];
		fout.write((char*)&buf[0],  sizeX*sizeY*sizeZ);

		for(j=0;j<sizeX*sizeY*sizeZ;j++)
			buf[j]=frame[i].green[j];
		fout.write((char*)&buf[0],  sizeX*sizeY*sizeZ);

		for(j=0;j<sizeX*sizeY*sizeZ;j++)
			buf[j]=frame[i].blue[j];
		fout.write((char*)&buf[0], sizeX*sizeY*sizeZ);

	}
	fout.close();
	return 0;
}


int Lattice::openFile()
{
	int i;
	int j;
	char buf[LATTICE_MAX_SIZE];
	
	unsigned char bufferInHeader[HEADER_SIZE];

	std::ifstream fin(latticeOpenAnimationFileName, std::ios_base::in | std::ios_base::binary);
	if (!fin.is_open()) return 1;


	fin.read((char*)&bufferInHeader[0], HEADER_SIZE);
	if ((bufferInHeader[PLAYBACK_OFFSET_FILEID]==0x4C)&
		(bufferInHeader[PLAYBACK_OFFSET_FILEID+1]==0x73)&
		(bufferInHeader[PLAYBACK_OFFSET_FILETYPE]==0x01))
	{
		latticeNewAnimationFrames=*(int*)(&bufferInHeader[PLAYBACK_OFFSET_FRAMECOUNT]);

		latticeNewAnimationLatticeX=bufferInHeader[PLAYBACK_OFFSET_LATTICESIZE];
		latticeNewAnimationLatticeY=bufferInHeader[PLAYBACK_OFFSET_LATTICESIZE+1];
		latticeNewAnimationLatticeZ=bufferInHeader[PLAYBACK_OFFSET_LATTICESIZE+2];

		lattice->newAnimation();
			
		for(i=0;i<32;i++)
			latticeAnimationTitle[i]=bufferInHeader[PLAYBACK_OFFSET_ANIMATIONTITLE+i];
		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_ANIMATION_TITLE,0);

		threadCopyContentCoreOpenglIn();

		i=0;
		for(i=0;i<lattice->frameCount;i++)
		{
			fin.read((char*)&buf[0],sizeX*sizeY*sizeZ);
			for(j=0;j<sizeX*sizeY*sizeZ;j++)
				frame[i].red[j]=buf[j];

			fin.read((char*)&buf[0], sizeX*sizeY*sizeZ);
			for(j=0;j<sizeX*sizeY*sizeZ;j++)
				frame[i].green[j]=buf[j];

			fin.read((char*)&buf[0], sizeX*sizeY*sizeZ);
			for(j=0;j<sizeX*sizeY*sizeZ;j++)
				frame[i].blue[j]=buf[j];

	
		}

		SendMessageW((HWND)threadCoreFrmFramesHandler,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_FRAME_LIST,latticeNewAnimationFrames);

	}

	fin.close();
	return 0;

}
