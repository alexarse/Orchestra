#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

#include "axLib.h"
#include "ControlBar.h"
#include "VideoInterface.h"
#include "VlcVideoPlayer.h"

class MediaPlayer : public wxPanel
{
public:
	/********************************************************************************//**
	 * @brief  Constructor
	 * @param win wxWindow pointer.
     * @param id
     * @param pt Position x, y.
     * @param size Size width, height
	 ***********************************************************************************/
    MediaPlayer(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size);

	/********************************************************************************//**
	 * @brief  Load 3d media files and video files. Calls respective functions inside classes. Returns false if it fails.
	 * @param Data3d 3D data, WE DONT KNOW YET WHAT!!!
     * @param videoPath Cleaned-up path to video for loading.
	 ***********************************************************************************/
    bool loadMedia(const char* videoPath); // @todo Implement loading 3d data!

	/********************************************************************************//**
	 * @brief  Resize the Media Player (can not override minimum).
	 * @param size Resize parameters.
	 ***********************************************************************************/
    void mSize(const wxSize& size);

	/********************************************************************************//**
	 * @brief  Callback to move slider.
	 ***********************************************************************************/
    static void vlcPositionChanged(const libvlc_event_t *event, void *data);

    void changeSlider();

    // Defines
    static const wxSize MINSIZE;

private:
    VideoInterface* videoInterface;
    ControlBar* controlBar;

    // Interface

    // Events
    void OnBackBtn(wxCommandEvent& event);
    void OnStopBtn(wxCommandEvent& event);
    void OnPlayPauseBtn(wxCommandEvent& event);
    void OnFwrdBtn(wxCommandEvent& event);

    void OnSliderLeftDown(wxCommandEvent& event);
    void OnSliderLeftUp(wxCommandEvent& event);
    void OnSliderMotion(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif // _MEDIAPLAYER_H_