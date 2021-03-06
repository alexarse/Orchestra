/********************************************************************************//**
 * @file	main.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	Main Application
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#include "main_3DPanel.h"

IMPLEMENT_APP(Orchestra);

//#define SEL_ONE  SELECT_ONLY_THIS_ID

bool Orchestra::OnInit()
{
	frame = new MainFrame(axT("Orchestra"));
	
	frame->Show();
	SetTopWindow(frame);

	return true;
}

MainFrame::MainFrame(const axString& title): wxFrame(NULL, axID_ANY, title, axPoint(30, 30), axSize(500, 500))
{
	SetBackgroundColour(axColor(80, 80, 80));
	mainPanel = new wxPanel(this, axID_ANY, axPoint(0, 0), this->GetSize());
	mainPanel->SetBackgroundColour(axColor(80, 80, 80));
	
	panel3D = new Device3D(mainPanel);
}
