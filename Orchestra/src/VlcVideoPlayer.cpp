#include "VlcVideoPlayer.h"

VlcVideoPlayer::VlcVideoPlayer(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size)
    : wxPanel(win, id, pt, size), firstPlay_(1)
{
	this->SetBackgroundColour(axColor(80, 80, 80));

    // Create new VLC instance.
    if(vlcInstance = libvlc_new(0, NULL));
    else {_DEBUG_ DSTREAM << "Can't Open VLC instance" << endl;}

}

VlcVideoPlayer::~VlcVideoPlayer()
{
	// @todo ERROR WHEN CLOSING IF NO VIDEO IS LOADED.
    //libvlc_media_player_release(vlcPlayer);
    //libvlc_release(vlcInstance); // Destroy VLC instance
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
void VlcVideoPlayer::play()
{
    // @todo Fix and use libvlc_media_player_set_pause(vlcPlayer, pause_);
    // It's more elegant and we can combine it with libvlc_media_player_is_playing(vlcPlayer) (returns 0 or 1).
    
    if (firstPlay_)
    {
        libvlc_media_player_play(vlcPlayer);
        firstPlay_ = !firstPlay_;
    }

    libvlc_media_player_set_pause(vlcPlayer, libvlc_media_player_is_playing(vlcPlayer));

    //_DEBUG_ DSTREAM << "VlcVideoPlayer Play(vlcPlayer, " << pause_ <<") was called." << endl; 
}

void VlcVideoPlayer::stop()
{
    libvlc_media_player_stop(vlcPlayer);
    firstPlay_ = 1;
    _DEBUG_ DSTREAM << "VlcVideoPlayer Stop() was called." << endl; 
}

bool VlcVideoPlayer::loadVideo(const char* path)
{
	if(vlcMedia = libvlc_media_new_path(vlcInstance, path))
	{
		if(vlcPlayer = libvlc_media_player_new(vlcInstance))
		{
            libvlc_media_player_set_media(vlcPlayer, vlcMedia);
            libvlc_media_release(vlcMedia);

			libvlc_media_player_set_hwnd(vlcPlayer, reinterpret_cast<void *> ((HWND)this->GetHandle())); // Needed for mixing VLC and wxWidgets.
			//libvlc_media_player_next_frame(vlcPlayer);
			//libvlc_video_set_format(vlcPlayer)
            _DEBUG_ DSTREAM << "Loaded video file." << endl;

        } 
        else 
        {
            return false;
            _DEBUG_ DSTREAM << "Can't create player from vlcMedia" << endl;
        }
    } 
    else 
    {
        return false;
        _DEBUG_ DSTREAM << "Can't media from path" << endl;
    }

    return true; // No fails loading.
}