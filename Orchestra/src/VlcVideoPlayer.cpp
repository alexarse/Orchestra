#include "VlcVideoPlayer.h"

// VLC Callbacks
void vlcPositionChanged(const libvlc_event_t *event, void* data);


VlcVideoPlayer::VlcVideoPlayer(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size)
    : wxPanel(win, id, pt, size), firstPlay_(1)
{
	this->SetBackgroundColour(axColor(80, 80, 80));

    // Create new VLC instance.
    char const* vlcOptions[] = {"--no-video-title-show"}; //Hide filename.

    // Create VLC instance
    if(vlcInstance = libvlc_new(1, vlcOptions));
    else {_DEBUG_ DSTREAM << "Can't Open VLC instance" << endl;}

    // Create VLC player
	if(vlcPlayer = libvlc_media_player_new(vlcInstance));
    else {_DEBUG_ DSTREAM << "Can't create player from vlcMedia" << endl;}

    // Create VLC EventManager
    if(vlcEventManager = libvlc_media_player_event_manager(vlcPlayer));
    else {_DEBUG_ DSTREAM << "Can't create VLC Event Manager" << endl;}


    // libVLC events and callback
    libvlc_event_attach(vlcEventManager, libvlc_MediaPlayerPositionChanged, ::vlcPositionChanged, NULL);

}

VlcVideoPlayer::~VlcVideoPlayer()
{
    //libvlc_media_release(vlcMedia);
    //libvlc_media_player_release(vlcPlayer);
    libvlc_release(vlcInstance); // Destroy VLC instance
}

double VlcVideoPlayer::getPosition() const
{
    return double(libvlc_media_player_get_position(vlcPlayer));
}

void VlcVideoPlayer::mSize(const wxSize& size)
{
    // Don't need checks because media player sends good data
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

}

// Control Buttons
void VlcVideoPlayer::backward()
{
    // @todo Fix audio click (if we have time!)
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
        libvlc_media_player_set_hwnd(vlcPlayer, reinterpret_cast<void *> ((HWND)this->GetHandle()));

        // Stuff
        //libvlc_media_player_next_frame(vlcPlayer);
		//libvlc_video_set_format(vlcPlayer);


        _DEBUG_ DSTREAM << "Loaded video file." << endl;
    }
    else
    {
        return false;
        _DEBUG_ DSTREAM << "Can't load media from path" << endl;
    }

    return true; // No fails loading.
}

