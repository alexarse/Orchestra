#ifndef _ORCHESTRA_MAIN_H_
#define _ORCHESTRA_MAIN_H_

#include "axLib.h"

class VideoInterface
{
public:
	virtual long getTimeMs()				 = 0;
	virtual long getTotalTimeMs()			 = 0;
	virtual void setVolume(double volume)	 = 0;
	virtual void play()						 = 0;
	virtual void stop()						 = 0;
	virtual void loadVideo(const char* path) = 0;
};

#endif