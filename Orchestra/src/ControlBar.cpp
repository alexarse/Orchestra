#include "ControlBar.h"

const wxSize ControlBar::MINSIZE = wxSize(300, 100);
const wxPoint ControlBar::BTN_OFFSET = wxPoint(100, 17);
const int ControlBar::BTN_DELTAX = 25;

// IDs
enum 
{
    BACK_BTN = 8000,
    STOP_BTN,
    PLAY_PAUSE_BTN,
    FWRD_BTN
};

BEGIN_EVENT_TABLE(ControlBar, wxPanel)
	EVT_PAINT(ControlBar::OnPaint)

    EVT_BUTTON(BACK_BTN, ControlBar::OnBackBtn)
	EVT_BUTTON(STOP_BTN, ControlBar::OnStopBtn)
	EVT_BUTTON(PLAY_PAUSE_BTN, ControlBar::OnPlayPauseBtn)
	EVT_BUTTON(FWRD_BTN, ControlBar::OnFwrdBtn)

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


    // Initialize buttons
    int x = BTN_OFFSET.x, deltaX = BTN_DELTAX, y = BTN_OFFSET.y; // Offset pour controls
    wxSize img_size(25, 25); // Size of button images
    
    
    axMultipleBitmap backwardIm(wxString("resources/ControlBar/backwardBtn.png"), 3, img_size);
    backwardBtn = new axButton(this, BACK_BTN, wxPoint(x, y), backwardIm);


    axMultipleBitmap stopIm(wxString("resources/ControlBar/stopBtn.png"), 3, img_size);
    stopBtn = new axButton(this, STOP_BTN, wxPoint(x += deltaX, y), stopIm);

    axMultipleBitmap playPauseIm(wxString("resources/ControlBar/playPauseBtn.png"), 6, img_size);
    playPauseBtn = new axToggle(this, PLAY_PAUSE_BTN, wxPoint(x += deltaX, y), playPauseIm, false);
	
    axMultipleBitmap forwardIm(wxString("resources/ControlBar/forwardBtn.png"), 3, img_size);
    forwardBtn = new axButton(this, FWRD_BTN, wxPoint(x += deltaX, y), forwardIm);

}

void ControlBar::mSize(const wxSize& size)
{
    if (size.x >= 0 && size.y >= 0)
    {
        if (size.x >= MINSIZE.x)
        {
            // Resize panel
            SetPosition(wxPoint(0, size.y - MINSIZE.y));
            SetSize(size.x, MINSIZE.y);

            // Move controls relative to resize
            int x = ((this->GetSize().x - MINSIZE.x) * 0.5) + BTN_OFFSET.x, 
				y = BTN_OFFSET.y, 
				deltaX = BTN_DELTAX;

            this->backwardBtn->SetPosition(wxPoint(x, y));
            this->stopBtn->SetPosition(wxPoint(x += deltaX, y));
            this->playPauseBtn->SetPosition(wxPoint(x += deltaX, y));
            this->forwardBtn->SetPosition(wxPoint(x += deltaX, y));

            Refresh();

            _DEBUG_ DSTREAM << "Resizing ControlBar: " << size.x << "x, " << size.y << "y." << endl;
        }
        else
        {
            SetPosition(wxPoint(0, size.y - MINSIZE.y));
            SetSize(MINSIZE);
            Refresh();
        }
    }
}

// Events
void ControlBar::OnBackBtn(wxCommandEvent& event)
{
    event.Skip();
    _DEBUG_ DSTREAM << "ControlBar OnBackBtn" << endl;
}
void ControlBar::OnStopBtn(wxCommandEvent& event)
{
    event.Skip();
    playPauseBtn->setToggleValue(false);
}
void ControlBar::OnPlayPauseBtn(wxCommandEvent& event)
{
    event.Skip();
}
void ControlBar::OnFwrdBtn(wxCommandEvent& event)
{
    event.Skip();
    _DEBUG_ DSTREAM << "ControlBar OnFwrdBtn" << endl;
}

void ControlBar::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    //this->mSize(wxSize(this->GetParent()->GetSize().x, 0));
    wxSize size = GetSize();
    
    dc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxSOLID));
    dc.SetBrush(wxBrush(wxColor(50, 50, 50)));
    dc.DrawRectangle(wxRect(0, 0, size.x, size.y));

}
