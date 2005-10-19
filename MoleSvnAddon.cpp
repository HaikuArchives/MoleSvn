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
#include <algorithm>

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

	// Create the resources manager
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

	// Delete the resources manager
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
	
	// Set the current working directory, which is where the user clicked
	BPath path(&m_CurrentDirectory);
	chdir(path.Path());
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Current directory = %s", path.Path()));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb entries = %i", m_lstEntry.size()));

	hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef>& CurDirEntriesMap = m_mapSvnEntries;
	BDirectory curDir(&m_CurrentDirectory);
	if(HasRepository(curDir))
	{
		// Load repository of the current directory
		LoadEntriesFile(curDir, CurDirEntriesMap);
		
		if(lstEntry.size())
		{
			// We apply a filter with all selected files
			UpdateEntriesFromList(CurDirEntriesMap, lstEntry);
		}
		else
		{
			// No files have been selected, so we apply a filter with the content of the current directory
			list<entry_ref> lstTmpEntry;
			list<BDirectory> lstTmpSubDir;
			GetEntriesList(curDir, lstTmpEntry, lstTmpSubDir);
			UpdateEntriesFromList(CurDirEntriesMap, lstTmpEntry);
		}
	}
	else
	{
		// Here, the current directory doesn't have a repository
		// We create a list of all directories that have been selected
		list<BDirectory> lstSelectedSubdir;
		list<entry_ref>::const_iterator ite = lstEntry.begin();
		while(ite != lstEntry.end())
		{
			BDirectory subdir(&*ite);
			if(subdir.InitCheck() == B_OK)
			{
				lstSelectedSubdir.push_back(subdir);
			}
			++ite;
		}
		
		// For each selected directory, we look if it has repository
		char tmp[B_FILE_NAME_LENGTH];
		list<BDirectory>::const_iterator ite2 = lstSelectedSubdir.begin();
		while(ite2 != lstSelectedSubdir.end())
		{
			// Retrieve entry_ref from the name
			const BDirectory& dirtmp = *ite2;
			BEntry entrytmp;
			entry_ref ertmp;
			dirtmp.GetEntry(&entrytmp);
			entrytmp.GetRef(&ertmp);
			entrytmp.GetName(tmp);
			
			BPath dirPath(&entrytmp);
			//SvnDirEntry* pEntry = new SvnDirEntry(string(tmp));
			SvnDirEntry* pEntry = new SvnDirEntry(dirPath);
			if(HasRepository(*ite2))
			{
				pEntry->SetStatus(SvnEntry::Unmodified);
			}
			else
			{
				pEntry->SetStatus(SvnEntry::NonVersioned);
			}

			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Dir entry added = %s (%s)", tmp, pEntry->GetStatusString().c_str()));
		
			CurDirEntriesMap[ertmp] = pEntry;
			
			++ite2;
		}
	}
}

bool MoleSvnAddon::HasRepository(const BDirectory& dir)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// Retrieve the subdirectory "svn"
	BEntry SvnEntry;
	return (dir.FindEntry(".svn", &SvnEntry) == B_OK);
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

const list<entry_ref>& MoleSvnAddon::GetSelectedEntryList() const
{
	return m_lstEntry;
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

hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>& MoleSvnAddon::GetSvnEntries()
{
	return m_mapSvnEntries;
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
bool AllInRepositoryFunc(entry_ref x)
{
	// Check if the file is in the svn entries
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "AllInRepositoryFunc : look for entry %s", x.name));	
	hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>::const_iterator ite = MoleSvnAddon::GetInstance()->GetSvnEntries().find(x);
	if(ite == MoleSvnAddon::GetInstance()->GetSvnEntries().end())
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "AllInRepositoryFunc : entry %s not found ", x.name));	
		return false;
	}
	
	SvnEntry::Status status = (*ite).second->GetStatus();
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "AllInRepositoryFunc : entry status %s", (*ite).second->GetStatusString().c_str() ));	
	// Check the status of the entry
	return (   (status != SvnEntry::NonVersioned) 
	        && (status != SvnEntry::Added)
	        && (status != SvnEntry::Undefined) );
}

bool AllFilesFunc(entry_ref x)
{
	BDirectory dir(&x);
	return (dir.InitCheck() != B_OK);
}

bool AllDirectoriesFunc(entry_ref x)
{
	BDirectory dir(&x);
	return (dir.InitCheck() == B_OK);
}

BPopUpMenu* MoleSvnAddon::CreateMenu()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	bool bCurDirHasRepo = HasRepository(BDirectory(&m_CurrentDirectory));
	bool bHasSelectedFiles = m_lstEntry.size();
	unsigned int nSelectedFilesCount = m_lstEntry.size();

	unsigned int nSize = 0;
	count_if(m_lstEntry.begin(), m_lstEntry.end(), AllInRepositoryFunc, nSize);
	bool bAllInRepository = (nSize == 0) ? false : (nSize == nSelectedFilesCount);
	
	nSize = 0;
	count_if(m_lstEntry.begin(), m_lstEntry.end(), AllFilesFunc, nSize);
	bool bAllFiles = (nSize == 0) ? false : (nSize == nSelectedFilesCount);

	nSize = 0;
	count_if(m_lstEntry.begin(), m_lstEntry.end(), AllDirectoriesFunc, nSize);
	bool bAllDirectories = (nSize == 0) ? false : (nSize == nSelectedFilesCount);
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "bCurDirHasRepo = %d", bCurDirHasRepo));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "bHasSelectedFiles = %d", bHasSelectedFiles));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "bAllInRepository = %d", bAllInRepository));
	
	// Create the menu
	BPopUpMenu* pMenu = new BPopUpMenu("menu");
	if(!bCurDirHasRepo && (nSelectedFilesCount <= 1) && !bAllInRepository && !bAllFiles )
	{
		pMenu->AddItem(new IconMenuItem(new Checkout()));
		if(nSelectedFilesCount == 1)
		{
			//pMenu->AddItem(new IconMenuItem(new Export()));
			//pMenu->AddItem(new IconMenuItem(new Import()));
		}
		//pMenu->AddItem(new IconMenuItem(new CreateRepositoryHere()));
		pMenu->AddSeparatorItem();
	}
	
	if( bAllInRepository || (bCurDirHasRepo && !bHasSelectedFiles))
	{
		pMenu->AddItem(new IconMenuItem(new Update()));
		pMenu->AddItem(new IconMenuItem(new Commit()));
		pMenu->AddSeparatorItem();
	}

	bool bNeedToAddSeparator = false;
	if( bCurDirHasRepo && bHasSelectedFiles && !bAllInRepository )
	{
		pMenu->AddItem(new IconMenuItem(new Add()));
		//pMenu->AddItem(new IconMenuItem(new AddToIgnoreList()));
		bNeedToAddSeparator = true;
	}
	
	if( bAllInRepository && bHasSelectedFiles )
	{
		pMenu->AddItem(new IconMenuItem(new Delete()));
		pMenu->AddItem(new IconMenuItem(new Revert()));	
		bNeedToAddSeparator = true;
	}
	
	// if the user has selected only one file in a repository
	if(bCurDirHasRepo && bAllInRepository && (nSelectedFilesCount == 1) )
	{
		pMenu->AddItem(new IconMenuItem(new Rename()));	
		bNeedToAddSeparator = true;
	}
	
	if(bNeedToAddSeparator)
	{
		pMenu->AddSeparatorItem();
		bNeedToAddSeparator = false;
	}
	
	if( bHasSelectedFiles && bAllInRepository )
	{
		pMenu->AddItem(new IconMenuItem(new Cleanup()));
		if( bCurDirHasRepo && nSelectedFilesCount == 1 )
			pMenu->AddItem(new IconMenuItem(new Resolved()));	
		pMenu->AddSeparatorItem();
	}
	
	if( bCurDirHasRepo || bAllInRepository )
	{
		pMenu->AddItem(new IconMenuItem(new Status()));
		pMenu->AddSeparatorItem();
	}
	

	//pMenu->AddItem(new IconMenuItem(new Help())); // ???
	//pMenu->AddItem(new IconMenuItem(new Settings()));
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
#if defined(_DEBUG_)	
		BEntry tmpEntry;
		dir.GetEntry(&tmpEntry);
		char tmp[B_FILE_NAME_LENGTH];
		tmpEntry.GetName(tmp);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Directory %s doesn't contain svn directory", tmp));
#endif //_DEBUG_		
		return entry;
	}
	
	BDirectory svnDir(&SvnEntry);
	if(svnDir.InitCheck() != B_OK)
	{
#if defined(_DEBUG_)	
		char tmp[B_FILE_NAME_LENGTH];
		SvnEntry.GetName(tmp);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Invalid svn entry_ref = %s", tmp));
#endif //_DEBUG_		
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

#define RETRIEVE_INFO(str, attribut) \
	string str; \
	const char* p##str = attribut; \
	if(p##str) \
		str.assign(p##str); \

void MoleSvnAddon::LoadEntriesFile(const BDirectory& dir, 
								   hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef> &hashEntriesMap)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// Check if the svn entries file exists
	BEntry entry(GetEntriesEntry(dir));
	if(entry.InitCheck() != B_OK)
		return;

	// Load the XML file	
	BPath path;
	entry.GetPath(&path);
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Loading file = %s", path.Path()));
	TiXmlDocument doc( path.Path() );
	doc.LoadFile();	
	if ( doc.Error() && doc.ErrorId() == TiXmlBase::TIXML_ERROR_OPENING_FILE ) 
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "File not found = %s", path.Path()));
		return;
	}
	else
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "File is valid = %s", path.Path()));

		// Now, we can extract infos
		TiXmlElement* pRoot = doc.RootElement();
		if(!pRoot)
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Bad XML format of the file %s", path.Path()));
			return;
		}
			
		TiXmlElement* pElt = pRoot->FirstChildElement();
		while(pElt)
		{
			// Retrieve common infos
			RETRIEVE_INFO(strName, pElt->Attribute("name"));
			RETRIEVE_INFO(strKind, pElt->Attribute("kind"));

			//TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Element = %s  name=%s ", pElt->Value(), strName.c_str()));
			
			SvnEntry* pEntry = NULL;
			entry_ref ertmp;
			
			// Check the type of the XML element
			if(strKind == string("file"))
			{
				// Retrieve entry_ref from the name
				BEntry entrytmp(&dir, strName.c_str());
				entrytmp.GetRef(&ertmp);
				
				// Retrieve infos about the file
				RETRIEVE_INFO(strCommittedRev, pElt->Attribute("committed-rev"));
				RETRIEVE_INFO(strCommittedDate, pElt->Attribute("committed-date"));
				
				if(strName.size() == 0)
				{
					// it's not a file, these is infos about the current directory
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
				
				
					BPath filePath(&entrytmp);
					//SvnFileEntry* pFileEntry = new SvnFileEntry(strName);
					SvnFileEntry* pFileEntry = new SvnFileEntry(filePath);
					//pFileEntry->SetCommittedRevision(strCommittedRev);
					pFileEntry->SetStatus(SvnEntry::Modified);
					pFileEntry->SetLastAuthor(strLastAuthor);
					pFileEntry->SetSchedule(strSchedule);
					pEntry = pFileEntry;
					TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "File entry added = %s", strName.c_str()));
				}
			}
			else // dir
			{
				if(strName.size())
				{
					// Retrieve entry_ref from the name
					BDirectory dirtmp(&dir, strName.c_str());				
					BEntry entrytmp;
					dirtmp.GetEntry(&entrytmp);
					entrytmp.GetRef(&ertmp);
			
					BPath dirPath(&entrytmp);
					//pEntry = new SvnDirEntry(strName);
					pEntry = new SvnDirEntry(dirPath);
					pEntry->SetStatus(SvnEntry::Unmodified);
					TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Dir entry added = %s", strName.c_str()));
				}
			}
		
			// Add entry to the map
			if(pEntry)
			{
				hashEntriesMap[ertmp] = pEntry;
			}
			
			// Next element
			pElt = pElt->NextSiblingElement();
		}
	}
	
	// Close the file
	// TinyXML ???
}

void MoleSvnAddon::GetEntriesList(const BDirectory& dir, 
								  list<entry_ref>& lstEntry, 
								  list<BDirectory>& lstSubdirectories)
{
	entry_ref direntry;
	BDirectory dirtmp(dir);
	while(dirtmp.GetNextRef(&direntry) != B_ENTRY_NOT_FOUND)
	{
		BEntry entry(&direntry);
		BPath path;
		entry.GetPath(&path);
		
		// Check if it's .svn
		if(strcmp(path.Leaf(), ".svn") != 0)
		{
			lstEntry.push_back(direntry);
			
			// Check if the entry is a directory
			BDirectory subdir(&direntry);
			if(subdir.InitCheck() == B_OK)
			{
				lstSubdirectories.push_back(subdir);
			}
		}
	}
}

void MoleSvnAddon::UpdateEntriesFromList(hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef> &hashEntriesMap,
										 const list<entry_ref>& lstEntry)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	list<entry_ref>::const_iterator ite = lstEntry.begin();
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Size = %d", lstEntry.size()));
	hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef>::const_iterator elt;
	while(ite != lstEntry.end())
	{
		elt = hashEntriesMap.find(*ite);
		SvnEntry* pEntry;
		BDirectory dir(&*ite);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Look = %s", (*ite).name));
		if(elt == hashEntriesMap.end())
		{
			// We must add a new entry, with nonversioned status
			BPath path(&(*ite));
			if(dir.InitCheck() == B_OK)
			{
				pEntry = new SvnDirEntry(path);
			}
			else
			{
				pEntry = new SvnFileEntry(path);
			}
			pEntry->SetStatus(SvnEntry::NonVersioned);
			hashEntriesMap[*ite] = pEntry;
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Add nonversionned element = %s", (*ite).name));
		}
		else
		{
			// We check if the file has been modified since the last commit
			if(dir.InitCheck() != B_OK)
			{
				hashEntriesMap[*ite]->SetStatus(SvnEntry::Modified);
			}
		}
		
		++ite;
	}	
}
/*
void MoleSvnAddon::AddEntry(const entry_ref& ref, SvnEntry* entry, BLooper* looper)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_mapSvnEntries[ref] = entry;

	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Add entry = %s", entry->GetRelativePath().c_str()));
	
	if(looper)
	{
		BMessage msg(ENTRY_ADDED);
		msg.AddPointer("ref", entry);
		looper->PostMessage(&msg);
	}
}
*/


