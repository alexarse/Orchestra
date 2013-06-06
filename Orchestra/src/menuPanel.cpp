/********************************************************************************//**
 * @file	MenuPanel.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	class MenuPanel
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#include "MenuPanel.h"

#define MENU_ID (8000)

BEGIN_EVENT_TABLE(MenuPanel, wxPanel)
	//EVT_PAINT(MenuPanel::OnPaint)
	EVT_LEFT_DOWN(MenuPanel::OnMouseLeftDown)
	EVT_LEFT_UP(MenuPanel::OnMouseLeftUp)
	EVT_MOTION(MenuPanel::OnMouseMotion)
END_EVENT_TABLE()

MenuPanel::MenuPanel(wxWindow* win, const wxWindowID& id, wxPoint pos, wxSize size, wxString currentFolderPath) :
	       wxPanel(win, id, pos, size)
{		
	wxImage::AddHandler(new wxPNGHandler);
	SetBackgroundColour(axColor(80, 80, 80));

	currentFolder = currentFolderPath;
	selectedFolder = selectedSubFolder = 0;

	if( remplirTableauInformation() )
	{
		creerMenu();
	}

	else
	{
		_DEBUG_ DSTREAM << "ERROR MenuPanel : Lire dans les dossiers." << endl;
	}
} 

int MenuPanel::creerMenu()
{
	// Images for axScrollBar.
	axMultipleBitmap scrollBarImg(wxT("resources/widget/scrollSmall.png"), 2, wxSize(11, 33));

	// Create axTreeMenu.
	menu = new axTreeMenu(this, wxID_ANY, wxPoint(0, 30), wxSize(GetSize().x, GetSize().y - 30), &scrollBarImg);

	// Images for folder and subfolder.
	axMultipleBitmap* mNodeImg = new axMultipleBitmap(wxT("resources/widget/mainNode2.png"), 2, wxSize(12, 12));
	axMultipleBitmap* sNodeImg  = new axMultipleBitmap(wxT("resources/widget/SubNode.png"), 2, wxSize(12, 12));
	axMultipleBitmap* sNodeImg2 = new axMultipleBitmap(wxT("resources/widget/blackNode.png"), 2, wxSize(12, 12));
	
	// UI info for main node.
	axTreeMenuData mNodeData = fillMainNodeData();

	// UI info for subnode.
	axTreeMenuData sNodeData = fillSubNodeData();

	// Create root node.
	axTreeMenuNode* root = new axTreeMenuNode(menu, wxID_ANY, wxT("Song List Menu"), mNodeData, mNodeImg);
	menu->addRootNode(root);
	menu->hideRoot(mNodeData.height);
	root->selectNode();

	int menu_id = MENU_ID;

	// Fill first row menu.
	for(unsigned int i = 0; i < folders.size(); ++i)
	{
		axTreeMenuNode* f = new axTreeMenuNode(root, wxID_ANY, folders[i].name, mNodeData, mNodeImg);
		root->addSubNode(f);

		t_folder* folder = &folders[i];
		// Fill second ro menu.
		for(unsigned int j = 0; j < folder->subfolders.size(); ++j)
		{
			f->addSubNode(menu_id, folder->subfolders[j].folderName, sNodeData, sNodeImg, SELECT_ONLY_THIS_ID);
			Connect(menu_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MenuPanel::OnButtonTest));
			++menu_id;
		}
	}
	/// @todo Deal with error.

	return 1;
}

axTreeMenuData MenuPanel::fillMainNodeData()
{
	axTreeMenuData mainNodeData;
	mainNodeData.nodeColorNormal		= wxColor(130, 130, 130);
	mainNodeData.nodeColorHover			= wxColor(135, 135, 135);
	mainNodeData.nodeColorSelected		= wxColor(125, 125, 125);
	mainNodeData.nodeTxtColorNormal		= wxColor(180, 180, 180);
	mainNodeData.nodeTxtColorHover		= wxColor(200, 200, 200);
	mainNodeData.nodeTxtColorSelected	= wxColor(160, 160, 160);
	mainNodeData.nodeContourColor		= wxColor(120, 120, 120);
	mainNodeData.height = 25;
	mainNodeData.nodeID = 0;

	return mainNodeData;
}

axTreeMenuData MenuPanel::fillSubNodeData()
{
	axTreeMenuData subNodeData;
	subNodeData.nodeColorNormal			= wxColor(140, 140, 140);
	subNodeData.nodeColorHover			= wxColor(145, 145, 145);
	subNodeData.nodeColorSelected		= wxColor(135, 135, 135);
	subNodeData.nodeTxtColorNormal		= wxColor(0, 0, 0);
	subNodeData.nodeTxtColorHover		= wxColor(200, 200, 200);
	subNodeData.nodeTxtColorSelected	= wxColor(70, 70, 70);
	subNodeData.nodeContourColor		= wxColor(120, 120, 120);
	subNodeData.height = 25;
	subNodeData.nodeID = 1;

	return subNodeData;
}

int MenuPanel::remplirTableauInformation()
{
	// Open current folder
	wxString path = currentFolder;
	wxDir dir( path );

	if ( !dir.IsOpened() )
    {
        _DEBUG_ DSTREAM << "ERROR : Le dossier n'a pas ouvert" << endl;
		return 0;
		/// @todo Deal with error
    }

	// Folder is open.
	else
	{
		int i = 0; // Folder count
		bool cont = dir.GetFirst(&path, wxEmptyString, wxDIR_DIRS);
		
		// Lit dans les dossiers. (Songs)
		while ( cont )
		{
			_DEBUG_ DSTREAM << "FOLDER : " << path << endl;

			// Init with null.
			t_folder info_default;
			folders.push_back( info_default );

			folders[i].name = path;
				
			/// @todo Deal with error.

			// Open sub folder.
			wxString subFolderName = currentFolder + path + wxT("/");
			wxString longSubFolderName = subFolderName;

			wxDir subDir( subFolderName );

			// Is not open
			if ( !subDir.IsOpened() )
			{
				_DEBUG_ DSTREAM << "ERROR : Le sous dossier n'a pas ouvert" << endl;
				/// @todo Deal wih error.
				return 0;
			}

			// Is open
			else
			{
				// Initialisation de la deuxieme boucle de lecture.
				bool subCont = subDir.GetFirst(&subFolderName, wxEmptyString, wxDIR_DIRS);
				int j = 0;

				// Lit dans les sous-dossiers. (Lessons)
				while ( subCont )
				{
					// Variable pour remplir le vector.
					t_info subFiles;
					folders[i].subfolders.push_back(subFiles);
					folders[i].subfolders[j].folderName = subFolderName;

					/// @todo Read folder info.
					wxArrayString* files = new wxArrayString();
					int nbFiles = subDir.GetAllFiles(longSubFolderName + subFolderName, files, wxEmptyString, wxDIR_DEFAULT);
					
					addFilesToFolderInfo(folders[i].subfolders[j], files);

					/// @todo Deal with error.

					subCont = subDir.GetNext(&subFolderName);
					++j;
				}

				++i;
				cont = dir.GetNext(&path);
			}
		}
	}

	return 1;
}

void MenuPanel::addFilesToFolderInfo(t_info& folder_info, wxArrayString* files)
{
	// Lire dans les lessons.
	for(int n = 0; n < files->GetCount(); ++n)
	{
		wxString s = files->Item(n);
		wxString s2 = getFileExtension(s);

		if( s2 == wxT(".png") )
		{
			_DEBUG_ DSTREAM << "PNG" << endl;
			folder_info.paritionImg.push_back(s);
		}

		else if( s2 == wxT(".avi") )
		{
			_DEBUG_ DSTREAM << "AVI" << endl;
			folder_info.video = s;
		}

		else if( s2 == wxT(".data") )
		{
			_DEBUG_ DSTREAM << "DATA" << endl;
			folder_info.markerData = s;
		}
	}
}

wxString MenuPanel::getFileExtension(wxString filePath)
{
	wxString pos = filePath[filePath.Length()];
	int k = 1;

	// Trouver l'extension.
	while(pos != '.')
	{
		pos = filePath[filePath.Length() - k];
		++k;
	}
						
	--k;
						
	// Creer un wxString avec l'extension.
	wxString s2;
	int size = k;
	for(int i = 0; i < size; ++i)
	{
		s2 += filePath[filePath.Length() - k];
		--k;
	}
	
	return s2;
}

t_info MenuPanel::getSelectionInfo()
{
	return folders[selectedFolder].subfolders[selectedSubFolder];
}

void MenuPanel::mSize(wxSize size)
{

}

void MenuPanel::OnButtonTest(wxCommandEvent& event)
{
}

void MenuPanel::OnMouseLeftDown(wxMouseEvent& event)
{
	
}

void MenuPanel::OnMouseLeftUp(wxMouseEvent& event)
{
}

void MenuPanel::OnMouseMotion(wxMouseEvent& event)
{

}

void MenuPanel::OnPaint(wxPaintEvent& event)
{

}