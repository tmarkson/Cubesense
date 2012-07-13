#include "stdafx.h"
#include "includeall.h"
#include "windows.h"
#include <mmsystem.h>
#include "math.h"
#include "fftw3.h"


#define ANALOG_SAMPLE_RATE (44100)
#define ANALOG_BUFFER_SIZE (ANALOG_SAMPLE_RATE/60)
#define ANALOG_FFT_SIZE (256)

//(ANALOG_SAMPLE_RATE/60)

short int waveIn1[ANALOG_BUFFER_SIZE];
short int waveIn2[ANALOG_BUFFER_SIZE];
short int waveInCopy1[ANALOG_BUFFER_SIZE];
short int waveInCopy2[ANALOG_BUFFER_SIZE];

int audioSoundFft[1024];

void threadAudioMain(void*)
{
/*	DWORD64 tcf;
	DWORD64 tc1;
	DWORD64 tc2;
	DWORD64 tc3;
	DWORD64 tcarray[128];
	int tcindex;

	QueryPerformanceFrequency((LARGE_INTEGER*)&tcf);
*/
	int average;

	HWAVEIN hWaveIn;
	MMRESULT result;

	WAVEFORMATEX pFormat;
	pFormat.wFormatTag=WAVE_FORMAT_PCM;
	pFormat.nChannels=1;
	pFormat.nSamplesPerSec=ANALOG_SAMPLE_RATE;
	pFormat.nAvgBytesPerSec=ANALOG_SAMPLE_RATE*2;
	pFormat.nBlockAlign=2;
	pFormat.wBitsPerSample=16;
	pFormat.cbSize=0;
	result = waveInOpen(&hWaveIn,0,&pFormat,0L,0L,WAVE_FORMAT_DIRECT);

	WAVEHDR WaveInHdr1;
	WaveInHdr1.lpData = (LPSTR)waveIn1;
	WaveInHdr1.dwBufferLength = ANALOG_BUFFER_SIZE*2;
	WaveInHdr1.dwBytesRecorded=0;
	WaveInHdr1.dwUser = 0L;
	WaveInHdr1.dwFlags = 0L;
	WaveInHdr1.dwLoops = 0L;
	result=waveInPrepareHeader(hWaveIn, &WaveInHdr1, sizeof(WAVEHDR));

	WAVEHDR WaveInHdr2;
	WaveInHdr2.lpData = (LPSTR)waveIn2;
	WaveInHdr2.dwBufferLength = ANALOG_BUFFER_SIZE*2;
	WaveInHdr2.dwBytesRecorded=0;
	WaveInHdr2.dwUser = 0L;
	WaveInHdr2.dwFlags = 0L;
	WaveInHdr2.dwLoops = 0L;
	result=waveInPrepareHeader(hWaveIn, &WaveInHdr2, sizeof(WAVEHDR));

	result=waveInAddBuffer(hWaveIn, &WaveInHdr1, sizeof(WAVEHDR));
	result=waveInAddBuffer(hWaveIn, &WaveInHdr2, sizeof(WAVEHDR));
	result = waveInStart(hWaveIn);

	fftw_complex* b1=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*ANALOG_FFT_SIZE);
	fftw_complex* b2=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*ANALOG_FFT_SIZE);
	fftw_plan p1=fftw_plan_dft_1d(ANALOG_FFT_SIZE, b1, b2, FFTW_FORWARD, FFTW_ESTIMATE);


	long fft_out_r[ANALOG_FFT_SIZE];
	long fft_out_i[ANALOG_FFT_SIZE];

	int i;
	for (i=0;i<ANALOG_BUFFER_SIZE;++i)
	{
		b1[i][0]=0;//20*sin((double)i/(double)ANALOG_BUFFER_SIZE*2.0*3.141*30);
		b1[i][1]=0;
	}
/*
	double tc1d;
	double tc2d;
	double tcrd;
	double tcfd;
*/



   //  fftw_destroy_plan(p);  
//}


//	tcindex=0;
	Sleep(1000);

//	QueryPerformanceCounter((LARGE_INTEGER*)&tc1);

	while(1==1)
	{
		Sleep(0);
	
	//	tcarray[tcindex]=tc1-tc2;

	//	if (tcindex==128)
	//		tcindex=0;
	//	tc3=(float)((float)tc1-(float)tc2)/(float)tcindex;
		
		while((WaveInHdr1.dwFlags&1)==0);
		WaveInHdr1.dwFlags=WaveInHdr1.dwFlags-1;
		result=waveInAddBuffer(hWaveIn, &WaveInHdr1, sizeof(WAVEHDR));
		memcpy(waveInCopy1,waveIn1,2*ANALOG_BUFFER_SIZE);

		average=0;	
		for (i=0; i < ANALOG_BUFFER_SIZE; ++i)
			average+=(waveInCopy1[i]);
		average=0;//average/ANALOG_BUFFER_SIZE;
		for (i=0; i < ANALOG_BUFFER_SIZE; ++i)
			waveInCopy1[i]=(waveInCopy1[i]-average);//*(0.5*(1-cos((2*3.141*i)/(ANALOG_BUFFER_SIZE-1))));

		for (i=0; i < ANALOG_FFT_SIZE; ++i)
			b1[i][0]=(waveInCopy1[i*44100/15360]>>6)*(0.5*(1-cos((2*3.141*i)/(ANALOG_FFT_SIZE-1))));
		fftw_execute(p1);
		for(i=0;i<ANALOG_FFT_SIZE;i++)
		{
			fft_out_r[i]=b2[i][0];
			fft_out_i[i]=b2[i][1];
		}
		for (i=0; i < ANALOG_FFT_SIZE; ++i)
			audioSoundFft[i]=10.0*log((double)(fft_out_r[i]*fft_out_r[i]+fft_out_i[i]*fft_out_i[i]));
		threadCopyContentAudioCoreIn();

		while((WaveInHdr2.dwFlags&1)==0);
		WaveInHdr2.dwFlags=WaveInHdr2.dwFlags-1;
		result=waveInAddBuffer(hWaveIn, &WaveInHdr2, sizeof(WAVEHDR));
		memcpy(waveInCopy2,waveIn2,2*ANALOG_BUFFER_SIZE);

		average=0;	
		for (i=0; i < ANALOG_BUFFER_SIZE; ++i)
			average+=(waveInCopy2[i]);//*(0.5*(1-cos((2*3.141*i)/(ANALOG_BUFFER_SIZE-1))));
		average=0;//average/ANALOG_BUFFER_SIZE;
		for (i=0; i < ANALOG_BUFFER_SIZE; ++i)
			waveInCopy2[i]=(waveInCopy2[i]-average);//*(0.5*(1-cos((2*3.141*i)/(ANALOG_BUFFER_SIZE-1))));

		for (i=0; i < ANALOG_FFT_SIZE; ++i)
			b1[i][0]=(waveInCopy2[i*44100/15360]>>6)*(0.5*(1-cos((2*3.141*i)/(ANALOG_FFT_SIZE-1))));
		fftw_execute(p1);
		for(i=0;i<ANALOG_FFT_SIZE;i++)
		{
			fft_out_r[i]=b2[i][0];
			fft_out_i[i]=b2[i][1];
		}
		for (i=0; i < ANALOG_FFT_SIZE; ++i)
			audioSoundFft[i]=10.0*log((double)(fft_out_r[i]*fft_out_r[i]+fft_out_i[i]*fft_out_i[i]));
		threadCopyContentAudioCoreIn();
/*		
		tcindex++;
		if (tcindex==1000)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&tc2);
			tc1d=tc1;
			tc2d=tc2;
			tcfd=tcf;
			tcrd=1/(tc2d-tc1d)*tcfd*tcindex*2;
			tcrd=tcrd;
		}
*/
	}


}