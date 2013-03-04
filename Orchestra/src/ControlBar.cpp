#include "ControlBar.h"

ControlBar::ControlBar(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size)
    : wxPanel(win, id, pt, size)
{
    SetBackgroundStyle(wxBG_STYLE_CUSTOM); // Tell some platforms not to use default background.
    wxImage::AddHandler(new wxPNGHandler); // Format of images to use (usually only one).
    SetBackgroundColour(wxColour(50, 50, 50));
}