#include "MediaPlayer.h"

const wxSize MediaPlayer::MINSIZE = wxSize(300, 500); // If you change this, also change VlcVideoPlayer MINSIZE!

// IDs
enum 
{
    BACK_BTN = 8000,
    STOP_BTN,
    PLAY_PAUSE_BTN,
    FWRD_BTN,

	SLIDER_LEFT_DOWN,
	SLIDER_LEFT_UP,
	SLIDER_MOTION,
};

//DEFINE_EVENT_TYPE(vlcEVT_POS)

// Events
BEGIN_EVENT_TABLE(MediaPlayer, wxPanel)
	//EVT_PAINT(MediaPlayer::OnPaint)

    EVT_BUTTON(BACK_BTN, MediaPlayer::OnBackBtn)
	EVT_BUTTON(STOP_BTN, MediaPlayer::OnStopBtn)
	EVT_BUTTON(PLAY_PAUSE_BTN, MediaPlayer::OnPlayPauseBtn)
	EVT_BUTTON(FWRD_BTN, MediaPlayer::OnFwrdBtn)

	EVT_BUTTON(SLIDER_LEFT_DOWN, MediaPlayer::OnSliderLeftDown)
	EVT_BUTTON(SLIDER_LEFT_UP, MediaPlayer::OnSliderLeftUp)
	EVT_BUTTON(SLIDER_MOTION, MediaPlayer::OnSliderMotion)

    //EVT_BUTTON(TEST, MediaPlayer::changeSlider)

	//EVT_BUTTON(ID_VOLUME_CHANGE, ControlBar::OnVolumeChange)
	//EVT_BUTTON(ID_VOLUME_CHANGE, ControlBar::OnVolumeChange)
END_EVENT_TABLE()

MediaPlayer* mediaPlayer;

MediaPlayer::MediaPlayer(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size)
    : wxPanel(win, id, pt, size)
{
	this->SetBackgroundColour(axColor(80, 80, 80));

    // Create controlBar first, to pass pointer to videoInterface (for callback).
    controlBar = new ControlBar(this, wxID_ANY, 
    			     wxPoint(0 , GetSize().y - ControlBar::MINSIZE.y), 
    			     wxSize(GetSize().x, ControlBar::MINSIZE.y));

    videoInterface = new VlcVideoPlayer(this, wxID_ANY, wxPoint(0, 0), wxSize(GetSize().x, GetSize().y - ControlBar::MINSIZE.y));

    mediaPlayer = this;
}

bool MediaPlayer::loadMedia(const char* videoPath)
{
    return videoInterface->loadVideo(videoPath);
}

void MediaPlayer::mSize(const wxSize& size)
{
    if (size.x >= 0 && size.y >= 0)
    {
        wxSize newSize = this->GetSize();
        // Resize x
        if (size.x >= MINSIZE.x)
        {
            newSize.x = size.x;
        }

        // Resize y
        if (size.y >= MINSIZE.y)
        {
            newSize.y = size.y;
        }

        this->SetSize(newSize);
        Refresh();


        // Resize children with newSize, so they never resize smaller than MediaPlayer::MINSIZE
        this->controlBar->mSize(newSize);
        this->videoInterface->mSize(wxSize(newSize.x, newSize.y - ControlBar::MINSIZE.y));

        _DEBUG_ DSTREAM << "Resizing MediaPlayer: " << size.x << "x, " << size.y << "y." << endl;
    }

}

// Events
void MediaPlayer::OnBackBtn(wxCommandEvent& event)
{
    videoInterface->backward();
    _DEBUG_ DSTREAM << "MediaPlayer OnBackBtn" << endl;
}
void MediaPlayer::OnStopBtn(wxCommandEvent& event)
{
    videoInterface->stop();
    _DEBUG_ DSTREAM << "MediaPlayer OnStopBtn" << endl;
}
void MediaPlayer::OnPlayPauseBtn(wxCommandEvent& event)
{
    videoInterface->playPause();
}
void MediaPlayer::OnFwrdBtn(wxCommandEvent& event)
{
    videoInterface->forward();
    _DEBUG_ DSTREAM << "MediaPlayer OnFwrdBtn" << endl;
}

void MediaPlayer::OnSliderLeftDown(wxCommandEvent& event)
{
    videoInterface->mute();
    videoInterface->playPause();
}
void MediaPlayer::OnSliderLeftUp(wxCommandEvent& event)
{
    videoInterface->unMute();
    videoInterface->playPause();
}
void MediaPlayer::OnSliderMotion(wxCommandEvent& event)
{
    videoInterface->navigate(controlBar->getSliderValue());

    _DEBUG_ DSTREAM << "MediaPlayer getting slider motion." << endl;
}

void MediaPlayer::changeSlider()
{
    controlBar->setSliderValue(videoInterface->getPosition());
    _DEBUG_ DSTREAM << "test" << endl;    
}

// VLC callbacks
void vlcPositionChanged(const libvlc_event_t *event, void *data) {

   // wxCommandEvent evt(vlcEVT_POS, TEST);

    //MediaPlayer::changeSlider();

    mediaPlayer->changeSlider();

    //wxCommandEvent vlcEvent(wxEVT_COMMAND_BUTTON_CLICKED, TEST);
    //wxPostEvent(this, vlcEvent);

    _DEBUG_ DSTREAM << "MediaPlayer VLC position changed callback"  << endl;
}