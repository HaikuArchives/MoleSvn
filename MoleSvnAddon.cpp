///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : MoleSvnAddon.cpp
// Description : implements the MoleSvnAddon class, the skeleton of the addon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#include "MoleSvnAddon.h"

#include "UI/MoleSvnIcons.h"
#include "UI/MenuItem.h"
#include "UI/IconMenuItem.h"
#include "UI/ResultsWindow.h"

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
MoleSvnAddon::MoleSvnAddon()
:m_pResources(NULL)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// Retrieve addon filename
	std::string filename = GetAddonFilename();
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Addon name = %s", filename.c_str()));
	
	BFile file(filename.c_str(), B_READ_ONLY); 
	if(file.InitCheck() != B_OK)
	{
		throw FileNotFound(filename);	
	}

	// Create resources manager
	m_pResources = new MoleSvnResources(&file);	
}

MoleSvnAddon::MoleSvnAddon(const MoleSvnAddon& addon)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}

MoleSvnAddon* MoleSvnAddon::GetInstance()
{
	static MoleSvnAddon* pInstance = NULL;

	if(!pInstance)
	{
		pInstance = new MoleSvnAddon();	
	}
	
	return pInstance;
}
	
MoleSvnAddon::~MoleSvnAddon()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	if(m_pResources)
	{
		delete m_pResources;
	}
	
	m_lstEntry.clear();
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////
void MoleSvnAddon::SetParameters(const entry_ref& rCurrentDirectory, 
	                             const list<entry_ref>& lstEntry)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_CurrentDirectory = rCurrentDirectory;
	m_lstEntry = lstEntry;
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb entries = %i", m_lstEntry.size()));
}

void MoleSvnAddon::ShowMenu(BPoint point)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// Create the menu
	BPopUpMenu menu("menu");
	menu.AddItem(new IconMenuItem("Update",		C_Update, 	R_Update));
	menu.AddItem(new IconMenuItem("Commit",		C_Commit,	R_Commit));
	menu.AddSeparatorItem();
	menu.AddItem(new IconMenuItem("Chekout", 	C_Checkout,	R_Checkout));
	menu.AddSeparatorItem();
	menu.AddItem(new IconMenuItem("Add", 		C_Add,		R_Add));
	menu.AddSeparatorItem();
	menu.AddItem(new IconMenuItem("Status", 	C_Status,	R_Status));
	menu.AddSeparatorItem();
	menu.AddItem(new IconMenuItem("About", 	C_About, 	R_LogoIcon));
	
	// Show the popup menu
	TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, &point, "Popup menu point"));
	MenuItem* pSelectedItem = static_cast<MenuItem *>(menu.Go(point, false, true));
	// !!! Be carefull !!!
	// pSelectedItem may be NULL if the user does'nt click on the popup menu !!
	if(pSelectedItem && pSelectedItem->GetCommand() == C_Update)
	{
		BScreen screen;
		BRect screenFrame = screen.Frame();
		const float fWindowWidth = 400.0f;
		const float fWindowHeight = 300.0f;
		BRect windowFrame((screenFrame.Width() - fWindowWidth) / 2.0f, 
		                  (screenFrame.Height() - fWindowHeight) / 2.0f, 
		                  (screenFrame.Width() - fWindowWidth) / 2.0f + fWindowWidth, 
		                  (screenFrame.Height() - fWindowHeight) / 2.0f + fWindowHeight);
		ResultsWindow* pWindow = new ResultsWindow(windowFrame, string("Update"));
		pWindow->Show();

		// Wait until the window thread terminates. If we don't do this,
		// our add-on might crash mysteriously, taking the Tracker with
		// it. See also "Be Newsletter Volume II Issue 10".

		int32 exitValue;
		wait_for_thread(pWindow->Thread(), &exitValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
MoleSvnResources* MoleSvnAddon::GetResources()
{
	return m_pResources;
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
image_id MoleSvnAddon::FindAddonImage()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	static int n = 0;
	void* memAddr = &n;
	
	image_info info; 
	int32 cookie = 0; 
	while (get_next_image_info(0, &cookie, &info) == B_OK) 
	{
		if (  (info.text <= memAddr && (((uint8 *)info.text)+info.text_size) > memAddr)
			||(info.data <= memAddr && (((uint8 *)info.data)+info.data_size) > memAddr)) 
		{
			// Found the image.
			return info.id;
		}
	}
	return -1;
}

std::string MoleSvnAddon::GetAddonFilename()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// Find the addon image id
	image_id image = FindAddonImage();

	// Retrieve infos about the image, in particular name ;)
	image_info info;
	if (get_image_info(image, &info) != B_OK) 
	{
		throw ImageException(image);	
	}
	
	return std::string(&info.name[0]);
}
