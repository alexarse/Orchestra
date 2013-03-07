/** @file mediaPlayer.cpp
	@ingroup Media
	@brief MediaWindow, ControlBar, TopBar
	@author Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
*/
#include "mediaPlayer.h"
#include "wx/dcbuffer.h"
#include "wx/image.h"
#include <math.h>

enum
{ 
	ID_PLAY_BTN = 8000,
	ID_STOP_BTN,
	ID_PAUSE_BTN,
	ID_LEFT_BTN,
	ID_RIGHT_BTN,
	ID_VOLUME_CHANGE,
	ID_SLIDER_DOWN,
	ID_SLIDER_LEFT_UP,

	//TopBar
	ID_SHOW_VIDEO,
	ID_SHOW_3D,
	ID_SPLIT,

	ID_UI_REFRESH
};

BEGIN_EVENT_TABLE(MediaWindow, wxPanel)
	EVT_PAINT(MediaWindow::OnPaint)

	EVT_BUTTON(ID_UI_REFRESH, MediaWindow::OnAudioEvent)
	EVT_TIMER(wxID_ANY, MediaWindow::OnUiTimer)
	
	 //ControlPanel
	EVT_BUTTON(ID_PLAY_BTN, MediaWindow::OnPlayBtn)
	EVT_BUTTON(ID_STOP_BTN, MediaWindow::OnStopBtn)
	EVT_BUTTON(ID_SLIDER_DOWN, MediaWindow::OnSliderDown)
	EVT_BUTTON(ID_SLIDER_LEFT_UP, MediaWindow::OnSliderLeftUp)
	EVT_BUTTON(ID_VOLUME_CHANGE, MediaWindow::OnVolumeChange)

	//TopBar
	EVT_BUTTON(ID_SHOW_VIDEO, MediaWindow::OnShowVideo)
	EVT_BUTTON(ID_SHOW_3D, MediaWindow::OnShow3D)
	EVT_BUTTON(ID_SPLIT, MediaWindow::OnSplit)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------------
// MediaWindow
//-----------------------------------------------------------------------------------
MediaWindow::MediaWindow(wxWindow* win): wxPanel(win, wxID_ANY)
{
	parent = win;
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	wxImage::AddHandler(new wxPNGHandler);
	SetBackgroundColour(wxColour(100, 100, 100));

	videoPlayer = new VideoPlayer(this, wxID_ANY);

	window3D = new mIrrWindow(this, wxID_ANY);
	device3D = new mIrrDevice(window3D);

	//-----------------------------------------------------------------------------------------------------
	//Should be in mIrrWindow in 3DPanel.h
	//-----------------------------------------------------------------------------------------------------
		float theta = M_PI * 0.5;
		window3D->AddCamera(0, m3d_Vector3D(cos(theta) * 1.8, 1.2f, sin(theta) * 1.8), m3d_Vector3D(0.0f, 1.0f, 0.0f));

		irr::scene::IAnimatedMesh* mesh = window3D->GetSceneManager()->getMesh("test_B3D.b3d");
		irr::scene::IAnimatedMeshSceneNode* node = window3D->GetSceneManager()->addAnimatedMeshSceneNode(mesh);
		
		if (node)
		{
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			node->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, true);
			node->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, true);
			
			node->setMaterialTexture(0, window3D->GetVideoDriver()->getTexture("test_m.png"));
		}
	//-----------------------------------------------------------------------------------------------------

	//audio = new AudioClass(this);
	//audio->setParent((MediaWindow*)this);
	//glTest = new wxGLCanvasSubClass(this);
	ctlBar = new ControlBar(this);
	topBar = new TopBar(this);

	uiTimer = new wxTimer(this);
	uiTimer->Start(1000/60);
	
	ctlBar->volume->setSliderValue(0.5);
	ctlBar->volumeBtn->setVolumeValue(0.5);
	videoPlayer->setVolume(0.5);
	//audio->setVolume(1.0);

	mSize();
}
MediaWindow::~MediaWindow()
{
	uiTimer->Stop();
	delete uiTimer;
}
void MediaWindow::OnVolumeChange(wxCommandEvent& event)
{	
	videoPlayer->setVolume(ctlBar->volume->getSliderValue());
}
void MediaWindow::OnPlayBtn(wxCommandEvent& event)
{
	//audio->playing = true;
	window3D->isRunning = true;
	videoPlayer->play();
}
void MediaWindow::OnSliderDown(wxCommandEvent& event)
{
	//audio->playing = false;
	
}
void MediaWindow::OnSliderLeftUp(wxCommandEvent& event)
{
	float v = ctlBar->slider->getSliderValue();
	//audio->setPointerPosition(v * audio->aBuffer->getNbFrames());
	//audio->playing = true;

}
void MediaWindow::OnStopBtn(wxCommandEvent& event)
{
	window3D->isRunning = false;
	videoPlayer->stop();
	//audio->playing = false;
	//audio->setPointerPosition(0);
	//ctlBar->slider->setSliderValue(0);
	//ctlBar->timeWidget->setTimeInSec(0);
}
void MediaWindow::OnUiTimer(wxTimerEvent &event)
{
	if(videoPlayer->getTimeMs() <= 0)
	{
		ctlBar->slider->setSliderValue(0);	
		ctlBar->timeWidget->setTimeInSec(0); 
	}
	else
	{
		double v = videoPlayer->getTimeMs() / (double)videoPlayer->getTotalTimeMs();

		ctlBar->slider->setSliderValue(v);	
		ctlBar->timeWidget->setTimeInSec(videoPlayer->getTimeMs() / 1000.0);
	}
}
void MediaWindow::OnAudioEvent(wxCommandEvent& event)
{	
	//double v = videoPlayer->getTimeMs() / (double)videoPlayer->getTotalTimeMs();
	//ctlBar->slider->setSliderValue(v);	
	//ctlBar->timeWidget->setTimeInSec(videoPlayer->getTimeMs()); 
}
void MediaWindow::mSize()
{
	wxSize size(parent->GetSize().x / 2, parent->GetSize().y - 77);
	SetSize(size);
	SetPosition(_P(0, 0));
	ctlBar->mSize();
	topBar->mSize();

	int y = size.y - ctlBar->GetSize().y - topBar->GetSize().y;
	if(topBar->get3dButtonValue() && topBar->getVideoButtonValue())
	{
		if(!topBar->getSplitButtonValue()) //VERTIAL
		{
			y /= 2;
			window3D->mSize(_S(size.x - 1, y));

			videoPlayer->SetPosition(_P(0, y + topBar->GetSize().y));
			videoPlayer->mSize(_S(size.x - 1, y));
		}
		else //HORIZONTAL
		{
			int x = (size.x - 1) / 2;
			window3D->mSize(_S(x, y));

			videoPlayer->SetPosition(_P(x, topBar->GetSize().y));
			videoPlayer->mSize(_S(x, y));
		}
	}
	else
	{
		if(topBar->get3dButtonValue())
			window3D->mSize(_S(size.x - 1, y));
		else
		{
			videoPlayer->SetPosition(_P(0, topBar->GetSize().y));
			videoPlayer->mSize(_S(size.x - 1, y));
		}

		
	}

	Refresh();
}
void MediaWindow::Testing()
{
	//wxLogMessage("TESTING");
}
void MediaWindow::OnShowVideo(wxCommandEvent& event)
{
	if(topBar->getVideoButtonValue()) videoPlayer->Show(true);
	else videoPlayer->Show(false);

	mSize();
}
void MediaWindow::OnSplit(wxCommandEvent& event)
{
	mSize();
}
void MediaWindow::OnShow3D(wxCommandEvent& event)
{
	if(topBar->get3dButtonValue()) window3D->Show(true);
	else window3D->Show(false);

	mSize();
}
void MediaWindow::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	//BACKGROUND
	dc.SetPen(wxPen(wxColor(100, 100, 100) , 0, wxSOLID));
	dc.SetBrush(wxBrush(wxColor(100,100,100)));
	dc.DrawRectangle(wxRect(0, 0, size.x, size.y));
}

//-----------------------------------------------------------------------------------
// ControlBar
//-----------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ControlBar, wxPanel)
	EVT_PAINT(ControlBar::OnPaint)
	EVT_BUTTON(ID_RIGHT_BTN, ControlBar::OnBtnNext)
	EVT_BUTTON(ID_PLAY_BTN, ControlBar::OnPlayBtn)
	EVT_BUTTON(ID_STOP_BTN, ControlBar::OnStopBtn)
	EVT_BUTTON(ID_SLIDER_LEFT_UP, ControlBar::OnSliderLeftUp)
	EVT_BUTTON(ID_SLIDER_DOWN, ControlBar::OnSliderDown)
	EVT_BUTTON(ID_VOLUME_CHANGE, ControlBar::OnVolumeChange)
	EVT_BUTTON(ID_VOLUME_CHANGE, ControlBar::OnVolumeChange)
END_EVENT_TABLE()

ControlBar::ControlBar(wxWindow* win): wxPanel(win, wxID_ANY)
{
	parent = win;
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	wxImage::AddHandler(new wxPNGHandler);
	SetBackgroundColour(wxColour(50, 50, 50));

	int x = (GetSize().x - 100) / 2;
	transportPanel = new wxPanel(this, wxID_ANY, wxPoint(x, 17), wxSize(100, 25));
	transportPanelBgBmp = _B(_T("resources/widgetImg/bgTransportPanel.png"));//_B(_T("bgTransportPanel.png"));
	transportPanel->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	transportPanel->Connect(wxEVT_PAINT, wxPaintEventHandler(ControlBar::OnTransportPanelPaint));

	leftBtn = new ImgBtn(transportPanel, ID_LEFT_BTN, _P(0, 0), 
						 _T("resources/widgetImg/left.png"), 
						 _T("resources/widgetImg/leftHover.png"), 
						 _T("resources/widgetImg/leftClick.png"));

	leftBtn->setBackgroundBitamp(_B(_T("resources/widgetImg/bgBtn.png")));

	playBtn = new ImgBtn(transportPanel, ID_PLAY_BTN, _P(25, 0), 
						 _T("resources/widgetImg/play.png"), 
						 _T("resources/widgetImg/playHover.png"), 
						 _T("resources/widgetImg/playClick.png"));

	playBtn->setBackgroundBitamp(_B(_T("resources/widgetImg/bgBtn.png")));
	playToogle = false;

	stopBtn = new ImgBtn(transportPanel, ID_STOP_BTN, _P(50, 0), 
						 _T("resources/widgetImg/stop.png"), 
						 _T("resources/widgetImg/stopHover.png"), 
						 _T("resources/widgetImg/stopClick.png"));

	stopBtn->setBackgroundBitamp(_B(_T("resources/widgetImg/bgBtn.png")));

	rightBtn = new ImgBtn(transportPanel, ID_RIGHT_BTN, _P(75, 0), 
						  _T("resources/widgetImg/right.png"), 
						  _T("resources/widgetImg/rightHover.png"), 
						  _T("resources/widgetImg/rightClick.png"));

	rightBtn->setBackgroundBitamp(_B(_T("resources/widgetImg/bgBtn.png")));

	
	slider = new SliderBar(this, ID_SLIDER_LEFT_UP, ID_SLIDER_DOWN, wxID_ANY, _P(5, 2), _S(GetSize().x - 10, 13), 
						   _T("resources/widgetImg/sliderCtrl.png"), 
						   _T("resources/widgetImg/sliderCtrlHover.png"), 
						   _T("resources/widgetImg/sliderCtrlClick.png")); 

	volume = new SliderBar(this, ID_VOLUME_CHANGE, wxID_ANY, ID_VOLUME_CHANGE,_P(GetSize().x - 8075, 17), _S(55, 13), 
						   _T("resources/widgetImg/sliderCtrl.png"), 
						   _T("resources/widgetImg/sliderCtrlHover.png"), 
						   _T("resources/widgetImg/sliderCtrlClick.png")); 

	volume->setBackgroundBitamp(_B(_T("resources/widgetImg/bgVolume.png")));

	timeWidget = new TimeWidget(this, wxID_ANY, _P(x - 80, 28));
	timeWidget->setBackgroundBitamp(_B(_T("resources/widgetImg/timeBg.png")));
	
	volumeBtn = new VolumeBtn(this, wxID_ANY, _P(GetSize().x - 105, 20), _T("resources/widgetImg/volumeBtn.png"));
	volumeBtn->setBackgroundBitamp(_B(_T("resources/widgetImg/bgBtn.png")));
}
void ControlBar::OnVolumeChange(wxCommandEvent& event)
{
	volumeBtn->setVolumeValue(volume->getSliderValue());
	event.Skip();
}
void ControlBar::OnSliderDown(wxCommandEvent& event)
{
	event.Skip();
}
void ControlBar::OnSliderLeftUp(wxCommandEvent& event)
{
	event.Skip();
}
void ControlBar::OnBtnNext(wxCommandEvent& event)
{
	event.Skip();
}
void ControlBar::OnPlayBtn(wxCommandEvent& event)
{
	if(!playToogle) 
	{
		playBtn->setImg(_B(_T("resources/widgetImg/pause.png")));
		playBtn->setImgClick(_B(_T("resources/widgetImg/pauseClick.png")));
		playBtn->setImgHover(_B(_T("resources/widgetImg/pauseHover.png")));
		playToogle = true;
	}

	else 
	{
		playBtn->setImg(_B(_T("resources/widgetImg/play.png")));
		playBtn->setImgClick(_B(_T("resources/widgetImg/playClick.png")));
		playBtn->setImgHover(_B(_T("resources/widgetImg/playHover.png")));
		playToogle = false;
	}

	playBtn->Refresh();
	event.Skip();
}
void ControlBar::OnStopBtn(wxCommandEvent& event)
{
	event.Skip();
}
void ControlBar::mSize()
{
	SetSize(parent->GetSize().x, 55);
	SetPosition(_P(0, parent->GetSize().y - 55));

	int x = (GetSize().x - 100) / 2;
	transportPanel->SetPosition(_P(x, 21));
	timeWidget->SetPosition(_P(40, 28));

	//slider->mSize();
	sliderBarResize();
	volumeResize();

	Refresh();
}
void ControlBar::sliderBarResize()
{	
	int x = GetSize().x - 80;
	slider->SetSize(x, 13);
	slider->SetPosition(_P(40, 2));

	slider->mSize(x);
	slider->Refresh();
}
void ControlBar::volumeResize()
{	
	int x = GetSize().x - 95;
	volume->SetSize(55, 13);
	volume->SetPosition(_P(x, 25));
	volume->mSize(55);
	volume->Refresh();

	volumeBtn->SetPosition(_P(x - 30, 20));
}
void ControlBar::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();
	dc.SetPen(wxPen(BG_GREY_COLOR , 1, wxSOLID));
	dc.SetBrush(wxBrush(BG_GREY_COLOR));
	dc.DrawRectangle(wxRect(0, 0, size.x, size.y));
	
	for(int y = 14, c = 50; y < size.y; y++, c--)
	{
		dc.SetPen(wxPen(_C(c, c, c), 1, wxSOLID));
		if(c < 5) dc.SetPen(wxPen(_C(5, 5, 5), 1, wxSOLID));
		dc.DrawLine(_P(0,y), _P(size.x, y));
	}

	dc.SetPen(wxPen(CONTOUR_DARK_GREY_COLOR , 3, wxSOLID));
	dc.DrawLine(0, 0, size.x, 0);
}

void ControlBar::OnTransportPanelPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();
	dc.SetPen(wxPen(BG_GREY_COLOR , 1, wxSOLID));
	dc.SetBrush(wxBrush(_C(200, 0, 0)));
	dc.DrawRectangle(wxRect(0, 0, size.x, size.y));
	for(int y = 0, c = 43; y < size.y; y++, c--)
	{
		dc.SetPen(wxPen(_C(c, c, c), 1, wxSOLID));
		if(c < 5) dc.SetPen(wxPen(_C(5, 5, 5), 1, wxSOLID));
		dc.DrawLine(_P(0,y), _P(size.x, y));
	}
	//dc.DrawBitmap(transportPanelBgBmp, 0, 0);
}


// TopBar
BEGIN_EVENT_TABLE(TopBar, wxPanel)
	EVT_BUTTON(ID_SHOW_VIDEO, TopBar::OnShowVideo)
	EVT_BUTTON(ID_SHOW_3D, TopBar::OnShow3D)
	EVT_BUTTON(ID_SPLIT, TopBar::OnSplit)
	EVT_PAINT(TopBar::OnPaint)
END_EVENT_TABLE()

TopBar::TopBar(wxWindow* win): wxPanel(win, wxID_ANY)
{
	parent = win;
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	wxImage::AddHandler(new wxPNGHandler);
	SetBackgroundColour(BG_GREY_COLOR);
	mSize();

	videoButton = new ImgToggle(this, ID_SHOW_VIDEO, wxPoint(5,2),"resources/widgetImg/videoCtrl_4.png", _S(40, 20));
	panel3dButton = new ImgToggle(this, ID_SHOW_3D, wxPoint(50,2), "resources/widgetImg/3dCtrl_4.png", _S(40, 20));
	splitButton = new ImgToggle(this, ID_SPLIT, wxPoint(95,2), "resources/widgetImg/split_4.png", _S(20, 20));
}
void TopBar::mSize()
{
	SetSize(parent->GetSize().x, 25);
	SetPosition(_P(0, 0));
	Refresh();
}
void TopBar::OnShowVideo(wxCommandEvent& event)
{
	event.Skip();
}
void TopBar::OnShow3D(wxCommandEvent& event)
{
	event.Skip();
}
void TopBar::OnSplit(wxCommandEvent& event)
{
	event.Skip();
}
bool TopBar::getVideoButtonValue()
{
	return videoButton->isOn;
}
bool TopBar::get3dButtonValue()
{
	return panel3dButton->isOn;
}
bool TopBar::getSplitButtonValue()
{
	return splitButton->isOn;
}
void TopBar::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();
	
	//BACKGROUND
	dc.SetPen(wxPen(BG_GREY_COLOR , 1, wxSOLID));
	dc.SetBrush(wxBrush(BG_GREY_COLOR));
	dc.DrawRectangle(wxRect(0, 0, size.x, size.y));
	
	dc.SetPen(wxPen(CONTOUR_DARK_GREY_COLOR , 3, wxSOLID));
	dc.DrawLine(0, size.y - 1, size.x, size.y - 1);
}