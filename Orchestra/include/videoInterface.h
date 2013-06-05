/********************************************************************************//**
 * @file	VideoInterface.h
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @author  Philippe Groarke <philippe.groarke@polymtl.ca>
 * @brief	class VideoInterface
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#ifndef _VIDEOINTERFACE_H_
#define _VIDEOINTERFACE_H_

#include "axLib.h"

struct VideoID
{
    int videoMoved;
    int videoStop;
};

class VideoInterface// : public virtual wxPanel
{
public:
    virtual double getPosition() const       = 0;
    virtual void mSize(const wxSize& size)   = 0;

	virtual long getTimeMs()				 = 0;
	/// @todo Needs Documentation.
	virtual long getTotalTimeMs()			 = 0;
	/// @todo Needs Documentation.
	virtual void setVolume(double volume)	 = 0;
    virtual void backward()                  = 0;
	virtual void stop()						 = 0;
	virtual void playPause()				 = 0;
    virtual void forward()                   = 0;
    virtual void mute()                      = 0;
    virtual void unMute()                    = 0;
    virtual void navigate(double pos)        = 0;
	virtual bool loadVideo(const char* path) = 0;

private:

    virtual void videoMovedCallback()        = 0;
};

#endif // _VIDEOINTERFACE_H_