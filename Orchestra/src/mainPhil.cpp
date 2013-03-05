/********************************************************************************//**
 * @file	main.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	Main Application
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#include "mainPhil.h"


// TODO: Delete optional testing includes
#include <Windows.h>

IMPLEMENT_APP(Orchestra);

#define SEL_ONE  SELECT_ONLY_THIS_ID

bool Orchestra::OnInit()
{
	frame = new MainFrame(axT("Orchestra"));
	
	frame->Show();
	SetTopWindow(frame);

	return true;
}


//---------------------------------------------------------------------------------
// MainFrame
//---------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_SIZING(MainFrame::OnSize)
	EVT_SIZE(MainFrame::OnSize)
	//EVT_MAXIMIZE(MainFrame::OnMaximize)
END_EVENT_TABLE()

MainFrame::MainFrame(const axString& title)
    : axFrame(NULL, axID_ANY, title, axPoint(30, 30), axSize(500, 500))
{
	SetBackgroundColour(axColor(80, 80, 80));
	mainPanel = new axPanel(this, axID_ANY, axPoint(0, 0), this->GetSize());
	mainPanel->SetBackgroundColour(axColor(80, 80, 80));

    testBar = new ControlBar(mainPanel, wxID_ANY, wxPoint(0 , this->GetSize().y - 100), wxSize(this->GetSize().x, 100));

}


void MainFrame::OnSize(wxSizeEvent& event)
{
    //testBar->mSize(wxSize(this->GetSize().x, this->GetSize().y));
    testBar->mSize(this->GetSize());
}
