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
#include "Svn/SvnDirEntry.h"
#include "Svn/SvnFileEntry.h"

#include <string>

//#define TIXML_USE_STL
#include "3rd/TinyXML/tinyxml.h"

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
	
	hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef>::iterator ite = m_mapSvnEntries.begin();
	
	while(ite != m_mapSvnEntries.end())
	{
		delete (*ite).second;
		++ite;
	}
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
	
	// Load repository of the current directory
	LoadRepository(BDirectory(&m_CurrentDirectory));
}

bool MoleSvnAddon::HasRepository(const BDirectory& dir)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// Retrieve the subdirectory "svn"
	BEntry SvnEntry;
	return (dir.FindEntry(".svn", &SvnEntry) == B_OK);
}

#define RETRIEVE_INFO(str, attribut) \
	string str; \
	const char* p##str = attribut; \
	if(p##str) \
		str.assign(p##str); \


bool MoleSvnAddon::LoadRepository(const BDirectory& dir)
{
	// Check if the dir contains .svn subdirectory
	if(!HasRepository(dir))
		return false;
	
	BEntry entry(GetEntriesEntry(dir));

	BPath path;
	entry.GetPath(&path);
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Loading file = %s", path.Path()));
	TiXmlDocument doc( path.Path() );
	doc.LoadFile();	
	if ( doc.Error() && doc.ErrorId() == TiXmlBase::TIXML_ERROR_OPENING_FILE ) 
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "File not found = %s", path.Path()));
		return false;
	}
	else
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Reading file ok = %s", path.Path()));

		// Now, we can extract infos
		TiXmlElement* pRoot = doc.RootElement();
		if(!pRoot)
			return false;
			
		TiXmlElement* pElt = pRoot->FirstChildElement();
		while(pElt)
		{
			// Retrieve common infos
			RETRIEVE_INFO(strName, pElt->Attribute("name"));
			RETRIEVE_INFO(strKind, pElt->Attribute("kind"));

			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Element = %s  name=%s ", pElt->Value(), strName.c_str()));
			
			if(strKind == string("file"))
			{
				// Retrieve entry_ref from the name
				BEntry entrytmp(&dir, strName.c_str());
				entry_ref ertmp;
				entrytmp.GetRef(&ertmp);
				
				// Retrieve infos about the file
				RETRIEVE_INFO(strCommittedRev, pElt->Attribute("committed-rev"));
				RETRIEVE_INFO(strCommittedDate, pElt->Attribute("committed-date"));
				
				if(strName.size() == 0)
				{
					// it's not a file, it's infos about a path
					//string strUrl(pElt->Attribute("url"));
					//string strUuid(pElt->Attribute("uuid"));
					//string strRevision(pElt->Attribute("revision"));
					//string strLastAuthor(pElt->Attribute("last-author"));
					RETRIEVE_INFO(strUrl, pElt->Attribute("url"));
					RETRIEVE_INFO(strUuid, pElt->Attribute("uuid"));
					RETRIEVE_INFO(strRevision, pElt->Attribute("revision"));
					RETRIEVE_INFO(strLastAuthor, pElt->Attribute("last-author"));
				}
				else
				{
					//string strTextTime(pElt->Attribute("text-time"));
					//string strChecksum(pElt->Attribute("checksum"));
					RETRIEVE_INFO(strTextTime, pElt->Attribute("text-time"));
					RETRIEVE_INFO(strChecksum, pElt->Attribute("checksum"));										
					RETRIEVE_INFO(strPropTime, pElt->Attribute("prop-time"));										
					RETRIEVE_INFO(strLastAuthor, pElt->Attribute("last-author"));
					RETRIEVE_INFO(strSchedule, pElt->Attribute("schedule"));

					SvnFileEntry* pFileEntry = new SvnFileEntry(strName);
					//pFileEntry->SetCommittedRevision(strCommittedRev);
					pFileEntry->SetLastAuthor(strLastAuthor);
					pFileEntry->SetSchedule(strSchedule);
					m_mapSvnEntries[ertmp] = pFileEntry;
				}
			}
			else // dir
			{
				// Retrieve entry_ref from the name
				BDirectory dirtmp(&dir, strName.c_str());				
				BEntry entrytmp;
				dirtmp.GetEntry(&entrytmp);
				entry_ref ertmp;
				entrytmp.GetRef(&ertmp);
				
				m_mapSvnEntries[ertmp] = new SvnDirEntry(strName);
			}
			
			// Next element
			pElt = pElt->NextSiblingElement();
		}
	}
	
	return true;
}

SvnEntry* MoleSvnAddon::IsInRepository(const entry_ref& e)
{
	hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef>::const_iterator ite = m_mapSvnEntries.find(e);
	
	if(ite == m_mapSvnEntries.end())
		return NULL;

	return (*ite).second;
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

const hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>& MoleSvnAddon::GetSvnEntries() const
{
	return m_mapSvnEntries;
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
bool AllInRepositoryFunc(entry_ref x)
{
	return MoleSvnAddon::GetInstance()->GetSvnEntries().find(x) != MoleSvnAddon::GetInstance()->GetSvnEntries().end(); 
}

BPopUpMenu* MoleSvnAddon::CreateMenu()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
/*
	bool bHasRepo = HasRepository(BDirectory(&m_CurrentDirectory));
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
*/
	bool bCurDirHasRepo = HasRepository(BDirectory(&m_CurrentDirectory));
	bool bHasSelectedFiles = m_lstEntry.size();

	bool bAllInRepository = find_if(m_lstEntry.begin(), m_lstEntry.end(), AllInRepositoryFunc) != m_lstEntry.end();

	// Create the menu
	BPopUpMenu* pMenu = new BPopUpMenu("menu");
	if(!bCurDirHasRepo)
	{
		pMenu->AddItem(new IconMenuItem(new Checkout()));
		pMenu->AddSeparatorItem();
	}
	
	if(bCurDirHasRepo || bHasSelectedFiles )
	{
		pMenu->AddItem(new IconMenuItem(new Update()));
		pMenu->AddItem(new IconMenuItem(new Commit()));
		pMenu->AddSeparatorItem();
	}

	bool bNeedToAddSeparator = false;
	if(bCurDirHasRepo && bHasSelectedFiles && !bAllInRepository)
	{
		pMenu->AddItem(new IconMenuItem(new Add()));
		bNeedToAddSeparator = true;
	}
	
	if(bCurDirHasRepo && bHasSelectedFiles && bAllInRepository)
	{
		pMenu->AddItem(new IconMenuItem(new Delete()));
		pMenu->AddItem(new IconMenuItem(new Revert()));	
		bNeedToAddSeparator = true;
	}
	
	// if the user has selected only one file
	if(bCurDirHasRepo && bAllInRepository && (m_lstEntry.size() == 1) )
	{
		pMenu->AddItem(new IconMenuItem(new Rename()));	
		bNeedToAddSeparator = true;
	}
	
	if(bNeedToAddSeparator)
	{
		pMenu->AddSeparatorItem();
		bNeedToAddSeparator = false;
	}

	pMenu->AddItem(new IconMenuItem(new About()));

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

BEntry MoleSvnAddon::GetEntriesEntry(const BDirectory& dir)
{
	BEntry entry;
	entry.Unset();
	
	// Check if dir contains a svn subdirectory
	if(!HasRepository(dir))
		return entry;
		
	// Retrieve the sub directory "svn"
	BEntry SvnEntry;
	if(dir.FindEntry(".svn", &SvnEntry) != B_OK)
	{
		BEntry tmpEntry;
		dir.GetEntry(&tmpEntry);
		char tmp[B_FILE_NAME_LENGTH];
		tmpEntry.GetName(tmp);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Directory %s doesn't contain svn directory", tmp));
		return entry;
	}
	
	BDirectory svnDir(&SvnEntry);
	if(svnDir.InitCheck() != B_OK)
	{
		char tmp[B_FILE_NAME_LENGTH];
		SvnEntry.GetName(tmp);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Invalid svn entry_ref = %s", tmp));
		return entry;
	}
	
	if(svnDir.FindEntry("entries", &entry) != B_OK)
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "No entries file !!"));
		entry.Unset();
		return entry;
	}
	
	return entry;		
}

