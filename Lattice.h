
#define LATTICE_DEFAULT_FRAMES				600
#define LATTICE_DEFAULT_SIZE_X				20
#define LATTICE_DEFAULT_SIZE_Y				20
#define LATTICE_DEFAULT_SIZE_Z				24

#define LATTICE_MAX_X						24
#define LATTICE_MAX_Y						24
#define LATTICE_MAX_Z						24
#define LATTICE_MAX_SIZE					(LATTICE_MAX_X*LATTICE_MAX_Y*LATTICE_MAX_Z)

#define LATTICE_ERROR_WRONG_SIZE			1
#define LATTICE_ERROR_WRONG_FRAME			2
#define LATTICE_ERROR_WRONG_VOXEL			3

#define LATTICE_GET_PIXEL_ADDRESS(x,y,z)	((z*sizeY+y)*sizeX+x)

#define PLAYBACK_OFFSET_FILEID				0x0000
#define PLAYBACK_OFFSET_FILETYPE			0x0002
#define PLAYBACK_OFFSET_RTAID				0x0003
#define PLAYBACK_OFFSET_FRAMECOUNT			0x0005
#define PLAYBACK_OFFSET_LATTICESIZE			0x0009
#define PLAYBACK_OFFSET_ANIMATIONTITLE		0x000C
#define PLAYBACK_OFFSET_STREAM				0x0100
#define HEADER_SIZE 256


class Lattice
{
private:
	double canvasStep;
	double canvasMinX;
	double canvasMaxX;
	double canvasMinY;
	double canvasMaxY;
	double canvasMinZ;
	double canvasMaxZ;

private:
	class Frame
	{
	public:
		unsigned char red[LATTICE_MAX_SIZE];
		unsigned char green[LATTICE_MAX_SIZE];
		unsigned char blue[LATTICE_MAX_SIZE];
	};

	Frame* frame;
	int frameCount;
	int sizeX;
	int sizeY;
	int sizeZ;


public:
	Lattice(void);
	virtual ~Lattice(void);
	int newAnimation(void);
	int testPatternRainbow(int f);
	int copyFrame(int f, unsigned char* buffer);
	int copyFrameForUsb(int f, unsigned char* buffer);
	int drawVoxel(int f, int x, int y, int z, int r, int g, int b);
	int	drawTorus(int f, double centerX, double centerY, double centerZ, double angleStart, double angleEnd, double radiusX, double radiusY, double radius, double rotationX, double rotationY, double rotationZ, double rotationAngleX, double rotationAngleY, double rotationAngleZ, int r, int g, int b);
	int drawCube(int f, int x1, int y1, int z1, int x2, int y2, int z2, int r, int g, int b);
	int cleanFrame(int f);
	int cleanFrames(int fStart, int fCount);
	int getFrameCount();
	int getSizeX();
	int getSizeY();
	int getSizeZ();
	int getSize();
	int saveFile();
	int openFile();
	int setCanvasStep(double step);
	double getCanvasStep();
	double getCanvasMinX();
	double getCanvasMaxX();
	double getCanvasMinY();
	double getCanvasMaxY();
	double getCanvasMinZ();
	double getCanvasMaxZ();


};

extern Lattice *lattice;

extern int latticeNewAnimationFrames;
extern int latticeNewAnimationLatticeX;
extern int latticeNewAnimationLatticeY;
extern int latticeNewAnimationLatticeZ;
extern int latticeLatticeFrames;
extern int latticeLatticeType;
extern int latticeLatticeSizeX;
extern int latticeLatticeSizeY;
extern int latticeLatticeSizeZ;
extern int latticeLatticeCustom;
extern int latticeLatticeCreateNew;
extern int latticeSelectedFrameFirst;
extern int latticeSelectedFrameLast;
extern int latticeSelectedFrameCurrent;
extern int latticeSelectionMade;
extern int latticeActiveFrame;
extern int latticeOpenAnimationFile;
extern char latticeOpenAnimationFileName[256+3+1];
extern int latticeOpenAnimationFileNameLength;
extern char latticeAnimationTitle[32];
extern int latticeSaveAnimationFile;
extern char latticeSaveAnimationFileName[256+3+1];
extern int latticeSaveAnimationFileNameLength;


void latticeInit();
int latticeHandler();