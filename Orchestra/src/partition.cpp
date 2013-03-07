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
} 

bool Partition::loadInfo(const wxString& data_path, const vector<wxString>& list)
{
	if(!loadMarkerInfo(data_path))
		return false;

	setImageList(list);

	currentImg = wxImage(imgList[0]);

	if(currentImg.IsOk())
	{
		resizeRatio_x = double(GetSize().x) / currentImg.GetWidth();
		resizeRatio_y = double(GetSize().y) / currentImg.GetHeight();

		currentImg.Rescale(currentImg.GetWidth() * resizeRatio_x, 
						   currentImg.GetHeight() * resizeRatio_y, 
						   wxIMAGE_QUALITY_HIGH);
	}
	else 
	{
		_DEBUG_ DSTREAM << "ERROR LOADING IMG" << endl;
	}

	Refresh();

	return true;
}

bool Partition::loadMarkerInfo(wxString path)
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

	//for(int i = 0; i < nbMarker; ++i)
	//{
	//	_DEBUG_ DSTREAM << "Num Img : " << markerData[i].numImg << endl;
	//	_DEBUG_ DSTREAM << "Num Pos : " << markerData[i].posInFile << endl;
	//}

	return true;
}
void Partition::setImageList(const vector<wxString>& list)
{
	imgList = list;
}
bool Partition::changeTime(double timeMs)
{
	timeMs /= 1000.0;

	if(timeMs > markerData[nbMarker - 1].time) 
	{
		selectedMarker = nbMarker - 1;
			
		// Mettre la bonne image.
		currentImg = wxImage(imgList[markerData[nbMarker - 1].numImg]);
		
		resizeRatio_x = double(GetSize().x) / currentImg.GetWidth();
		resizeRatio_y = double(GetSize().y) / currentImg.GetHeight();

		currentImg.Rescale(currentImg.GetWidth() * resizeRatio_x, 
						   currentImg.GetHeight() * resizeRatio_y, 
						   wxIMAGE_QUALITY_HIGH);

		// TODO S'ASSURER QU'ON NE DEPASSE PAS LA GRANDEUR DU TABLEAU.
		createSelectedMarkerImage();
		Refresh();

		return true;
	}

	for(int i = 0; i < nbMarker - 1; ++i)
	{
		//_DEBUG_ DSTREAM << "MARKER IMG : " << markerData[i].numImg << endl;
		_DEBUG_ DSTREAM << "MARKER TIME : " << markerData[i].time << endl;

		if(markerData[i].time <= timeMs && markerData[i + 1].time >= timeMs) 
		{
			selectedMarker = i;
			
			currentImg = wxImage(imgList[markerData[i].numImg]);

			resizeRatio_x = double(GetSize().x) / currentImg.GetWidth();
			resizeRatio_y = double(GetSize().y) / currentImg.GetHeight();

			currentImg.Rescale(currentImg.GetWidth() * resizeRatio_x, 
							   currentImg.GetHeight() * resizeRatio_y, 
							   wxIMAGE_QUALITY_HIGH);

			// TODO S'ASSURER QU'ON NE DEPASSE PAS LA GRANDEUR DU TABLEAU.
			createSelectedMarkerImage();
			Refresh();

			return true;
		}
	}

	return false;
}
void Partition::processMarkerBitmap(int idNum)
{
	//wxImage img(markerData[idNum].size.x, markerData[idNum].size.y);
	//img.InitAlpha();
	//
	//for(int i = 0; i < markerData[idNum].size.x; i++)
	//	for(int j = 0; j < markerData[idNum].size.y; j++)
	//		img.SetAlpha(i, j, 110);
	//		
	//img.SetRGB(wxRect(0, 0, markerData[idNum].size.x, markerData[idNum].size.y), 255, 0, 0);
	//img.Rescale(img.GetWidth() * x_ratio, img.GetHeight() * y_ratio, wxIMAGE_QUALITY_HIGH); //wxIMAGE_QUALITY_NORMAL);
	//markerBitmap = wxBitmap(img, 32);
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
	//fullSelectedBitmap = wxBitmap(img, 32);
	currentMarkerImg = img;
}
void Partition::mSize(wxSize size)
{
	this->SetSize(size);

	currentImg = wxImage(imgList[markerData[selectedMarker].numImg]);

	resizeRatio_x = double(size.x) / currentImg.GetWidth();
	resizeRatio_y = double(size.y) / currentImg.GetHeight();

	currentImg.Rescale(currentImg.GetWidth() * resizeRatio_x, 
						currentImg.GetHeight() * resizeRatio_y, 
						wxIMAGE_QUALITY_HIGH);

	// TODO S'ASSURER QU'ON NE DEPASSE PAS LA GRANDEUR DU TABLEAU.
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

	if(currentImg.IsOk())
	{
		wxBitmap img(currentImg);
		dc.DrawBitmap(img, 0, 0);
	}

	if(currentMarkerImg.IsOk())
	{
		_DEBUG_ DSTREAM << "MARKER IMG EXIST (OnPaint)" << endl;
		wxBitmap img(currentMarkerImg);
		
		t_point pt = markerData[selectedMarker].point;
		dc.DrawBitmap(currentMarkerImg, pt.x * resizeRatio_x, pt.y * resizeRatio_y);
	}
}