//WXWIDGET
#include "wx/wx.h"
#include "definition.h"
//#include "audioPlayer.h"
#include "videoPlayer.h"
#include "widgetControl.h"
#include "3DPanel.h"

class TopBar : public wxPanel
{
public:
    TopBar(wxWindow* win);
	void mSize();
	bool getVideoButtonValue();
	bool get3dButtonValue();
	bool getSplitButtonValue();

private:
	wxWindow* parent;
	ImgToggle* videoButton;
	ImgToggle* panel3dButton;
	ImgToggle* splitButton;
	
	void OnPaint(wxPaintEvent& event);
	void OnShowVideo(wxCommandEvent& event);
	void OnShow3D(wxCommandEvent& event);
	void OnSplit(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

class ControlBar : public wxPanel
{
public:
    ControlBar(wxWindow* win);
	wxPanel* transportPanel;
	ImgBtn* playBtn;
	ImgBtn* stopBtn;
	ImgBtn* pauseBtn;
	ImgBtn* leftBtn;
	ImgBtn* rightBtn;
	SliderBar* slider;
	SliderBar* volume;
	VolumeBtn* volumeBtn;
	TimeWidget* timeWidget;
	wxBitmap transportPanelBgBmp;

	void mSize();
	void sliderBarResize();
	void volumeResize();
	//SliderBar* slider;
	//NumberBoxControl* ligneBox;
	//A_WaveformPlay* slider;

private:
	wxWindow* parent;
	void OnPaint(wxPaintEvent& event);
	void OnTransportPanelPaint(wxPaintEvent& event);
	void OnBtnNext(wxCommandEvent& event);
	void OnVolumeChange(wxCommandEvent& event);
	void OnPlayBtn(wxCommandEvent& event);
	void OnClickEvent(wxCommandEvent& event);
	void OnStopBtn(wxCommandEvent& event);
	void OnSliderDown(wxCommandEvent& event);
	void OnSliderLeftUp(wxCommandEvent& event);

	bool playToogle;
	

	DECLARE_EVENT_TABLE()
};

class MediaWindow : public wxPanel
{
public:
    MediaWindow(wxWindow* win);
	~MediaWindow();
	void mSize();
	void Testing();

	mIrrWindow* window3D;
	mIrrDevice* device3D;
	VideoPlayer* videoPlayer;
	//AudioClass* audio;
	ControlBar* ctlBar;
	TopBar* topBar;
	
	//wxGLCanvasSubClass* glTest;
private:
	wxWindow* parent;
	wxTimer* uiTimer;

	void OnPaint(wxPaintEvent& event);
	void OnAudioEvent(wxCommandEvent& event);
	void OnUiTimer(wxTimerEvent &event);

	//ControlBar
	void OnPlayBtn(wxCommandEvent& event);
	void OnVolumeChange(wxCommandEvent& event);
	void OnStopBtn(wxCommandEvent& event);
	void OnSliderDown(wxCommandEvent& event);
	void OnSliderLeftUp(wxCommandEvent& event);

	//TopBar
	void OnShowVideo(wxCommandEvent& event);
	void OnShow3D(wxCommandEvent& event);
	void OnSplit(wxCommandEvent& event);

	//bool isShowBoth, videoIsShown, panel3DIsShown;

	DECLARE_EVENT_TABLE()
};