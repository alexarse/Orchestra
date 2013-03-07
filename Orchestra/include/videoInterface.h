#ifndef _VIDEOINTERFACE_H_
#define _VIDEOINTERFACE_H_

#include "axLib.h"

class VideoInterface
{
public:
	virtual long getTimeMs()				 = 0;
	virtual long getTotalTimeMs()			 = 0;
	virtual void setVolume(double volume)	 = 0;
	virtual void play()						 = 0;
	virtual void stop()						 = 0;
	virtual bool loadVideo(const char* path) = 0;
};

#endif // _VIDEOINTERFACE_H_