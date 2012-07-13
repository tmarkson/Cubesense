#include "stdafx.h"
#include "includeall.h"


int playbackPlaybackCommand;
int playbackPlaying;
int playbackRepeat;
int playbackSelectionOnly;

void playbackInit()
{
	playbackPlaying=0;
}

void playbackHandler()
{
	if (playbackPlaybackCommand==1)
	{
		if (playbackSelectionOnly)
			latticeActiveFrame=latticeSelectedFrameFirst;
		playbackPlaying=1;
		playbackPlaybackCommand=0;
	}
	if (playbackPlaybackCommand==2)
	{
		playbackPlaying=0;
		playbackPlaybackCommand=0;
	}
	if (playbackPlaybackCommand==3)
	{
		playbackRepeat=1;
		playbackPlaybackCommand=0;
	}	
	if (playbackPlaybackCommand==4)
	{
		playbackRepeat=0;
		playbackPlaybackCommand=0;
	}
	if (playbackPlaybackCommand==5)
	{
		playbackSelectionOnly=1;
		playbackPlaybackCommand=0;
	}	
	if (playbackPlaybackCommand==6)
	{
		playbackSelectionOnly=0;
		playbackPlaybackCommand=0;
	}
}
