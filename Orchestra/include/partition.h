#ifndef DEF_PARTITION_H
#define DEF_PARTITION_H

#include "axLib.h"
#include <vector>

struct t_point {short x, y;};
struct t_size {short x, y;};

struct t_data
{
	int posInFile;
	t_point point;
	t_size size;
	short numImg;
	double time;
};

class Partition: public wxPanel
{
public:
	Partition(wxWindow* win, wxWindowID id, const wxPoint& pt, const wxSize& size);

	bool loadInfo(const wxString& data_path, const vector<wxString>& list);
	bool loadMarkerInfo(wxString path);
	void setImageList(const vector<wxString>& list);	
	bool changeTime(double timeMs);

	void mSize(wxSize size);

private:
	t_data* markerData;
	int nbMarker, selectedMarker;
	wxImage currentImg, currentMarkerImg;
	vector<wxString> imgList;

	double resizeRatio_x, resizeRatio_y;

	void processMarkerBitmap(int idNum);
	void createSelectedMarkerImage();

	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif
