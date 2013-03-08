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
	frame = new MainFrame(wxT("Orchestra"));
	
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

MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(30, 30), wxSize(500, 500))
{
	SetBackgroundColour(axColor(80, 80, 80));
    this->SetMinSize(wxSize(300, 500));
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), GetSize());
	mainPanel->SetBackgroundColour(wxColor(80, 80, 80));

    // Create mediaPlayer
    mediaPlayer = new MediaPlayer(mainPanel, wxID_ANY, 
    			     wxPoint(0 , 0), 
    			     wxSize(GetSize()));

    //char* path = "resources/test.mp4";
    //mediaPlayer->loadMedia(path);

}


void MainFrame::OnSize(wxSizeEvent& event)
{
    //testBar->mSize(wxSize(this->GetSize().x, this->GetSize().y));
    // Je crois qu'il faut resize le mainPanel aussi avant de resize testBar.
    mainPanel->SetSize(GetSize());
    mediaPlayer->mSize(GetSize());
}
