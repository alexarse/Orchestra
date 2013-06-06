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

/// @todo Needs Documentation.
struct t_info
{
	wxString folderName;
	wxString video, markerData, animation;
	vector<wxString> paritionImg;
};

/// @todo Needs Documentation.
struct t_folder
{
	wxString name;
	vector<t_info> subfolders;
};

/********************************************************************************//**
* @brief MenuPanel
* @todo Needs Documentation.
***********************************************************************************/
class MenuPanel: public wxPanel
{
public:
	MenuPanel(wxWindow* win, const wxWindowID& id, wxPoint pos, wxSize size, wxString currentFolderPath);

	/********************************************************************************//**
	* @brief Resize
	* @param size New size of the panel.
	***********************************************************************************/
	void mSize(wxSize size);

	t_info getSelectionInfo();

private:

	wxString currentFolder;
	vector< t_folder > folders;
	int selectedFolder, selectedSubFolder;

	axTreeMenu* menu;

	int remplirTableauInformation();
	int creerMenu();

	axTreeMenuData fillMainNodeData();
	axTreeMenuData fillSubNodeData();
	wxString getFileExtension(wxString filePath);
	void addFilesToFolderInfo(t_info& folder_info, wxArrayString* files);

	void OnButtonTest(wxCommandEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif
