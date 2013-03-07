/********************************************************************************//**
 * @file	main.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	Main Application
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#include "main_Partition.h"

IMPLEMENT_APP(Orchestra);

bool Orchestra::OnInit()
{
	frame = new MainFrame(axT("Orchestra"));
	
	frame->Show();
	SetTopWindow(frame);

	return true;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_SIZE(MainFrame::OnSize)
END_EVENT_TABLE()

MainFrame::MainFrame(const axString& title): axFrame(NULL, axID_ANY, title, axPoint(30, 30), axSize(500, 500))
{
	SetBackgroundColour(axColor(80, 80, 80));
	mainPanel = new axPanel(this, axID_ANY, axPoint(0, 0), this->GetSize());
	mainPanel->SetBackgroundColour(axColor(80, 80, 80));

	vector<wxString> imgs;
	imgs.push_back("resources/Song1/test000.png");
	imgs.push_back("resources/Song1/test001.png");
	imgs.push_back("resources/Song1/test002.png");
	imgs.push_back("resources/Song1/test003.png");
	imgs.push_back("resources/Song1/test004.png");
	imgs.push_back("resources/Song1/test005.png");
	
	partition = new Partition(mainPanel, wxID_ANY, wxPoint(0, 0), GetSize());
	partition->loadInfo("resources/Song1/output.data", imgs);

	partition->changeTime(100000.0);
}

void MainFrame::OnSize(wxSizeEvent& event)
{
	wxSize size = GetSize();
	size.x -= 20;
	size.y -= 20;
	mainPanel->SetSize(size);
	partition->mSize(size);
}