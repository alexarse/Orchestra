#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

#include "axLib.h"
#include "ControlBar.h"

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
	 * @brief  Resize the Media Player (can not override minimum).
	 * @param size Resize parameters.
	 ***********************************************************************************/
    void mSize(const wxSize& size);

    // Defines
    static const wxSize MINSIZE;

private:
    ControlBar* controlBar;

    // Interface

    // Events
    void OnBackBtn(wxCommandEvent& event);
    void OnStopBtn(wxCommandEvent& event);
    void OnPlayPauseBtn(wxCommandEvent& event);
    void OnFwrdBtn(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif // _MEDIAPLAYER_H_