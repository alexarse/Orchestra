/********************************************************************************//**
 * @file	ControlBar.h
 * @author	Philippe Groarke <philippe.groarke@polymtl.ca>
 * @brief	Control Bar
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#ifndef _CONTROLBAR_H_
#define _CONTROLBAR_H_

#include "axLib.h"


class ControlBar : public wxPanel
{

public:

	/********************************************************************************//**
	 * @brief  Constructor
	 * @param win wxWindow pointer.
     * @param id
     * @param pt Position x, y.
     * @param size Size width, height
	 ***********************************************************************************/
    ControlBar(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size);

	/********************************************************************************//**
	 * @brief  Resize the Control Bar (can not override minimum).
	 * @param size Resize parameters.
	 ***********************************************************************************/
    void mSize(const wxSize& size);

	/********************************************************************************//**
	 * @brief  Get slider value (between 0.0 and 1.0)
	 ***********************************************************************************/
    double getSliderValue() const;

	/********************************************************************************//**
	 * @brief  Move slider position
     * @param val Value to change slider by (between 0.0 and 1.0)
	 ***********************************************************************************/
    void setSliderValue(double val);
    
    // Defines
    static const wxSize MINSIZE;
    static const wxPoint BTN_OFFSET;
    static const int BTN_DELTAX;
    static const wxPoint SLIDER_OFFSET;

private:

    // Interface
    axButton* backwardBtn;
    axButton* forwardBtn;
    axButton* stopBtn;
    axToggle* playPauseBtn;
    axSlider* slider;
    //axSlider* volumeCtrl;
    //axTimeCtrl* timeCtrl;

    //scoreCtrl* scoreCtrl;

    // Events
    void OnBackBtn(wxCommandEvent& event);
    void OnStopBtn(wxCommandEvent& event);
    void OnPlayPauseBtn(wxCommandEvent& event);
    void OnFwrdBtn(wxCommandEvent& event);

    void OnSliderLeftDown(wxCommandEvent& event);
    void OnSliderLeftUp(wxCommandEvent& event);
    void OnSliderMotion(wxCommandEvent& event);

    void OnPaint(wxPaintEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif //_CONTROLBAR_H_
