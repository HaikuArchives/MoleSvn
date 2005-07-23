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

#include "Svn/SvnCommands.h"

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
	
	// Set current working directory, where the user has clicked
	BPath path(&m_CurrentDirectory);
	chdir(path.Path());
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Current directory = %s", path.Path()));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb entries = %i", m_lstEntry.size()));
}

void MoleSvnAddon::ShowMenu(BPoint point)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// Create popupmenu
	BPopUpMenu* pMenu =  CreateMenu();

	// Show the popup menu
	TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, &point, "Popup menu point"));
	MenuItem* pSelectedItem = static_cast<MenuItem *>(pMenu->Go(point, false, true));
	// !!! Be carefull !!!
	// pSelectedItem may be NULL if the user doesn't click on the popup menu !!
	if(pSelectedItem)
	{
		// Execute the selected command
		pSelectedItem->GetSvnCommand()->Execute();
	}

	// Wait until the window thread terminates. If we don't do this,
	// our add-on might crash mysteriously, taking the Tracker with
	// it. See also "Be Newsletter Volume II Issue 10".
	int32 exitValue;
	while(m_setThread.size())
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb threads = %d", m_setThread.size()));
		thread_id id = *m_setThread.begin();
		
		// Wait for thread
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Wait for thread id = %d", id));
		wait_for_thread(id, &exitValue);
		
		// Remove thread_id from the running threads set
		RemoveThread(id);
	}
		
}

void MoleSvnAddon::AddThread(thread_id id)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_setThread.insert(id);
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Add thread id = %d", id));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb threads = %d", m_setThread.size()));
}
		
void MoleSvnAddon::RemoveThread(thread_id id)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	set<thread_id, ltthread_id>::iterator ite = m_setThread.find(id);
	if(ite != m_setThread.end())
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Erase thread id = %d", *ite));
		m_setThread.erase(*ite);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb threads = %d", m_setThread.size()));
	}
	else
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Thread id not found = %d", *ite));
	}
}


///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////
MoleSvnResources* MoleSvnAddon::GetResources()
{
	return m_pResources;
}

entry_ref* MoleSvnAddon::GetCurrentDirectory()
{
	return &m_CurrentDirectory;
}


string MoleSvnAddon::GetEntryNameList() const
{
	string strRes;
	list<entry_ref>::const_iterator ite = m_lstEntry.begin();
	
	while(ite != m_lstEntry.end())
	{
		strRes += string("\"") + string( (*ite).name ) + string("\" ");		
		++ite;
	}
	
	return strRes;
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
BPopUpMenu* MoleSvnAddon::CreateMenu()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	bool bHasRepo = HasRepository();
	bool bHasSelectedFiles = m_lstEntry.size();

	// Create the menu
	BPopUpMenu* pMenu = new BPopUpMenu("menu");
	if(!bHasRepo)
	{
		pMenu->AddItem(new IconMenuItem(new Checkout()));
		pMenu->AddSeparatorItem();
	}
	if(bHasSelectedFiles || bHasRepo)
	{
		pMenu->AddItem(new IconMenuItem(new Update()));
		pMenu->AddItem(new IconMenuItem(new Commit()));
		pMenu->AddSeparatorItem();
	}
	
	if(bHasRepo && bHasSelectedFiles)
	{
		pMenu->AddItem(new IconMenuItem(new Add()));
		pMenu->AddItem(new IconMenuItem(new Delete()));
		pMenu->AddItem(new IconMenuItem(new Revert()));	
		// if the user has selected only one file
		if(m_lstEntry.size() == 1)
			pMenu->AddItem(new IconMenuItem(new Rename()));	
		pMenu->AddSeparatorItem();
	}
			
	if(bHasSelectedFiles)
	{
		pMenu->AddItem(new IconMenuItem(new Cleanup()));
		pMenu->AddItem(new IconMenuItem(new Resolved()));	
		pMenu->AddSeparatorItem();
	}
	
	if( (!bHasRepo && bHasSelectedFiles) || bHasRepo)
	{
		pMenu->AddItem(new IconMenuItem(new Status()));
		pMenu->AddSeparatorItem();
	}
	
	pMenu->AddItem(new IconMenuItem(new About()));

//	pMenu->AddItem(new IconMenuItem(new Blame()));


	// returns the popupmenu
	return pMenu;
}

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
	
	return std::string(info.name);
}

bool MoleSvnAddon::HasRepository()
{
	BEntry entry; 
	BDirectory dir(&m_CurrentDirectory);
	return (dir.FindEntry(".svn", &entry) == B_OK);
}

