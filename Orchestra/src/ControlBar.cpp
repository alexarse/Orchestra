#include "ControlBar.h"

const wxSize MINSIZE = wxSize(300, 100);

enum 
{
    BACK_BTN = 8000,
    FWRD_BTN,
    STOP_BTN,
    PLAY_BTN
};

BEGIN_EVENT_TABLE(ControlBar, wxPanel)
	EVT_PAINT(ControlBar::OnPaint)
    
    //EVT_BUTTON(BACK_BTN, ControlBar::test)

	//EVT_BUTTON(ID_RIGHT_BTN, ControlBar::OnBtnNext)
	//EVT_BUTTON(ID_PLAY_BTN, ControlBar::OnPlayBtn)
	//EVT_BUTTON(ID_STOP_BTN, ControlBar::OnStopBtn)
	//EVT_BUTTON(ID_SLIDER_LEFT_UP, ControlBar::OnSliderLeftUp)
	//EVT_BUTTON(ID_SLIDER_DOWN, ControlBar::OnSliderDown)
	//EVT_BUTTON(ID_VOLUME_CHANGE, ControlBar::OnVolumeChange)
	//EVT_BUTTON(ID_VOLUME_CHANGE, ControlBar::OnVolumeChange)
END_EVENT_TABLE()

ControlBar::ControlBar(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size)
    : wxPanel(win, id, pt, size)
{
    // Heavy lifting
    this->SetBackgroundStyle(wxBG_STYLE_CUSTOM); // Tell some platforms not to use default background.
    //wxImage::AddHandler(new wxPNGHandler); // Format of images to use (usually only one).
    this->SetBackgroundColour(wxColour(50, 50, 50));
    //this->Connect(wxEVT_PAINT, wxPaintEventHandler(ControlBar::test));
    //this->SetMinSize(wxSize(300,100)); // For sizers

    // Container pour boutons central
    //transportPanel = new wxPanel(this, wxID_ANY, wxPoint(50, 17), wxSize(100, 25));
	//transportPanel->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	//transportPanel->Connect(wxEVT_PAINT, wxPaintEventHandler(ControlBar::OnTransportPanelPaint));

    // Initialize buttons
    axMultipleBitmap backwardIm(wxString("resources/ControlBar/backwardBtn.png"), 3, wxSize(25, 25));
    backwardBtn = new axButton(this, BACK_BTN, wxPoint(0,0), backwardIm);
	backwardBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

    axMultipleBitmap forwardIm(wxString("resources/ControlBar/forwardBtn.png"), 3, wxSize(25, 25));
    forwardBtn = new axButton(this, FWRD_BTN, wxPoint(75,0), forwardIm);
	forwardBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

    axMultipleBitmap stopIm(wxString("resources/ControlBar/stopBtn.png"), 3, wxSize(25, 25));
    stopBtn = new axButton(this, STOP_BTN, wxPoint(25,0), stopIm);
	stopBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

    axMultipleBitmap playPauseIm(wxString("resources/ControlBar/playPauseBtn.png"), 6, wxSize(25, 25));
    playPauseBtn = new axToggle(this, PLAY_BTN, wxPoint(50,0), playPauseIm, false);
	//playPauseBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

}

void ControlBar::mSize(const wxSize& size)
{
    if (size.x >= 0 && size.y >= 0)
    {
        if (size.x >= MINSIZE.x && size.y >= MINSIZE.y)
        {
            this->SetSize(size);
        }   
    }
}



// Events
void ControlBar::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    //this->mSize(wxSize(this->GetParent()->GetSize().x, 0));

    _DEBUG_ DSTREAM << "calice" << endl;
}

void ControlBar::test(wxPaintEvent& event)
{
    this->mSize(wxSize(this->GetParent()->GetSize().x, 0));
}