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

MainFrame::MainFrame(const axString& title): axFrame(NULL, axID_ANY, title, axPoint(30, 30), axSize(500, 500))
{
	SetBackgroundColour(axColor(80, 80, 80));
	mainPanel = new axPanel(this, axID_ANY, axPoint(0, 0), this->GetSize());
	mainPanel->SetBackgroundColour(axColor(80, 80, 80));

    ControlBar* test = new ControlBar(mainPanel, wxID_ANY, wxPoint(0 , this->GetSize().y - 100), wxSize(this->GetSize().x, 100));
    //test->mSize(wxSize(500, 5));


    //Sleep(2000);

    //test->mSize(wxSize(100, 50));

    //Sleep(2000);

    //test->mSize(wxSize(200, 150));

}
