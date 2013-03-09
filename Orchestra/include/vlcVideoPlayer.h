#ifndef _VLCVIDEOPLAYER_H_
#define _VLCVIDEOPLAYER_H_

#include "axLib.h"
#include "videoInterface.h"
#include "vlc.h"

class VlcVideoPlayer : public VideoInterface
{
public:
	/********************************************************************************//**
	 * @brief  Constructor
	 * @param win wxWindow pointer.
     * @param id
     * @param pt Position x, y.
     * @param size Size width, height
	 ***********************************************************************************/
    VlcVideoPlayer(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size);

    ~VlcVideoPlayer();

    virtual double getPosition() const;
    virtual void mSize(const wxSize& size);

	virtual long getTimeMs();
	virtual long getTotalTimeMs();
	virtual void setVolume(double volume);
    virtual void backward();
	virtual void stop();
	virtual void playPause();
    virtual void forward();
    virtual void mute();
    virtual void unMute();
    virtual void navigate(double pos);
	virtual bool loadVideo(const char* path);


private:

	libvlc_instance_t* vlcInstance;
	libvlc_media_t* vlcMedia;
	libvlc_media_player_t* vlcPlayer;
    libvlc_event_manager_t* vlcEventManager;

    bool firstPlay_;
};

#endif // _VLCVIDEOPLAYER_H_