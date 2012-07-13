
#define LATTICE_SIZE_X 8
#define LATTICE_SIZE_Y 8
#define LATTICE_SIZE_Z 8
#define LATTICE_SIZE (LATTICE_SIZE_X*LATTICE_SIZE_Y*LATTICE_SIZE_Z)

extern "C"
{
	void __declspec(dllexport) scriptMain();
	char __declspec(dllexport) glBuffer[24*24*24];
	int  __declspec(dllexport) audioFft[1024];
}

void scriptMain()
{

	int x;
	int y;
	int z;
	
	int sp[LATTICE_SIZE_X];
	int audioFftFiltered[1024];

	int i,j;
	int len;
	int t;
	
	len=4;
	
	for(i=0;i<256-len;i++)
	{
		t=0;
		for(j=0;j<len;j++)
		{
			t=t+audioFft[i+j];
		}
		audioFftFiltered[i]=t/len;
	}
	
	
	for(x=0;x<LATTICE_SIZE_X;x++)
	{
		z=0;
		for(y=0;y<2;y++)
			z=z+audioFftFiltered[x*2+y+2];
		sp[x]=(z/2.0-100)/5;
		if (sp[x]>LATTICE_SIZE_Z)
			sp[x]=LATTICE_SIZE_Z;
		if (sp[x]<0)
			sp[x]=0;
	}
		

	for(x=0;x<LATTICE_SIZE_Y;x++)
		for(y=0;y<LATTICE_SIZE_Y;y++)
			for(z=0;z<LATTICE_SIZE_Z;z++)
			{
				glBuffer[z*LATTICE_SIZE_Y*LATTICE_SIZE_X+y*LATTICE_SIZE_X+x]=0;
				glBuffer[z*LATTICE_SIZE_Y*LATTICE_SIZE_X+y*LATTICE_SIZE_X+x+LATTICE_SIZE]=0;
				glBuffer[z*LATTICE_SIZE_Y*LATTICE_SIZE_X+y*LATTICE_SIZE_X+x+2*LATTICE_SIZE]=0;
			}

	for(x=0;x<LATTICE_SIZE_X;x++)
	{
		for(z=0;z<sp[x];z++)
			glBuffer[z*LATTICE_SIZE_Y*LATTICE_SIZE_X+7-x+LATTICE_SIZE]=255;
		glBuffer[sp[x]*LATTICE_SIZE_Y*LATTICE_SIZE_X+7-x]=255;	
	}



}
	
