#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

#include "axLib.h"
#include "ControlBar.h"
#include "VideoInterface.h"
#include "VlcVideoPlayer.h"

/// @todo Needs Documentation.
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
	 * @brief Load 3D media files and video files. Calls respective functions inside classes. 
	 * @param Data3d 3D data, WE DONT KNOW YET WHAT!!!
     * @param videoPath Cleaned-up path to video for loading.
	 * @return false if it fails.
	 ***********************************************************************************/
    bool loadMedia(const char* videoPath); // @todo Implement loading 3D data!

	/********************************************************************************//**
	 * @brief Resize the Media Player (can not override minimum).
	 * @param size Resize parameters.
	 ***********************************************************************************/
    void mSize(const wxSize& size);

	/// @todo Needs Documentation.
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

    void changeSlider(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif // _MEDIAPLAYER_H_