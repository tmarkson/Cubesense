#include "stdafx.h"
#include "includeall.h"
#include "windows.h"
#include <cstdio>
#include "process.h"
#include "math.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned char *scriptSourceCode;
unsigned int scriptSourceCodeLength;
unsigned int scriptReadyToRun;
unsigned int scriptReadyToRunRealTime;
unsigned int scriptType;
int scriptRunning;
int threadScriptRunning;
unsigned char scriptErrors[SCRIPT_ERRORS_LENGTH];
unsigned int scriptErrorCount;
unsigned int scriptErrorRow[SCRIPT_ERRORS_COUNT];
int scriptStopScript;
HANDLE scriptThreadHandle;
int scriptTerminateThread;
int scriptSoundFft[1024];


void scriptInit()
{
	scriptRunning=0;
} 

namespace scriptInterface
{
	public interface class IHost
	{
		virtual bool checkTermination();
		virtual void showProgress(int p);
		virtual void showNumber(int n);
		int drawVoxel(int f, int x, int y, int z, int r, int g, int b);
		int drawCube(int f, int x1, int y1, int z1, int x2, int y2, int z2, int r, int g, int b);
		int drawTorus(int f, double centerX, double centerY, double centerZ, double angleStart, double angleEnd, double radiusX, double radiusY, double radius, double rotationX, double rotationY, double rotationZ, double rotationAngleX, double rotationAngleY, double rotationAngleZ, int r, int g, int b);
		int getFrameCount();
		int getSizeX();
		int getSizeY();
		int getSizeZ();
		int rnd(int max);
		double getCanvasMinX();
		double getCanvasMaxX();
		double getCanvasMinY();
		double getCanvasMaxY();
		double getCanvasMinZ();
		double getCanvasMaxZ();
		double getCanvasStep();
		double msin(double a);
		double mcos(double a);
		int setCanvasStep(double step);

	};
	public interface class IScript
	{
		void Initialize(IHost ^Host);
		void Main();
	};
}

public ref class ScriptIHost : scriptInterface::IHost
{
public:
	virtual void showProgress(int p)
	{
		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SET_PROGRES_BAR_VALUE,p);
	}

	virtual bool checkTermination()
	{
		int r;
		WaitForSingleObject(threadMutexScriptStatus, INFINITE);
		r=scriptTerminateThread;
		ReleaseMutex(threadMutexScriptStatus);	
		return r;
	}
	virtual void showNumber(int n)
	{
		SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_DEBUG_SHOW_NUMBER,n);
	}

	virtual int drawVoxel(int f, int x, int y, int z, int r, int g, int b)
	{
		return lattice->drawVoxel(f, x, y ,z, r, g, b);
	}
	virtual int drawCube(int f, int x1, int y1, int z1, int x2, int y2, int z2, int r, int g, int b)
	{
		return lattice->drawCube(f, x1, y1, z1, x2, y2, z2, r, g, b);
	}
	virtual int drawTorus(int f, double centerX, double centerY, double centerZ, double angleStart,  double angleEnd, double radiusX, double radiusY, double radius, double rotationX, double rotationY, double rotationZ, double rotationAngleX, double rotationAngleY, double rotationAngleZ, int r, int g, int b)
	{
		return lattice->drawTorus(f, centerX, centerY, centerZ, angleStart, angleEnd, radiusX, radiusY, radius, rotationX, rotationY, rotationZ, rotationAngleX, rotationAngleY, rotationAngleZ, r, g, b);
	}
	virtual int getFrameCount()
	{
		return lattice->getFrameCount();
	}
	virtual int getSizeX()
	{
		return lattice->getSizeX();
	}
	virtual int getSizeY()
	{
		return lattice->getSizeY();
	}
	virtual int getSizeZ()
	{
		return lattice->getSizeZ();
	}
	virtual double getCanvasMinX()
	{
		return lattice->getCanvasMinX();
	}
	virtual double getCanvasMaxX()
	{
		return lattice->getCanvasMinX();
	}
	virtual double getCanvasMinY()
	{
		return lattice->getCanvasMinY();
	}
	virtual double getCanvasMaxY()
	{
		return lattice->getCanvasMinY();
	}
	virtual double getCanvasMinZ()
	{
		return lattice->getCanvasMinZ();
	}
	virtual double getCanvasMaxZ()
	{
		return lattice->getCanvasMaxZ();
	}
	virtual double getCanvasStep()
	{
		return lattice->getCanvasStep();
	}
	virtual int setCanvasStep(double step)
	{
		lattice->setCanvasStep(step);
		return 1;
	}
	virtual double msin(double a)
	{
		return (double)sin((double)a);
	}
	virtual double mcos(double a)
	{
		return (double)cos((double)a);
	}
	virtual int rnd(int max)
	{
		int r;
		r=rand();
		r=r%max;
		return r;
	}
};



System::String^ scriptAppendVb(System::String^ script)
{
	System::String^ appendedScript;
	appendedScript=
		"Imports System"
		+System::Environment::NewLine+
		"Public Class Script"
		+System::Environment::NewLine+
		"Implements scriptInterface.IScript"
		+System::Environment::NewLine+
		"Dim cs As scriptInterface.IHost"
		+System::Environment::NewLine+
		"Public Sub Initialize(Host As scriptInterface.IHost) Implements scriptInterface.IScript.Initialize"
		+System::Environment::NewLine+
		"cs = Host"
		+System::Environment::NewLine+
		"Main()"
		+System::Environment::NewLine+
		"End Sub"
		+System::Environment::NewLine+
		script
		+System::Environment::NewLine+
		"End Class"
		+System::Environment::NewLine;
	return appendedScript;
}

System::String^ scriptAppendCs(System::String^ script)
{
	System::String^ appendedScript;
	appendedScript=
		"using System;"
		+System::Environment::NewLine+
		"class Script: scriptInterface.IScript"
		+System::Environment::NewLine+
		"{"
		+System::Environment::NewLine+
		"scriptInterface.IHost cs;"
		+System::Environment::NewLine+
		"public virtual void Initialize(scriptInterface.IHost Host)"
		+System::Environment::NewLine+
		"{"
		+System::Environment::NewLine+
		"cs = Host;"
		+System::Environment::NewLine+
		"Main();"
		+System::Environment::NewLine+
		"}"
		+System::Environment::NewLine+
		script
		+System::Environment::NewLine+
		"}"
		+System::Environment::NewLine;
	return appendedScript;
}



DWORD WINAPI scriptCompile( LPVOID lpParam ) 
//void scriptCompile(void*)
{
	int i,j,k,l,p;
	DWORD64 tcf;
	DWORD64 tc1;
	DWORD64 tc2;
	DWORD64 tc3;
	char tc[128];
	System::String ^script;
	unsigned char* singleError;
	System::String ^singleErrorSS;
	System::String ^singleErrorSSP;

	System::String ^appFullName;
	scriptInterface::IScript ^compiledScript;

	System::CodeDom::Compiler::CodeDomProvider ^provider;
	System::CodeDom::Compiler::CompilerParameters ^params;
	System::CodeDom::Compiler::CompilerResults ^results;
	System::CodeDom::Compiler::ICodeCompiler ^compiler;
	
	QueryPerformanceFrequency((LARGE_INTEGER*)&tcf);
	QueryPerformanceCounter((LARGE_INTEGER*)&tc1);
	
	srand(time(NULL));

	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_MAIN_STATUS,2);
	SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_SCRIPT_ERRORS,0);

	script=gcnew System::String((char*)scriptSourceCode);


	appFullName=System::Reflection::Assembly::GetEntryAssembly()->CodeBase;
	if (scriptType==SCRIPT_TYPE_VB)
		provider=gcnew  Microsoft::VisualBasic::VBCodeProvider();
	if (scriptType==SCRIPT_TYPE_CS)
		provider=gcnew  Microsoft::CSharp::CSharpCodeProvider();
	
	params=gcnew System::CodeDom::Compiler::CompilerParameters();
	params->GenerateExecutable=false;
	params->GenerateInMemory=true;
	params->IncludeDebugInformation=false;
	appFullName=appFullName->Substring(8,appFullName->Length-8);
	params->ReferencedAssemblies->Add(appFullName);
	params->ReferencedAssemblies->Add("System.Windows.Forms.dll");
	params->ReferencedAssemblies->Add("System.dll");
	compiler=provider->CreateCompiler() ;
	
	if (scriptType==SCRIPT_TYPE_VB)
		script=scriptAppendVb(script);
	if (scriptType==SCRIPT_TYPE_CS)
		script=scriptAppendCs(script);

	results = compiler->CompileAssemblyFromSource(params, script);

	scriptErrorCount=results->Errors->Count;
	p=0;
	if (results->Errors->Count!=0)
	{
		
		
		for(i=0;i<scriptErrorCount;i++)
		{
			singleErrorSS=((System::Object^)results->Errors[i])->ToString();
			l=singleErrorSS->Length;

			for(j=0;j<l;j++)
				if (','==singleErrorSS[j])
				{
					k=j;
					j=l;
				}
			for(j=k;j>=0;j--)
				if ('('==singleErrorSS[j])
				{
					if (scriptType==SCRIPT_TYPE_VB)
						scriptErrorRow[i]= System::Int32::Parse(singleErrorSS->Substring(j+1,k-1-j-1+1))-SCRIPT_EXTRA_LINES_VB;
					if (scriptType==SCRIPT_TYPE_CS)
						scriptErrorRow[i]= System::Int32::Parse(singleErrorSS->Substring(j+1,k-1-j-1+1))-SCRIPT_EXTRA_LINES_CS;
					sprintf_s(&tc[0], 20,"%i", scriptErrorRow[i]);
					singleErrorSSP=singleErrorSS->Substring(j,1)+gcnew System::String(tc)+singleErrorSS->Substring(k,l-k);//,l-k)
					j=0;
				}
				
			;
			l=singleErrorSSP->Length;
			

			//if (singleError!=0)
			//	delete singleError;
			//System::Runtime::InteropServices::Marshal::FreeHGlobal((System::IntPtr)(void*)singleError);
			singleError = (unsigned char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(singleErrorSSP);

			for(j=0;j<l;j++)
				if (j+p<SCRIPT_ERRORS_LENGTH)
					scriptErrors[j+p]=singleError[j];
			scriptErrors[p+l]=0;
			p=p+l+1;
 
		}
		SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_SCRIPT_ERRORS,0);


	}
	else
	{
		if (results->Errors->Count==0)
		{
			SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_SCRIPT_ERRORS,0);
			SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SET_PROGRES_BAR_VALUE,0);
			SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_MAIN_STATUS,3);

			QueryPerformanceCounter((LARGE_INTEGER*)&tc2);
			SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_COMPILETIME,(tc2-tc1)*1000/tcf);

	
			scriptInterface::IHost ^scriptIHost;
			scriptIHost=gcnew ScriptIHost;

			array<System::Object^>^ fParameters;
			fParameters = gcnew array<System::Object^>(1);
			fParameters[0]=scriptIHost;
			System::Object ^ o;
			o = results->CompiledAssembly->CreateInstance("Script");
			System::Type ^t;
			t = o->GetType();
			System::Reflection::MethodInfo ^mi;
			mi = t->GetMethod("Initialize");
			mi->Invoke(o, fParameters);

			QueryPerformanceCounter((LARGE_INTEGER*)&tc3);
			SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_RUNTIME,(tc3-tc2)*1000/tcf);

			SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SET_PROGRES_BAR_VALUE,0);
		}
	}
	WaitForSingleObject(threadMutexScriptStatus, INFINITE);
	threadScriptRunning=0;
	ReleaseMutex(threadMutexScriptStatus);
	return 0;
}


#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



using namespace std;



std::string exec(char* cmd)
{
    FILE* pipe = _popen(cmd, "rt");
    if (!pipe) return "ERROR";
    char buffer[8192];
    std::string result = "";
  /*  while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
    }

	*/
	while(fgets(buffer, 64, pipe))
	{
		result += buffer;
	}


    int r=_pclose(pipe);
    return result;
}

//#include <unistd.h>
#include <direct.h>

void scriptCompileRealTimeSource()
{





	std::string result = "";
	char   psBuffer[128];
	FILE   *pPipe;
	_chdir("F:\\Lumisense\\eigthCubed\\Software\\CubeSense\\Simulations");

	pPipe = _popen( "C:\\MinGW\\bin\\g++ -c -DBUILDING_EXAMPLE_DLL uscript.cpp  2>&1 && C:\\MinGW\\bin\\g++ -shared -o uscript.dll uscript.o -Wl,--out-implib,uscript.a 2>&1", "rt" );
	while(fgets(psBuffer, 128, pPipe))
		result += psBuffer;

	_chdir("F:\\Lumisense\\eigthCubed\\Software\\CubeSense");

	int i,j,k,l;


	scriptErrorCount=0;
	k=0;
	j=0;
	i=0;
	l=0;
	int ln=result.length();

	while(i<ln)
	{
		if ((result[i]=='\n'))
		{
			for(j=k;j<i;j++)
			{
				scriptErrors[l]=result[j];
				l=l+1;
			}
			scriptErrors[l]=0;
 			l=l+1;
			scriptErrorCount=scriptErrorCount+1;
			i=i+1;
		}
		i=i+1;
	}



	SendMessageW((HWND)wndprocFrmScriptOutputHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_SCRIPT_ERRORS,0);




/*	pPipe = _popen( "C:\\MinGW\\bin\\g++ -shared -o dll_test1.dll dll_test1.o -Wl,--out-implib,dll_test1.a 2>&1", "rt" );
	while(fgets(psBuffer, 128, pPipe))
		result += psBuffer;
*/

	/*
    _chdir("simulations\\");


	std::string result = "";

   char   psBuffer[128];
   FILE   *pPipe;
// ; C:\\MinGW\\bin\\g++ -shared -o dll_test1.dll dll_test1.o -Wl,--out-implib dll_test1.as
   if( (pPipe = _popen( "C:\MinGW\bin\g++ -shared -o dll_test1.dll dll_test1.o -Wl,--out-implib dll_test1.a", "rt" )) == NULL )
      exit( 1 );

   while(fgets(psBuffer, 128, pPipe))
   {
      printf(psBuffer);
	  result += psBuffer;
   }

   if (feof( pPipe))
   {
     printf( "\nProcess returned %d\n", _pclose( pPipe ) );
   }
   else
   {
     printf( "Error: Failed to read the pipe to the end.\n");
   }*/

}

void scriptHandler()
{


	if ((scriptReadyToRunRealTime)&(!scriptRunning))
	{
		scriptCompileRealTimeSource();
		scriptReadyToRunRealTime=0;

	}

	if ((scriptReadyToRun)&(!scriptRunning))
	{

		scriptRunning=1;
		threadScriptRunning=1;
		scriptStopScript=0;
		scriptReadyToRun=0;
		scriptTerminateThread=0;
//		scriptThreadHandle=(HANDLE)CreateThread(scriptCompile,0,NULL);
		scriptThreadHandle=CreateThread(NULL, NULL, scriptCompile, NULL, NULL, NULL);

	}
	else
	{
		WaitForSingleObject(threadMutexScriptStatus, INFINITE);
		if (threadScriptRunning==0)
		{
			scriptRunning=0;
		}
		ReleaseMutex(threadMutexScriptStatus);
	}

	if ((scriptStopScript==1)&(scriptRunning==1))
	{
		WaitForSingleObject(threadMutexScriptStatus, INFINITE);
		scriptTerminateThread=1;
		ReleaseMutex(threadMutexScriptStatus);
	}
}

int scriptRealTimeCommand;
int scriptRealTimePlaying;
void (*scriptMain)(void);
HMODULE hdll;
char* scriptGlBuffer;
int* audioFft;
void* ttt;

void scriptRealTimeHandler()
{
	int i;

	if (scriptRealTimeCommand==1)
	{
		//hdll = LoadLibraryA("F:\\Lumisense\\eigthCubed\\Software\\CubeSense\\Simulations\\uscript.dll");
		hdll = LoadLibraryA("F:\\Lumisense\\eigthCubed\\Software\\CubeSense\\Simulations\\uscript.dll");
		if (hdll!=0)
		{
			scriptMain=(void(*)(void))GetProcAddress(hdll,"scriptMain"); 
			scriptGlBuffer=(char*)GetProcAddress(hdll,"glBuffer"); 
			audioFft=(int*)GetProcAddress(hdll,"audioFft"); 
			//glBuffer=0;

			scriptRealTimePlaying=1;
			scriptRealTimeCommand=0;
		}
	}
	if (scriptRealTimeCommand==2)
	{
		FreeLibrary(hdll);
		scriptRealTimePlaying=0;
		scriptRealTimeCommand=0;
		scriptGlBuffer=0;
		scriptMain=0;
	}
	if (scriptRealTimePlaying==1) 
	{
		threadCopyContentAudioCoreOut();
		for(i=0;i<1024;i++)
			audioFft[i]=scriptSoundFft[i];
	

		scriptMain();
	}
	return;

}

