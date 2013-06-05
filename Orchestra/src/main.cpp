/********************************************************************************//**
 * @file	main.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	Main Application
 * @date	Creation 06/02/2013
 ***********************************************************************************/
#include "main.h"

IMPLEMENT_APP(Orchestra);

bool Orchestra::OnInit()
{
	frame = new MainFrame(wxT("Orchestra"));
	
	frame->Show();
	SetTopWindow(frame);

	return true;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_SIZING(MainFrame::OnSize)
	EVT_SIZE(MainFrame::OnSize)
	EVT_MAXIMIZE(MainFrame::OnMaximize)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxPoint(30, 30), wxSize(500, 500))
{
	SetBackgroundColour(axColor(80, 80, 80));
	SetMinSize(wxSize(700, 500));
	CreateMenu();
	
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), this->GetSize());
	mainPanel->SetBackgroundColour(wxColor(80, 80, 80));

	menuPanel = new MenuPanel(mainPanel, MAIN_FRAME_MENU_EVENT, 
							  wxPoint(0, 0), wxSize(150, 400), 
							  wxGetCwd() + wxT("/resources/data/") ); 

	wxSize s = GetSize();
	int x = (s.x - menuPanel->GetSize().x) * 0.5;

	// Create mediaPlayer
    mediaPlayer = new MediaPlayer(mainPanel, wxID_ANY, wxPoint(menuPanel->GetSize().x ,0), wxSize(wxSize(x, s.y)) );
	
	partition = new Partition(mainPanel, wxID_ANY, 
							  wxPoint(mediaPlayer->GetSize().x + menuPanel->GetSize().x, s.y),
							  wxSize(x, s.y));
	
	partition->loadInfo( menuPanel->getSelectionInfo().markerData, menuPanel->getSelectionInfo().paritionImg );

	Maximize(true);

	// @todo a changer.
    char* path = "resources/test.mp4";
    mediaPlayer->loadMedia( path );
}

void MainFrame::OnSize(wxSizeEvent& event)
{
	resize();
}

void MainFrame::OnMaximize(wxMaximizeEvent& event)
{
	resize();
}

void MainFrame::resize()
{
	wxSize s = GetSize();
	int x = (s.x - menuPanel->GetSize().x) * 0.5;

	mainPanel->SetSize(GetSize());
	mediaPlayer->mSize(wxSize(x, s.y));
	partition->mSize(wxSize(x, s.y));
	partition->SetPosition(wxPoint(menuPanel->GetSize().x + mediaPlayer->GetSize().x, 0));
}

void MainFrame::CreateMenu()
{
	// @TODO A CHANGER AU COMPLET
	wxMenuBar* menubar = new wxMenuBar;
	wxMenu* file = new wxMenu;
	file->Append(wxID_OPEN, wxT("&Open"));
	file->Append(wxID_EXIT, wxT("&Quit"));
	menubar->Append(file, wxT("&File"));

	wxMenu* edit = new wxMenu;
	edit->Append(wxID_OPEN, wxT("&Play"));
	edit->Append(wxID_OPEN, wxT("&Stop"));
	edit->AppendSeparator();
	edit->Append(wxID_OPEN, wxT("&Go To.."));
	edit->AppendSeparator();
	edit->Append(wxID_EXIT, wxT("&Preference"));
	menubar->Append(edit, wxT("&Edit"));

	wxMenu* view = new wxMenu;
	view->Append(wxID_OPEN, wxT("&Open"));
	view->Append(wxID_EXIT, wxT("&Quit"));
	menubar->Append(view, wxT("&View"));

	wxMenu* help = new wxMenu;
	help->Append(wxID_EXIT, wxT("&About"));
	menubar->Append(help, wxT("&Help"));

	SetMenuBar(menubar);
}