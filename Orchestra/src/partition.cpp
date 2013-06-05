/********************************************************************************//**
 * @file	partition.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	class Partition
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#include "partition.h"

#include <fstream>
#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------------
// Partition
//-----------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(Partition, wxPanel)
	EVT_PAINT(Partition::OnPaint)
	EVT_LEFT_DOWN(Partition::OnMouseLeftDown)
	EVT_LEFT_UP(Partition::OnMouseLeftUp)
	EVT_MOTION(Partition::OnMouseMotion)
END_EVENT_TABLE()

Partition::Partition(wxWindow* win, wxWindowID id, const wxPoint& pt, const wxSize& size): wxPanel(win, id, pt, size)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM); 		
	wxImage::AddHandler(new wxPNGHandler);

	selectedMarker = 0;
	nbMarker = 0;
	markerData = NULL;
	pastResizeTick = 0;
} 

bool Partition::loadInfo(const wxString& data_path, const vector<wxString>& list)
{
	if(!loadMarkerInfo(data_path)) return false;
		
	setImageList(list);

	return true;
}

bool Partition::loadMarkerInfo( wxString path )
{
	ifstream data(path.char_str(), ios::binary);

	if(data.fail())
	{
		_DEBUG_ DSTREAM << "ERROR : Load data in Partition" << endl;
		return false;
	}

	else
	{
		data.seekg(0);
		nbMarker = 0;
		data.read((char*)&nbMarker, sizeof(int));
		markerData = new t_data[nbMarker];

		_DEBUG_ DSTREAM << "NB CUE : " << nbMarker << endl;

		data.read((char*)markerData, sizeof(t_data) * nbMarker);
		data.close();
	}

	return true;
}

void Partition::setImageList(const vector<wxString>& list)
{
	imgList = list;
	currentImg = wxImage(imgList[0]);
	Refresh();
}

bool Partition::changeTime( double timeMs )
{
	timeMs /= 1000.0;

	if(timeMs > markerData[nbMarker - 1].time) 
	{
		selectedMarker = nbMarker - 1;
		scaleImage(markerData[nbMarker - 1].numImg);
		createSelectedMarkerImage();
		Refresh();

		return true;
	}

	for(int i = 0; i < nbMarker - 1; ++i)
	{
		if(markerData[i].time <= timeMs && markerData[i + 1].time >= timeMs) 
		{
			selectedMarker = i;
			scaleImage(markerData[i].numImg);
			createSelectedMarkerImage();
			Refresh();

			return true;
		}
	}

	return false;
}

void Partition::createSelectedMarkerImage()
{
	t_size size = markerData[selectedMarker].size;

	int x = size.x * resizeRatio_x;
	int y = size.y * resizeRatio_y;

	wxImage img(x, y);
	img.InitAlpha();
	
	for(int i = 0; i < x; ++i)
		for(int j = 0; j < y; ++j)
			img.SetAlpha(i, j, 110);
			
	img.SetRGB(wxRect(0, 0, x, y), 180, 180, 180);
	currentMarkerImg = img;
}

void Partition::scaleImage(const int& imagelistPosition)
{
	int x = GetSize().x - 100, y = GetSize().y - 100;
	currentImg = wxImage( imgList[imagelistPosition] );
	resizeRatio_x = double(x) / currentImg.GetWidth();
	resizeRatio_y = double(y) / currentImg.GetHeight();
	currentImg.Rescale(x, y, wxIMAGE_QUALITY_HIGH);
}

void Partition::mSize(wxSize size)
{
	//wxLongLong clickTime = wxGetLocalTimeMillis();
	//if(clickTime - pastResizeTick >= wxLongLong(400))
	//pastResizeTick = clickTime;

	SetSize(size);
	scaleImage(markerData[selectedMarker].numImg);
	createSelectedMarkerImage();
	Refresh();
}

void Partition::OnMouseLeftDown(wxMouseEvent& event)
{
	
}

void Partition::OnMouseLeftUp(wxMouseEvent& event)
{
}

void Partition::OnMouseMotion(wxMouseEvent& event)
{
	//wxPoint pt = event.GetPosition();

	//int i = imgMarkerStartPosition;
	//while(markerData[i].numImg == selectedBitmap)
	//{
	//	if(pt.x >= 10 + markerData[i].point.x * x_ratio && 
	//	   pt.x < 10 + markerData[i].point.x * x_ratio + markerData[i].size.x * x_ratio &&
	//	   pt.y >=  50 + markerData[i].point.y * y_ratio && 
	//	   pt.y <  50 + markerData[i].point.y * x_ratio + markerData[i].size.y * y_ratio)
	//	{
	//		selectedMouseHover = i;
	//		processSelectedBitmap(selectedMouseHover);
	//		selected = true;
	//		Refresh();
	//		break;
	//	}
	//	else selected = false;

	//	i++;
	//}
	//if(i != selectedMouseHover)
	//{
	//	selected = false;
	//	Refresh();
	//}
}

void Partition::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	dc.SetPen( wxPen( wxColor(0, 0, 0), 2, wxSOLID) );
    dc.SetBrush( wxBrush( wxColor(250, 250, 250) ) );
    dc.DrawRectangle( wxRect(0, 0, size.x, size.y) );

	if(currentImg.IsOk())
	{
		wxBitmap img(currentImg);
		dc.DrawBitmap(img, 50, 50);
	}

	if(currentMarkerImg.IsOk())
	{
		_DEBUG_ DSTREAM << "MARKER IMG EXIST (OnPaint)" << endl;
		wxBitmap img(currentMarkerImg);
		
		t_point pt = markerData[selectedMarker].point;
		dc.DrawBitmap(currentMarkerImg, 50 + pt.x * resizeRatio_x, 50 + pt.y * resizeRatio_y);
	}
}