/********************************************************************************//**
 * @file	ControlBar.h
 * @author	Philippe Groarke <philippe.groarke@polymtl.ca>
 * @brief	Control Bar
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#ifndef _CONTROLBAR_H_
#define _CONTROLBAR_H_

#include "axLib.h"

// TODO: DELETE
typedef mImageButton axButton;
typedef mToggleImage axToggle;

class ControlBar : public wxPanel
{

public:

	/********************************************************************************//**
	 * @brief  Constructor
	 * @param title Program name
	 ***********************************************************************************/
    ControlBar(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size);

	/********************************************************************************//**
	 * @brief  Resize the Control Bar (can not override minimum).
	 * @param size Resize parameters.
	 ***********************************************************************************/
    void mSize(const wxSize& size);

private:

    // Interface
    wxPanel* transportPanel;
    axButton* backwardBtn;
    axButton* forwardBtn;
    axButton* stopBtn;
    axToggle* playPauseBtn;
    //axSlider* slider;
    //axSlider* volumeCtrl;
    //axTimeCtrl* timeCtrl;

    //scoreCtrl* scoreCtrl;

    // Events
	void OnPaint(wxPaintEvent& event);

    //void test(wxCommandEvent& event);
    void test(wxPaintEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif //_CONTROLBAR_H_