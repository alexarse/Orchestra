/********************************************************************************//**
 * @file	MenuPanel.cpp
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief	class MenuPanel
 * @date	Creation 07/03/2013
 ***********************************************************************************/
#include "MenuPanel.h"

#define MENU_ID (8000)

//-----------------------------------------------------------------------------------
// MenuPanel
//-----------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MenuPanel, wxPanel)
	//EVT_PAINT(MenuPanel::OnPaint)
	EVT_LEFT_DOWN(MenuPanel::OnMouseLeftDown)
	EVT_LEFT_UP(MenuPanel::OnMouseLeftUp)
	EVT_MOTION(MenuPanel::OnMouseMotion)
END_EVENT_TABLE()

MenuPanel::MenuPanel(wxWindow* win, const wxWindowID& id, wxPoint pos, wxSize size, wxString path) :
	       wxPanel(win, id, pos, size)
{
	//SetBackgroundStyle(wxBG_STYLE_CUSTOM); 		
	wxImage::AddHandler(new wxPNGHandler);

	SetBackgroundColour(axColor(80, 80, 80));

	currentFolder = path;

	selectedFolder = 0;
	selectedSubFolder = 0;

	if(remplirTableauInformation())
	{
		creerMenu();
	}
	else
	{
		_DEBUG_ DSTREAM << "ERROR MenuPanel : Lire dans les dossiers." << endl;
	}
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
		bool cont = dir.GetFirst(&path, wxEmptyString, wxDIR_DIRS);
		int i = 0; // Folder count

		// Lit dans les dossiers. (Songs)
		while ( cont )
		{
			_DEBUG_ DSTREAM << "FOLDER : " << path << endl;

			// Init with null.
			t_folder info_default;
			folders.push_back(info_default);

			folders[i].name = path;
				
			/// @todo Deal with error.

			// Open sub folder.
			wxString subFolderName = currentFolder + path + wxT("/");
			wxString longSubFolderName = subFolderName;
			_DEBUG_ DSTREAM << "SUBFOLDER : " << subFolderName << endl;

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

					_DEBUG_ DSTREAM << " SUBFOLDER : " << subFolderName << endl;

					/// @todo Read folder info.
					wxArrayString* files = new wxArrayString();
					int nbFiles = subDir.GetAllFiles(longSubFolderName + subFolderName, files, wxEmptyString, wxDIR_DEFAULT);
					
					// Lire dans les lessons.
					for(int n = 0; n < files->GetCount(); ++n)
					{
						//_DEBUG_ DSTREAM << "TEST : " << files->Item(n) << endl;
						wxString s = files->Item(n);
						wxString pos = s[s.Length()];
						int k = 1;

						// Trouver l'extension.
						while(pos != '.')
						{
							pos = s[s.Length() - k];
							_DEBUG_ DSTREAM << s[s.Length() - k] << endl;
							++k;
						}
						
						--k;
						
						// Creer un wxString avec l'extension.
						wxString s2;
						int size = k;
						for(int i = 0; i < size; ++i)
						{
							s2 += s[s.Length() - k];
							--k;
						}
						//_DEBUG_ DSTREAM << ".... : " << s2 << endl;

						if( s2 == wxT(".png") )
						{
							_DEBUG_ DSTREAM << "PNG" << endl;
							folders[i].subfolders[j].paritionImg.push_back(s);
						}

						else if( s2 == wxT(".avi") )
						{
							_DEBUG_ DSTREAM << "AVI" << endl;
							folders[i].subfolders[j].video = s;
						}

						else if( s2 == wxT(".data") )
						{
							_DEBUG_ DSTREAM << "DATA" << endl;
							folders[i].subfolders[j].markerData = s;
						}
					}

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
t_info MenuPanel::getSelectionInfo()
{
	return folders[selectedFolder].subfolders[selectedSubFolder];
}

int MenuPanel::creerMenu()
{
	// Images for axScrollBar.
	axMultipleBitmap scrollBarImg(wxT("resources/widget/scrollSmall.png"), 2, wxSize(11, 33));

	// Create axTreeMenu.
	menu = new axTreeMenu(this, wxID_ANY, wxPoint(0, 30), wxSize(GetSize().x, GetSize().y - 30), &scrollBarImg);

	// Images for folder and subfolder.
	axMultipleBitmap* mainNodeImg = new axMultipleBitmap(wxT("resources/widget/mainNode2.png"),  2, wxSize(12, 12));
	axMultipleBitmap* subNodeImg  = new axMultipleBitmap(wxT("resources/widget/SubNode.png"),   2, wxSize(12, 12));
	axMultipleBitmap* subNodeImg2 = new axMultipleBitmap(wxT("resources/widget/blackNode.png"), 2, wxSize(12, 12));
	
	//// UI info for main node.
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

	// UI info for subnode.
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

	// Create root node.
	axTreeMenuNode* root = new axTreeMenuNode(menu, wxID_ANY, wxT("Song List Menu"), mainNodeData, mainNodeImg);
	menu->addRootNode(root);
	menu->hideRoot(mainNodeData.height);
	root->selectNode();

	int menu_id = MENU_ID;

	// Fill first row menu.
	for(unsigned int i = 0; i < folders.size(); ++i)
	{
		axTreeMenuNode* f = new axTreeMenuNode(root, wxID_ANY, folders[i].name, 
											   mainNodeData, mainNodeImg);
		root->addSubNode(f);

		// Fill second ro menu.
		for(unsigned int j = 0; j < folders[i].subfolders.size(); ++j)
		{
			f->addSubNode(menu_id, folders[i].subfolders[j].folderName, 
				          subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);

			// Connect event.
			Connect(menu_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MenuPanel::OnButtonTest));

			++menu_id;
		}
	}
	/// @todo Deal with error.

	return 1;
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