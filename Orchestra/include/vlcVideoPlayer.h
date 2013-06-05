/********************************************************************************//**
 * @file	VlcVideoPlayer.h
 * @author  Philippe Groarke <philippe.groarke@polymtl.ca>
 * @brief	class VlcVideoPlayer
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#ifndef _VLCVIDEOPLAYER_H_
#define _VLCVIDEOPLAYER_H_

#include "axLib.h"
#include "videoInterface.h"
#include "vlc.h"

/// @todo Needs Documentation.
class VlcVideoPlayer : public VideoInterface, public wxPanel
{
public:

	/********************************************************************************//**
	 * @brief  Constructor
	 * @param win wxWindow pointer.
     * @param id
     * @param pt Position x, y.
     * @param size Size width, height
	 ***********************************************************************************/
    VlcVideoPlayer(wxWindow* win, const VideoID& id, wxPoint pt, wxSize size);

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

    virtual void videoMovedCallback();
    void OnVideoCallback(wxCommandEvent& event);
	void videoTimeCallback();
	//void OnTimeCallback(wxCommandEvent& event);

    VideoID videoID_;

    // VLC Callbacks
    static void vlcPositionChanged(const libvlc_event_t *event, void* data);
	static void vlcTimeChanged(const libvlc_event_t *event, void* data);

    bool firstPlay_;

    DECLARE_EVENT_TABLE()

	_DEBUG_ int nb_time_callback;
};

#endif // _VLCVIDEOPLAYER_H_