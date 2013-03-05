#include "ControlBar.h"

const wxSize ControlBar::MINSIZE = wxSize(300, 100);

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
    //this->SetBackgroundStyle(wxBG_STYLE_CUSTOM); // Tell some platforms not to use default background.
    //wxImage::AddHandler(new wxPNGHandler); // Format of images to use (usually only one).
    this->SetBackgroundColour(wxColour(50, 50, 50));
    //this->Connect(wxEVT_PAINT, wxPaintEventHandler(ControlBar::test));
    //this->SetMinSize(wxSize(300,100)); // For sizers

    // Container pour boutons central
    //transportPanel = new wxPanel(this, wxID_ANY, wxPoint(50, 17), wxSize(100, 25));
	//transportPanel->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	//transportPanel->Connect(wxEVT_PAINT, wxPaintEventHandler(ControlBar::OnTransportPanelPaint));

    // Initialize buttons
    int x = 0, delta = 25;
    wxSize img_size(25, 25);
    
    axMultipleBitmap backwardIm(wxString("resources/ControlBar/backwardBtn.png"), 3, img_size);
    backwardBtn = new axButton(this, BACK_BTN, wxPoint(x++ * delta ,0), backwardIm); // 0
	//backwardBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

    axMultipleBitmap stopIm(wxString("resources/ControlBar/stopBtn.png"), 3, img_size);
    stopBtn = new axButton(this, STOP_BTN, wxPoint(x++ * delta, 0), stopIm); // 25
	//stopBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

    axMultipleBitmap playPauseIm(wxString("resources/ControlBar/playPauseBtn.png"), 6, img_size);
    playPauseBtn = new axToggle(this, PLAY_BTN, wxPoint(x++ * delta, 0), playPauseIm, false); // 50
	//playPauseBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));
	
    axMultipleBitmap forwardIm(wxString("resources/ControlBar/forwardBtn.png"), 3, img_size);
    forwardBtn = new axButton(this, FWRD_BTN, wxPoint(x++ * delta, 0), forwardIm); // 75
	//forwardBtn->setBackgroundImage(wxBitmap(_T("resources/ControlBar/backgroundBtn.png"), wxBITMAP_TYPE_PNG));

}

void ControlBar::mSize(const wxSize& size)
{
    if (size.x >= 0 && size.y >= 0)
    {
        if (size.x >= MINSIZE.x)
        {
            SetPosition(wxPoint(0, size.y - MINSIZE.y));
            SetSize(size.x, MINSIZE.y);

            _DEBUG_ DSTREAM << "Resizing ControlBar: " << size.x << "x, " << size.y << "y." << endl;

            Refresh();
        }   
    }
}



// Events
void ControlBar::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    //this->mSize(wxSize(this->GetParent()->GetSize().x, 0));
    wxSize size = GetSize();
    
    dc.SetPen(wxPen(wxColor(0`, 0, 0), 1, wxSOLID));
    dc.SetBrush(wxBrush(wxColor(250, 0, 0)));
    dc.DrawRectangle(wxRect(0, 0, size.x, size.y));

    _DEBUG_ DSTREAM << "calice" << endl;
}

void ControlBar::test(wxPaintEvent& event)
{
    //this->mSize(wxSize(this->GetParent()->GetSize().x, 0));
}
