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
	 * @param title Program name
	 ***********************************************************************************/
    ControlBar(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size);

	/********************************************************************************//**
	 * @brief  Resize the Control Bar (can not override minimum).
	 * @param size Target resize parameters.
	 ***********************************************************************************/
    void mSize(wxSize size);

private:


    //DECLARE_EVENT_TABLE()
};

#endif //_CONTROLBAR_H_