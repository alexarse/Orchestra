/********************************************************************************//**
 * @file	partition.h
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	class MenuPanel
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#ifndef DEF_MENU_PANEL_H
#define DEF_MENU_PANEL_H

#include "axLib.h"
#include <vector>

struct t_info
{
	wxString folderName;
	wxString video, markerData, animation;
	vector<wxString> paritionImg;
};

struct t_folder
{
	wxString name;
	vector<t_info> subfolders;
};

/********************************************************************************//**
* @brief MenuPanel
***********************************************************************************/
class MenuPanel: public wxPanel
{
public:
	MenuPanel(wxWindow* win, const wxWindowID& id, wxPoint pos, wxSize size, wxString path);

	/********************************************************************************//**
	* @brief Resize
	* @param size New size of the panel.
	***********************************************************************************/
	void mSize(wxSize size);



private:

	wxString currentFolder;
	vector< t_folder > folders;
	int selectedFolder, selectedSubFolder;

	axTreeMenu* menu;

	int remplirTableauInformation();
	int creerMenu();

	void OnButtonTest(wxCommandEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif
