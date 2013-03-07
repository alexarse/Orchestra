/********************************************************************************//**
 * @file	main.h
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	Main Application
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#ifndef _ORCHESTRA_MAIN_H_
#define _ORCHESTRA_MAIN_H_

#include "axLib.h"
#include "partition.h"

class MainFrame : public wxFrame
{
public:
	/********************************************************************************//**
	 * @brief  Constructor
	 * @param title Program name
	 ***********************************************************************************/
    MainFrame(const wxString& title);

	/********************************************************************************//**
	 * @brief  Destructor
	 ***********************************************************************************/
	~MainFrame(){}
	
private:
	
	wxPanel* mainPanel;
	Partition* partition;

	/********************************************************************************//**
	 * @brief  MainFrame is the only Class to use wxSizeEvent and takes care of 
	 *		   resizing his child panels
	 ***********************************************************************************/
	_EVENT_ void OnSize(wxSizeEvent& event);

	/********************************************************************************//**
	 * @brief  MainFrame is the only Class to use wxMwximizeEvent and takes care of 
	 *		   resizing his child panels
	 ***********************************************************************************/
	_EVENT_ void OnMaximize(wxMaximizeEvent& event);

	DECLARE_EVENT_TABLE()
};

class Orchestra: public wxApp
{
public:

private:
    virtual bool OnInit();
	
	MainFrame* frame;
};

#endif