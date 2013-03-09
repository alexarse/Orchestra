#include "ControlBar.h"

const wxSize ControlBar::MINSIZE = wxSize(300, 100);
const wxPoint ControlBar::BTN_OFFSET = wxPoint(100, 22);
const int ControlBar::BTN_DELTAX = 25;
const wxPoint ControlBar::SLIDER_OFFSET = wxPoint(20, 5);

// IDs
enum 
{
    BACK_BTN = 8000,
    STOP_BTN,
    PLAY_PAUSE_BTN,
    FWRD_BTN,

	SLIDER_LEFT_DOWN,
	SLIDER_LEFT_UP,
	SLIDER_MOTION
};

BEGIN_EVENT_TABLE(ControlBar, wxPanel)
	EVT_PAINT(ControlBar::OnPaint)

    EVT_BUTTON(BACK_BTN, ControlBar::OnBackBtn)
	EVT_BUTTON(STOP_BTN, ControlBar::OnStopBtn)
	EVT_BUTTON(PLAY_PAUSE_BTN, ControlBar::OnPlayPauseBtn)
	EVT_BUTTON(FWRD_BTN, ControlBar::OnFwrdBtn)

	EVT_BUTTON(SLIDER_LEFT_DOWN, ControlBar::OnSliderLeftDown)
	EVT_BUTTON(SLIDER_LEFT_UP, ControlBar::OnSliderLeftUp)
	EVT_BUTTON(SLIDER_MOTION, ControlBar::OnSliderMotion)

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

    // Slider
	axSliderID sliderID;
	sliderID.leftDownID = SLIDER_LEFT_DOWN; 
	sliderID.leftUpID = SLIDER_LEFT_UP;
	sliderID.motionID = SLIDER_MOTION;

	axSliderData sliderData;
	sliderData.imgs = axMultipleBitmap(wxT("resources/ControlBar/sliderCtrl.png"), 3, wxSize(12, 12), UP_TO_DOWN);
	sliderData.bgColorNormal		= wxColor(50, 50, 50); 
	sliderData.bgColorHover			= wxColor(70, 70, 70); 
	sliderData.bgColorClicked		= wxColor(100, 100, 100);
	sliderData.sliderColorNormal	= wxColor(200, 0, 0); 
	sliderData.sliderColorHover		= wxColor(240, 0, 0);
	sliderData.sliderColorClicked	= wxColor(230, 0, 0);
	sliderData.sliderContourColor	= wxColor(0, 0, 0);
	sliderData.contourColor			= wxColor(50, 50, 50);
	sliderData.sliderHeight			= 8;

	slider = new axSlider(this, sliderID, sliderData, SLIDER_OFFSET, wxSize(300, 16), 0.5, 0.0, 1.0);
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

            // Resize slider
            //int slider_x = ((this->GetSize().x - MINSIZE.x)/2) + SLIDER_OFFSET.x, slider_y = SLIDER_OFFSET.y;
            this->slider->SetSize(wxSize(this->GetSize().x - (SLIDER_OFFSET.x * 3), slider->GetSize().y));

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

double ControlBar::getSliderValue() const
{
    return this->slider->getValue();
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


void ControlBar::OnSliderLeftDown(wxCommandEvent& event)
{
    event.Skip();
}
void ControlBar::OnSliderLeftUp(wxCommandEvent& event)
{
    event.Skip();
}
void ControlBar::OnSliderMotion(wxCommandEvent& event)
{
    event.Skip();

    _DEBUG_ DSTREAM << "ControlBar getting slider motion." << endl;
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
