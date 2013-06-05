/********************************************************************************//**
 * @file	partition.h
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	class Partition
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#ifndef DEF_PARTITION_H
#define DEF_PARTITION_H

#include "axLib.h"
#include <vector>

struct t_point {short x, y;};
struct t_size {short x, y;};

/********************************************************************************//**
* @brief Is use for markers data info.
***********************************************************************************/
struct t_data
{
	int posInFile;
	t_point point;
	t_size size;
	short numImg;
	double time;
};

/********************************************************************************//**
* @brief Partition deals with the partition images and selected bars.
***********************************************************************************/
class Partition: public wxPanel
{
public:
	Partition(wxWindow* win, wxWindowID id, const wxPoint& pt, const wxSize& size);

	/********************************************************************************//**
	* @brief Load markers info and list of images.
	* @param data_path Path for markers info.
	* @param list List of images.
	***********************************************************************************/
	bool loadInfo(const wxString& data_path, const vector<wxString>& list);

	/********************************************************************************//**
	* @brief Load only markers info.
	* @param path Path for markers info.
	***********************************************************************************/
	bool loadMarkerInfo(wxString path);

	/********************************************************************************//**
	* @brief Load only images list.
	* @param list List of all images.
	***********************************************************************************/
	void setImageList(const vector<wxString>& list);	

	/********************************************************************************//**
	* @brief Set the right marker image.
	* @param timeMs Time in millisecond.
	***********************************************************************************/
	bool changeTime(double timeMs);

	/********************************************************************************//**
	* @brief Resize
	* @param size New size of the panel.
	*
	* @todo Set minimum time interval to resize images.
	***********************************************************************************/
	void mSize(wxSize size);

private:
	t_data* markerData;
	int nbMarker, selectedMarker;
	wxImage currentImg, currentMarkerImg;
	vector<wxString> imgList;

	double resizeRatio_x, resizeRatio_y;

	wxLongLong pastResizeTick;

	/********************************************************************************//**
	* @brief Create and resize a transparent image for the selected marker.
	***********************************************************************************/
	void createSelectedMarkerImage();
	void scaleImage(const int& imagelistPosition);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif
