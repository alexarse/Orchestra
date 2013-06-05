/// @todo Needs Documentation Header.
#include "VlcVideoPlayer.h"

// VLC Callbacks
//void vlcPositionChanged(const libvlc_event_t *event, void* data);

BEGIN_EVENT_TABLE(VlcVideoPlayer, wxPanel)
    EVT_BUTTON(wxID_ANY, VlcVideoPlayer::OnVideoCallback)
END_EVENT_TABLE()

VlcVideoPlayer::VlcVideoPlayer(wxWindow* win, const VideoID& id, wxPoint pt, wxSize size)
    : wxPanel(win, wxID_ANY, pt, size), videoID_(id), firstPlay_(1)
{
	SetBackgroundColour(axColor(0, 0, 0));

	_DEBUG_ nb_time_callback = 0;

    // Create new VLC instance.
    char const* vlcOptions[] = {"--no-video-title-show"}; //Hide filename.

	vlcInstance = NULL;
	vlcPlayer = NULL;

    // Create VLC instance
	vlcInstance = libvlc_new(1, vlcOptions);

    if( vlcInstance )
	{
		vlcPlayer = libvlc_media_player_new(vlcInstance);

		// Create VLC player
		if( vlcPlayer )
		{
			// Create VLC EventManager
			vlcEventManager = libvlc_media_player_event_manager(vlcPlayer);

			if( !vlcEventManager )
			{
				_DEBUG_ DSTREAM << "Can't create VLC Event Manager" << endl;
				wxMessageDialog (this, "Can't create VLC Event Manager");
			}
		}
		else // vlcPlayer
		{
			_DEBUG_ DSTREAM << "Can't create player from vlcMedia" << endl;
			wxMessageDialog (this, "Can't create player from vlcMedia");
		}
	}

    else // vlcInstance.
	{
		_DEBUG_ DSTREAM << "Can't Open VLC instance" << endl;
		wxMessageDialog (this, "Can't Open VLC instance");
	}

    // libVLC events and callback
	if( vlcInstance && vlcPlayer && vlcEventManager )
	{
		libvlc_event_attach(vlcEventManager, 
							libvlc_MediaPlayerPositionChanged, 
							VlcVideoPlayer::vlcPositionChanged, 
							this);
		
		libvlc_event_attach(vlcEventManager, 
							libvlc_MediaPlayerTimeChanged, 
							VlcVideoPlayer::vlcTimeChanged, 
							this);
	}
}

VlcVideoPlayer::~VlcVideoPlayer()
{
	if( vlcInstance )
	{
		libvlc_release(vlcInstance); // Destroy VLC instance
	}
}

double VlcVideoPlayer::getPosition() const
{
    return double( libvlc_media_player_get_position( vlcPlayer ));
}

void VlcVideoPlayer::mSize(const wxSize& size)
{
    // Don't need checks because media player sends good data.
    this->SetSize(size);
    this->Refresh();

    _DEBUG_ DSTREAM << "Resizing VideoInterface: " << size.x << "x, " << size.y << "y." << endl;
}

long VlcVideoPlayer::getTimeMs()
{
    return libvlc_media_player_get_time(vlcPlayer);
}

long VlcVideoPlayer::getTotalTimeMs()
{
    return libvlc_media_player_get_length(vlcPlayer);
}

void VlcVideoPlayer::setVolume(double volume)
{
	/// @todo
}

// Control Buttons
void VlcVideoPlayer::backward()
{
    // @todo Fix audio click (if we have time!).
    libvlc_media_player_set_position(vlcPlayer, libvlc_media_player_get_position (vlcPlayer) - 0.1); // Backward 10%
}

void VlcVideoPlayer::stop()
{
    libvlc_media_player_stop(vlcPlayer);
    firstPlay_ = 1;

    _DEBUG_ DSTREAM << "VlcVideoPlayer Stop() was called." << endl;
}

void VlcVideoPlayer::playPause()
{
    if (firstPlay_)
    {
        libvlc_media_player_play(vlcPlayer);
        firstPlay_ = !firstPlay_;
    }

    libvlc_media_player_set_pause(vlcPlayer, libvlc_media_player_is_playing(vlcPlayer));
}

void VlcVideoPlayer::forward()
{
    // @todo Fix audio click (if we have time!)
    libvlc_media_player_set_position(vlcPlayer, libvlc_media_player_get_position (vlcPlayer) + 0.1); // Forward 10%
}

void VlcVideoPlayer::mute()
{
    libvlc_audio_set_mute(vlcPlayer, true);
}

void VlcVideoPlayer::unMute()
{
    libvlc_audio_set_mute(vlcPlayer, false);
}

void VlcVideoPlayer::navigate(double pos)
{
    libvlc_media_player_set_position(vlcPlayer, float(pos));
}

bool VlcVideoPlayer::loadVideo(const char* path)
{
	if(vlcMedia = libvlc_media_new_path(vlcInstance, path))
	{
        libvlc_media_player_set_media(vlcPlayer, vlcMedia);
        libvlc_media_release(vlcMedia);

        // Needed for mixing VLC and wxWidgets.
        // Needs to be after above calls, or else bug with stop button!
        libvlc_media_player_set_hwnd( vlcPlayer, reinterpret_cast<void *> ( (HWND)this->GetHandle() ) );

		/// @todo ????
        // Stuff
        //libvlc_media_player_next_frame(vlcPlayer);
		//libvlc_video_set_format(vlcPlayer);

        _DEBUG_ DSTREAM << "Loaded video file." << endl;
    }
    else
    {
		_DEBUG_ DSTREAM << "Can't load media from path" << endl;
		wxMessageDialog (this, "Can't load media from path");

        return false;
    }

    return true; // Didn't fails loading.
}

void VlcVideoPlayer::videoMovedCallback()
{
    if (videoID_.videoMoved)
    {
        wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, videoID_.videoMoved);
        wxPostEvent(this, btnEvent);
    }
}

void VlcVideoPlayer::vlcPositionChanged(const libvlc_event_t *event, void* data)
{
    ((VlcVideoPlayer*)data)->videoMovedCallback();
}

void VlcVideoPlayer::vlcTimeChanged(const libvlc_event_t *event, void* data)
{
    ((VlcVideoPlayer*)data)->videoTimeCallback();
}

void VlcVideoPlayer::OnVideoCallback(wxCommandEvent& event)
{
    event.Skip();
}

void VlcVideoPlayer::videoTimeCallback()
{
	_DEBUG_ ++nb_time_callback;
	_DEBUG_ if( nb_time_callback %50 == 0)
	_DEBUG_ {
	_DEBUG_		DSTREAM << "Time : " << getTimeMs() << endl;
	_DEBUG_ }
}
